#ifndef CEF_BRIDGE_SHARED_MEMORY_MANAGER_H
#define CEF_BRIDGE_SHARED_MEMORY_MANAGER_H

#include <vcruntime.h>

#include <memory>
#include <optional>
#include <string>
#include <unordered_map>

#include "shm_obj.h"


namespace shared_memory {
template<class KeyT>
class ShmManager {
 public:
  ShmManager();
  std::shared_ptr<ShmObj> GetOrCreateShm(KeyT const &key, size_t size);
  std::shared_ptr<ShmObj> GetShm(KeyT const &key);

 private:
  std::unordered_map<KeyT, std::shared_ptr<ShmObj>> chunks_;
};
}  // namespace shared_memory

#endif