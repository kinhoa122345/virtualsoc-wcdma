//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef DCE_STUB_HPP
#define DCE_STUB_HPP

#include "libsimsoc/module.hpp"
#include "libsimsoc/interfaces/RS232.hpp"

namespace simsoc {

class DCE_Stub: public Module,
                public AbstractRS232_DCE {
public:
  DCE_Stub(sc_core::sc_module_name name);
  void bind(AbstractRS232_DTE *dte_) {}
  void send(uint8_t c);
  void set_rts(bool rts_signal);
  void set_dtr(bool dtr_signal);
};

} // namespace simsoc

#endif //DCE_STUB_HPP
