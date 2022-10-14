#ifndef CEF_BRIDGE_SHARED_MEMORY_OBJ_WIN_H
#define CEF_BRIDGE_SHARED_MEMORY_OBJ_WIN_H

#include <Windows.h>
#include <stdint.h>
#include <vcruntime.h>

#include <string>

#include "shm_obj.h"

namespace shared_memory {
class ShmObjWin : public ShmObj::Delegate {
 public:
  ShmObjWin(int key, size_t sz_x, size_t sz_y, size_t sz_elem);
  int GetKey() const override;
  int8_t *GetBuf() const override;
  size_t GetByteSize() const override;
  size_t GetXSize() const override;
  size_t GetYSize() const override;

  ~ShmObjWin();

 private:
  size_t sz_x_, sz_y_, sz_elem_;
  int key_;
  HANDLE h_map_file_;
};
}  // namespace shared_memory

#endif