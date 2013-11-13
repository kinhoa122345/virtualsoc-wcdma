//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "libsimsoc/components/ti_am1x_mdio.hpp"

namespace simsoc  {
namespace TI_AM1x {

  // ------------------------------------------------------------------
  MDIO::MDIO(sc_core::sc_module_name name)
    :TI_AM1x_core<MDIO>(name, this)
  {}

  // ------------------------------------------------------------------
  MDIO::~MDIO() {}

  // ------------------------------------------------------------------
  uint32_t MDIO::read_word(uint32_t address) {
    warning()
      << "reading at address " << std::hex << address
      << std::endl;
    return 0;
  }

  // ------------------------------------------------------------------
  void MDIO::write_word(uint32_t address, uint32_t data) {
    warning()
      << "writing " << std::hex << data
      << " at address " << std::hex << address
      << std::endl;
  }

} // namespace TI_AM1x
} // namespace simsoc
