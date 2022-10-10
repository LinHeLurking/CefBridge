# CMakeList.txt : CMake project for CefBridge, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("CefBridge")

# Globally set C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)

add_executable (CefBridge "src/CefBridge.cpp" "src/CefBridge.h")

# Use folders in the resulting project files.
set_property(GLOBAL PROPERTY OS_FOLDERS ON)


#
# CEF detection
#

# CEF_ROOT is set with IDE config
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CEF_ROOT}/cmake")

# Execute FindCEF.cmake which must exist in CMAKE_MODULE_PATH.
find_package(CEF REQUIRED)

#
# Define CEF-based targets.
#

# Include the libcef_dll_wrapper target.
# Comes from the libcef_dll/CMakeLists.txt file in the binary distribution
# directory.
add_subdirectory(${CEF_LIBCEF_DLL_WRAPPER_PATH} libcef_dll_wrapper)

add_subdirectory(src/cefclient)

# Display configuration settings.
PRINT_CEF_CONFIG()


