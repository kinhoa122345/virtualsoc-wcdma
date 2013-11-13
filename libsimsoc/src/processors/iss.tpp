//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

// Implementation of "iss.hpp"
// This file is included only by "iss.cpp"

#ifdef HAVE_CONFIG_H
# include "libsimsoc/config.h"
#endif

#include "iss.hpp"
#include "libsimsoc/tools/debugger/debugger.hpp"

using namespace std;

namespace simsoc {

  template <typename P>
  bool ISS<P>::elf_bind_flag = false;

  template <typename P>
  const sc_core::sc_time ISS<P>::PER_INSTRUCTION_TIME =
    sc_core::sc_time(10,sc_core::SC_NS);

#ifdef PARALLEL
#ifdef AFFINITY_CPU

  template <typename P>
  pthread_mutex_t ISS<P>::affinity_lock = PTHREAD_MUTEX_INITIALIZER;

  template <typename P>
  int ISS<P>::affinityId = 0;

  template <typename P>
  int ISS<P>::processorNum = 1;//processor in the real machine
#endif
#endif // PARALLEL

  /*
   * ISS constructor
   */

  template <typename P>
  ISS<P>::ISS(sc_core::sc_module_name nm,
              P *processor,
              int _processorId,
              bool _holdoff_processor):
    Module(nm),
    processor_id(_processorId),
    holdoff_processor(_holdoff_processor),
    proc(*processor),
    nb_instr(0)
  {
    assert(processor);
    info() << "Constructing ISS of processor " <<proc.name() <<endl;

#ifdef PARALLEL
#ifdef AFFINITY_CPU
    processorNum = sysconf(_SC_NPROCESSORS_CONF);
#endif
    SC_THREAD(proxy);//yield cpu cyclic for many device

    if (pthread_mutex_init(&syn_start, NULL) != 0) {
      perror("ISS::syn_start mutex_init failed");
      exit(-1);
    }
    pthread_mutex_lock(&syn_start);
    if (pthread_create(&tid, NULL, pthread_helper, this) != 0) {
      perror("ISS<P,I>::pthread_helper create failed");
      exit(-1);
    }
    pthread_detach(tid);
#else
    SC_THREAD(compute);
    sensitive << boot_event;
    if (holdoff_processor)
      dont_initialize();
#endif
    debug() << "end of constructor" << endl;
  }


  // ISS destructor
  template<typename P>
  ISS<P>::~ISS() {
#ifdef PARALLEL
    pthread_mutex_destroy(&syn_start);
#endif
    if (nb_instr>0)
      info() <<dec <<nb_instr <<" instructions executed\n";
  }

  // ISS thread
  template <typename P>
  void ISS<P>::compute() {
    if (proc.mode>proc.max_mode_available()) {
      SimulationMode old = proc.mode;
      proc.mode = proc.max_mode_available();
      warning() <<"Mode " <<dec <<old <<" is not available for this architecture;"
                <<" switch back to mode " <<proc.mode <<endl;
    }
    switch(proc.mode) {
    case INTERPRET :
      interpret();
      break;
    case INTERPRET_CACHE:
    case DYN_TRANS_SPEC:
    case DYN_COMP:
      dyntrans();
      break;
    default:
      error() << "Simulation mode not yet implemented\n" ;
    }
  }

  // Interpret instructions of class I for processor of class P
  template <typename P>
  void ISS<P>::interpret() {
    info() << "starting " << proc.get_arch() << " interpreter;"
           << " bus size is " <<dec << proc.bus_width() <<hex << " bits"
           << endl;

    typename P::Instruction *instr;

    int iquantum = proc.iquantum;

    this->proc.debugger_cycle();

    while (true) {
      try {
        while(true) {
          instr = proc.fetch_instruction();
          debug() <<"execute: \t" <<*instr <<endl;

          if (--iquantum<=0) {
            debug() <<"enter wait(" <<proc.tquantum <<").\n";
            iquantum = proc.iquantum;
            wait(proc.tquantum);
          }
          ++nb_instr;
          instr->exec(proc);
          delete instr;

          proc.hook();//do some arch special

          if (proc.is_something_pending()) {
            proc.reset_pending();
            //       check_memory_error();
            if (proc.is_it_pending())
              proc.raise_interrupt();
          }

          this->proc.debugger_cycle();
        }
      } catch (ISS_Exception &e) {
        debug() <<"processor exception catched: " <<e.what() <<".\n";
      }
    }
  }

  /*
   * Interpret instructions of class I for processor of class P
   * Same as above except that instructions are cached
   */
  template <typename P>
  void ISS<P>::dyntrans() {
    info() <<"Dynamic translation is enabled" <<endl;
    typename P::Instruction *instr;

    int iquantum = proc.iquantum;

    while (true) {
      try {
        while(true) {
          //assert(!proc.is_something_pending());
          instr = proc.fetch_instr_from_cache();
          if (proc.do_statistics())
            proc.update_statistics(instr);
          ++nb_instr;

          debug() <<"execute: \t" <<*instr <<endl;
          instr->exec(proc);

          proc.hook();//do some arch special
          if (--iquantum<=0) {
            debug() <<"enter wait(" <<proc.tquantum <<").\n";
            iquantum = proc.iquantum;
            wait(proc.tquantum);
          }

          if (proc.is_something_pending()) {
            proc.reset_pending();
            //       check_memory_error();
            if (proc.is_it_pending())
              proc.raise_interrupt();
          }
        }
      } catch (ISS_Exception &e) {
        info() <<"processor exception catched: " <<e.what() <<".\n";
      }
    }
  }

  template <typename P>
  void ISS<P>::end_of_elaboration() {
    debug() << "end of elaboration for " << proc.get_arch()
            << " ISS in mode " <<dec << (int) proc.mode
            << endl;
#ifdef PARALLEL
    //mpc8641d: processor1 is boot holdoff, and will release by processor0 at MCM
    if(!holdoff_processor)
      release_processor();
#endif
  }

} // simsoc namespace
