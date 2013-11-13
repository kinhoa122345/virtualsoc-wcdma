//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "libsimsoc/components/ti_am1x_emac_control.hpp"
#include "libsimsoc/components/ti_am1x_emac_control_p.hpp"
#include "libsimsoc/components/ti_am1x_emac_module.hpp"

#include <cstdlib>

namespace simsoc  {
namespace TI_AM1x {

  // ------------------------------------------------------------------
  enum emac_ctrl_action {
    EMAC_REVID     ,
    EMAC_SOFTRESET ,
    EMAC_INTCONTROL,
    EMAC_CENABLE   ,
    EMAC_CSTAT     ,
    EMAC_CRXIMAX   ,
    EMAC_CTXIMAX   ,
  };

  static enum emac_ctrl_action EMAC_INVALID = (enum emac_ctrl_action) -1;

  // ------------------------------------------------------------------
#define READER(NAME) &EMAC_CONTROL::_rd_##NAME
#define WRITER(NAME) &EMAC_CONTROL::_wr_##NAME

#define RO_ACCESS(NAME) { READER(NAME), NULL         }
#define WO_ACCESS(NAME) { NULL        , WRITER(NAME) }
#define RW_ACCESS(NAME) { READER(NAME), WRITER(NAME) }

  const EMAC_CONTROL::ac_access_t EMAC_CONTROL::accessors[] = {
    RO_ACCESS(REVID         ),
    RW_ACCESS(SOFTRESET     ),
    RW_ACCESS(INTCONTROL    ),
    RW_ACCESS(CENABLE       ),
    RO_ACCESS(CSTAT         ),
    RW_ACCESS(CRXIMAX       ),
    RW_ACCESS(CTXIMAX       ),
  };

  // ------------------------------------------------------------------
  class emac_ctrl_ac_t {
  public:
    uint32_t         rawaddress;
    emac_ctrl_action action;
    size_t           index;

  public:
    static emac_ctrl_ac_t classify(uint32_t address);

  public:
    emac_ctrl_ac_t(uint32_t address)
      :rawaddress(address)
      ,action    (EMAC_INVALID)
      ,index     (0)
    {}

    emac_ctrl_ac_t(uint32_t         address  ,
                   emac_ctrl_action action   ,
                   uint32_t         index = 0)
      :rawaddress(address)
      ,action    (action)
      ,index     (index)
    {}

    emac_ctrl_ac_t(uint32_t         address  ,
                   emac_ctrl_action action   ,
                   uint16_t         idx1     ,
                   uint16_t         idx2     )
      :rawaddress(address)
      ,action    (action)
      ,index     (((uint32_t) idx1 << 16) | idx2)
    {}

  public:
    static const uint32_t REVID          = 0x00000000;
    static const uint32_t SOFTRESET      = 0x00000004;
    static const uint32_t INTCONTROL     = 0x0000000C;
    static const uint32_t C0RXTHRESHEN   = 0x00000010;
    static const uint32_t C0RXEN         = 0x00000014;
    static const uint32_t C0TXEN         = 0x00000018;
    static const uint32_t C0MISCEN       = 0x0000001C;
    static const uint32_t C1RXTHRESHEN   = 0x00000020;
    static const uint32_t C1RXEN         = 0x00000024;
    static const uint32_t C1TXEN         = 0x00000028;
    static const uint32_t C1MISCEN       = 0x0000002C;
    static const uint32_t C2RXTHRESHEN   = 0x00000030;
    static const uint32_t C2RXEN         = 0x00000034;
    static const uint32_t C2TXEN         = 0x00000038;
    static const uint32_t C2MISCEN       = 0x0000003C;
    static const uint32_t C0RXTHRESHSTAT = 0x00000040;
    static const uint32_t C0RXSTAT       = 0x00000044;
    static const uint32_t C0TXSTAT       = 0x00000048;
    static const uint32_t C0MISCSTAT     = 0x0000004C;
    static const uint32_t C1RXTHRESHSTAT = 0x00000050;
    static const uint32_t C1RXSTAT       = 0x00000054;
    static const uint32_t C1TXSTAT       = 0x00000058;
    static const uint32_t C1MISCSTAT     = 0x0000005C;
    static const uint32_t C2RXTHRESHSTAT = 0x00000060;
    static const uint32_t C2RXSTAT       = 0x00000064;
    static const uint32_t C2TXSTAT       = 0x00000068;
    static const uint32_t C2MISCSTAT     = 0x0000006C;
    static const uint32_t C0RXIMAX       = 0x00000070;
    static const uint32_t C0TXIMAX       = 0x00000074;
    static const uint32_t C1RXIMAX       = 0x00000078;
    static const uint32_t C1TXIMAX       = 0x0000007C;
    static const uint32_t C2RXIMAX       = 0x00000080;
    static const uint32_t C2TXIMAX       = 0x00000084;
};

