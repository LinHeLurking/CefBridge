#include "cef_bridge_win.h"

#include <filesystem>
#include <iostream>

size_t constexpr MAX_NAME_LEN = 512;

namespace cef_bridge {
int CefBridgeWin::Launch() {
  auto target_path_str = SearchCefClient();
  // Add argument
  target_path_str += L" --off-screen-rendering-enabled";
  TCHAR target_path_c_str[MAX_NAME_LEN];
  wcscpy_s(target_path_c_str, target_path_str.c_str());
  std::wcout << "Target path: " << target_path_c_str << std::endl;

  ZeroMemory(&start_up_info_, sizeof(start_up_info_));
  start_up_info_.cb = sizeof(start_up_info_);
  ZeroMemory(&process_info_, sizeof(process_info_));

  // Start the child process.
  auto res = CreateProcess(
      nullptr,           // No module name (use command line)
      target_path_c_str, // Command line
      nullptr,           // Process handle not inheritable
      nullptr,           // Thread handle not inheritable
      FALSE,             // Set handle inheritance to FALSE
      0,                 // No creation flags
      nullptr,           // Use parent's environment block
      nullptr,           // Use parent's starting directory
      &start_up_info_,   // Pointer to STARTUPINFO structure
      &process_info_     // Pointer to PROCESS_INFORMATION structure
      );
  if (!res) {
    printf("CreateProcess failed (%ld).\n", GetLastError());
    return 0;
  }

  // Wait until child process exits.
  WaitForSingleObject(process_info_.hProcess, INFINITE);
  return 0;
}

std::wstring CefBridgeWin::SearchCefClient() const {
  TCHAR self_path_c_str[MAX_NAME_LEN];
  GetModuleFileName(nullptr, self_path_c_str, MAX_NAME_LEN);

  constexpr TCHAR target_name[] = L"cefclient.exe";
  const std::vector<std::vector<std::wstring>> possible_directories = {
      {}, {L"cef_client"}};
  for (auto& dir_levels : possible_directories) {
    auto path = std::filesystem::path(self_path_c_str).parent_path();
    for (auto& level : dir_levels) {
      path.append(level);
    }
    path.append(target_name);
    if (exists(path)) {
      auto res = path.wstring();
      return res;
    }
  }
  return L"";
}

CefBridgeWin::~CefBridgeWin() {
  TerminateProcess(process_info_.hProcess, 0);
}
}
