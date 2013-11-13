//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "libsimsoc/processors/arm_v6/arm_v6_debugger.hpp"
#include "libsimsoc/processors/arm_v6/arm_v6_processor.hpp"
#include "libsimsoc/processors/iss_exception.hpp"
#include "libsimsoc/io.hpp"

#include <vector>
#include <algorithm>
#include <inttypes.h>

namespace simsoc {

  // ------------------------------------------------------------------
  ARMv6_Debugger::ARMv6_Debugger(ARMv6_Processor &processor)
    :m_proc(processor)
  {}

  // ------------------------------------------------------------------
  bool ARMv6_Debugger::add_breakpoint(uint64_t address64, uint64_t length) {
    if ((address64 >> 32) || (address64 & 0x3))
      return false;

    uint32_t address = (uint32_t) address64;

    if (m_traps.find(address) != m_traps.end())
      return true;

    const uint32_t instruction = m_proc.mmu.read_word(address);

    try {
      m_proc.mmu.write_word(address, TRAP_EABI_INSTRUCTION);
    } catch (ISS_Exception) {
      return false;
    }
    m_traps[address] = instruction;

    return true;
  }

  // ------------------------------------------------------------------
  bool ARMv6_Debugger::del_breakpoint(uint64_t address64, uint64_t length) {
    if ((address64 >> 32) || (address64 & 0x3))
      return false;

    uint32_t address = (uint32_t) address64;
    traps_t::iterator instruction = m_traps.find(address);

    if (instruction == m_traps.end())
      return false;

    try {
      m_proc.mmu.write_word(address, instruction->second);
    } catch (ISS_Exception) {
      return false;
    }
    m_traps.erase(instruction);

    return true;
  }

  // ------------------------------------------------------------------
  bool ARMv6_Debugger::readregs(bytes_t &result) {
    Marshaller marshaller(result, Marshaller::ED_LITTLE);

    for (size_t i = 0; i < 16; ++i) {
      uint32_t reg = m_proc.slv6_proc.regs[i];

      if (i == 15) reg -= 8; // FIXME: think about thumb mode
      marshaller.push_uint32(reg);
    }

    return true;
  }

  bool ARMv6_Debugger::readreg(size_t reg_num,bytes_t &result) {
    Marshaller marshaller(result, Marshaller::ED_LITTLE);

    if ( reg_num >= 0 && reg_num < 16) {
      uint32_t reg = m_proc.slv6_proc.regs[reg_num];

      if (reg_num == 15) reg -= 8; // FIXME: think about thumb mode
      marshaller.push_uint32(reg);
    }

    return true;
  }

  // ------------------------------------------------------------------
  size_t ARMv6_Debugger::read(uint64_t address64, size_t length, bytes_t &result) {
    if ((address64 >> 32))
      return false;

    tlm::tlm_generic_payload payload;

    result.resize(length);

    payload.set_command(tlm::TLM_READ_COMMAND);
    payload.set_streaming_width(1);
    payload.set_address(address64);
    payload.set_data_ptr(&result[0]);
    payload.set_data_length(length);

    unsigned rsize = m_proc.transport_dbg(0, payload);

    result.resize(rsize);

    return length;
  }

  // ------------------------------------------------------------------
  void ARMv6_Debugger::enable_traps () {
    traps_t::const_iterator it;

    for (it = m_traps.begin(); it != m_traps.end(); ++it) {
      try {
        m_proc.mmu.write_word(it->first, TRAP_EABI_INSTRUCTION);
      } catch (ISS_Exception) {}
    }
  }

  // ------------------------------------------------------------------
  void ARMv6_Debugger::disable_traps() {
    traps_t::const_iterator it;

    for (it = m_traps.begin(); it != m_traps.end(); ++it) {
      try {
        m_proc.mmu.write_word(it->first, it->second);
      } catch (ISS_Exception) {}
    }
  }
}
