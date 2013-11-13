//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "libsimsoc/components/ti_am1x_rtc.hpp"

// --------------------------------------------------------------------
namespace simsoc  {
namespace TI_AM1x {

  // ------------------------------------------------------------------
  RTC::RTC(sc_core::sc_module_name name)
    :TI_AM1x_core<RTC>(name, this)
  {}

  // ------------------------------------------------------------------
  RTC::~RTC() {}

  // ------------------------------------------------------------------
  uint32_t RTC::read_word(uint32_t address) {
    debug()
      << "reading at address " << std::hex << address
      << std::endl;
    return 0;
  }

  // ------------------------------------------------------------------
  void RTC::write_word(uint32_t address, uint32_t value) {
    debug()
      << "writing [" << std::hex << value
      << "] at address [" << std::hex << address
      << "]" << std::endl;
  }

} // namespace TI_AM1x
} // namespace simsoc