  // ------------------------------------------------------------------
  emac_ctrl_ac_t emac_ctrl_ac_t::classify(uint32_t address) {
    const uint32_t rawaddress = address;

#define INVALID            (emac_ctrl_ac_t(rawaddress))
#define ADDRESS(C)         (emac_ctrl_ac_t(rawaddress, C))
#define ADDRESS_I(C, I)    (emac_ctrl_ac_t(rawaddress, C, I))
#define ADDRESS_C(C, K, I) (emac_ctrl_ac_t(rawaddress, C, K, I))

    if (address >> 16 || (address & 3))
      return INVALID;

    switch (address) {
    case REVID         : return ADDRESS  (EMAC_REVID     );
    case SOFTRESET     : return ADDRESS  (EMAC_SOFTRESET );
    case INTCONTROL    : return ADDRESS  (EMAC_INTCONTROL);
    case C0RXTHRESHEN  : return ADDRESS_C(EMAC_CENABLE, IT_RXTHRESH, 0);
    case C0RXEN        : return ADDRESS_C(EMAC_CENABLE, IT_RX      , 0);
    case C0TXEN        : return ADDRESS_C(EMAC_CENABLE, IT_TX      , 0);
    case C0MISCEN      : return ADDRESS_C(EMAC_CENABLE, IT_MISC    , 0);
    case C1RXTHRESHEN  : return ADDRESS_C(EMAC_CENABLE, IT_RXTHRESH, 1);
    case C1RXEN        : return ADDRESS_C(EMAC_CENABLE, IT_RX      , 1);
    case C1TXEN        : return ADDRESS_C(EMAC_CENABLE, IT_TX      , 1);
    case C1MISCEN      : return ADDRESS_C(EMAC_CENABLE, IT_MISC    , 1);
    case C2RXTHRESHEN  : return ADDRESS_C(EMAC_CENABLE, IT_RXTHRESH, 2);
    case C2RXEN        : return ADDRESS_C(EMAC_CENABLE, IT_RX      , 2);
    case C2TXEN        : return ADDRESS_C(EMAC_CENABLE, IT_TX      , 2);
    case C2MISCEN      : return ADDRESS_C(EMAC_CENABLE, IT_MISC    , 2);
    case C0RXTHRESHSTAT: return ADDRESS_C(EMAC_CSTAT  , IT_RXTHRESH, 0);
    case C0RXSTAT      : return ADDRESS_C(EMAC_CSTAT  , IT_RX      , 0);
    case C0TXSTAT      : return ADDRESS_C(EMAC_CSTAT  , IT_TX      , 0);
    case C0MISCSTAT    : return ADDRESS_C(EMAC_CSTAT  , IT_MISC    , 0);
    case C1RXTHRESHSTAT: return ADDRESS_C(EMAC_CSTAT  , IT_RXTHRESH, 1);
    case C1RXSTAT      : return ADDRESS_C(EMAC_CSTAT  , IT_RX      , 1);
    case C1TXSTAT      : return ADDRESS_C(EMAC_CSTAT  , IT_TX      , 1);
    case C1MISCSTAT    : return ADDRESS_C(EMAC_CSTAT  , IT_MISC    , 1);
    case C2RXTHRESHSTAT: return ADDRESS_C(EMAC_CSTAT  , IT_RXTHRESH, 2);
    case C2RXSTAT      : return ADDRESS_C(EMAC_CSTAT  , IT_RX      , 2);
    case C2TXSTAT      : return ADDRESS_C(EMAC_CSTAT  , IT_TX      , 2);
    case C2MISCSTAT    : return ADDRESS_C(EMAC_CSTAT  , IT_MISC    , 2);
    case C0RXIMAX      : return ADDRESS_I(EMAC_CRXIMAX, 0);
    case C0TXIMAX      : return ADDRESS_I(EMAC_CTXIMAX, 0);
    case C1RXIMAX      : return ADDRESS_I(EMAC_CRXIMAX, 1);
    case C1TXIMAX      : return ADDRESS_I(EMAC_CTXIMAX, 1);
    case C2RXIMAX      : return ADDRESS_I(EMAC_CRXIMAX, 2);
    case C2TXIMAX      : return ADDRESS_I(EMAC_CTXIMAX, 2);
    }

    return INVALID;

#undef INVALID
#undef ADDRESS
#undef ADDRESS_I
#undef ADDRESS_C
  }

