#include "cef_bridge.h"

#include "cef_bridge_win.h"

namespace cef_bridge {
CefBridge::CefBridge() : bridge_d_(std::make_unique<CefBridgeWin>()) {}

CefBridge::~CefBridge() {
  // Call Destructor
  bridge_d_.reset();
}
}  // namespace cef_bridge
