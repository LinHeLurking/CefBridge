#include "shm_manager.h"

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

std::shared_ptr<ShmObj> ShmManager::GetOrCreateShm(int const &key,
                                                         size_t size) {
  if (chunks_.count(key)) {
    return chunks_[key];
  }
  return chunks_[key] = std::make_shared<ShmObj>(key, size);
}
}  // namespace shared_memory