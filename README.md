For my boys at the SC&C: a simple sample Windows keylogger. Core functionality only.

## Known issues
- Can potentially remove certain keys from being logged without affecting overall functionality; `VK_LSHIFT` and `VK_RSHIFT` have already been commented out

My first Windows program. If there are issues, let me know.

All common/printable keys should be mapped. Logic should be okay. Should probably also add comments.

## Info
Runs as a process in the background (makes no other attempt to hide itself). Will keylog to a file of your choice (specified in klogger.h). Source code divided as such because of the expectation of future added functionality.
