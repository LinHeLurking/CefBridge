#ifndef CEF_BRIDGE_OSR_RENDER_HANDLER_SHM_WIN_H
#define CEF_BRIDGE_OSR_RENDER_HANDLER_SHM_WIN_H

#include <memory>

#include "osr_render_handler_win.h"
#include "osr_shm_renderer.h"


namespace client {
class OsrShmRenderHandlerWin : public OsrRenderHandlerWin {
 public:
  OsrShmRenderHandlerWin(const OsrRendererSettings& settings, HWND hwnd);
  virtual ~OsrShmRenderHandlerWin();

  // Must be called immediately after object creation.
  void Initialize(CefRefPtr<CefBrowser> browser);

  void SetSpin(float spinX, float spinY) override;
  void IncrementSpin(float spinDX, float spinDY) override;
  bool IsOverPopupWidget(int x, int y) const override;
  int GetPopupXOffset() const override;
  int GetPopupYOffset() const override;
  void OnPopupShow(CefRefPtr<CefBrowser> browser, bool show) override;
  void OnPopupSize(CefRefPtr<CefBrowser> browser, const CefRect& rect) override;
  void OnPaint(CefRefPtr<CefBrowser> browser,
               CefRenderHandler::PaintElementType type,
               const CefRenderHandler::RectList& dirtyRects, const void* buffer,
               int width, int height) override;
  void OnAcceleratedPaint(CefRefPtr<CefBrowser> browser,
                          CefRenderHandler::PaintElementType type,
                          const CefRenderHandler::RectList& dirtyRects,
                          void* share_handle) override;

 private:
  void Render() override;
  bool painting_popup_;
  OsrShmRenderer renderer_;
};
}  // namespace client

#endif