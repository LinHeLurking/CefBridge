#ifndef CEF_BRIDGE_CEF_LAUNCHER_LAUNCHER_H
#define CEF_BRIDGE_CEF_LAUNCHER_LAUNCHER_H

#include <memory>

namespace cef_bridge {
class CefBridge {
public:
  class Delegate {
  public:
    virtual int Launch() = 0;

    virtual ~Delegate() = default;
  };

  CefBridge();
  ~CefBridge();

  int Launch() const {
    return bridge_delegate_->Launch();
  }

private:
  std::unique_ptr<Delegate> bridge_delegate_;
};
}
#endif  // !CEF_BRIDGE_CEF_LAUNCHER_LAUNCHER_H
