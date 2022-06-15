#include <Windows.h>

void doHide() {
  CURSORINFO cursor_info = {sizeof(CURSORINFO)};

  if (GetCursorInfo(&cursor_info) && cursor_info.flags == 1) {
    // std::cout << "hide\n";
    while(ShowCursor(false)>=0);
  }
  // else
  // {
  //     std::cout << "Win32 error: " << GetLastError() << std::endl; // GetCursorInfo function failed
  // }
}

void doShow() {
  CURSORINFO cursor_info = {sizeof(CURSORINFO)};

  if (GetCursorInfo(&cursor_info) && cursor_info.flags == 0) {
    // std::cout << "show\n";
    while(ShowCursor(true)<=0);
  }
  // else
  // {
  //   std::cout << "Win32 error: " << GetLastError() << std::endl; // GetCursorInfo function failed
  // }
}