  // ------------------------------------------------------------------
  EMAC_CONTROL::EMAC_CONTROL(sc_core::sc_module_name name)
    :TI_AM1x_core<EMAC_CONTROL>(name, this)
    ,m_p(NULL)
  {
    m_p = new EMAC_CONTROL_Private();
    this->_reset();
  }

  // ------------------------------------------------------------------
  EMAC_CONTROL::~EMAC_CONTROL() {
    if (m_p != NULL)
      delete m_p;
  }

  // ------------------------------------------------------------------
  signals::SignalInitiatorPort_Level&
  EMAC_CONTROL::get_signal(size_t group, emac_intkind_e kind) {
    assert(group < NCOREGRPS);
    return m_p->coreints[group][kind].signal;
  }

  // ------------------------------------------------------------------
  void EMAC_CONTROL::_reset() {
    for (size_t i = 0; i < NCOREGRPS; ++i)
      m_p->coreints[i].reset();
  }

  // ------------------------------------------------------------------
  uint32_t EMAC_CONTROL::read_word(uint32_t address) {
    debug()
      << "reading at address " << std::hex << address
      << std::endl;

    const emac_ctrl_ac_t ac = emac_ctrl_ac_t::classify(address);

    if (ac.action == EMAC_INVALID) {
      warning()
        << "invalid address: " << std::hex << address
        << std::endl;
      return 0;
    }

    const ac_access_t &access = accessors[ac.action];

    if (access.reader == NULL) {
      warning()
        << "trying to access a non-readable register at address "
        << std::hex << address
        << std::endl;
      return 0;
    }

    return (this->*access.reader)(ac);
  }

  // ------------------------------------------------------------------
  void EMAC_CONTROL::write_word(uint32_t address, uint32_t value) {
    debug()
      << "writing " << std::hex << value
      << " at address " << std::hex << address
      << std::endl;

    const emac_ctrl_ac_t ac = emac_ctrl_ac_t::classify(address);

    if (ac.action == EMAC_INVALID) {
      warning()
        << "invalid address: " << std::hex << address
        << std::endl;
      return ;
    }

    const ac_access_t &access = accessors[ac.action];

    if (access.writer == NULL) {
      warning()
        << "trying to access a non-writable register at address "
        << std::hex << address
        << std::endl;
      return ;
    }

    (this->*access.writer)(ac, value);
  }

  // ------------------------------------------------------------------
  uint32_t EMAC_CONTROL::_rd_REVID(const emac_ctrl_ac_t &ac) {
    return REVID;
  }

  // ------------------------------------------------------------------
  void EMAC_CONTROL::_wr_SOFTRESET(const emac_ctrl_ac_t &ac, uint32_t data) {
    if (data & 0x1)
      this->_reset();           // FIXME: reset should not be immediate
  }

  uint32_t EMAC_CONTROL::_rd_SOFTRESET(const emac_ctrl_ac_t &ac) {
    return 0;
  }

  // ------------------------------------------------------------------
  uint32_t EMAC_CONTROL::_rd_INTCONTROL(const emac_ctrl_ac_t &ac) {
    return 0;
  }

  void EMAC_CONTROL::_wr_INTCONTROL(const emac_ctrl_ac_t &ac, uint32_t data) {
  }

