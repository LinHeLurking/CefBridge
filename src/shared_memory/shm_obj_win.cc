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
ShmObjWin::ShmObjWin(int key, size_t sz_x, size_t sz_y, size_t sz_elem) {
  char sz_name[256];
  std::string key_str = "Shared Chunk(" + std::to_string(key) + ")";
  strncpy_s(sz_name, key_str.c_str(), key_str.size());
  size_t size = sz_elem * sz_x * sz_y;
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
  sz_x_ = sz_x;
  sz_y_ = sz_y;
  sz_elem_ = sz_elem;
}

int ShmObjWin::GetKey() const { return key_; }

size_t ShmObjWin::GetByteSize() const { return sz_elem_ * sz_x_ * sz_y_; }
size_t ShmObjWin::GetXSize() const { return sz_x_; }
size_t ShmObjWin::GetYSize() const { return sz_y_; }

int8_t* ShmObjWin::GetBuf() const {
  auto buf =
      MapViewOfFile(h_map_file_, FILE_MAP_ALL_ACCESS, 0, 0, GetByteSize());
  // TODO: Replace with better error handling
  assert(buf);
  return static_cast<int8_t*>(buf);
}

ShmObjWin::~ShmObjWin() { CloseHandle(h_map_file_); }

}  // namespace shared_memory