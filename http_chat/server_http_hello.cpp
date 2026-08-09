#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <iostream>
#include <string>
#include <thread>

using namespace std;

void handleClient(SOCKET clientSocket){
    if(clientSocket == INVALID_SOCKET){
        cout << "accept failed" << endl;
        return;
    }
    char buffer[4096]{};
    
    int len = recv(clientSocket,buffer,sizeof(buffer)-1,0);
    if(len > 0){
        buffer[len] = '\0';
        cout << "browser request:" << endl;
        cout << buffer << endl;
    }

    string body = "<h1>Hello course_manager</h1>";

    string response =
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/html; charset=utf-8\r\n"
    "Content-Length: " + to_string(body.size()) + "\r\n"
    "Connection: close\r\n"
    "\r\n"+
    body;
    send(clientSocket,response.c_str(),response.size(),0);

    closesocket(clientSocket);
}

int main(){
    WSADATA wsa;
    if(WSAStartup(MAKEWORD(2,2), &wsa) != 0){
        cout << "WSASTARTUP FAILED!" << endl;
        return 1;
    }

    SOCKET ser_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(ser_sock == INVALID_SOCKET){
        cout << "SOCKET FAILED" << endl;
        WSACleanup();
        return 1;
    }
    sockaddr_in serAddr{};
    serAddr.sin_family = AF_INET;
    serAddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    serAddr.sin_port = htons(8088);
    if(bind(ser_sock,(sockaddr*)& serAddr,sizeof(serAddr)) == SOCKET_ERROR){
        cout << "bind failed" << endl;
        closesocket(ser_sock);
        WSACleanup();
        return 1;
    }
    if (listen(ser_sock, SOMAXCONN) == SOCKET_ERROR) {
        cout << "listen failed" << endl;
        closesocket(ser_sock);
        WSACleanup();
        return 1;
    }
    cout << "HTTP server running: http://127.0.0.1:8088" << endl;
    while(true){
        SOCKET clientSocket = accept(ser_sock,nullptr,nullptr);
        thread(handleClient,clientSocket).detach();
    }

    closesocket(ser_sock);
    WSACleanup();
    return 0;
}