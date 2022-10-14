#include "shm_manager.h"

#include <stdint.h>
#include <vcruntime.h>

#include <algorithm>
#include <cstring>
#include <memory>
#include <optional>

namespace shared_memory {

ShmManager::ShmManager() {}

std::shared_ptr<ShmObj> ShmManager::GetShm(int const &key) {
  if (chunks_.count(key)) {
    return chunks_[key];
  } else {
    return nullptr;
  }
}

std::shared_ptr<ShmObj> ShmManager::GetOrCreateShm(int const &key, size_t sz_x,
                                                   size_t sz_y,
                                                   size_t sz_elem) {
  if (chunks_.count(key)) {
    auto chunk = chunks_[key];
    size_t old_sz_x = chunk->GetXSize();
    size_t old_sz_y = chunk->GetYSize();
    if (sz_x <= old_sz_x && sz_y <= old_sz_y) {
      return chunk;
    }
    sz_x = std::max(sz_x, old_sz_x * 2);
    sz_y = std::max(sz_y, old_sz_y * 2);
    auto old_chunk = std::move(chunk);
    chunk = std::make_shared<ShmObj>(key, sz_x, sz_y, sz_elem);
    int8_t *old_buf = old_chunk->GetBuf();
    int8_t *buf = chunk->GetBuf();
    for (size_t i = 0; i < old_sz_y; ++i) {
      std::memcpy(buf, old_buf, old_sz_x);
    }
    return chunk;
  } else {
    return chunks_[key] = std::make_shared<ShmObj>(key, sz_x, sz_y, sz_elem);
  }
}
}  // namespace shared_memory