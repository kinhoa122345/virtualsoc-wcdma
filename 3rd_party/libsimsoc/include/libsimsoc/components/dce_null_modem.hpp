//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef DCE_NULL_MODEM_HPP
#define DCE_NULL_MODEM_HPP

#include "libsimsoc/module.hpp"
#include "libsimsoc/interfaces/RS232.hpp"

namespace simsoc {

class NullModem: public Module,
                 public MultiRS232_DCE {
public:
  MultiRS232_DCE_Port dce_0, dce_1;
  AbstractRS232_DTE *dte_0, *dte_1;

  NullModem(sc_core::sc_module_name name);

  void bind(AbstractRS232_DTE *dte, unsigned int id);

  void end_of_elaboration();

  void send(uint8_t c, unsigned int id);
  void set_rts(bool rts_signal, unsigned id);
  void set_dtr(bool dtr_signal, unsigned id);
};

} // namespace simsoc

#endif //DCE_NULL_MODEM_HPP
