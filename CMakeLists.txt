# CMakeList.txt : CMake project for CefBridge, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.12)

project ("CefBridge")

# Globally set C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)

add_executable (cef_launcher 
"src/main.cc"
"src/cef_launcher/launcher.h"
"src/cef_launcher/launcher.cc" 
"src/cef_launcher/launcher_win.h"
"src/cef_launcher/launcher_win.cc"
)

set(shared_memory_src 
"${CMAKE_CURRENT_SOURCE_DIR}/src/shared_memory/shm_manager.h"
"${CMAKE_CURRENT_SOURCE_DIR}/src/shared_memory/shm_manager.cc"
"${CMAKE_CURRENT_SOURCE_DIR}/src/shared_memory/shm_obj.h"
"${CMAKE_CURRENT_SOURCE_DIR}/src/shared_memory/shm_obj.cc"
"${CMAKE_CURRENT_SOURCE_DIR}/src/shared_memory/shm_obj_win.h"
"${CMAKE_CURRENT_SOURCE_DIR}/src/shared_memory/shm_obj_win.cc"
)

# Enable unicode for all WIN32 API
add_compile_definitions(UNICODE=1)

# Use folders in the resulting project files.
set_property(GLOBAL PROPERTY OS_FOLDERS ON)

#
# CEF detection
#

if(DEFINED ENV{CEF_ROOT})
  # message(STATUS "Setting CEF_ROOT as $ENV{CEF_ROOT}")
  set(CEF_ROOT $ENV{CEF_ROOT})
endif()

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

add_subdirectory(src/cef_client)

add_dependencies(cef_launcher cefclient)

find_package(OpenGL REQUIRED)

set(test_reader_src
"src/test_reader/reader.cc"
"src/test_reader/renderer.h"
"src/test_reader/renderer.cc"
)
add_executable(test_reader WIN32 ${test_reader_src} ${shared_memory_src})
target_link_libraries(test_reader OpenGL::GL)

