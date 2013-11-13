//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#if !defined (LIBSIMSOC_TI_AM1X_EMAC_HPP__)
# define LIBSIMSOC_TI_AM1X_EMAC_HPP__

# include "libsimsoc/module.hpp"
# include "libsimsoc/interfaces/tlm.hpp"
# include "libsimsoc/interfaces/tlm_signal.hpp"

# include <inttypes.h>
# include <cstring>

namespace simsoc  {
namespace TI_AM1x {

  // ------------------------------------------------------------------
  class MDIO;
  class EMAC_MOD;
  class EMAC_CONTROL;

  // ------------------------------------------------------------------
  class EMAC {
    friend class MDIO;
    friend class EMAC_MOD;
    friend class EMAC_CONTROL;

  public:
    static const size_t NCHANNELS = 8;
    static const size_t NMACS     = 8;

  public:
    EMAC(const std::string& name);
    virtual ~EMAC();

  public:
    MDIO         &mdio        () { return *m_mdio; }
    EMAC_MOD     &emac_module () { return *m_emac_mod; }
    EMAC_CONTROL &emac_control() { return *m_emac_ctrl; }

  private:
    MDIO         *m_mdio;
    EMAC_MOD     *m_emac_mod;
    EMAC_CONTROL *m_emac_ctrl;

  private:
    EMAC(const EMAC&);            // GNI
    EMAC& operator=(const EMAC&); // GNI
  };

} // namespace TI_AM1x
} // namespace simsoc

#endif // !LIBSIMSOC_TI_AM1X_EMAC_HPP__
