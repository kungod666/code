#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <mysql.h>
#include <sodium.h>

#include <cctype>
#include <cstring>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

const int SERVER_PORT = 8088;

struct HttpRequest {
    string method;
    string rawPath;
    string path;
    string query;
    string version;
    map<string, string> headers;
    string body;
};

struct HttpResponse {
    int status = 200;
    string statusText = "OK";
    string contentType = "text/plain";
    string body;
};

struct DbConfig {
    const char* host = "localhost";
    const char* user = "root";
    const char* password = "Pkunz20060915";
    const char* database = "course_manager";
    unsigned int port = 3306;
};

string hashPassword(const string& password) {
    char hash[crypto_pwhash_STRBYTES];

    if (crypto_pwhash_str_alg(
            hash,
            password.c_str(),
            password.size(),
            crypto_pwhash_OPSLIMIT_INTERACTIVE,
            crypto_pwhash_MEMLIMIT_INTERACTIVE,
            crypto_pwhash_ALG_ARGON2ID13) != 0) {
        throw runtime_error("password hash failed");
    }

    return string(hash);
}

bool verifyPassword(const string& password, const string& passwordHash) {
    return crypto_pwhash_str_verify(
               passwordHash.c_str(),
               password.c_str(),
               password.size()) == 0;
}

MYSQL* openDb() {
    static DbConfig config;

    MYSQL* conn = mysql_init(nullptr);
    if (!conn) {
        return nullptr;
    }

    MYSQL* ok = mysql_real_connect(
        conn,
        config.host,
        config.user,
        config.password,
        config.database,
        config.port,
        nullptr,
        0);

    if (!ok) {
        mysql_close(conn);
        return nullptr;
    }

    mysql_set_character_set(conn, "utf8mb4");
    return conn;
}

string sqlEscape(MYSQL* conn, const string& value) {
    //escape:转义
    string escaped;
    escaped.resize(value.size() * 2 + 1);

    unsigned long len = mysql_real_escape_string(
        //mysql_real_escape_string()是MYSQL  C API里的函数，用来把用户输入安全拼尽sql语句
        /*防止两个问题
        1. 用户输入里有单引号，导致 SQL 语法坏掉
        2. SQL 注入*/
        conn,
        &escaped[0],
        value.c_str(),
        static_cast<unsigned long>(value.size()));

    escaped.resize(len);
    return escaped;
}

string jsonEscape(const string& value) {
    string out;

    for (char ch : value) {
        switch (ch) {
            case '\\':
                out += "\\\\";
                break;
            case '"':
                out += "\\\"";
                break;
            case '\n':
                out += "\\n";
                break;
            case '\r':
                out += "\\r";
                break;
            case '\t':
                out += "\\t";
                break;
            default:
                out += ch;
                break;
        }
    }

    return out;
}

string urlDecode(const string& value) {
    string out;

    for (size_t i = 0; i < value.size(); i++) {
        if (value[i] == '+') {
            out += ' ';
        } else if (value[i] == '%' && i + 2 < value.size()) {
            string hex = value.substr(i + 1, 2);
            char decoded = static_cast<char>(strtol(hex.c_str(), nullptr, 16));
            out += decoded;
            i += 2;
        } else {
            out += value[i];
        }
    }

    return out;
}

map<string, string> parseParams(const string& text) {
    map<string, string> params;
    size_t start = 0;

    while (start <= text.size()) {
        size_t amp = text.find('&', start);
        string part = amp == string::npos ? text.substr(start) : text.substr(start, amp - start);

        if (!part.empty()) {
            size_t eq = part.find('=');
            string key = eq == string::npos ? part : part.substr(0, eq);
            string value = eq == string::npos ? "" : part.substr(eq + 1);
            params[urlDecode(key)] = urlDecode(value);
        }

        if (amp == string::npos) {
            break;
        }

        start = amp + 1;
    }

    return params;
}

bool isIntegerText(const string& text) {
    if (text.empty()) {
        return false;
    }

    for (char ch : text) {
        if (!isdigit(static_cast<unsigned char>(ch))) {
            return false;
        }
    }

    return true;
}

string paramOrEmpty(const map<string, string>& params, const string& key) {
    auto it = params.find(key);
    return it == params.end() ? "" : it->second;
}