  // ------------------------------------------------------------------
  uint32_t EMAC_CONTROL::_rd_CENABLE(const emac_ctrl_ac_t &ac) {
    size_t group = ((ac.index >>  0) & 0xFFFF);
    size_t index = ((ac.index >> 16) & 0xFFFF);

    return m_p->coreints[group][(emac_intkind_e) index].enabled;
  }

  void EMAC_CONTROL::_wr_CENABLE(const emac_ctrl_ac_t &ac, uint32_t data) {
    size_t         group =                  ((ac.index >>  0) & 0xFFFF);
    emac_intkind_e ikind = (emac_intkind_e) ((ac.index >> 16) & 0xFFFF);

    EMAC_CoreInterrupts &coreint = m_p->coreints[group];

    coreint.set_enabled_mask_R(ikind, data);
    if (!coreint.pending(ikind))
      coreint[ikind].signal = false;
    else if (!coreint[ikind].pulsed) {
      coreint[ikind].signal = true;
      coreint[ikind].pulsed = true;
    }
  }

  // ------------------------------------------------------------------
  uint32_t EMAC_CONTROL::_rd_CSTAT(const emac_ctrl_ac_t &ac) {
    size_t group = ((ac.index >>  0) & 0xFFFF);
    size_t index = ((ac.index >> 16) & 0xFFFF);

    return m_p->coreints[group].pending((emac_intkind_e) index);
  }

  // ------------------------------------------------------------------
  uint32_t EMAC_CONTROL::_rd_CRXIMAX(const emac_ctrl_ac_t &ac) {
    return 0;
  }

  void EMAC_CONTROL::_wr_CRXIMAX(const emac_ctrl_ac_t &ac, uint32_t data) {
  }

  // ------------------------------------------------------------------
  uint32_t EMAC_CONTROL::_rd_CTXIMAX(const emac_ctrl_ac_t &ac) {
    return 0;
  }

  void EMAC_CONTROL::_wr_CTXIMAX(const emac_ctrl_ac_t &ac, uint32_t data) {
  }

  // ------------------------------------------------------------------
  void EMAC_CONTROL::update_rx_for_chan(uint8_t chan, bool status) {
    for (size_t i = 0; i < NCOREGRPS; ++i) {
      EMAC_CoreInterrupts &stats = m_p->coreints[i];

      stats.set_pending(IT_RX, chan, status);
      if (!stats.masked(IT_RX, chan))
        stats[IT_RX].signal = false;
      else if (!stats[IT_RX].pulsed) {
        stats[IT_RX].signal = true;
        stats[IT_RX].pulsed = true;
      }
    }
  }

  // ------------------------------------------------------------------
  void EMAC_CONTROL::update_tx_for_chan(uint8_t chan, bool status) {
    for (size_t i = 0; i < NCOREGRPS; ++i) {
      EMAC_CoreInterrupts &stats = m_p->coreints[i];

      if (status == stats.pending(IT_TX))
        continue ;
      stats.set_pending(IT_TX, chan, status);
      if (!status)
        stats[IT_TX].signal = false;
      else if (!stats[IT_TX].pulsed) {
        stats[IT_TX].signal = true;
        stats[IT_TX].pulsed = true;
      }
    }
  }

  // ------------------------------------------------------------------
  void EMAC_CONTROL::update_mc(emac_intmisc_e it, bool status) {
    for (size_t i = 0; i < NCOREGRPS; ++i) {
      EMAC_CoreInterrupts &stats = m_p->coreints[i];

      if (status == stats.pending(IT_MISC))
        continue ;
      stats.set_pending(IT_MISC, (int) it, status);
      if (!status)
        stats[IT_MISC].signal = false;
      else if (!stats[IT_TX].pulsed) {
        stats[IT_MISC].signal = true;
        stats[IT_MISC].pulsed = true;
      }
    }
  }

  // ------------------------------------------------------------------
  void EMAC_CONTROL::acknowledge(size_t group, emac_intkind_e kind) {
    EMAC_CoreInterrupts &coreint = m_p->coreints[group];

    if (coreint[kind].pulsed) {
      coreint[kind].pulsed = coreint.pending(kind);
      coreint[kind].signal = coreint.pending(kind);
    }
  }

} // namespace TI_AM1x
} // namespace simsoc
