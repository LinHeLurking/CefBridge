#include "renderer.h"

#include <stdint.h>
#include <vcruntime_string.h>

#include <algorithm>
#include <vector>

#include "../shared_memory/shm_manager.h"
#include "../shared_memory/shm_obj.h"

namespace test_reader {

namespace {
/* auto g_shm = shared_memory::ShmObj(0, 800, 600, sizeof(int8_t)); */
/* int32_t* g_buf = new int32_t[800 * 600]; */
bool g_buf_initialized = false;
GLuint g_tex_id = -1;
}  // namespace

void Display() {
  if (!g_buf_initialized) {
    std::vector<int32_t> data(800 * 600);
    std::fill(data.begin(), data.end(), 0xFF0000FF);
    glGenTextures(1, &g_tex_id);
    glBindTexture(GL_TEXTURE_2D, g_tex_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 200, 200, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, data.data());
    g_buf_initialized = true;
  }

  glShadeModel(GL_SMOOTH);
  glDisable(GL_DEPTH_TEST);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  /* glBindTexture(GL_TEXTURE_2D, g_tex_id); */

  glBegin(GL_QUADS);

  glColor4ub(255, 0, 0, 255);
  /* glTexCoord2f(0, 1); */
  glVertex2i(-1, 1);

  glColor4ub(0, 0, 0, 255);
  /* glTexCoord2f(0, 0); */
  glVertex2i(-1, -1);

  glColor4ub(0, 0, 255, 255);
  /* glTexCoord2f(1, 0); */
  glVertex2i(1, -1);

  glColor4ub(0, 255, 0, 255);
  /* glTexCoord2f(1, 1); */
  glVertex2i(1, 1);

  glEnd();
  glFlush();

  // Rotate a triangle around
  /* glClear(GL_COLOR_BUFFER_BIT); */
  /* glBegin(GL_TRIANGLES); */
  /* glColor3f(1.0f, 0.0f, 0.0f); */
  /* glVertex2i(0, 1); */
  /* glColor3f(0.0f, 1.0f, 0.0f); */
  /* glVertex2i(-1, -1); */
  /* glColor3f(0.0f, 0.0f, 1.0f); */
  /* glVertex2i(1, -1); */
  /* glEnd(); */
  /* glFlush(); */
}

long WINAPI WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  static PAINTSTRUCT ps;

  switch (uMsg) {
    case WM_PAINT:
      Display();
      BeginPaint(hWnd, &ps);
      EndPaint(hWnd, &ps);
      return 0;
    case WM_SIZE:
      glViewport(0, 0, LOWORD(lParam), HIWORD(lParam));
      PostMessage(hWnd, WM_PAINT, 0, 0);
      return 0;
    case WM_CLOSE:
      PostQuitMessage(0);
      return 0;
  }
  return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

HWND CreateOpenGLWindow(LPCTSTR title, int x, int y, int width, int height,
                        BYTE type, DWORD flags) {
  int pf;
  HDC hDC;
  HWND hWnd;
  WNDCLASS wc;
  PIXELFORMATDESCRIPTOR pfd;
  static HINSTANCE hInst = 0;

  // Only register the window class once
  if (!hInst) {
    hInst = GetModuleHandle(nullptr);
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = (WNDPROC)WindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInst;
    wc.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = nullptr;
    wc.lpszMenuName = nullptr;
    wc.lpszClassName = TEXT("OpenGL");

    if (!RegisterClass(&wc)) {
      MessageBox(nullptr, TEXT("RegisterClass() failed: "),
                 TEXT("Cannot register window class."), MB_OK);
      return nullptr;
    }
  }

  hWnd = CreateWindowW(TEXT("OpenGL"), title,
                       WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
                       x, y, width, height, nullptr, nullptr, hInst, nullptr);
  if (hWnd == nullptr) {
    MessageBox(nullptr, TEXT("CreateWindow() failed: "),
               TEXT("Cannot create a window."), MB_OK);
    return nullptr;
  }

  hDC = GetDC(hWnd);
  memset(&pfd, 0, sizeof(pfd));
  pfd.nSize = sizeof(pfd);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | flags;
  pfd.iPixelType = type;
  pfd.cColorBits = 32;

  pf = ChoosePixelFormat(hDC, &pfd);
  if (pf == 0) {
    MessageBox(nullptr, TEXT("ChoosePixelFormat() failed: "),
               TEXT("Cannot find a suitable pixel format."), MB_OK);
    return nullptr;
  }

  if (!SetPixelFormat(hDC, pf, &pfd)) {
    MessageBox(nullptr, TEXT("SetPixelFormat() failed: "),
               TEXT("Cannot set format specified."), MB_OK);
    return nullptr;
  }

  DescribePixelFormat(hDC, pf, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

  ReleaseDC(hWnd, hDC);

  return hWnd;
}
}  // namespace test_reader
