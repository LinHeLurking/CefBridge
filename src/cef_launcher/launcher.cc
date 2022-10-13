#include "launcher.h"

#include "launcher_win.h"

namespace cef_bridge {
CefLauncher::CefLauncher() : bridge_d_(std::make_unique<CefLauncherWin>()) {}

CefLauncher::~CefLauncher() {
  // Call Destructor
  bridge_d_.reset();
}
}  // namespace cef_bridge
