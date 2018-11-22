#pragma once

// Change output file path here:
wchar_t kbtestfile[] = L"C:\\Users\\Admin\\Documents\\klog-test.txt";

HHOOK kbhook;                                             // handle to keyboard hooking procedure

LRESULT CALLBACK LowLevelKeyboardProc(INT, WPARAM, LPARAM);