HttpResponse jsonResponse(const string& body) {
    return {200, "OK", "application/json", body};
}

HttpResponse textResponse(int status, const string& statusText, const string& body) {
    return {status, statusText, "text/plain", body};
}

HttpResponse badRequest(const string& message) {
    return textResponse(400, "Bad Request", message);
}

HttpResponse serverError(const string& message) {
    return textResponse(500, "Internal Server Error", message);
}

string homePage() {
    return R"HTML(<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <title>course_manager web learning</title>
    <style>
        body {
            font-family: Arial, "Microsoft YaHei", sans-serif;
            margin: 24px;
            color: #222;
        }

        input, button, select {
            padding: 6px 8px;
            margin: 4px;
        }

        table {
            border-collapse: collapse;
            width: 100%;
            margin-top: 12px;
        }

        th, td {
            border: 1px solid #ccc;
            padding: 8px;
            text-align: left;
        }

        .hidden {
            display: none;
        }

        .bar {
            margin: 12px 0;
        }

        .danger {
            color: #a40000;
        }
    </style>
</head>
<body>
    <h1>course_manager web learning</h1>

    <section id="loginPanel">
        <h2>login or register</h2>
        <input id="username" placeholder="username">
        <input id="password" placeholder="password" type="password">
        <button id="loginBtn">login</button>
        <p id="loginMsg"></p>
    </section>

    <section id="appPanel" class="hidden">
        <div class="bar">
            current user_id: <span id="currentUserText"></span>
            <button id="logoutBtn">logout</button>
        </div>

        <h2>settings</h2>
        <label>
            <input id="selfUpdate" type="checkbox">
            self update
        </label>
        <input id="redlineDays" type="number" min="1" max="100" placeholder="redline days">
        <button id="saveSettingsBtn">save settings</button>
        <span id="settingsMsg"></span>

        <h2>add task</h2>
        <input id="course" placeholder="course">
        <input id="title" placeholder="title">
        <input id="dueDate" type="date">
        <button id="addTaskBtn">add task</button>

        <h2>tasks</h2>
        <button id="loadTasksBtn">load tasks</button>
        <p id="taskMsg"></p>

        <table>
            <thead>
                <tr>
                    <th>id</th>
                    <th>course</th>
                    <th>title</th>
                    <th>due date</th>
                    <th>done</th>
                    <th>actions</th>
                </tr>
            </thead>
            <tbody id="taskBody"></tbody>
        </table>
    </section>

    <script>
        let currentUserId = null;

        function formBody(data) {
            let parts = [];

            for (let key in data) {
                parts.push(
                    encodeURIComponent(key) + "=" + encodeURIComponent(data[key])
                );
            }

            return parts.join("&");
        }

        async function postForm(path, data) {
            let response = await fetch(path, {
                method: "POST",
                headers: {
                    "Content-Type": "application/x-www-form-urlencoded"
                },
                body: formBody(data)
            });

            return await response.json();
        }

        function requireLogin() {
            if (currentUserId === null) {
                alert("please login first");
                return false;
            }

            return true;
        }

        async function loadSettings() {
            let response = await fetch("/api/settings?user_id=" + currentUserId);
            let settings = await response.json();

            document.getElementById("selfUpdate").checked = settings.self_update === 1;
            document.getElementById("redlineDays").value = settings.redline_days;
        }

        async function loadTasks() {
            if (!requireLogin()) {
                return;
            }

            let response = await fetch("/api/tasks?user_id=" + currentUserId);
            let tasks = await response.json();
            let taskBody = document.getElementById("taskBody");

            taskBody.innerHTML = "";

            for (let task of tasks) {
                let tr = document.createElement("tr");

                let doneText = task.done === 1 ? "done" : "not done";

                tr.innerHTML =
                    "<td>" + task.id + "</td>" +
                    "<td>" + task.course + "</td>" +
                    "<td>" + task.title + "</td>" +
                    "<td>" + task.due_date + "</td>" +
                    "<td>" + doneText + "</td>" +
                    "<td>" +
                        "<button data-action='done' data-id='" + task.id + "'>done</button>" +
                        "<button data-action='delete' data-id='" + task.id + "'>delete</button>" +
                    "</td>";

                taskBody.appendChild(tr);
            }

            document.getElementById("taskMsg").textContent = "loaded " + tasks.length + " task(s)";
        }

        document.getElementById("loginBtn").onclick = async function () {
            let username = document.getElementById("username").value;
            let password = document.getElementById("password").value;

            let result = await postForm("/api/login", {
                username: username,
                password: password
            });

            if (result.ok) {
                currentUserId = result.user_id;
                document.getElementById("loginPanel").classList.add("hidden");
                document.getElementById("appPanel").classList.remove("hidden");
                document.getElementById("currentUserText").textContent = currentUserId;
                document.getElementById("loginMsg").textContent = "";
                await loadSettings();
                await loadTasks();
            } else {
                document.getElementById("loginMsg").textContent = result.message;
            }
        };

        document.getElementById("logoutBtn").onclick = function () {
            currentUserId = null;
            document.getElementById("appPanel").classList.add("hidden");
            document.getElementById("loginPanel").classList.remove("hidden");
        };

        document.getElementById("saveSettingsBtn").onclick = async function () {
            if (!requireLogin()) {
                return;
            }

            let result = await postForm("/api/settings", {
                user_id: currentUserId,
                self_update: document.getElementById("selfUpdate").checked ? 1 : 0,
                redline_days: document.getElementById("redlineDays").value
            });

            document.getElementById("settingsMsg").textContent = result.ok ? "saved" : result.message;
        };

        document.getElementById("addTaskBtn").onclick = async function () {
            if (!requireLogin()) {
                return;
            }

            let result = await postForm("/api/tasks", {
                user_id: currentUserId,
                course: document.getElementById("course").value,
                title: document.getElementById("title").value,
                due_date: document.getElementById("dueDate").value
            });

            if (result.ok) {
                document.getElementById("course").value = "";
                document.getElementById("title").value = "";
                document.getElementById("dueDate").value = "";
                await loadTasks();
            } else {
                document.getElementById("taskMsg").textContent = result.message;
            }
        };

        document.getElementById("loadTasksBtn").onclick = loadTasks;

        document.getElementById("taskBody").onclick = async function (event) {
            let button = event.target;

            if (button.tagName !== "BUTTON") {
                return;
            }

            let action = button.getAttribute("data-action");
            let taskId = button.getAttribute("data-id");

            if (action === "done") {
                await postForm("/api/tasks/done", {
                    user_id: currentUserId,
                    id: taskId
                });
                await loadTasks();
            }

            if (action === "delete") {
                await postForm("/api/tasks/delete", {
                    user_id: currentUserId,
                    id: taskId
                });
                await loadTasks();
            }
        };
    </script>
</body>
</html>)HTML";
}

