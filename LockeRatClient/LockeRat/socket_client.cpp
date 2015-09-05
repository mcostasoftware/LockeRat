#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>

#pragma comment(lib, "Ws2_32.lib")


SOCKET startClient(int portNum, char ipAddress[]) {
	int funcStatus = 0;
	WSADATA wsaData;
	SOCKET sock = INVALID_SOCKET;
	struct sockaddr_in server;
	//Initializing WinSocket

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		printf("WSAStartup() failed: %d\n", WSAGetLastError());
	}
	printf("WinSock initialized\n");
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
		printf("socket() failed: %d\n", WSAGetLastError());
	}
	printf("Socket created\n");

	server.sin_addr.s_addr = inet_addr(ipAddress);
	server.sin_family = AF_INET;
	server.sin_port = htons(portNum);

	//Connect to server
	if (connect(sock, (struct sockaddr *)&server, sizeof(server)) != 0) {
		printf("Connect() failed %d\b", WSAGetLastError());
	}
	printf("Connected to server.");

	return sock;
}