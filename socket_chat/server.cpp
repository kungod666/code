#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <iostream>
#include <string>
using namespace std;
//socket = 操作系统给程序提供的一个网络通信入口
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
    /*INADDR_LOOPBACK表示127.0.0.1即本地ip
    htonl:把数据转为网络字节符
    ip给服务器地址时需要htonl*/
    serAddr.sin_port = htons(9000);
    //htons用于端口转换
    if(bind(ser_sock,(sockaddr*)&serAddr,sizeof(serAddr)) == SOCKET_ERROR){//信息绑定
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
    SOCKET clientSocket = accept(ser_sock, nullptr, nullptr);
    //accept() 是在 客户端执行 connect() 连接服务器时 被触发，不是等客户端 send() 消息后才触发。
    /*关于accept:
    其为阻塞函数，即如果没有客户端的到来它会一直等*/
    /*为什么要新创一个socket接口？
    答：防止server_socket被占用导致后继客户端不能等到它的"监听服务员(并发性任务处理)""*/
    if (clientSocket == INVALID_SOCKET) {
        cout << "accept failed" << endl;
        closesocket(ser_sock);
        WSACleanup();
        return 1;
    }
    char buffer[1024]{};
    int len = recv(clientSocket,buffer,sizeof(buffer)-1,0);
    /*flags表示发送/接收的行为，0为默认行为，入门阶段不用管*/
    
    //-1是为了再存一个"\n",把clientSocket的信息导入buffer
    if(len > 0){
        cout << "client says" << buffer << endl;
    }
    string reply = "server received your message";
    send(clientSocket,reply.c_str(),reply.size(),0);
    closesocket(clientSocket);
    closesocket(ser_sock);
    /*关闭服务器监听 socket。
    因为这个最小版本只处理一个客户端，所以处理完就退出。*/
    return 0;
}