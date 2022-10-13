#ifndef CEF_BRIDGE_SHARED_MEMORY_OBJ_H
#define CEF_BRIDGE_SHARED_MEMORY_OBJ_H

#include <stdint.h>
#include <vcruntime.h>

#include <memory>
#include <string>

namespace shared_memory {
class ShmObj {
 public:
  class Delegate {
   public:
    /**
     * @brief Get the key of shared memory.
     *
     * @return std::string
     */

    virtual std::string GetKey() const = 0;
    /**
     * @brief Get the read/write buffer of shared memory
     *
     * @return int8_t*
     */
    virtual int8_t *GetBuf() const = 0;

    /**
     * @brief Get the size of shared memory.
     *
     * @return size_t
     */
    virtual size_t GetSize() const = 0;
    virtual ~Delegate() {}
  };
  ShmObj(std::string const &key, size_t size);
  virtual ~ShmObj(){};

  std::string GetKey() const { return shm_obj_d_->GetKey(); }
  size_t GetSize() const { return shm_obj_d_->GetSize(); }
  int8_t *GetBuf() const { return shm_obj_d_->GetBuf(); }

 private:
  std::unique_ptr<Delegate> shm_obj_d_;
};
}  // namespace shared_memory

#endif