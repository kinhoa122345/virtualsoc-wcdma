//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef DCE_HOST_UART_HPP
#define DCE_HOST_UART_HPP

#include <termios.h>
#include "libsimsoc/interfaces/RS232.hpp"
#include "libsimsoc/module.hpp"

namespace simsoc {

class DCE_HostUART: public Module,
                    public AbstractRS232_DCE {
public:
  AbstractRS232_DTE *dte;

protected:
  int fd;

  struct termios hostuart_tios;

public:
  SC_HAS_PROCESS(DCE_HostUART);
  DCE_HostUART(sc_core::sc_module_name name);
  ~DCE_HostUART();
  void bind(AbstractRS232_DTE *dte_) {dte = dte_;}
  void end_of_elaboration(); // called by the SystemC kernel

  // for protocol RS-232 DCE
  void send(uint8_t c);
  void set_rts(bool rts_signal);
  void set_dtr(bool dtr_signal);

protected:
  void compute();
};

} // namespace simsoc

#endif //DCE_HOST_UART_HPP
