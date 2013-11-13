//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef YIELD_HPP
#define YIELD_HPP

#include <systemc>
#include <inttypes.h>

namespace simsoc {

  const sc_core::sc_time YIELD_DURATION = sc_core::sc_time(10,sc_core::SC_US);
  inline void YIELD() {sc_core::wait(YIELD_DURATION);}

  // Must be a macro because of the return statment.
#define METHOD_YIELD() sc_core::next_trigger(YIELD_DURATION); return

} // namespace simsoc

#endif //YIELD_HPP