//对request的字符串处理
/*http格式:
请求行
请求头1
请求头2
请求头3
空行(\r\n\r\n)
请求体(body)*/
HttpRequest parseRequest(const string& raw) {
    HttpRequest req;

    size_t headerEnd = raw.find("\r\n\r\n");
    string headerText = headerEnd == string::npos ? raw : raw.substr(0, headerEnd);
    req.body = headerEnd == string::npos ? "" : raw.substr(headerEnd + 4);

    istringstream stream(headerText);
    //把 headerText 这个字符串包装成一个“可以像 cin 一样读取的流”。
    string line;

    if (getline(stream, line)) {
        //getline()遇到\n停止，但不会去掉最后的\r
        if (!line.empty() && line.back() == '\r') {
            line.pop_back(); //去掉尾部\r
        }

        istringstream firstLine(line);
        firstLine >> req.method >> req.rawPath >> req.version;
    }

    while (getline(stream, line)) {
        //stream每次在getline时像一个读取指针，不会每次从头读
        //而是从上一次读完的位置继续往后读。
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        size_t colon = line.find(':');
        // 停在字符串数组的下标位置
        if (colon != string::npos) {//只有存在：时才进入if分支，避免对body的重复读取
            string key = line.substr(0, colon);
            string value = line.substr(colon + 1);

            while (!value.empty() && value.front() == ' ') {
                value.erase(value.begin());
            }

            req.headers[key] = value;
            //map<string,string> headers
        }
    }

    req.path = req.rawPath;
    size_t question = req.rawPath.find('?');

    if (question != string::npos) {
        req.path = req.rawPath.substr(0, question);
        req.query = req.rawPath.substr(question + 1);
    }

    return req;
}

