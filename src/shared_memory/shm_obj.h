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
     * @return int
     */

    virtual int GetKey() const = 0;
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
    virtual size_t GetByteSize() const = 0;
    /**
     * @brief Get the last dimension of 2d shared memory
     * 
     * @return size_t 
     */
    virtual size_t GetXSize() const = 0;
    /**
     * @brief Get the first dimension of 2d shared memory
     * 
     * @return size_t 
     */
    virtual size_t GetYSize() const = 0;
    virtual ~Delegate() {}
  };
  ShmObj(int key, size_t sz_x, size_t sz_y, size_t sz_elem);
  virtual ~ShmObj(){};

  int GetKey() const { return shm_obj_d_->GetKey(); }
  size_t GetByteSize() const { return shm_obj_d_->GetByteSize(); }
  size_t GetXSize() const { return shm_obj_d_->GetXSize(); }
  size_t GetYSize() const { return shm_obj_d_->GetYSize(); }
  int8_t *GetBuf() const { return shm_obj_d_->GetBuf(); }

 private:
  std::unique_ptr<Delegate> shm_obj_d_;
};
}  // namespace shared_memory

#endif