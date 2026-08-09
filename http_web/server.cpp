#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

/*Http协议规定服务端回复给浏览器的报文要以CRLF结尾(\r\n)*/
string getParam(const string& data, const string& key) {
    string target = key + "=";
    size_t pos = data.find(target);

    if (pos == string::npos) return "";

    pos += target.size();

    size_t end = data.find("&", pos);
    if (end == string::npos) {
        return data.substr(pos);
    }

    return data.substr(pos, end - pos);
}

void sendResponse(SOCKET clientSocket, const string& contentType, const string& body) {
    string response =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: " + contentType + "; charset=utf-8\r\n"
        "Content-Length: " + to_string(body.size()) + "\r\n"
        "Connection: close\r\n"
        "\r\n" +
        body;
        //http协议规定body与固定格式之间要有CRLF

    send(clientSocket, response.c_str(), response.size(), 0);
}

void send404(SOCKET clientSocket) {
    string body = "404 Not Found";

    string response =
        "HTTP/1.1 404 Not Found\r\n"
        "Content-Type: text/plain; charset=utf-8\r\n"
        "Content-Length: " + to_string(body.size()) + "\r\n"
        "Connection: close\r\n"
        //因为当前关于这个clientSocket的设计是
        /*recv一次后send一次后closesocket()
        因此必须connection:close让浏览器不要重复使用socket*/

        //后期可以学习keep-alive
        "\r\n" +
        body;

    send(clientSocket, response.c_str(), response.size(), 0);
}

string homePage() {
    //R"()"表示cpp的原始字符串，在这个括号里的字符串可以不经过转码直接写
    //比如引号就不用\"而"即可
    return R"(
<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <title>course_manager mini</title>
</head>
<body>
    <h1>course_manager mini</h1>

    <div>
        <input id="username" placeholder="username">
        <input id="password" placeholder="password">
        <button id="loginBtn">login</button>
    </div>

    <hr>

    <button id="loadTasksBtn">load tasks</button>

    <ul id="taskList"></ul>

    <script>
        let currentUserId = null;

        document.getElementById("loginBtn").onclick = async function () {
            let username = document.getElementById("username").value;
            let password = document.getElementById("password").value;
            
            let response = await fetch("/api/login", {
                method: "POST",
                headers: {
                    "Content-Type": "application/x-www-form-urlencoded"
                },
                body: "username=" + username + "&password=" + password
            });

            let result = await response.json();

            if (result.ok) {
                currentUserId = result.user_id;
                alert("login success, user_id = " + currentUserId);
            } else {
                alert("login failed");
            }
        };

        document.getElementById("loadTasksBtn").onclick = async function () {
            if (currentUserId === null) {
                alert("please login first");
                return;
            }

            let response = await fetch("/api/tasks?user_id=" + currentUserId);
            let tasks = await response.json();

            let taskList = document.getElementById("taskList");
            taskList.innerHTML = "";

            for (let task of tasks) {
                let li = document.createElement("li");
                li.textContent = task.title;
                taskList.appendChild(li);
            }
        };
    </script>
</body>
</html>
)";
}

void handleClient(SOCKET clientSocket) {
    char buffer[4096]{};

    int len = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);

    if (len <= 0) {
        closesocket(clientSocket);
        return;
    }

    buffer[len] = '\0';

    string request = buffer;

    cout << "browser request:" << endl;
    cout << request << endl;

    istringstream iss(request);

    string method;
    string rawPath;
    string version;

    iss >> method >> rawPath >> version;

    string path = rawPath;
    string query = "";

    size_t questionPos = rawPath.find("?");

    //表示浏览器所发有对某样数据的请求
    if (questionPos != string::npos) {
        path = rawPath.substr(0, questionPos);
        query = rawPath.substr(questionPos + 1);
    }

    size_t bodyPos = request.find("\r\n\r\n");
    string body = "";

    if (bodyPos != string::npos) {
        body = request.substr(bodyPos + 4);
    }

    if (method == "GET" && path == "/") {
        sendResponse(clientSocket, "text/html", homePage());
    }
    else if (method == "POST" && path == "/api/login") {
        string username = getParam(body, "username");
        string password = getParam(body, "password");

        if (username == "alice" && password == "123") {
            sendResponse(clientSocket, "application/json", R"({"ok":true,"user_id":1})");
        }
        else if (username == "bob" && password == "456") {
            sendResponse(clientSocket, "application/json", R"({"ok":true,"user_id":2})");
        }
        else {
            sendResponse(clientSocket, "application/json", R"({"ok":false})");
        }
    }
    else if (method == "GET" && path == "/api/tasks") {
        string userId = getParam(query, "user_id");

        if (userId == "1") {
            sendResponse(clientSocket, "application/json",
                R"([{"id":1,"title":"alice task 1"},{"id":2,"title":"alice task 2"}])");
        }
        else if (userId == "2") {
            sendResponse(clientSocket, "application/json",
                R"([{"id":3,"title":"bob task 1"},{"id":4,"title":"bob task 2"}])");
        }
        else {
            sendResponse(clientSocket, "application/json", R"([])");
        }
    }
    else {
        send404(clientSocket);
    }

    closesocket(clientSocket);
}

int main() {
    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cout << "WSAStartup failed" << endl;
        return 1;
    }

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (serverSocket == INVALID_SOCKET) {
        cout << "socket failed" << endl;
        WSACleanup();
        return 1;
    }

    sockaddr_in serverAddr{};

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    serverAddr.sin_port = htons(8088);

    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        cout << "bind failed" << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        cout << "listen failed" << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    cout << "server running: http://127.0.0.1:8088/" << endl;

    while (true) {
        SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);

        if (clientSocket == INVALID_SOCKET) {
            cout << "accept failed" << endl;
            continue;
        }

        handleClient(clientSocket);
    }

    closesocket(serverSocket);
    WSACleanup();

    return 0;
}