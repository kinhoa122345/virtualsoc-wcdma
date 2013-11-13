//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "dce_null_modem.hpp"
#include "libsimsoc/display.hpp"
using namespace sc_core;
using namespace std;

namespace simsoc {

NullModem::NullModem(sc_module_name name):
  Module(name), dce_0(this,0), dce_1(this,1), dte_0(NULL), dte_1(NULL)
{}

void NullModem::bind(AbstractRS232_DTE *dte, unsigned int id) {
  if (id==0)
    dte_0 = dte;
  else if (id==1)
    dte_1 = dte;
  else
    UNREACHABLE;
}

void NullModem::end_of_elaboration() {
  if (!dte_0||!dte_1) {
    error() <<"the DTE interfaces are not connected" <<endl;
    exit(3);
  }
}

void NullModem::send(uint8_t c, unsigned int id) {
  if (id==0) {
    debug() <<"character " <<c <<" (" <<(int) c <<") transmitted from uart 0 to uart 1" <<endl;
    dte_1->receive(c);
  } else {
    debug() <<"character " <<c <<" (" <<(int) c <<") transmitted from uart 1 to uart 0" <<endl;
    dte_0->receive(c);
  }
}

void NullModem::set_rts(bool rts_signal, unsigned int id) {
  if (id==0) {
    info() <<"RTS0 = CTS1 = " <<dec <<rts_signal <<endl;
    dte_1->set_cts(rts_signal);
  } else {
    info() <<"RTS1 = CTS0 = " <<dec <<rts_signal <<endl;
    dte_0->set_cts(rts_signal);
  }
}

void NullModem::set_dtr(bool dtr_signal, unsigned int id) {
  if (id==0) {
    info() <<"DTR0 = DSR1 = " <<dec <<dtr_signal <<endl;
    dte_1->set_dsr(dtr_signal);
  } else {
    info() <<"DTR1 = DSR0 = " <<dec <<dtr_signal <<endl;
    dte_0->set_dsr(dtr_signal);
  }
}

} // namespace simsoc
