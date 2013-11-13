/*
 *  Copyright (c) 2007,
 *  Commissariat a l'Energie Atomique (CEA)
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without modification,
 *  are permitted provided that the following conditions are met:
 *
 *   - Redistributions of source code must retain the above copyright notice, this
 *     list of conditions and the following disclaimer.
 *
 *   - Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the documentation
 *     and/or other materials provided with the distribution.
 *
 *   - Neither the name of CEA nor the names of its contributors may be used to
 *     endorse or promote products derived from this software without specific prior
 *     written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 *  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED.
 *  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 *  INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 *  OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 *  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 *  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Authors: Gilles Mouchard (gilles.mouchard@cea.fr)
 */

#ifndef __FS_UTILS_ENDIAN_ENDIAN_HH__
#define __FS_UTILS_ENDIAN_ENDIAN_HH__

//modifined for SimSoc
#if defined (__linux__)
#include <endian.h>
#elif defined (__APPLE__)
#include <machine/endian.h>
#else
#error Please indicate where to find the <endian.h> header on your system!
#endif

#include <string>
#include <vector>
#include <inttypes.h>
using namespace std;

namespace simsoc {

  typedef enum {E_BIG_ENDIAN, E_LITTLE_ENDIAN} endian_type;

#if defined(__GNUC__) && (__GNUC__ >= 3)
  inline void BSwap(uint8_t& value) __attribute__((always_inline));
  inline void BSwap(uint16_t& value) __attribute__((always_inline));
  inline void BSwap(uint32_t& value) __attribute__((always_inline));
  inline void BSwap(uint64_t& value) __attribute__((always_inline));

  inline uint8_t Host2BigEndian(uint8_t value) __attribute__((always_inline));
  inline uint8_t BigEndian2Host(uint8_t value) __attribute__((always_inline));
  inline uint8_t Host2LittleEndian(uint8_t value) __attribute__((always_inline));
  inline uint8_t LittleEndian2Host(uint8_t value) __attribute__((always_inline));
  inline uint16_t Host2BigEndian(uint16_t value) __attribute__((always_inline));
  inline uint16_t BigEndian2Host(uint16_t value) __attribute__((always_inline));
  inline uint16_t Host2LittleEndian(uint16_t value) __attribute__((always_inline));
  inline uint16_t LittleEndian2Host(uint16_t value) __attribute__((always_inline));
  inline uint32_t Host2BigEndian(uint32_t value) __attribute__((always_inline));
  inline uint32_t BigEndian2Host(uint32_t value) __attribute__((always_inline));
  inline uint32_t Host2LittleEndian(uint32_t value) __attribute__((always_inline));
  inline uint32_t LittleEndian2Host(uint32_t value) __attribute__((always_inline));
  inline uint64_t Host2BigEndian(uint64_t value) __attribute__((always_inline));
  inline uint64_t BigEndian2Host(uint64_t value) __attribute__((always_inline));
  inline uint64_t Host2LittleEndian(uint64_t value) __attribute__((always_inline));
  inline uint64_t LittleEndian2Host(uint64_t value) __attribute__((always_inline));

  inline int8_t Host2BigEndian(int8_t value) __attribute__((always_inline));
  inline int8_t BigEndian2Host(int8_t value) __attribute__((always_inline));
  inline int8_t Host2LittleEndian(int8_t value) __attribute__((always_inline));
  inline int8_t LittleEndian2Host(int8_t value) __attribute__((always_inline));
  inline int16_t Host2BigEndian(int16_t value) __attribute__((always_inline));
  inline int16_t BigEndian2Host(int16_t value) __attribute__((always_inline));
  inline int16_t Host2LittleEndian(int16_t value) __attribute__((always_inline));
  inline int16_t LittleEndian2Host(int16_t value) __attribute__((always_inline));
  inline int32_t Host2BigEndian(int32_t value) __attribute__((always_inline));
  inline int32_t BigEndian2Host(int32_t value) __attribute__((always_inline));
  inline int32_t Host2LittleEndian(int32_t value) __attribute__((always_inline));
  inline int32_t LittleEndian2Host(int32_t value) __attribute__((always_inline));
  inline int64_t Host2BigEndian(int64_t value) __attribute__((always_inline));
  inline int64_t BigEndian2Host(int64_t value) __attribute__((always_inline));
  inline int64_t Host2LittleEndian(int64_t value) __attribute__((always_inline));
  inline int64_t LittleEndian2Host(int64_t value) __attribute__((always_inline));

  inline uint8_t Host2Target(endian_type target_endian, uint8_t value) __attribute__((always_inline));
  inline uint16_t Host2Target(endian_type target_endian, uint16_t value) __attribute__((always_inline));
  inline uint32_t Host2Target(endian_type target_endian, uint32_t value) __attribute__((always_inline));
  inline uint64_t Host2Target(endian_type target_endian, uint64_t value) __attribute__((always_inline));

