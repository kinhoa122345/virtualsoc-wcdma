//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

// Base class for all processors.
// Used for example by the ELF loader

#ifndef PROCESSOR_BASE_HPP
#define PROCESSOR_BASE_HPP

#include "common.hpp"
#include "libsimsoc/context.hpp"
#include "libsimsoc/module.hpp"
#include "libsimsoc/interfaces/tlm_signal.hpp"
#include <tlm_utils/multi_passthrough_target_socket.h>

namespace simsoc {

  class ProcessorBase: public Module {
    Architecture architecture; // simulated architecture

  public:
    ProcessorBase(sc_core::sc_module_name name, Architecture arch);
    virtual ~ProcessorBase() {};
    
    // Accessing the PC and general purpose registers
    virtual void set_pc(uint64_t addr) = 0;
    virtual uint64_t get_pc() const = 0;
    virtual void set_sp(uint64_t addr) = 0;
    virtual uint64_t get_gp_register(size_t n) const = 0;
    virtual void set_gp_register(size_t n, uint64_t data) = 0;

    // Setting the endianness. Exit with an error by default
    virtual void set_endian_little();
    virtual void set_endian_big();
    #define NO_MMU
    #ifndef NO_MMU
    // main port (bus side)
    virtual tlm::tlm_initiator_socket<> &get_rw_port() = 0;
    #endif

    // first interrupt port
    virtual SignalTargetPort<bool> &get_it_port() = 0;

    #ifndef NO_MMU
    // Debug port    
    tlm_utils::multi_passthrough_target_socket<ProcessorBase> debug_port;
    virtual unsigned int transport_dbg(int, tlm::tlm_generic_payload &payload) = 0;
    #endif

    inline Architecture get_arch() const {return architecture;}
  };

} // namespace simsoc

#endif // PROCESSOR_BASE_HPP
