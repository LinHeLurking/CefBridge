#include <Windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

#include <iostream>

#include "renderer.h"

using namespace test_reader;

int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine,
                   int nCmdShow) {
  HDC hDC;
  HGLRC hRC;
  HWND hWnd;
  MSG msg;

  hWnd = CreateOpenGLWindow(TEXT("Test Renderer"), 0, 0, 800, 600, PFD_TYPE_RGBA, 0);
  if (hWnd == nullptr) {
    std::exit(1);
  }

  hDC = GetDC(hWnd);
  hRC = wglCreateContext(hDC);
  wglMakeCurrent(hDC, hRC);

  ShowWindow(hWnd, nCmdShow);

  while (GetMessage(&msg, hWnd, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  wglMakeCurrent(nullptr, nullptr);
  ReleaseDC(hWnd, hDC);
  wglDeleteContext(hRC);
  DestroyWindow(hWnd);

  return msg.wParam;
}