  inline uint8_t Target2Host(endian_type target_endian, uint8_t value) __attribute__((always_inline));
  inline uint16_t Target2Host(endian_type target_endian, uint16_t value) __attribute__((always_inline));
  inline uint32_t Target2Host(endian_type target_endian, uint32_t value) __attribute__((always_inline));
  inline uint64_t Target2Host(endian_type target_endian, uint64_t value) __attribute__((always_inline));

  inline int8_t Host2Target(endian_type target_endian, int8_t value) __attribute__((always_inline));
  inline int16_t Host2Target(endian_type target_endian, int16_t value) __attribute__((always_inline));
  inline int32_t Host2Target(endian_type target_endian, int32_t value) __attribute__((always_inline));
  inline int64_t Host2Target(endian_type target_endian, int64_t value) __attribute__((always_inline));

  inline int8_t Target2Host(endian_type target_endian, int8_t value) __attribute__((always_inline));
  inline int16_t Target2Host(endian_type target_endian, int16_t value) __attribute__((always_inline));
  inline int32_t Target2Host(endian_type target_endian, int32_t value) __attribute__((always_inline));
  inline int64_t Target2Host(endian_type target_endian, int64_t value) __attribute__((always_inline));

#endif

  inline void BSwap(uint8_t& value)
  {
  }

  inline void BSwap(uint16_t& value)
  {
    value = (value >> 8) | (value << 8);
  }

  inline void BSwap(uint32_t& value)
  {
#if defined(__i386__)
    __asm__ __volatile__("bswap %0" : "=r" (value) : "0" (value));
#else
    value = (value >> 24) | ((value >> 8) & 0x0000ff00UL) | ((value << 8) & 0x00ff0000UL) | (value << 24);
#endif
  }

  inline void BSwap(uint64_t& value)
  {
#if defined(__i386__)
    __asm__ __volatile__("bswap %%eax; bswap %%edx; xchg %%eax, %%edx" : "=&A" (value) : "0" (value));
#else
    value = (value >> 56) | ((value & 0x00ff000000000000ULL) >> 40) |
      ((value & 0x0000ff0000000000ULL) >> 24) | ((value & 0x000000ff00000000ULL) >> 8) |
      ((value & 0x00000000ff000000ULL) << 8) | ((value & 0x0000000000ff0000ULL) << 24) |
      ((value & 0x000000000000ff00ULL) << 40) | ((value << 56));
#endif
  }

  inline uint8_t Host2BigEndian(uint8_t value)
  {
    return value;
  }

  inline uint8_t BigEndian2Host(uint8_t value)
  {
    return value;
  }

  inline uint8_t Host2LittleEndian(uint8_t value)
  {
    return value;
  }

  inline uint8_t LittleEndian2Host(uint8_t value)
  {
    return value;
  }

  inline uint16_t Host2BigEndian(uint16_t value)
  {
#if BYTE_ORDER == LITTLE_ENDIAN
    BSwap(value);
#endif
    return value;
  }

  inline uint16_t BigEndian2Host(uint16_t value)
  {
#if BYTE_ORDER == LITTLE_ENDIAN
    BSwap(value);
#endif
    return value;
  }

  inline uint16_t Host2LittleEndian(uint16_t value)
  {
#if BYTE_ORDER == BIG_ENDIAN
    BSwap(value);
#endif
    return value;
  }

  inline uint16_t LittleEndian2Host(uint16_t value)
  {
#if BYTE_ORDER == BIG_ENDIAN
    BSwap(value);
#endif
    return value;
  }

  inline uint32_t Host2BigEndian(uint32_t value)
  {
#if BYTE_ORDER == LITTLE_ENDIAN
    BSwap(value);
#endif
    return value;
  }

  inline uint32_t BigEndian2Host(uint32_t value)
  {
#if BYTE_ORDER == LITTLE_ENDIAN
    BSwap(value);
#endif
    return value;
  }

  inline uint32_t Host2LittleEndian(uint32_t value)
  {
#if BYTE_ORDER == BIG_ENDIAN
    BSwap(value);
#endif
    return value;
  }

  inline uint32_t LittleEndian2Host(uint32_t value)
  {
#if BYTE_ORDER == BIG_ENDIAN
    BSwap(value);
#endif
    return value;
  }

  inline uint64_t Host2BigEndian(uint64_t value)
  {
#if BYTE_ORDER == LITTLE_ENDIAN
    BSwap(value);
#endif
    return value;
  }

  inline uint64_t BigEndian2Host(uint64_t value)
  {
#if BYTE_ORDER == LITTLE_ENDIAN
    BSwap(value);
#endif
    return value;
  }

  inline uint64_t Host2LittleEndian(uint64_t value)
  {
#if BYTE_ORDER == BIG_ENDIAN
    BSwap(value);
#endif
    return value;
  }

