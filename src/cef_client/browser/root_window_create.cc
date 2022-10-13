// Copyright (c) 2016 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "root_window.h"

#include "root_window_views.h"

#if defined(OS_WIN)
#include "root_window_win.h"
#elif defined(OS_LINUX)
#include "root_window_gtk.h"
#elif defined(OS_MAC)
#include "root_window_mac.h"
#endif

namespace client {

// static
scoped_refptr<RootWindow> RootWindow::Create(bool use_views) {
  if (use_views) {
    return new RootWindowViews();
  }

#if defined(OS_WIN)
  return new RootWindowWin();
#elif defined(OS_LINUX)
  return new RootWindowGtk();
#elif defined(OS_MAC)
  return new RootWindowMac();
#else
#error Unsupported platform
#endif
}

}  // namespace client
