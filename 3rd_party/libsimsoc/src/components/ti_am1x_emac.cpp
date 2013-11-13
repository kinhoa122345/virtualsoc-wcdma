//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "libsimsoc/components/ti_am1x_emac.hpp"
#include "libsimsoc/components/ti_am1x_mdio.hpp"
#include "libsimsoc/components/ti_am1x_emac_module.hpp"
#include "libsimsoc/components/ti_am1x_emac_control.hpp"

typedef sc_core::sc_module_name name_t;

namespace simsoc  {
namespace TI_AM1x {

  // ------------------------------------------------------------------
  EMAC::EMAC(const std::string& name)
    :m_mdio     (NULL)
    ,m_emac_mod (NULL)
    ,m_emac_ctrl(NULL)
  {
    std::string name_mdio      = name + "_MDIO";
    std::string name_emac_mod  = name + "_EMAC_MOD";
    std::string name_emac_ctrl = name + "_EMAC_CTRL";

    this->m_mdio      = new MDIO        (name_t(name_mdio     .c_str()));
    this->m_emac_mod  = new EMAC_MOD    (name_t(name_emac_mod .c_str()), *this);
    this->m_emac_ctrl = new EMAC_CONTROL(name_t(name_emac_ctrl.c_str()));
  }

  // ------------------------------------------------------------------
  EMAC::~EMAC() {
    delete this->m_mdio;
    delete this->m_emac_mod;
    delete this->m_emac_ctrl;
  }

} // namespace TI_AM1x
} // namespace simsoc
