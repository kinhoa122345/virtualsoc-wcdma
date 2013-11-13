//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef ISS_HPP
#define ISS_HPP

#include "processor.hpp"
#include "iss_exception.hpp"
#include <libsimsoc/translation_page.hpp>
#include <string>

#ifdef PARALLEL

#include <pthread.h>

#define AFFINITY_CPU//you can define it to get better performance on multi-core machine

#ifdef AFFINITY_CPU

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <unistd.h>
#include <sched.h>
#endif // AFFINITY_CPU

#endif // PARALLEL

namespace simsoc {

  template <typename P>
  class ISS : public Module {
    static const sc_core::sc_time PER_INSTRUCTION_TIME;

  protected:
    int processor_id;
    bool holdoff_processor; //is freeze this processor, used by mpc8641d
    static bool elf_bind_flag;

  public:
    P &proc;
    uint64_t nb_instr; // correct only in mode D0 and D1

#ifdef PARALLEL
    void freeze_processor() { pthread_mutex_lock(&syn_start); };
    void release_processor() { pthread_mutex_unlock(&syn_start); };
    //for thread data...
#ifdef AFFINITY_CPU
    static pthread_mutex_t affinity_lock;
    static int affinityId; //used by allocate cpu
    static int processorNum;//processor in the real machine
#endif
    pthread_t tid;
    pthread_mutex_t syn_start;

    static void* pthread_helper(void* arg) {
#ifdef AFFINITY_CPU
      cpu_set_t mask;
      int tmp;

      pthread_mutex_lock(&affinity_lock);
      tmp = affinityId;
      affinityId++;
      pthread_mutex_unlock(&affinity_lock);

      if(tmp < processorNum) {
        CPU_ZERO(&mask);
        CPU_SET(tmp, &mask);//allocate processor_id to cpu processor_id
        if(sched_setaffinity(0, sizeof(cpu_set_t), &mask) == -1)
          perror("warn: pthread setaffinity failed");
      }
#endif
      ISS* p = (ISS *)arg;
      p->freeze_processor();
      p->compute();
      return 0;
    }
    void proxy() {while(1) YIELD();}//yield cpu for others
#else
    //sc_core::sc_event it_event;
    sc_core::sc_event boot_event;
#endif

    SC_HAS_PROCESS(ISS);
    ISS(sc_core::sc_module_name nm,
         P *processor,
         int processor_id = 0,
         bool holdoff_processor = false); // you can freeze some processor
                                          // using this parameter
    ~ISS();

    void compute ();
    void interpret();
    void dyntrans();
    void end_of_elaboration();

  protected:
    void _debugger_cycle();
  };

} // namespace simsoc

// We do not include "iss.tpp" here,
// because the user can only use a restricted number of parameter values.
// Code for these parameter values is created in "iss.cpp".

#endif // ISS_HPP
