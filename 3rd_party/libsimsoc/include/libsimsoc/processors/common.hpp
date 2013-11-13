//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef COMMON_HPP
#define COMMON_HPP

/*
 * This file contains definitions common to all architectures
 */

#include <iostream>
#include <inttypes.h>

namespace simsoc {

  typedef enum {INTERPRET=0,
                INTERPRET_CACHE=1,
                DYN_TRANS_SPEC=2,
                DYN_COMP=3 } SimulationMode;

  /*
   * This type is the return status from executing a pseudo instruction.
   * It contains generic status information. Some return values
   * may be specific to an architecture...
   * The instructions are split in two groups: the OK group and the special group
   * For the OK group, the next instruction to execute is the next pseudo
   * hence only increment the pointer with ++
   * For special instructions, the next instruction has to be calculated.
   */

  typedef enum {OK=0, BRANCH=1, FORWARD_BRANCH=2, BACK_BRANCH=3, BRANCH_SAME_PAGE=4,
                LONG_BRANCH=5, CALL=6, RETURN=7 ,
                SPECIAL=8, NEXT_PAGE=9, LAST_PSEUDO=10 } PseudoStatus;

  // table of strings with names
  extern const char * PSEUDOSTATUS_NAMES[];
  std::ostream& operator<<(std::ostream &os, const PseudoStatus& s);

  typedef enum { ARM=0, POWERPC=1, MIPS=2, LAST_ARCH=3 } Architecture;
  typedef enum { MIPS32=0,MIPS64=1} MIPS_SpecFlag;

  // table of strings with names for printing
  extern const char * ARCH_NAMES[];
  std::ostream& operator<<(std::ostream &os, const Architecture &a);

  // Define a template functions for sign extension
  typedef uint32_t BUS32;
  typedef uint64_t BUS64;

  template <typename word_t>
  word_t sign_ext(uint8_t);

  template <typename word_t>
  word_t sign_ext(uint16_t);

  template <typename word_t>
  word_t sign_ext(uint32_t);

  template <>
  inline uint32_t sign_ext<uint32_t>(uint8_t a) {
    return static_cast<uint32_t>(static_cast<int32_t>(static_cast<int8_t>(a)));
  }
  template <>
  inline uint32_t sign_ext<uint32_t>(uint16_t a) {
    return static_cast<uint32_t>(static_cast<int32_t>(static_cast<int16_t>(a)));
  }
  template <>
  inline uint32_t sign_ext<uint32_t>(uint32_t a) {return a;}

  template <>
  inline uint64_t sign_ext<uint64_t>(uint8_t a) {
    return static_cast<uint64_t>(static_cast<int64_t>(static_cast<int8_t>(a)));
  }
  template <>
  inline uint64_t sign_ext<uint64_t>(uint16_t a) {
    return static_cast<uint64_t>(static_cast<int64_t>(static_cast<int16_t>(a)));
  }
  template <>
  inline uint64_t sign_ext<uint64_t>(uint32_t a) {
    return static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(a)));
  }

} // namespace simsoc

#endif // COMMON_HPP
