//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#if !defined (LIBSIMSOC_TI_AM1X_EMAC_CONTROL_P_HPP__)
# define LIBSIMSOC_TI_AM1X_EMAC_CONTROL_P_HPP__

# include "libsimsoc/interfaces/tlm_signal.hpp"
# include "libsimsoc/components/ti_am1x_emac_control.hpp"
# include "libsimsoc/components/ti_am1x_emac_module_p.hpp"

namespace simsoc  {
namespace TI_AM1x {

  // ------------------------------------------------------------------
  class EMAC_CoreIntExInfos {
  public:
    EMAC_CoreIntExInfos() {
      this->reset();
    }

    void reset() {
      this->pulsed  = false;
      this->enabled = false;
      this->signal  = false;
    }

  public:
    typedef signals::SignalInitiatorPort_Level outsignal_t;

    bool        pulsed ;
    bool        enabled;
    outsignal_t signal ;
  };

  // ------------------------------------------------------------------
  class EMAC_CoreInterrupts: public EMAC_INTVEC_Base {
  public:
    EMAC_CoreIntExInfos& operator[](emac_intkind_e kind)
    { return m_signals[kind]; }

  public:
    void set_enabled_mask_R(emac_intkind_e kind, uint32_t mask) {
      m_enabled[kind] |= mask & masks[kind];
    }

    void clr_enabled_mask_R(emac_intkind_e kind, uint32_t mask) {
      m_enabled[kind] &= ~(mask & masks[kind]);
    }

    virtual void reset() {
      this->EMAC_INTVEC_Base::reset();
      for (size_t i = 0; i < 4; ++i)
        m_signals[i].reset();
    }

  protected:
    EMAC_CoreIntExInfos m_signals[4];
  };

  // ------------------------------------------------------------------
  struct EMAC_CONTROL_Private {
    EMAC_CoreInterrupts coreints[EMAC_CONTROL::NCOREGRPS];
  };

} // namespace TI_AM1x
} // namespace simsoc

#endif // !LIBSIMSOC_TI_AM1X_EMAC_CONTROL_P_HPP__
