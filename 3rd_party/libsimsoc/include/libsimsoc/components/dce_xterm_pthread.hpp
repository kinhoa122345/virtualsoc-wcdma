//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef DCE_XTERM_PTHREAD_HPP
#define DCE_XTERM_PTHREAD_HPP

#include <pthread.h>
#include "libsimsoc/module.hpp"
#include "libsimsoc/interfaces/RS232.hpp"

namespace simsoc {

class DCE_Xterm_PTHREAD: public Module,
                         public AbstractRS232_DCE
{
public:
  static bool wait_before_close;

  pthread_t uart_thread;
  pthread_mutex_t input_mutex;
  pthread_cond_t input_cond;
  bool simulation_started;

  AbstractRS232_DTE *dte;

protected:
  int r_descriptor;
  int w_descriptor;
  int filedesA[2];
  int filedesB[2];

public:

  SC_HAS_PROCESS(DCE_Xterm_PTHREAD);
  DCE_Xterm_PTHREAD(sc_core::sc_module_name name, const char *path = NULL);
  ~DCE_Xterm_PTHREAD();
  void bind(AbstractRS232_DTE *dte_) {dte = dte_;}
  void end_of_elaboration(); // called by the SystemC kernel
  static void* compute_pthread(void *);
  // for protocol RS-232 DCE
  void send(uint8_t c);
  void set_rts(bool rts_signal);
  void set_dtr(bool dtr_signal);

protected:
  void compute();
};

} // namespace simsoc

#endif //DCE_XTERM_PTHREAD_HPP
