//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#if !defined(LIBSIMSOC_I_GDB_HPP__)
# define LIBSIMSOC_I_GDB_HPP__

# include <inttypes.h>
# include <sys/types.h>
# include <vector>
# include <map>

# include <tlm.h>

namespace simsoc {

  class DebugInterface {
  public:
    virtual ~DebugInterface () { /* interface */ }

  public:
    typedef std::vector<uint8_t> bytes_t;

    virtual bool add_breakpoint(uint64_t address, uint64_t length) = 0;
    virtual bool del_breakpoint(uint64_t address, uint64_t length) = 0;

    virtual bool readregs(bytes_t &result) = 0;
    virtual bool readreg(size_t reg_num, bytes_t &result) = 0;
    virtual size_t read(uint64_t address, size_t length, bytes_t &result) = 0;

    virtual void enable_traps () = 0;
    virtual void disable_traps() = 0;
  };

  class BreakpointsTableExtension
    : public tlm::tlm_extension<BreakpointsTableExtension>
  {
  protected:
    std::map<uint32_t, uint32_t> m_breakpoints;
  };

}

#endif // !LIBSIMSOC_I_GDB_HPP__
