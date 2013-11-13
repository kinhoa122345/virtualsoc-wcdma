//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef ARM_V6_DEBUGGER_HPP
#define ARM_V6_DEBUGGER_HPP

# include "libsimsoc/interfaces/gdb.hpp"

# include <inttypes.h>
# include <map>

namespace simsoc {

  class ARMv6_Processor;

  class ARMv6_Debugger: public DebugInterface {
  public:
    // FIXME: endianness ?
    static const uint32_t TRAP_EABI_INSTRUCTION = 0xE1200070;

  public:
    ARMv6_Debugger(ARMv6_Processor &processor);

  public:                       // DebugInterface
    virtual bool add_breakpoint(uint64_t address, uint64_t length);
    virtual bool del_breakpoint(uint64_t address, uint64_t length);

    virtual bool readregs(bytes_t &result);
    virtual bool readreg(size_t reg_num, bytes_t &result);
    virtual size_t read(uint64_t address, size_t length, bytes_t &result);

    virtual void enable_traps ();
    virtual void disable_traps();

  protected:
    typedef std::map<uint32_t, uint32_t> traps_t;

    ARMv6_Processor &m_proc;
    traps_t        m_traps;
  };

}

#endif // !ARM_V6_DEBUGGER_HPP
