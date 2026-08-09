#define WIN32_LEN_AND_MEAN
#include <winsock2.h>
#include <iostream>
#include <thread>
using namespace std;
void handleClient(SOCKET clientSocket){
    char buffer[1024]{};
    int len = recv(clientSocket,buffer,sizeof(buffer)-1,0);
    if(len > 0){//len:读取行数
        buffer[len] = '\0';
        cout << "client says: " << buffer << endl;
    }
    string m = "server received!Hello client!";
    send(clientSocket,m.c_str(),sizeof(m),0);
    closesocket(clientSocket);
}
int main(){
    WSADATA was;
    if(WSAStartup(WORD(2.2), &was) != 0){
        cout << "WSASTARTUP FAILED!" << endl;
        WSACleanup();
        return 1;
    }
    SOCKET ser_sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(ser_sock == INVALID_SOCKET){
        cout << "START SOCKET FAILED!" << endl;
        closesocket(ser_sock);
        WSACleanup();
        return 1;
    }
    sockaddr_in ser_add{};
    ser_add.sin_family = AF_INET;
    ser_add.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    ser_add.sin_port = htons(9000);
    if(bind(ser_sock,(sockaddr*)&ser_add,sizeof(ser_add)) == SOCKET_ERROR){
        cout << "SOCKET BIND FAILED" << endl;
        closesocket(ser_sock);
        WSACleanup();
        return 1;
    }
    if(listen(ser_sock,SOMAXCONN) == SOCKET_ERROR){
        cout << "LISTEN FAILED" << endl;
        closesocket(ser_sock);
        WSACleanup();
        return 1;
    }
    while(true){
        SOCKET clientSocket = accept(ser_sock,nullptr,nullptr);
        thread(handleClient,clientSocket).detach();
    }
    closesocket(ser_sock);
    WSACleanup();
    return 0;
}