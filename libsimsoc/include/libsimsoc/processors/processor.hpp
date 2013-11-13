//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

// Base class for the processors using the DT0/DT1/DT2 mechanism.

#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP

#include "processor_base.hpp"
#include "libsimsoc/interfaces/dmi.hpp"
#include "libsimsoc/translation_page.hpp"
#include <tlm_h/tlm_sockets/tlm_initiator_socket.h>
#include <tlm_h/tlm_sockets/tlm_target_socket.h>

#include <stdio.h>
using namespace std;

namespace simsoc {

// forward declaration
class DebugInterface;
class Debugger;

class Processor: public ProcessorBase {

protected:
  const char *stat_file;
  const uint64_t initial_sp;

protected:
  bool something_pending; // some event happened
  bool it_pending; // an interrupt has occurred

public:
  static ParameterInt simulation_mode;
  
  SimulationMode mode;
  size_t dt3_threshold;
  const int iquantum;
  const sc_core::sc_time tquantum;

  Processor(sc_core::sc_module_name name, Architecture arch);

  virtual ~Processor ();

  virtual const TranslationPage *get_current_page() const = 0;
  virtual SimulationMode max_mode_available() const = 0;

  // statistics computation:
  bool do_statistics() const {return stat_file[0];}
  virtual void write_statistics(std::ostream& os = std::cout) = 0;
  virtual void read_statistics(std::istream& is) =0;

  virtual void raise_interrupt() =0;

  inline void set_something_pending() { something_pending = true; }
  inline void set_it_pending () { it_pending = true; }

  // SystemC hooks
  void end_of_elaboration();    // Initialize debugger
  void end_of_simulation();     // Finalize debugger

  // real methods
  inline bool is_something_pending() const {return something_pending;}
  inline bool is_it_pending() const {return it_pending;}
  inline void reset_pending() {something_pending = false;}
  inline void it_ack() {it_pending = false;}

public:
  // Debugger entry point
  virtual DebugInterface* create_dbi();

  Debugger* debugger() { return m_debugger; }
  void debugger_cycle();

protected:
  Debugger *m_debugger;
};

} // namespace simsoc

#endif //PROCESSOR_HPP
