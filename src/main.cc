#include <iostream>

#include "cef_launcher/launcher.h"


int main() {
  cef_bridge::CefLauncher const bridge;
  return bridge.Launch();
}
