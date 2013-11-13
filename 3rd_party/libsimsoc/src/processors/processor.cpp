//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifdef HAVE_CONFIG_H
# include <libsimsoc/config.h>
#endif

#include <libsimsoc/processors/processor.hpp>
#include <libsimsoc/tools/debugger/debugger.hpp>
#include <libsimsoc/processors/llvm_gen_parameters.hpp>

#include <signal.h>

using namespace sc_core;

namespace simsoc {

#ifdef HAVE_LLVM
  ParameterInt Processor::simulation_mode("processor","-DT",
                                       "dynamic translation mode (0, 1, 2, or 3)",2);
#else
  ParameterInt Processor::simulation_mode("processor","-DT",
                     "dynamic translation mode (0, 1, 2, or 3 [3 requires LLVM])",2);
#endif

  static ParameterStrQueue stat_files("processor","-stat",
                                      "write statistics to this file");
  static ParameterBool debug_mode("processor","-d",
                                  "enable debug mode");
  static ParameterUintQueue stack_pointers("processor","-sp",
                                           "intialize stack pointer to this value",
                                           0);
  static ParameterInt 
  instruction_quantum("processor","-iq",
          "number of instructions (or blocks when DT>1) executed before yielding",256);
  static ParameterInt 
  instruction_time("processor","-it",
          "(SystemC) time per instruction (or block when DT>1) (in nanoseconds)",10);


  Processor::Processor(sc_core::sc_module_name nm, Architecture arch):
    ProcessorBase(nm,arch),
    stat_file(stat_files.front()),
    initial_sp(stack_pointers.front()),
    something_pending(false), it_pending(false),
    mode(static_cast<SimulationMode>(simulation_mode.get())),
    dt3_threshold(DT3_threshold.get()),
    iquantum(instruction_quantum.get()),
    tquantum(sc_time(instruction_time.get(),SC_NS)*iquantum),
    m_debugger(NULL)
  {
    stat_files.pop_front();
    stack_pointers.pop_front();
  }

  Processor::~Processor() {
    if (m_debugger)
      delete m_debugger;
  }

  //--------------------------------------------------------------------
  // SystemC Hooks
  //--------------------------------------------------------------------
  void Processor::end_of_elaboration() {
    if (initial_sp)
      set_sp(initial_sp);

    if (debug_mode.get()) {
      DebugInterface *dbi = create_dbi();

      if (dbi == NULL) {
        warning()
          << "debugger interface not supported by given architecture"
          << std::endl;
      } else {
#if defined(DEBUG_GDB_PROTOCOL)
        this->m_debugger = new Debugger(*dbi, this);
#else
        this->m_debugger = new Debugger(*dbi);
#endif

        if (this->mode != INTERPRET) {
          warning()
            << "Lowering DT mode to [INTERPRET] when remote debugging is requested"
            << std::endl;
          this->mode = INTERPRET;
        }
      }
    }
  }

  // ------------------------------------------------------------------
  // Debugger routines
  // ------------------------------------------------------------------
  DebugInterface* Processor::create_dbi() {
    return NULL;
  }

  void Processor::end_of_simulation () {
    if (m_debugger)
      m_debugger->stop();
  }

  void Processor::debugger_cycle() {
    if (!m_debugger)
      return ;

    if (!m_debugger->active()) {
      warning() << "Waiting for GDB client" << std::endl;
      m_debugger->start();
      warning() << "GDB client connected" << std::endl;
    }
    m_debugger->cycle();
  }

} //namespace simsoc
