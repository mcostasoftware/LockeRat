#pragma once
#include <Windows.h>

SOCKET startClient(int portNum, char ipAddress[]);
int startLogging(SOCKET sock);