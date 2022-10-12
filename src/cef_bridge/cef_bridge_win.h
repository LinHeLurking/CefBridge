#ifndef CEF_BRIDGE_CEF_LAUNCHER_WIN_H
#define CEF_BRIDGE_CEF_LAUNCHER_WIN_H

#include "cef_bridge.h"
#include <Windows.h>
#include <string>

#pragma comment(lib, "user32.lib")

namespace cef_bridge {
class CefBridgeWin final : public CefBridge::Delegate {
public:
  int Launch() override;
  std::wstring SearchCefClient() const;
  ~CefBridgeWin() override;

private:
  STARTUPINFO start_up_info_{};
  PROCESS_INFORMATION process_info_{};
};
}

#endif
