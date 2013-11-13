//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef IT_STUB_HPP_
#define IT_STUB_HPP_

#include "libsimsoc/interfaces/tlm.hpp"
#include "libsimsoc/interfaces/tlm_signal.hpp"
#include "libsimsoc/module.hpp"

namespace simsoc {

class IT_Stub: public Module,
               public SignalTarget<bool> {
public:
  SignalTargetPort<bool> it_port;

  IT_Stub(sc_core::sc_module_name name);

  void signal(bool);
};

} // namespace simsoc

#endif /*IT_STUB_HPP_*/
