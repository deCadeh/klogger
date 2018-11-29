For my boys at the SC&C: a simple sample Windows keylogger. Core functionality only.

## Known issues
- Can potentially remove certain keys from being logged without affecting overall functionality; `VK_LSHIFT` and `VK_RSHIFT` have already been commented out

My first Windows program. If there are issues, let me know.

All common/printable keys should be mapped. Logic should be okay. Should probably also add comments.

## Info
Runs as a process in the background (makes no other attempt to hide itself). Will determine user directory with which to write .txt file. Source code divided as such because of the expectation of future added functionality.

Note on net.c/net.h: Just wanted to learn WININET.

## Resources and documentation
[Virtual-Key Codes](https://docs.microsoft.com/en-us/windows/desktop/inputdev/virtual-key-codes)<br/>
[Hooks](https://docs.microsoft.com/en-us/windows/desktop/winmsg/hooks)<br/>
[SetWindowsHookEx function](https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-setwindowshookexw)<br/>
[LowLevelKeyboardProc callback function](https://msdn.microsoft.com/en-us/library/windows/desktop/ms644985(v=vs.85).aspx)<br/>
[GetKeyState function](https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-getkeystate)<br/>
[GetForegroundWindow function](https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-getforegroundwindow)<br/>
[GetWindowText function](https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-getwindowtextw)<br/>
