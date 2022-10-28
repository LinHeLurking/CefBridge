#include "osr_shm_renderer.h"

#include <vcruntime.h>

#include <cstring>

#include "include/base/cef_logging.h"
#include "include/internal/cef_types.h"
#include "include/internal/cef_types_wrappers.h"

namespace client {
OsrShmRenderer::OsrShmRenderer(const OsrRendererSettings& settings)
    : settings_(settings),
      painting_browser_id_(0),
      view_width_(0),
      view_height_(0),
      spin_x_(0),
      spin_y_(0) {}

OsrShmRenderer::~OsrShmRenderer() {}

void OsrShmRenderer::Render() {
  // TODO: Send frame buffer into shared memory
}

void OsrShmRenderer::OnPopupShow(CefRefPtr<CefBrowser> browser, bool show) {
  if (!show) {
    // Clear the popup rectangle
    ClearPopupRects();
  }
}

void OsrShmRenderer::OnPopupSize(CefRefPtr<CefBrowser> browser,
                                 const CefRect& rect) {
  if (rect.width <= 0 || rect.height <= 0) return;
  original_popup_rect_ = rect;
  popup_rect_ = GetPopupRectInWebView(original_popup_rect_);
}

CefRect OsrShmRenderer::GetPopupRectInWebView(const CefRect& original_rect) {
  CefRect rc(original_rect);
  // if x or y are negative, move them to 0.
  if (rc.x < 0) rc.x = 0;
  if (rc.y < 0) rc.y = 0;
  // if popup goes outside the view, try to reposition origin
  if (rc.x + rc.width > view_width_) rc.x = view_width_ - rc.width;
  if (rc.y + rc.height > view_height_) rc.y = view_height_ - rc.height;
  // if x or y became negative, move them to 0 again.
  if (rc.x < 0) rc.x = 0;
  if (rc.y < 0) rc.y = 0;
  return rc;
}

void OsrShmRenderer::ClearPopupRects() {
  popup_rect_.Set(0, 0, 0, 0);
  original_popup_rect_.Set(0, 0, 0, 0);
}

void OsrShmRenderer::OnPaint(CefRefPtr<CefBrowser> browser,
                             CefRenderHandler::PaintElementType type,
                             const CefRenderHandler::RectList& dirtyRects,
                             const void* buffer, int width, int height) {
  painting_browser_id_ = browser->GetIdentifier();
  if (type == PET_VIEW) {
    int old_width = view_width_;
    int old_height = view_height_;

    view_width_ = width;
    view_height_ = height;

    if (settings_.show_update_rect) update_rect_ = dirtyRects[0];

    if (old_width != view_width_ || old_height != view_height_ ||
        (dirtyRects.size() == 1 &&
         dirtyRects[0] == CefRect(0, 0, view_width_, view_height_))) {
      // Update/resize the whole texture.
      auto shm_obj = shm_mgr_.GetOrCreateShm(browser->GetIdentifier(),
                                             view_width_, view_height_);
      int8_t* shared_buf = shm_obj->GetBuf();
      std::memcpy(shared_buf, buffer, shm_obj->GetByteSize());
    } else {
      // Update just the dirty rectangles
      for (auto i = dirtyRects.begin(); i != dirtyRects.end(); ++i) {
        const CefRect& rect = *i;
        DCHECK(rect.x + rect.width <= view_width_);
        DCHECK(rect.y + rect.height <= view_height_);
        auto shm_obj = shm_mgr_.GetOrCreateShm(browser->GetIdentifier(),
                                               view_width_, view_height_);
        int8_t* shared_buf = shm_obj->GetBuf();
        for (int row = rect.y; row < rect.y + rect.height; ++row) {
          std::memcpy(shared_buf, buffer, rect.width);
        }
      }
    }
  } else if (type == PET_POPUP && popup_rect_.width > 0 &&
             popup_rect_.height > 0) {
    int skip_pixels = 0, x = popup_rect_.x;
    int skip_rows = 0, y = popup_rect_.y;
    int w = width;
    int h = height;

    // Adjust the popup to fit inside the view
    if (x < 0) {
      skip_pixels = -x;
      x = 0;
    }
    if (y < 0) {
      skip_pixels = -y;
      y = 0;
    }
    if (x + w > view_width_) w -= x + w - view_width_;
    if (y + h > view_height_) h -= y + h - view_height_;

    // Update the popup rectangle
    /* int8_t* shared_buf = */
    /*     shm_mgr_ */
    /*         .GetOrCreateShm(browser->GetIdentifier(), view_width_,
     * view_height_) */
    /*         ->GetBuf(); */
    int8_t* shared_buf =
        shm_mgr_.GetOrCreateShm(0, view_width_, view_height_)->GetBuf();
    for (int row = skip_rows; row < skip_rows + h; ++row) {
      std::memcpy(
          shared_buf + row * width + skip_pixels,
          static_cast<const int8_t*>(buffer) + row * width + skip_pixels, w);
    }
  }
}

void OsrShmRenderer::SetSpin(float spinX, float spinY) {
  spin_x_ = spinX;
  spin_y_ = spinY;
}

void OsrShmRenderer::IncrementSpin(float spinDX, float spinDY) {
  spin_x_ -= spinDX;
  spin_y_ -= spinDY;
}

}  // namespace client
