// Stub for the simlight code
// NB: compiled as C++ code.

#ifndef SLV6_ARM_MMU_H
#define SLV6_ARM_MMU_H

#include "../arm_v5_mmu.hpp"

namespace simsoc {

  typedef struct ARMv6_MMU SLv6_MMU;

  static inline void init_MMU(SLv6_MMU *mmu, uint32_t begin, uint32_t size) {}
  static inline void destruct_MMU(SLv6_MMU *mmu) {}
  
  static inline uint8_t slv6_read_byte(SLv6_MMU *mmu, uint32_t addr) {
    return mmu->read_byte(addr);
  }

  static inline uint16_t slv6_read_half(SLv6_MMU *mmu, uint32_t addr) {
    return mmu->read_half(addr);
  }

  // Using a macro instead of an inline function changes the compiler
  // decision about inling ARMv6_MMU::read_word.
//   static inline uint32_t slv6_read_word(SLv6_MMU *mmu, uint32_t addr) {
//     return mmu->read_word(addr);
//   }
#define slv6_read_word(mmu, addr) mmu->read_word(addr)

  static inline void slv6_write_byte(SLv6_MMU *mmu, uint32_t addr, uint8_t data) {
    mmu->write_byte(addr,data);
  }

  static inline void slv6_write_half(SLv6_MMU *mmu, uint32_t addr, uint16_t data) {
    mmu->write_half(addr,data);
  }

//   static inline void slv6_write_word(SLv6_MMU *mmu, uint32_t addr, uint32_t data) {
//     mmu->write_word(addr,data);
//   }
#define slv6_write_word(mmu,addr,data) mmu->write_word(addr,data)

  static inline uint8_t slv6_read_byte_as_user(SLv6_MMU *mmu, uint32_t addr) {
    if (!mmu->user_mode) {
      mmu->user_mode = true;
      const uint8_t data = slv6_read_byte(mmu,addr);
      mmu->user_mode = false;
      return data;
    } else
      return mmu->read_byte(addr);
  }
  
  static inline uint32_t slv6_read_word_as_user(SLv6_MMU *mmu, uint32_t addr) {
    if (!mmu->user_mode) {
      mmu->user_mode = true;
      const uint32_t data = slv6_read_word(mmu,addr);
      mmu->user_mode = false;
      return data;
    } else
      return mmu->read_word(addr);
  }
  
  static inline void slv6_write_byte_as_user(SLv6_MMU *mmu, uint32_t addr, uint8_t data) {
    if (!mmu->user_mode) {
      mmu->user_mode = true;
      slv6_write_byte(mmu,addr,data);
      mmu->user_mode = false;
    } else
      slv6_write_byte(mmu,addr,data);
  }
  
  static inline void slv6_write_word_as_user(SLv6_MMU *mmu, uint32_t addr, uint32_t data) {
    if (!mmu->user_mode) {
      mmu->user_mode = true;
      slv6_write_word(mmu,addr,data);
      mmu->user_mode = false;
    } else
      slv6_write_word(mmu,addr,data);
  }

} // namespace simsoc

#endif // SLV6_ARM_MMU_H
