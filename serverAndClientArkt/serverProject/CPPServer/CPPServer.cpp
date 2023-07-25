// CPPServer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <tchar.h> // Include tchar.h to use the _T macro
#include <iostream>

#pragma comment(lib, "ws2_32.lib")

#define PORT 8080

using namespace std;
int main(int argc, char const* argv[])
{
    // SETTING UP THE  DLL FOR USE OF SOCKETS (WINSOCKETS SPECIFICALLY)
    SOCKET serverSocket, acceptSocket;

    // wsaData means setting up the data structure for the window socket
    WSADATA wsaData;
    int wsaerr;
    WORD wVersionRequested = MAKEWORD(2, 2);

    // starting up the winsocket api
    wsaerr = WSAStartup(wVersionRequested, &wsaData);
    if (wsaerr!= 0) {
        perror("WSAStartup failed");
        return 0;
    }
    else {
        cout << "The status is: " << wsaData.szSystemStatus << endl;
    }

    // SETTING UP THE SOCKETS

    serverSocket = INVALID_SOCKET;

    // this specifies the protocols use for the socket AF_INET specifies the internet protocol example ipv4
    // and  sock_stream and ipproto_tcp specify that tcp is being used
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (serverSocket == INVALID_SOCKET) {
        perror("Error at socket()");
        WSACleanup();
        return 0;
    }
    else {
        cout << "socket healthy " << endl;
    }

    // BIND SOCKET TO PORT  
    SOCKADDR_IN service;
    service.sin_family = AF_INET;
    InetPton(AF_INET, _T("127.0.0.1"), &service.sin_addr.s_addr);

    service.sin_port = htons(PORT);
    if (bind(serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
        perror("bind failed");
        closesocket(serverSocket);
        WSACleanup();
        return 0;
    }
    else {
        cout << "binding healthy" << endl;
    }

    // LISTEN FOR INCOMING SOCKETS
    if (listen(serverSocket, 1) == SOCKET_ERROR) {
        perror("listen() error on listening socket: ");
    }
    else {
        cout << "listening for connection" << endl;
    }

    // ACCEPT THE CONNECTION AND PAUSE THE CODE( WAITS UTIL THE CONNECTION GOES THROUGH)
    acceptSocket = accept(serverSocket, NULL, NULL);
    if (acceptSocket == INVALID_SOCKET) {
        perror("accept failed: ");
        WSACleanup();
        return -1;
    }

    cout << "Accepted connection " << endl;
    system("pause");
    WSACleanup();

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
