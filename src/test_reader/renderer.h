#ifndef CEF_BRIDGE_TEST_READER_RENDERER_H
#define CEF_BRIDGE_TEST_READER_RENDERER_H

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

namespace test_reader {
void Display();

long WINAPI WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HWND CreateOpenGLWindow(LPCTSTR title, int x, int y, int width, int height,
                        BYTE type, DWORD flags);
}  // namespace cef_bridge::test_reader

#endif
