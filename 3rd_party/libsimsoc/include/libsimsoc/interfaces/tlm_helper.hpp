//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef TLM_HELPER_HPP
#define TLM_HELPER_HPP

#include <tlm.h>
#include <inttypes.h>

namespace simsoc {

  inline void set_payload(tlm::tlm_generic_payload &pl,
                          const uint64_t addr,
                          uint8_t *data,
                          const unsigned int length) {
    pl.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
    pl.set_address(addr);
    pl.set_data_ptr(data);
    pl.set_data_length(length);
    pl.set_dmi_allowed(false);
  }

} // namespace simsoc

#endif // TLM_HELPER_HPP
