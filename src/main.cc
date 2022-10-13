#include <iostream>

#include "cef_bridge/cef_bridge.h"


int main() {
  cef_bridge::CefBridge const bridge;
  return bridge.Launch();
}
