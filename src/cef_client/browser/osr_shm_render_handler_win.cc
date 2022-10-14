#include "osr_shm_render_handler_win.h"

#include <windef.h>

#include "include/wrapper/cef_helpers.h"


namespace client {

OsrShmRenderHandlerWin::OsrShmRenderHandlerWin(
    const OsrRendererSettings& settings, HWND hwnd)
    : OsrRenderHandlerWin(settings, hwnd), renderer_(settings) {}

OsrShmRenderHandlerWin::~OsrShmRenderHandlerWin() {}

void OsrShmRenderHandlerWin::Initialize(CefRefPtr<CefBrowser> browser) {
  CEF_REQUIRE_UI_THREAD();
  SetBrowser(browser);
}

void OsrShmRenderHandlerWin::SetSpin(float spinX, float spinY) {
  CEF_REQUIRE_UI_THREAD();
  renderer_.SetSpin(spinX, spinY);
  Invalidate();
}
void OsrShmRenderHandlerWin::IncrementSpin(float spinDX, float spinDY) {
  CEF_REQUIRE_UI_THREAD();
  renderer_.IncrementSpin(spinDX, spinDY);
  Invalidate();
}
bool OsrShmRenderHandlerWin::IsOverPopupWidget(int x, int y) const {
  CEF_REQUIRE_UI_THREAD();
  const CefRect& rc = renderer_.popup_rect();
  int popup_right = rc.x + rc.width;
  int popup_bottom = rc.y + rc.height;
  return (x >= rc.x) && (x < popup_right) && (y >= rc.y) && (y < popup_bottom);
}

int OsrShmRenderHandlerWin::GetPopupXOffset() const {
  CEF_REQUIRE_UI_THREAD();
  return renderer_.original_popup_rect().x - renderer_.popup_rect().x;
}

int OsrShmRenderHandlerWin::GetPopupYOffset() const {
  CEF_REQUIRE_UI_THREAD();
  return renderer_.original_popup_rect().y - renderer_.popup_rect().y;
}

void OsrShmRenderHandlerWin::OnPopupShow(CefRefPtr<CefBrowser> browser,
                                         bool show) {
  CEF_REQUIRE_UI_THREAD();

  if (!show) {
    renderer_.ClearPopupRects();
    browser->GetHost()->Invalidate(PET_VIEW);
  }

  renderer_.OnPopupShow(browser, show);
}

void OsrShmRenderHandlerWin::OnPopupSize(CefRefPtr<CefBrowser> browser,
                                         const CefRect& rect) {
  CEF_REQUIRE_UI_THREAD();
  renderer_.OnPopupSize(browser, rect);
}

void OsrShmRenderHandlerWin::OnPaint(
    CefRefPtr<CefBrowser> browser, CefRenderHandler::PaintElementType type,
    const CefRenderHandler::RectList& dirtyRects, const void* buffer, int width,
    int height) {
  CEF_REQUIRE_UI_THREAD();
  if (painting_popup_) {
    renderer_.OnPaint(browser, type, dirtyRects, buffer, width, height);
    return;
  }

  renderer_.OnPaint(browser, type, dirtyRects, buffer, width, height);
  if (type == PET_VIEW && !renderer_.popup_rect().IsEmpty()) {
    painting_popup_ = true;
    browser->GetHost()->Invalidate(PET_POPUP);
    painting_popup_ = false;
  }
  renderer_.Render();
}

void OsrShmRenderHandlerWin::OnAcceleratedPaint(
    CefRefPtr<CefBrowser> browser, CefRenderHandler::PaintElementType type,
    const CefRenderHandler::RectList& dirtyRects, void* share_handle) {
  // Not used with this implementation.
  NOTREACHED();
}

void OsrShmRenderHandlerWin::Render() { renderer_.Render(); }
// void Osr
}  // namespace client