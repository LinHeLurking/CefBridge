#include "shm_obj_win.h"

#include <Windows.h>
#include <corecrt_wstring.h>
#include <handleapi.h>
#include <memoryapi.h>
#include <vcruntime.h>
#include <winnt.h>

#include <cassert>
#include <stdexcept>
#include <string>

namespace shared_memory {
ShmObjWin::ShmObjWin(const std::string& key, size_t size) {
  char sz_name[256];
  strncpy_s(sz_name, key.c_str(), key.size());
  h_map_file_ =
      CreateFileMappingA(INVALID_HANDLE_VALUE,  // use paging file
                         nullptr,               // default security
                         PAGE_READWRITE,        // read/write access
                         0,            // maximum object size (high-order DWORD)
                         (DWORD)size,  // maximum object size (low-order DWORD)
                         sz_name       // name of mapping object
      );
  // TODO: Replace with better error handling
  assert(h_map_file_);
  key_ = key;
  size_ = size;
}

std::string ShmObjWin::GetKey() const { return key_; }

size_t ShmObjWin::GetSize() const { return size_; }

int8_t* ShmObjWin::GetBuf() const {
  auto buf = MapViewOfFile(h_map_file_, FILE_MAP_ALL_ACCESS, 0, 0, size_);
  // TODO: Replace with better error handling
  assert(buf);
  return static_cast<int8_t*>(buf);
}

ShmObjWin::~ShmObjWin() { CloseHandle(h_map_file_); }

}  // namespace shared_memory