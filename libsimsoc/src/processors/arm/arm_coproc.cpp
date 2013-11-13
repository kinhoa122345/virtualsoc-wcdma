//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "arm_coproc.hpp"
#include "libsimsoc/processors/arm/arm_processor.hpp"

using namespace sc_core;

namespace simsoc {

ARM_Coprocessor::ARM_Coprocessor(sc_module_name name, ARM_Processor *proc):
  Module(name), processor(*proc)
{
  assert(proc);
}

void ARM_Coprocessor::cdp(uint8_t opcode1, uint8_t opcode2,
                          uint8_t CRd, uint8_t CRn, uint8_t CRm) {
  processor.undefined_interrupt();
}

void ARM_Coprocessor::cdp2(uint8_t opcode1, uint8_t opcode2,
                           uint8_t CRd, uint8_t CRn, uint8_t CRm) {
  processor.undefined_interrupt();
}

void ARM_Coprocessor::ldc(bool l, uint8_t CRd, bool p, bool u,
                          uint32_t Rn_value, bool w, uint8_t offset) {
  processor.undefined_interrupt();
}

void ARM_Coprocessor::ldc2(bool l, uint8_t CRd, bool p, bool u,
                           uint32_t Rn_value, bool w, uint8_t offset) {
  processor.undefined_interrupt();
}

void ARM_Coprocessor::stc(bool l, uint8_t CRd, bool p, bool u,
                          uint32_t Rn_value, bool w, uint8_t offset) {
  processor.undefined_interrupt();
}

void ARM_Coprocessor::stc2(bool l, uint8_t CRd, bool p, bool u,
                           uint32_t Rn_value, bool w, uint8_t offset) {
  processor.undefined_interrupt();
}

void ARM_Coprocessor::mcr(uint8_t opcode1, uint8_t opcode2,
                          uint32_t Rd_value, uint8_t CRn, uint8_t CRm) {
  processor.undefined_interrupt();
}

void ARM_Coprocessor::mcr2(uint8_t opcode1, uint8_t opcode2,
                           uint32_t Rd_value, uint8_t CRn, uint8_t CRm) {
  processor.undefined_interrupt();
}

uint32_t ARM_Coprocessor::mrc(uint8_t opcode1, uint8_t opcode2,
                              uint8_t CRn, uint8_t CRm) {
  processor.undefined_interrupt();
  return 0;
}

uint32_t ARM_Coprocessor::mrc2(uint8_t opcode1, uint8_t opcode2,
                               uint8_t CRn, uint8_t CRm) {
  processor.undefined_interrupt();
  return 0;
}

} // namespace simsoc
