//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef ARM_V6_COPROC_HPP
#define ARM_V6_COPROC_HPP

#include <libsimsoc/module.hpp>
#include <inttypes.h>
#include <systemc>

namespace simsoc {

  class ARMv6_Processor;

  class ARMv6_Coprocessor: public Module {
  public:
    ARMv6_Coprocessor(sc_core::sc_module_name name, ARMv6_Processor *proc);
    virtual ~ARMv6_Coprocessor() {};

    // following functions return false if the instruction is not implemented
    // In such a case, the caller shall raise an undefined instruction exception
    
    virtual bool mcr(uint8_t opcode1, uint8_t opcode2,
                     uint32_t Rd_value, uint8_t CRn, uint8_t CRm) {
      return false;
    }

    virtual bool mrc(uint32_t &result, uint8_t opcode1, uint8_t opcode2,
                     uint8_t CRn, uint8_t CRm) {
      return false;
    }
    
    // TODO: other coprocessor instructions

  protected:
    ARMv6_Processor &processor;
  };

} // namespace simsoc

#endif // ARM_V6_COPROC_HPP