//从 HTTP 请求头里找 Content-Length，并返回 body 的长度。
int contentLengthFromHeaders(const string& rawHeaders) {
    istringstream stream(rawHeaders);
    string line;

    while (getline(stream, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        string lower = line;
        for (char& ch : lower) {
            ch = static_cast<char>(tolower(static_cast<unsigned char>(ch)));
        }

        if (lower.rfind("content-length:", 0) == 0) {
            //rfind:从位置 0 开始匹配 content-length;如果匹配成功，返回 0(0不是下标)
            //用rfind而不用find在于更保险(有可能body部分有content-length)
            string value = line.substr(strlen("Content-Length:"));
            return atoi(value.c_str());
        }
    }

    return 0;
}

//便于准确处理http请求
/*底层原因:TCP!
信息的传递按照TCP协议

TCP真实模型:
两端之间有一条可靠的字节管道
你往里面塞字节
对方按顺序拿字节

---->TCP不保证消息边界!
---->一次recv不一定能正确处理收到的信息
(TCP是水管，你用杯子接水，它不保证你一次接完一杯水)

而http就是水流里规定:
看到 \r\n\r\n，说明请求头结束
再根据 Content-Length 继续读 body*/


//因此，此函数即字符串算法，抱歉正确接完所有请求
bool recvHttpRequest(SOCKET clientSocket, string& raw) {
    char buffer[4096];
    raw.clear();

    while (raw.find("\r\n\r\n") == string::npos) {//只要请求头没接收完
        int len = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (len <= 0) {
            return false;
        }

        raw.append(buffer, len);
        //append():把一段内容追加到字符串末尾

        if (raw.size() > 1024 * 1024) {
            return false;
        }
    }

    size_t headerEnd = raw.find("\r\n\r\n");
    int bodyNeed = contentLengthFromHeaders(raw.substr(0, headerEnd + 4));
    size_t totalNeed = headerEnd + 4 + bodyNeed;

    while (raw.size() < totalNeed) {//没到content-length就一直recv
        int len = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (len <= 0) {
            return false;
        }

        raw.append(buffer, len);
    }

    return true;
}

/*response格式：
状态行
响应头
空行
响应体
标准形式:

HTTP/version status_code status_text
Header-Name: Header-Value
Header-Name: Header-Value

body*/
string buildHttpResponse(const HttpResponse& res) {
    string response =
        "HTTP/1.1 " + to_string(res.status) + " " + res.statusText + "\r\n"
        "Content-Type: " + res.contentType + "; charset=utf-8\r\n"
        "Content-Length: " + to_string(res.body.size()) + "\r\n"
        "Connection: close\r\n"
        "\r\n" +
        res.body;

    return response;
}

HttpResponse handleLogin(MYSQL* conn, const HttpRequest& req) {
    map<string, string> form = parseParams(req.body);
    string username = paramOrEmpty(form, "username");
    string password = paramOrEmpty(form, "password");

    if (username.empty() || password.empty()) {
        return jsonResponse(R"({"ok":false,"message":"username and password required"})");
    }

    string safeName = sqlEscape(conn, username);
    string sql = "select id, password_hash from users where user_name = '" + safeName + "'";

    if (mysql_query(conn, sql.c_str())) {
        return serverError(mysql_error(conn));
    }

    MYSQL_RES* result = mysql_store_result(conn);
    if (!result) {
        return serverError(mysql_error(conn));
    }

    MYSQL_ROW row = mysql_fetch_row(result);

    if (!row) {
        mysql_free_result(result);

        string passwordHash;
        try {
            passwordHash = hashPassword(password);
        } catch (const exception& ex) {
            return serverError(ex.what());
        }

        string safeHash = sqlEscape(conn, passwordHash);
        string insertSql =
            "insert into users(user_name, password_hash) values('" + safeName + "', '" + safeHash + "')";

        if (mysql_query(conn, insertSql.c_str())) {
            return serverError(mysql_error(conn));
        }

        int userId = static_cast<int>(mysql_insert_id(conn));

        string settingSql =
            "insert into setting(self_update, redline_days, user_id) values(0, 5, " + to_string(userId) + ")";
        mysql_query(conn, settingSql.c_str());

        return jsonResponse("{\"ok\":true,\"created\":true,\"user_id\":" + to_string(userId) + "}");
    }

    int userId = atoi(row[0]);
    string passwordHash = row[1] ? row[1] : "";
    mysql_free_result(result);

    if (!verifyPassword(password, passwordHash)) {
        return jsonResponse(R"({"ok":false,"message":"wrong password"})");
    }

    return jsonResponse("{\"ok\":true,\"created\":false,\"user_id\":" + to_string(userId) + "}");
}

HttpResponse handleGetSettings(MYSQL* conn, const HttpRequest& req) {
    map<string, string> query = parseParams(req.query);
    string userId = paramOrEmpty(query, "user_id");

    if (!isIntegerText(userId)) {
        return badRequest("invalid user_id");
    }

    string sql = "select self_update, redline_days from setting where user_id = " + userId;

    if (mysql_query(conn, sql.c_str())) {
        return serverError(mysql_error(conn));
    }

    MYSQL_RES* result = mysql_store_result(conn);
    if (!result) {
        return serverError(mysql_error(conn));
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    string body;

    if (row) {
        body = string("{\"self_update\":") + (row[0] ? row[0] : "0") +
               ",\"redline_days\":" + (row[1] ? row[1] : "5") + "}";
    } else {
        body = R"({"self_update":0,"redline_days":5})";
    }

    mysql_free_result(result);
    return jsonResponse(body);
}

HttpResponse handleSaveSettings(MYSQL* conn, const HttpRequest& req) {
    map<string, string> form = parseParams(req.body);
    string userId = paramOrEmpty(form, "user_id");
    string selfUpdate = paramOrEmpty(form, "self_update");
    string redlineDays = paramOrEmpty(form, "redline_days");

    if (!isIntegerText(userId) || !isIntegerText(redlineDays)) {
        return badRequest("invalid setting data");
    }

    int redline = atoi(redlineDays.c_str());
    if (redline < 1 || redline > 100) {
        return jsonResponse(R"({"ok":false,"message":"redline_days must be 1-100"})");
    }

    string flag = selfUpdate == "1" ? "1" : "0";
    string sql =
        "insert into setting(self_update, redline_days, user_id) values(" + flag + ", " + to_string(redline) + ", " + userId + ") "
        "on duplicate key update self_update = values(self_update), redline_days = values(redline_days)";

    if (mysql_query(conn, sql.c_str())) {
        return serverError(mysql_error(conn));
    }

    return jsonResponse(R"({"ok":true})");
}

HttpResponse handleGetTasks(MYSQL* conn, const HttpRequest& req) {
    map<string, string> query = parseParams(req.query);
    string userId = paramOrEmpty(query, "user_id");

    if (!isIntegerText(userId)) {
        return badRequest("invalid user_id");
    }

    string sql =
        "select id, course, title, due_date, done, user_id "
        "from tasks where user_id = " + userId + " order by due_date";

    if (mysql_query(conn, sql.c_str())) {
        return serverError(mysql_error(conn));
    }

    MYSQL_RES* result = mysql_store_result(conn);
    if (!result) {
        return serverError(mysql_error(conn));
    }

    string json = "[";
    bool first = true;
    MYSQL_ROW row;

    while ((row = mysql_fetch_row(result))) {
        if (!first) {
            json += ",";
        }

        first = false;
        json += "{";
        json += "\"id\":" + string(row[0] ? row[0] : "0") + ",";
        json += "\"course\":\"" + jsonEscape(row[1] ? row[1] : "") + "\",";
        json += "\"title\":\"" + jsonEscape(row[2] ? row[2] : "") + "\",";
        json += "\"due_date\":\"" + jsonEscape(row[3] ? row[3] : "") + "\",";
        json += "\"done\":" + string(row[4] ? row[4] : "0") + ",";
        json += "\"user_id\":" + string(row[5] ? row[5] : "0");
        json += "}";
    }

    json += "]";

    mysql_free_result(result);
    return jsonResponse(json);
}

HttpResponse handleAddTask(MYSQL* conn, const HttpRequest& req) {
    map<string, string> form = parseParams(req.body);
    string userId = paramOrEmpty(form, "user_id");
    string course = paramOrEmpty(form, "course");
    string title = paramOrEmpty(form, "title");
    string dueDate = paramOrEmpty(form, "due_date");

    if (!isIntegerText(userId)) {
        return badRequest("invalid user_id");
    }

    if (course.empty() || title.empty() || dueDate.empty()) {
        return jsonResponse(R"({"ok":false,"message":"course, title and due_date required"})");
    }

    string sql =
        "insert into tasks(course, title, due_date, user_id) values('" +
        sqlEscape(conn, course) + "', '" +
        sqlEscape(conn, title) + "', '" +
        sqlEscape(conn, dueDate) + "', " +
        userId + ")";

    if (mysql_query(conn, sql.c_str())) {
        return serverError(mysql_error(conn));
    }

    return jsonResponse("{\"ok\":true,\"id\":" + to_string(static_cast<int>(mysql_insert_id(conn))) + "}");
}

HttpResponse handleDeleteTask(MYSQL* conn, const HttpRequest& req) {
    map<string, string> form = parseParams(req.body);
    string userId = paramOrEmpty(form, "user_id");
    string id = paramOrEmpty(form, "id");

    if (!isIntegerText(userId) || !isIntegerText(id)) {
        return badRequest("invalid delete data");
    }

    string sql = "delete from tasks where id = " + id + " and user_id = " + userId;

    if (mysql_query(conn, sql.c_str())) {
        return serverError(mysql_error(conn));
    }

    return jsonResponse("{\"ok\":true,\"affected\":" + to_string(static_cast<long long>(mysql_affected_rows(conn))) + "}");
}

HttpResponse handleDoneTask(MYSQL* conn, const HttpRequest& req) {
    map<string, string> form = parseParams(req.body);
    string userId = paramOrEmpty(form, "user_id");
    string id = paramOrEmpty(form, "id");

    if (!isIntegerText(userId) || !isIntegerText(id)) {
        return badRequest("invalid done data");
    }

    string sql = "update tasks set done = 1 where id = " + id + " and user_id = " + userId;

    if (mysql_query(conn, sql.c_str())) {
        return serverError(mysql_error(conn));
    }

    return jsonResponse("{\"ok\":true,\"affected\":" + to_string(static_cast<long long>(mysql_affected_rows(conn))) + "}");
}

HttpResponse routeRequest(const HttpRequest& req) {
    if (req.method == "GET" && req.path == "/") {
        return {200, "OK", "text/html", homePage()};
    }

    MYSQL* conn = openDb();
    if (!conn) {
        return serverError("database connection failed");
    }

    HttpResponse response;

    if (req.method == "POST" && req.path == "/api/login") {
        response = handleLogin(conn, req);
    } else if (req.method == "GET" && req.path == "/api/settings") {
        response = handleGetSettings(conn, req);
    } else if (req.method == "POST" && req.path == "/api/settings") {
        response = handleSaveSettings(conn, req);
    } else if (req.method == "GET" && req.path == "/api/tasks") {
        response = handleGetTasks(conn, req);
    } else if (req.method == "POST" && req.path == "/api/tasks") {
        response = handleAddTask(conn, req);
    } else if (req.method == "POST" && req.path == "/api/tasks/delete") {
        response = handleDeleteTask(conn, req);
    } else if (req.method == "POST" && req.path == "/api/tasks/done") {
        response = handleDoneTask(conn, req);
    } else {
        response = textResponse(404, "Not Found", "404 Not Found");
    }

    mysql_close(conn);
    return response;
}

void handleClient(SOCKET clientSocket) {
    string rawRequest;

    if (!recvHttpRequest(clientSocket, rawRequest)) {
        closesocket(clientSocket);
        return;
    }

    HttpRequest req = parseRequest(rawRequest);

    cout << req.method << " " << req.rawPath << endl;

    HttpResponse response = routeRequest(req);
    string rawResponse = buildHttpResponse(response);

    send(clientSocket, rawResponse.c_str(), static_cast<int>(rawResponse.size()), 0);
    closesocket(clientSocket);
}

int main() {
    if (sodium_init() < 0) {
        cout << "libsodium init failed" << endl;
        return 1;
    }

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
    serverAddr.sin_port = htons(SERVER_PORT);

    if (bind(serverSocket, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR) {
        cout << "bind failed, port may be in use" << endl;
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

    cout << "course_manager web learning server running:" << endl;
    cout << "http://127.0.0.1:" << SERVER_PORT << "/" << endl;

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
