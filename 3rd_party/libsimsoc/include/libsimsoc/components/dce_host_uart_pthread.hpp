//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef DCE_HOST_UART_PTHREAD_HPP
#define DCE_HOST_UART_PTHREAD_HPP

#include "libsimsoc/module.hpp"
#include <termios.h>
#include "libsimsoc/interfaces/RS232.hpp"

namespace simsoc {

class DCE_HostUART_PTHREAD: public Module,
                            public AbstractRS232_DCE
{
public:
  AbstractRS232_DTE *dte;

  pthread_t uart_thread;
  pthread_mutex_t input_mutex;
  pthread_cond_t input_cond;
  bool simulation_started;

protected:
  int fd;

  struct termios hostuart_tios;

public:
  SC_HAS_PROCESS(DCE_HostUART_PTHREAD);
  DCE_HostUART_PTHREAD(sc_core::sc_module_name name);
  ~DCE_HostUART_PTHREAD();
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

#endif //DCE_HOST_UART_PTHREAD_HPP
