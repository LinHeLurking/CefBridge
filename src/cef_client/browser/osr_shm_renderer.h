#ifndef CEF_BRIDGE_OSR_SHM_RENDERER_H
#define CEF_BRIDGE_OSR_SHM_RENDERER_H

#include "../../shared_memory/shm_manager.h"
#include "include/cef_browser.h"
#include "include/cef_render_handler.h"
#include "include/internal/cef_ptr.h"
#include "osr_renderer_settings.h"

namespace client {
class OsrShmRenderer {
 public:
  explicit OsrShmRenderer(const OsrRendererSettings& settings);
  ~OsrShmRenderer();

  // Render to the screen.
  void Render();

  // Forwarded from CefRenderHandler callbacks.
  void OnPopupShow(CefRefPtr<CefBrowser> browser, bool show);
  // |rect| must be in pixel coordinates.
  void OnPopupSize(CefRefPtr<CefBrowser> browser, const CefRect& rect);
  void OnPaint(CefRefPtr<CefBrowser> browser,
               CefRenderHandler::PaintElementType type,
               const CefRenderHandler::RectList& dirtyRects, const void* buffer,
               int width, int height);

  // Apply spin.
  void SetSpin(float spinX, float spinY);
  void IncrementSpin(float spinDX, float spinDY);

  int GetViewWidth() const { return view_width_; }
  int GetViewHeight() const { return view_height_; }

  CefRect popup_rect() const { return popup_rect_; }
  CefRect original_popup_rect() const { return original_popup_rect_; }

  void ClearPopupRects();

 private:
  using ShmManager = ::shared_memory::ShmManager;

  CefRect GetPopupRectInWebView(const CefRect& original_rect);

  inline bool IsTransparent() const {
    return CefColorGetA(settings_.background_color) == 0;
  }

  inline int GetViewPixelSize() const { return 4 * view_width_ * view_height_; }

  const OsrRendererSettings settings_;
  int painting_browser_id_;
  int view_width_;
  int view_height_;
  CefRect popup_rect_;
  CefRect original_popup_rect_;
  float spin_x_;
  float spin_y_;
  CefRect update_rect_;
  ShmManager shm_mgr_;

  DISALLOW_COPY_AND_ASSIGN(OsrShmRenderer);
};
}  // namespace client

#endif