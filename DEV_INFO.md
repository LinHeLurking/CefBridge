Download CEF binaries from [here](https://cef-builds.spotifycdn.com/index.html). Do not try to build Chromium yourself
unless you have tremendous spare time and computational resources. Extract downloaded tar ball into some directory.
And set `CEF_ROOT` as that directory in CMake. You can set that in IDE settings. Add `-DCEF_ROOT=<...>` to IDE's CMake
configure arguments.
