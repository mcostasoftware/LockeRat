#include "Header.h"
#include <stdio.h>

int main() {
	
	SOCKET sock = startClient(20015, "127.0.0.1");
	if (sock != INVALID_SOCKET) {
	startLogging(sock);
	}
	return 0;
}