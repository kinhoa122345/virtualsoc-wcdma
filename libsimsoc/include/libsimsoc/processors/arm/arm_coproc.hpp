//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef ARM_COPROC_HPP
#define ARM_COPROC_HPP

#include <libsimsoc/module.hpp>
#include <inttypes.h>
#include <systemc>

namespace simsoc {

class ARM_Processor;

class ARM_Coprocessor: public Module
{
public:
  ARM_Coprocessor(sc_core::sc_module_name name, ARM_Processor *proc);
  virtual ~ARM_Coprocessor() {};

  virtual void cdp(uint8_t opcode1, uint8_t opcode2,
                   uint8_t CRd, uint8_t CRn, uint8_t CRm);

  virtual void cdp2(uint8_t opcode1, uint8_t opcode2,
                    uint8_t CRd, uint8_t CRn, uint8_t CRm);

  virtual void ldc(bool l, uint8_t CRd, bool p, bool u,
                   uint32_t Rn_value, bool w, uint8_t offset);

  virtual void ldc2(bool l, uint8_t CRd, bool p, bool u,
                    uint32_t Rn_value, bool w, uint8_t offset);

  virtual void stc(bool l, uint8_t CRd, bool p, bool u,
                   uint32_t Rn_value, bool w, uint8_t offset);

  virtual void stc2(bool l, uint8_t CRd, bool p, bool u,
                    uint32_t Rn_value, bool w, uint8_t offset);

  virtual void mcr(uint8_t opcode1, uint8_t opcode2,
                   uint32_t Rd_value, uint8_t CRn, uint8_t CRm);

  virtual void mcr2(uint8_t opcode1, uint8_t opcode2,
                    uint32_t Rd_value, uint8_t CRn, uint8_t CRm);

  virtual uint32_t mrc(uint8_t opcode1, uint8_t opcode2,
                       uint8_t CRn, uint8_t CRm);

  virtual uint32_t mrc2(uint8_t opcode1, uint8_t opcode2,
                        uint8_t CRn, uint8_t CRm);

protected:
  ARM_Processor &processor;
};

} // namespace simsoc

#endif //ARM_COPROC_HPP
