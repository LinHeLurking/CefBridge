#include "shm_obj.h"

#include <string>

#include "shm_obj_win.h"

namespace shared_memory {
ShmObj::ShmObj(std::string const &key, size_t size)
    : shm_obj_d_(new ShmObjWin(key, size)) {}
}  // namespace shared_memory