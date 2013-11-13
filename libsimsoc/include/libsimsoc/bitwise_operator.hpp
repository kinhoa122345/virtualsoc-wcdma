//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef BITWISE_OPERATOR_HPP
#define BITWISE_OPERATOR_HPP

#include "simsoc-config.h"
#include <inttypes.h>
#include <vector>

#define NBLOCKS(size, blocksize) \
  (((size) + (blocksize) - 1) / (blocksize))

namespace simsoc {

  inline uint32_t rotateRight(uint32_t i, uint8_t r) {
    return (i<<(32-r)) | (i>>r);
  }

  inline uint8_t numberOfSetBitsIn(uint32_t i) {
    uint8_t n=0;
    while (i) {
      n+=(i&1);
      i>>=1;
    }
    return n;
  }

  inline uint32_t signExtend24to32(uint32_t i) {
    if (i&(1<<23))
      return 0xff000000|i;
    else
      return 0x00ffffff&i;
  }

  inline int32_t signExtend11to32(uint32_t i) {
    if (i&(1<<10))
      return 0xfffff800|i;
    else
      return 0x000007ff&i;
  }

  // Fucntions used by the MIPS processor
  inline bool notWordValue(uint32_t) {return false;}
  inline bool notWordValue(uint64_t x) {
    if (x&(1<<31))
      return x>>32 == 0xffffffff;
    else
      return x>>32 == 0;
  }

  // ------------------------------------------------------------------
#ifndef SIMSOC_HAVE_FLS
  inline size_t fls(uint32_t x) {
    size_t result = 0;
    if (x&0xffff0000) {
      result += 16;
      x>>=16;
    }
    if (x&0xff00) {
      result += 8;
      x>>=8;
    }
    if (x&0xf0) {
      result += 4;
      x>>=4;
    }
    if (x&0xc) {
      result += 2;
      x>>=2;
    }
    if (x&2) return result+2;
    else return result+x;
  }
#endif // !SIMSOC_HAVE_FLS

  // ------------------------------------------------------------------
  inline uint32_t swap_32(uint32_t data) {
    return
        ((data & 0x000000FF) << 24)
      | ((data & 0x0000FF00) <<  8)
      | ((data & 0x00FF0000) >>  8)
      | ((data & 0xFF000000) >> 24);
  }

  inline uint16_t swap_16(uint16_t data) {
    return
        ((data & 0x00FF) << 8)
      | ((data & 0xFF00) >> 8);
  }

  // ------------------------------------------------------------------
  template < class ctype >
  inline ctype full(size_t count) {
    return ((ctype) 1 << count) - ((ctype) 1);
  }

  template < class ctype >
  inline ctype bit(ctype value, size_t position) {
    return (value >> position) & 0x1;
  }

  template < class ctype >
  inline ctype bits(ctype value, int end, int start) {
    return value
      << (((8u * sizeof(ctype))-1)-end)
      >> ((((8u * sizeof(ctype))-1)-end)+start);
  }

  template < class ctype >
  inline ctype topbits(ctype value, size_t size) {
    return (value >> size) << size;
  }

  template < class ctype >
  inline ctype is_set(ctype value, size_t position) {
    return value & (((ctype) 1) << position);
  }

  template < class ctype >
  inline void set_bit(ctype &value, size_t position) {
    value |= ((ctype) 1 << position);
  }

  template < class ctype >
  inline void unset_bit(ctype &value, size_t position) {
    value &= ~((ctype) 1 << position);
  }

  // ------------------------------------------------------------------
  template < class T, size_t To, size_t From = To >
  class bits_t {
  public:
    typedef T ctype_t;

    static const size_t from  = From;
    static const size_t to    = To;
    static const size_t nbits = 1 + (to - from);

    static const ctype_t mask0 = (((ctype_t) 1) << nbits) - 1;
    static const ctype_t mask  = (mask0 << from);

  public:
    inline static bool is_set(ctype_t value) {
      return (value & mask);
    }

    inline static void set(ctype_t &value, ctype_t bits) {
      value |= (bits & mask0) << to;
    }

    inline static ctype_t get(ctype_t value) {
      return (value >> from) & mask0;
    }

    inline static void set_on_1(ctype_t &value, ctype_t bits) {
      value |= (bits & mask0) << to;
    }

    inline static void clr_on_1(ctype_t &value, ctype_t bits) {
      value &= (~bits & mask0) << to;
    }
  };

  // ------------------------------------------------------------------
  inline void u64_setlo(uint64_t &the, uint32_t lo) {
    the &= (0xFFFFFFFF00000000LL);
    the |= lo;
  }

  inline void u64_sethi(uint64_t &the, uint32_t hi) {
    the &= (0x00000000FFFFFFFFLL);
    the |= ((uint64_t) hi) << 32;
  }

  // ------------------------------------------------------------------
  inline uint32_t u32_le(const uint8_t *the) {
    return
        (uint32_t) the[0] <<  0
      | (uint32_t) the[1] <<  8
      | (uint32_t) the[2] << 16
      | (uint32_t) the[3] << 24;
  }

} // namespace simsoc

#endif //BITWISE_OPERATOR_HPP
