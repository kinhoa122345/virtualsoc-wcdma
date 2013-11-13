//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef RS232_HPP
#define RS232_HPP

#include <libsimsoc/display.hpp>
#include <inttypes.h>
#include <iostream>

namespace simsoc {

// Data Terminal Equipment (DTE)
struct AbstractRS232_DTE {
  virtual ~AbstractRS232_DTE() {}
  virtual void receive(uint8_t c)=0; // non-blocking
  virtual void set_cts(bool cts_signal)=0; // non-blocking
  virtual void set_dsr(bool dsr_signal)=0; // non-blocking

  // optional:
  //  (functions below shall be called when the value of the signal changes)
  //   virtual data_carrier_detect() {} //DCD
  //   virtual ring_indicator() {}     //RI
  //   ...
};



// Data Circuit-terminating Equipment (DCE)
struct AbstractRS232_DCE {
  virtual ~AbstractRS232_DCE() {}
  virtual void bind(AbstractRS232_DTE*)=0;
  virtual void send(uint8_t c)=0; // non-blocking
  virtual void set_rts(bool value)=0; // non-blocking
  virtual void set_dtr(bool value)=0; // non-blocking
};

/******************************************************************************/
// for components with many DCE ports (see components/null_modem.[ch]pp for example)

struct MultiRS232_DCE {
  virtual ~MultiRS232_DCE() {}
  virtual void send(uint8_t c, unsigned int id)=0;
  virtual void set_rts(bool rts_signal, unsigned int id)=0;
  virtual void set_dtr(bool dtr_signal, unsigned int id)=0;
  virtual void bind(AbstractRS232_DTE*, unsigned int id)=0;
};

struct MultiRS232_DCE_Port: public AbstractRS232_DCE {
  static unsigned int num;
  MultiRS232_DCE *host;
  unsigned int id;
  MultiRS232_DCE_Port(MultiRS232_DCE *h, unsigned int n): host(h), id(n) {}
  // for vector initialization:
  MultiRS232_DCE_Port(MultiRS232_DCE *h): host(h), id(0) {num=0;}
  MultiRS232_DCE_Port(const MultiRS232_DCE_Port &mp): host(mp.host), id(num++) {}

  void bind(AbstractRS232_DTE *dte) {
    host->bind(dte,id);
  }

  void send(uint8_t c) {
    host->send(c,id);
  }
  void set_rts(bool rts_signal) {
    host->set_rts(rts_signal,id);
  }
  void set_dtr(bool dtr_signal) {
    host->set_dtr(dtr_signal,id);
  }
};

} // namespace simsoc

#endif //RS232_HPP
