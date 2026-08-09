#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <iostream>
#include <string>

using namespace std;

int main() {
    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cout << "WSAStartup failed" << endl;
        return 1;
    }

    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (clientSocket == INVALID_SOCKET) {
        cout << "socket failed" << endl;
        WSACleanup();
        return 1;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    serverAddr.sin_port = htons(9000);

    if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        /*connect而非bind是客户端所需操作*/
        cout << "connect failed" << endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    string message = "hello server";

    send(clientSocket, message.c_str(), message.size(), 0);

    char buffer[1024]{};

    int len = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);

    if (len > 0) {
        cout << "server says: " << buffer << endl;
    }

    closesocket(clientSocket);
    WSACleanup();

    return 0;
}