  inline uint64_t LittleEndian2Host(uint64_t value)
  {
#if BYTE_ORDER == BIG_ENDIAN
    BSwap(value);
#endif
    return value;
  }

  inline int8_t Host2BigEndian(int8_t value) { return Host2BigEndian((uint8_t) value); }
  inline int8_t BigEndian2Host(int8_t value) { return BigEndian2Host((uint8_t) value); }
  inline int8_t Host2LittleEndian(int8_t value) { return Host2LittleEndian((uint8_t) value); }
  inline int8_t LittleEndian2Host(int8_t value) { return LittleEndian2Host((uint8_t) value); }

  inline int16_t Host2BigEndian(int16_t value) { return Host2BigEndian((uint16_t) value); }
  inline int16_t BigEndian2Host(int16_t value) { return BigEndian2Host((uint16_t) value); }
  inline int16_t Host2LittleEndian(int16_t value) { return Host2LittleEndian((uint16_t) value); }
  inline int16_t LittleEndian2Host(int16_t value) { return LittleEndian2Host((uint16_t) value); }

  inline int32_t Host2BigEndian(int32_t value) { return Host2BigEndian((uint32_t) value); }
  inline int32_t BigEndian2Host(int32_t value) { return BigEndian2Host((uint32_t) value); }
  inline int32_t Host2LittleEndian(int32_t value) { return Host2LittleEndian((uint32_t) value); }
  inline int32_t LittleEndian2Host(int32_t value) { return LittleEndian2Host((uint32_t) value); }

  inline int64_t Host2BigEndian(int64_t value) { return Host2BigEndian((uint64_t) value); }
  inline int64_t BigEndian2Host(int64_t value) { return BigEndian2Host((uint64_t) value); }
  inline int64_t Host2LittleEndian(int64_t value) { return Host2LittleEndian((uint64_t) value); }
  inline int64_t LittleEndian2Host(int64_t value) { return LittleEndian2Host((uint64_t) value); }

  inline uint8_t Host2Target(endian_type target_endian, uint8_t value)
  {
    return (target_endian == E_BIG_ENDIAN) ? Host2BigEndian(value) : Host2LittleEndian(value);
  }

  inline uint16_t Host2Target(endian_type target_endian, uint16_t value)
  {
    return (target_endian == E_BIG_ENDIAN) ? Host2BigEndian(value) : Host2LittleEndian(value);
  }

  inline uint32_t Host2Target(endian_type target_endian, uint32_t value)
  {
    return (target_endian == E_BIG_ENDIAN) ? Host2BigEndian(value) : Host2LittleEndian(value);
  }

  inline uint64_t Host2Target(endian_type target_endian, uint64_t value)
  {
    return (target_endian == E_BIG_ENDIAN) ? Host2BigEndian(value) : Host2LittleEndian(value);
  }

  inline uint8_t Target2Host(endian_type target_endian, uint8_t value)
  {
    return (target_endian == E_BIG_ENDIAN) ? BigEndian2Host(value) : LittleEndian2Host(value);
  }

  inline uint16_t Target2Host(endian_type target_endian, uint16_t value)
  {
    return (target_endian == E_BIG_ENDIAN) ? BigEndian2Host(value) : LittleEndian2Host(value);
  }

  inline uint32_t Target2Host(endian_type target_endian, uint32_t value)
  {
    return (target_endian == E_BIG_ENDIAN) ? BigEndian2Host(value) : LittleEndian2Host(value);
  }

  inline uint64_t Target2Host(endian_type target_endian, uint64_t value)
  {
    return (target_endian == E_BIG_ENDIAN) ? BigEndian2Host(value) : LittleEndian2Host(value);
  }

  inline int8_t Host2Target(endian_type target_endian, int8_t value) { return Host2Target(target_endian, (uint8_t) value); }
  inline int16_t Host2Target(endian_type target_endian, int16_t value) { return Host2Target(target_endian, (uint16_t) value); }
  inline int32_t Host2Target(endian_type target_endian, int32_t value) { return Host2Target(target_endian, (uint32_t) value); }
  inline int64_t Host2Target(endian_type target_endian, int64_t value) { return Host2Target(target_endian, (uint64_t) value); }

  inline int8_t Target2Host(endian_type target_endian, int8_t value) { return Host2Target(target_endian, (uint8_t) value); }
  inline int16_t Target2Host(endian_type target_endian, int16_t value) { return Host2Target(target_endian, (uint16_t) value); }
  inline int32_t Target2Host(endian_type target_endian, int32_t value) { return Host2Target(target_endian, (uint32_t) value); }
  inline int64_t Target2Host(endian_type target_endian, int64_t value) { return Host2Target(target_endian, (uint64_t) value); }

} // end of namespace simsoc


#endif

