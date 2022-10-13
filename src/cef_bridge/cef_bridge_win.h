#ifndef CEF_BRIDGE_CEF_LAUNCHER_WIN_H
#define CEF_BRIDGE_CEF_LAUNCHER_WIN_H

#include <Windows.h>

#include <string>

#include "cef_bridge.h"

#pragma comment(lib, "user32.lib")

namespace cef_bridge {
class CefBridgeWin final : public CefBridge::Delegate {
 public:
  int Launch() override;
  static std::wstring SearchCefClient();

 private:
  STARTUPINFO start_up_info_{};
  PROCESS_INFORMATION process_info_{};
};
}  // namespace cef_bridge

#endif
