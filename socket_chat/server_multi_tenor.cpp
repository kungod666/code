#define WIN32_LEAN_AND_MEAN
/*在这一版中，为了处理server.cpp中一次只能处理一个客户端的问题
现对原代码重构，保证能多线程工作处理并发任务

逻辑是:
主线程：一直等新客户端连接
while true:
    clientSocket = accept(serverSocket)
    创建一个线程处理 clientSocket
不让主线程处理是为了防止主线程一旦被recv(...)卡住就无法处理后续客户端

*/
#include <winsock2.h>
#include <iostream>
#include <string>
#include <thread>//开线程所需
using namespace std;
//socket = 操作系统给程序提供的一个网络通信入口
void handleClient(SOCKET clientSocket){
    char buffer[1024];
    int len = recv(clientSocket,buffer,sizeof(buffer)-1,0);
    if(len > 0){
        buffer[len] = '\0';
        cout << "clinet says: " << buffer << endl;
    }
    string reply = "server received,hello client!";
    send(clientSocket,reply.c_str(),reply.size(),0);
    closesocket(clientSocket);
}

int main(){
    WSADATA wsaData;
    //Windows使用socket前必须先初始化网络库
    //wasData用来接收初始化信息
    /*那 wsaData 是干嘛的？
    它不是用来判断成功失败的主依据。
    它是 WSAStartup 成功后，Windows 填进去的一份“网络库信息”。
    类似于mysql与cpp连接的conn*/
    if(WSAStartup(MAKEWORD(2,2),&wsaData) != 0){
        //MAKEWORD(2,2)表示使用Winsock 2.2版本
        //返回值不是0表示Windows网络库初始化失败
        cout << "WASStartup failed" << endl;
        return 1;
    }
    SOCKET ser_sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    //创建一个 IPv4 + TCP 的 socket
    /*但此时只是一个空的通信对象，它还不知道要连
    哪个ip，这个ip下的哪个端口，所以需要一个服务器地址结构体解决*/
    if(ser_sock == INVALID_SOCKET){
        cout << "socket failed" << endl;
        WSACleanup();//清除库配置
        return 1;
    }
    sockaddr_in serAddr{};
    /*定义服务器地址结构体。用来描述
    服务器监听哪个 IP
    服务器监听哪个端口*/
    serAddr.sin_family = AF_INET;//ipv4
    serAddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    //sin_addr是serAddr结构体中的结构体,专门存ipv4

    /*INADDR_LOOPBACK表示127.0.0.1即本地ip
    htonl:把数据转为网络字节符
    ip给服务器地址时需要htonl*/
    serAddr.sin_port = htons(9000);
    //htons用于端口转换
    if(bind(ser_sock,(sockaddr*)&serAddr,sizeof(serAddr)) == SOCKET_ERROR){//信息绑定

        //很多 socket 函数失败时都会返回 SOCKET_ERROR
        //但socket(...)失败返回INVALID_SOCKET


        cout << "bind failed" << endl;
        closesocket(ser_sock);
        WSACleanup();
        return 1;
    }
    if (listen(ser_sock, SOMAXCONN) == SOCKET_ERROR) {
        //开始监听客户端
        //SOMAXCONN可以理解成允许多个客户端排队等待连接
        cout << "listen failed" << endl;
        closesocket(ser_sock);
        WSACleanup();
        return 1;
    }
    cout << "server is listening on 127.0.0.1:9000" << endl;
    while(true){
        SOCKET clientSocket = accept(ser_sock, nullptr, nullptr);
        /*accept三个参数分别是:
        第一个：服务器监听 socket
        第二个：用来保存客户端 IP/端口的地址结构体
        第三个：这个地址结构体的长度
        关于第三个参数:你传入的是 clientAddr 这个地址容器的大小；accept 改写的是“实际写入客户端地址信息的长度”。

        如果想要记录客户端的ip及端口，可以这么写:
        socketaddr_in clientAddr{};
        int clientAddrlen = sizeof(clientAddr);
        
        SOCKET clientSocket = accept(
            ser_sock,
            (sockaddr*)&clientAddr,
            &clientAddrLen
        );*/
        if (clientSocket == INVALID_SOCKET) {
            cout << "accept failed" << endl;
            closesocket(clientSocket);
            continue;
        }
        thread(handleClient,clientSocket).detach();
        //thread 表示新开线程,参数为函数名+函数参数,detach表示与主线程断开关系
        //避免主机因等待thread线程而卡住情况
    }
    return 0;
}