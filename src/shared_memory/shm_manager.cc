#include "shm_manager.h"

#include <memory>
#include <optional>

namespace shared_memory {

template <class KeyT>
ShmManager<KeyT>::ShmManager() {}

template <class KeyT>
std::shared_ptr<ShmObj> ShmManager<KeyT>::GetShm(KeyT const &key) {
  if (chunks_.count(key)) {
    return chunks_[key];
  } else {
    return nullptr;
  }
}

template <class KeyT>
std::shared_ptr<ShmObj> ShmManager<KeyT>::GetOrCreateShm(KeyT const &key,
                                                         size_t size) {
  if (chunks_.count(key)) {
    return chunks_[key];
  }
  return chunks_[key] = std::make_shared<ShmObj>(key, size);
}
}  // namespace shared_memory