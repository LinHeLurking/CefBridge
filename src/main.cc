#include <iostream>

#include "cef_launcher/launcher.h"

int main() {
  cef_bridge::CefLauncher const launcher;
  return launcher.Launch();
}
