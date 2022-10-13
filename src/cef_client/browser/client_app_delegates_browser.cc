// Copyright (c) 2012 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "client_app_browser.h"

#include "client_browser.h"

namespace client {

// static
void ClientAppBrowser::RegisterCookieableSchemes(
    std::vector<std::string>& cookieable_schemes) {}

// static
void ClientAppBrowser::CreateDelegates(DelegateSet& delegates) {
  browser::CreateDelegates(delegates);
}

}  // namespace client
