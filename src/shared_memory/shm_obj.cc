#include "shm_obj.h"

#include <vcruntime.h>

#include <string>

#include "shm_obj_win.h"


namespace shared_memory {
ShmObj::ShmObj(int key, size_t sz_x, size_t sz_y, size_t sz_elem)
    : shm_obj_d_(new ShmObjWin(key, sz_x, sz_y, sz_elem)) {}
}  // namespace shared_memory