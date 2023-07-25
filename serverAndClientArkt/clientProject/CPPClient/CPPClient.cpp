// CPPClient.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <tchar.h> // Include tchar.h to use the _T macro
#include <iostream>

#pragma comment(lib, "ws2_32.lib")
#define PORT 8080
using namespace std;

int main()
{
    // SETTING UP THE DLL FOR USE OF SOCKETS (WINSOCKETS SPECIFICALLY)
    SOCKET clientSocket;
    WSADATA wsaData;
    int wsaerr;
    WORD wVersionRequested = MAKEWORD(2, 2);

    wsaerr = WSAStartup(wVersionRequested, &wsaData);
    if (wsaerr != 0) {
        perror("winsock dll not found: ");
        return 0;
    }
    else {
        cout << "status: " << wsaData.szSystemStatus << endl;
    }

    // CREAT SOCKET
    clientSocket = INVALID_SOCKET;
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        perror("Error at socket: ");
        WSACleanup();
        return 0;
    }
    else {
        cout << "socket healthy" << endl;
    }

    // CONNECTING WITH THE SERVER
    SOCKADDR_IN clientService;
    clientService.sin_family = AF_INET;
    InetPton(AF_INET, _T("127.0.0.1"), &clientService.sin_addr.s_addr);
    clientService.sin_port = htons(PORT);
    if (connect(clientSocket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR) {
        perror("Client connect failed: ");
        WSACleanup();
        return 0;
    }
    else {
        cout << "client healthy" << endl;
        cout << "client can send and recieve data" << endl;
    }
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
