#ifndef CEF_BRIDGE_CEF_LAUNCHER_LAUNCHER_H
#define CEF_BRIDGE_CEF_LAUNCHER_LAUNCHER_H

#include <memory>

namespace cef_bridge {
class CefLauncher {
 public:
  class Delegate {
   public:
    virtual int Launch() = 0;

    virtual ~Delegate() = default;
  };

  CefLauncher();
  ~CefLauncher();

  [[nodiscard]] int Launch() const { return bridge_d_->Launch(); }

 private:
  std::unique_ptr<Delegate> bridge_d_;
};
}  // namespace cef_bridge
#endif  // !CEF_BRIDGE_CEF_LAUNCHER_LAUNCHER_H
