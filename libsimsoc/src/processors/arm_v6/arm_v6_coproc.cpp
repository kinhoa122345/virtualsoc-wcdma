//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "arm_v6_coproc.hpp"
#include "arm_v6_processor.hpp"
#include <cassert>

using namespace sc_core;

namespace simsoc {

  ARMv6_Coprocessor::ARMv6_Coprocessor(sc_module_name name,
                                       ARMv6_Processor *proc):
    Module(name), processor(*proc)
  {
    assert(proc);
  }

  bool slv6_MCR_send(struct SLv6_Processor *proc, uint8_t n,
                     uint8_t opcode_1, uint8_t opcode_2,
                     uint8_t CRn, uint8_t CRm, uint32_t Rd) {
    const bool defined =
      proc->proc_ptr->coprocessors[n]->mcr(opcode_1,opcode_2,Rd,CRn,CRm);
    if (!defined) exec_undefined_instruction(proc,NULL);
    return defined;
  }

  bool slv6_MCRR_send(struct SLv6_Processor *proc,
                      uint8_t n, uint32_t x) {
    TODO("MCRR send");
  }

  bool slv6_MRRC_first_value(struct SLv6_Processor *proc,
                             uint32_t *result, uint8_t n) {
    TODO("MRRC fisrt value");
  }

  bool slv6_MRRC_second_value(struct SLv6_Processor *proc,
                              uint32_t *result, uint8_t n) {
    TODO("MRRC second value");
  }

  bool slv6_MRC_value(struct SLv6_Processor *proc,
                      uint32_t *result, uint8_t n,
                      uint8_t opcode_1, uint8_t opcode_2,
                      uint8_t CRn, uint8_t CRm) {
    const bool defined =
      proc->proc_ptr->coprocessors[n]->mrc(*result,opcode_1,opcode_2,CRn,CRm);
    if (!defined) exec_undefined_instruction(proc,NULL);
    return defined;
  }

} // namespace simsoc
