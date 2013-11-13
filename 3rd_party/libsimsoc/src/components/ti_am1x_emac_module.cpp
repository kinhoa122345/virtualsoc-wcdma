//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "libsimsoc/components/ti_am1x_emac_module.hpp"
#include "libsimsoc/components/ti_am1x_emac_module_p.hpp"

#include "libsimsoc/bitwise_operator.hpp"
#include "libsimsoc/components/ti_am1x_emac_control.hpp"
#include "libsimsoc/network/ethernet/ether-transport.hpp"

#include <cstdlib>
#include <cstring>
#include <memory>

#include <unistd.h>

namespace simsoc  {
namespace TI_AM1x {

  // ------------------------------------------------------------------
  const uint8_t EMAC_INTVEC_Base::masks[4] =
    { 0x03, 0xFF, 0xFF, 0xFF };

  // ------------------------------------------------------------------
  enum emac_action {
    // Modifications => [EMAC_MOD::accessors] update
    EMAC_REVID            ,     // [TX|RX]REVID
    EMAC_CONTROL          ,     // [TX|RX]REVID
    EMAC_TEARDOWN         ,     // [TX|RX]TEARDOWN
    EMAC_INTSTATRAW       ,     // [TX|RX|MAC]INTSTATRAW
    EMAC_INTSTATMASKED    ,     // [TX|RX|MAC]INTSTATMASKED
    EMAC_INTMASKSET       ,     // [TX|RX|MAC]INTMASKSET
    EMAC_INTMASKCLEAR     ,     // [TX|RX|MAC]INTMASKCLEAR
    EMAC_MACINTVECTOR     ,     // MACINTVECTOR
    EMAC_MACEOIVECTOR     ,     // MACEOIVECTOR
    EMAC_RXMBPENABLE      ,     // EXMBPENABLE
    EMAC_RXUNICASTSET     ,     // RXUNICASTSET
    EMAC_RXUNICASTCLEAR   ,     // RXUNICASTCLEAR
    EMAC_RXMAXLEN         ,     // RXMAXLEN
    EMAC_RXBUFFEROFFSET   ,     // RXBUFFEROFFSET
    EMAC_RXFILTERLOWTHRESH,     // RXFILTERLOWTHRESH
    EMAC_RXFLOWTHRESH     ,     // RX[n]FLOWTRESH
    EMAC_RXFREEBUFFER     ,     // RX[n]FREEBUFFER
    EMAC_MACCONTROL       ,     // MACCONTROL
    EMAC_MACSTATUS        ,     // MACSTATUS
    EMAC_EMCONTROL        ,     // EMCONTROL
    EMAC_FIFOCONTROL      ,     // FIFOCONTROL
    EMAC_MACCONFIG        ,     // MACCONFIG
    EMAC_SOFTRESET        ,     // SOFTRESET
    EMAC_MACSRCADDR       ,     // MACSRCADDR[LO|HI]
    EMAC_MACHASH          ,     // MACHASH[n]
    EMAC_BOFFTEST         ,     // BOFFTEST
    EMAC_TPACETEST        ,     // TPACETEST
    EMAC_PAUSE            ,     // [RX|TX]PAUSE
    EMAC_MACADDR          ,     // MACADDR[LO|HI]
    EMAC_MACINDEX         ,     // MACINDEX
    EMAC_TXHDP            ,     // TX[n]HDP
    EMAC_RXHDP            ,     // RX[n]HDP
    EMAC_TXCP             ,     // TX[n]CP
    EMAC_RXCP             ,     // RX[n]CP
    EMAC_STATS            ,     // Statistic registers
  };

  static enum emac_action EMAC_INVALID = (enum emac_action) -1;

  // ------------------------------------------------------------------
#define READER(NAME) &EMAC_MOD::_read_##NAME
#define WRITER(NAME) &EMAC_MOD::_write_##NAME

#define RO_ACCESS(NAME) { READER(NAME), NULL         }
#define WO_ACCESS(NAME) { NULL        , WRITER(NAME) }
#define RW_ACCESS(NAME) { READER(NAME), WRITER(NAME) }

  const EMAC_MOD::ac_access_t EMAC_MOD::accessors[] = {
    // Must appear in [enum emac_action] order.
    RO_ACCESS (REVID            ),
    RW_ACCESS (CONTROL          ),
    WO_ACCESS (TEARDOWN         ),
    RO_ACCESS (INTSTATRAW       ),
    RO_ACCESS (INTSTATMASKED    ),
    RW_ACCESS (INTMASKSET       ),
    WO_ACCESS (INTMASKCLEAR     ),
    RO_ACCESS (MACINTVECTOR     ),
    WO_ACCESS (MACEOIVECTOR     ),
    RW_ACCESS (RXMBPENABLE      ),
    RW_ACCESS (RXUNICASTSET     ),
    WO_ACCESS (RXUNICASTCLEAR   ),
    RW_ACCESS (RXMAXLEN         ),
    RW_ACCESS (RXBUFFEROFFSET   ),
    RW_ACCESS (RXFILTERLOWTHRESH),
    RW_ACCESS (RXFLOWTHRESH     ),
    RW_ACCESS (RXFREEBUFFER     ),
    RW_ACCESS (MACCONTROL       ),
    RO_ACCESS (MACSTATUS        ),
    RW_ACCESS (EMCONTROL        ),
    RW_ACCESS (FIFOCONTROL      ),
    RO_ACCESS (MACCONFIG        ),
    RW_ACCESS (SOFTRESET        ),
    RW_ACCESS (MACSRCADDR       ),
    RW_ACCESS (MACHASH          ),
    RO_ACCESS (BOFFTEST         ),
    RO_ACCESS (TPACETEST        ),
    RO_ACCESS (PAUSE            ),
    RW_ACCESS (MACADDR          ),
    RW_ACCESS (MACINDEX         ),
    RW_ACCESS (TXHDP            ),
    RW_ACCESS (RXHDP            ),
    RW_ACCESS (TXCP             ),
    RW_ACCESS (RXCP             ),
    RW_ACCESS (STATS            ),
  };

  // ------------------------------------------------------------------
  class emac_ac_t {
  public:
    uint32_t    rawaddress;
    emac_action action;
    size_t      index;

  public:
    static emac_ac_t classify(uint32_t address);

  public:
    emac_ac_t(uint32_t address)
      :rawaddress(address)
      ,action    (EMAC_INVALID)
      ,index     (0)
    {}

    emac_ac_t(uint32_t    address  ,
              emac_action action   ,
              size_t      index = 0)
      :rawaddress(address)
      ,action    (action)
      ,index     (index)
    {}

  public:
    static const uint32_t A_TXREVID           = 0x00000000;
    static const uint32_t A_TXCONTROL         = 0x00000004;
    static const uint32_t A_TXTEARDOWN        = 0x00000008;
    static const uint32_t A_RXREVID           = 0x00000010;
    static const uint32_t A_RXCONTROL         = 0x00000014;
    static const uint32_t A_RXTEARDOWN        = 0x00000018;
    static const uint32_t A_TXINTSTATRAW      = 0x00000080;
    static const uint32_t A_TXINTSTATMASKED   = 0x00000084;
    static const uint32_t A_TXINTMASKSET      = 0x00000088;
    static const uint32_t A_TXINTMASKCLEAR    = 0x0000008C;
    static const uint32_t A_MACINVECTOR       = 0x00000090;
    static const uint32_t A_MACEOIVECTOR      = 0x00000094;
    static const uint32_t A_RXINTSTATRAW      = 0x000000A0;
    static const uint32_t A_RXINTSTATMASKED   = 0x000000A4;
    static const uint32_t A_RXINTMASKSET      = 0x000000A8;
    static const uint32_t A_RXINTMASKCLEAR    = 0x000000AC;
    static const uint32_t A_MACINTSTATRAW     = 0x000000B0;
    static const uint32_t A_MACINTSTATMASKED  = 0x000000B4;
    static const uint32_t A_MACINTMASKSET     = 0x000000B8;
    static const uint32_t A_MACINTMASKCLEAR   = 0x000000BC;
    static const uint32_t A_RXMBPENABLE       = 0x00000100;
    static const uint32_t A_RXUNICASTSET      = 0x00000104;
    static const uint32_t A_RXUNICASTCLEAR    = 0x00000108;
    static const uint32_t A_RXMAXLEN          = 0x0000010C;
    static const uint32_t A_RXBUFFEROFFSET    = 0x00000110;
    static const uint32_t A_RXFILTERLOWTHRESH = 0x00000114;
    static const uint32_t A_MACCONTROL        = 0x00000160;
    static const uint32_t A_MACSTATUS         = 0x00000164;
    static const uint32_t A_EMCONTROL         = 0x00000168;
    static const uint32_t A_FIFOCONTROL       = 0x0000016C;
    static const uint32_t A_MACCONFIG         = 0x00000170;
    static const uint32_t A_SOFTRESET         = 0x00000174;
    static const uint32_t A_MACSRCADDRLO      = 0x000001D0;
    static const uint32_t A_MACSRCADDRHI      = 0x000001D4;
    static const uint32_t A_MACHASH1          = 0x000001D8;
    static const uint32_t A_MACHASH2          = 0x000001DC;
    static const uint32_t A_BOFFTEST          = 0x000001E0;
    static const uint32_t A_TPACETEST         = 0x000001E4;
    static const uint32_t A_RXPAUSE           = 0x000001E8;
    static const uint32_t A_TXPAUSE           = 0x000001EC;
    static const uint32_t A_MACADDRLO         = 0x00000500;
    static const uint32_t A_MACADDRHI         = 0x00000504;
    static const uint32_t A_MACINDEX          = 0x00000508;

    static const uint32_t AC_RXFLOWTHRESH = 0x00000120;
    static const uint32_t AC_RXFREEBUFFER = 0x00000140;
    static const uint32_t AC_TXHDP        = 0x00000600;
    static const uint32_t AC_RXHDP        = 0x00000620;
    static const uint32_t AC_TXCP         = 0x00000640;
    static const uint32_t AC_RXCP         = 0x00000660;
    static const uint32_t AC_STATS        = 0x00000200;
  };

  // ------------------------------------------------------------------
  enum lohi_e { LOIDX, HIIDX };

  emac_ac_t emac_ac_t::classify(uint32_t address) {
    const uint32_t rawaddress = address;

#define INVALID           (emac_ac_t(rawaddress))
#define ADDRESS(C)        (emac_ac_t(rawaddress, C))
#define ADDRESS_I(C, I)   (emac_ac_t(rawaddress, C, I))
#define IN_RANGE(A, OFF)  ((A) >= (OFF) && (A) < NCHANNELS * 4 + (OFF))
#define RANGE_OFF(A, OFF) (((A) - (OFF)) >> 2)

    if (address >> 16 || (address & 3))
      return INVALID;

    switch (address) {
    case A_TXREVID          : return ADDRESS_I(EMAC_REVID            , TXIDX);
    case A_TXCONTROL        : return ADDRESS_I(EMAC_CONTROL          , TXIDX);
    case A_TXTEARDOWN       : return ADDRESS_I(EMAC_TEARDOWN         , TXIDX);
    case A_RXREVID          : return ADDRESS_I(EMAC_REVID            , RXIDX);
    case A_RXCONTROL        : return ADDRESS_I(EMAC_CONTROL          , RXIDX);
    case A_RXTEARDOWN       : return ADDRESS_I(EMAC_TEARDOWN         , RXIDX);
    case A_TXINTSTATRAW     : return ADDRESS_I(EMAC_INTSTATRAW       , TXIDX);
    case A_TXINTSTATMASKED  : return ADDRESS_I(EMAC_INTSTATMASKED    , TXIDX);
    case A_TXINTMASKSET     : return ADDRESS_I(EMAC_INTMASKSET       , TXIDX);
    case A_TXINTMASKCLEAR   : return ADDRESS_I(EMAC_INTMASKCLEAR     , TXIDX);
    case A_MACINVECTOR      : return ADDRESS  (EMAC_MACINTVECTOR     );
    case A_MACEOIVECTOR     : return ADDRESS  (EMAC_MACEOIVECTOR     );
    case A_RXINTSTATRAW     : return ADDRESS_I(EMAC_INTSTATRAW       , RXIDX);
    case A_RXINTSTATMASKED  : return ADDRESS_I(EMAC_INTSTATMASKED    , RXIDX);
    case A_RXINTMASKSET     : return ADDRESS_I(EMAC_INTMASKSET       , RXIDX);
    case A_RXINTMASKCLEAR   : return ADDRESS_I(EMAC_INTMASKCLEAR     , RXIDX);
    case A_MACINTSTATRAW    : return ADDRESS_I(EMAC_INTSTATRAW       , MACIDX);
    case A_MACINTSTATMASKED : return ADDRESS_I(EMAC_INTSTATMASKED    , MACIDX);
    case A_MACINTMASKSET    : return ADDRESS_I(EMAC_INTMASKSET       , MACIDX);
    case A_MACINTMASKCLEAR  : return ADDRESS_I(EMAC_INTMASKCLEAR     , MACIDX);
    case A_RXMBPENABLE      : return ADDRESS  (EMAC_RXMBPENABLE      );
    case A_RXUNICASTSET     : return ADDRESS  (EMAC_RXUNICASTSET     );
    case A_RXUNICASTCLEAR   : return ADDRESS  (EMAC_RXUNICASTCLEAR   );
    case A_RXMAXLEN         : return ADDRESS  (EMAC_RXMAXLEN         );
    case A_RXBUFFEROFFSET   : return ADDRESS  (EMAC_RXBUFFEROFFSET   );
    case A_RXFILTERLOWTHRESH: return ADDRESS  (EMAC_RXFILTERLOWTHRESH);
    case A_MACCONTROL       : return ADDRESS  (EMAC_MACCONTROL       );
    case A_MACSTATUS        : return ADDRESS  (EMAC_MACSTATUS        );
    case A_EMCONTROL        : return ADDRESS  (EMAC_EMCONTROL        );
    case A_FIFOCONTROL      : return ADDRESS  (EMAC_FIFOCONTROL      );
    case A_MACCONFIG        : return ADDRESS  (EMAC_MACCONFIG        );
    case A_SOFTRESET        : return ADDRESS  (EMAC_SOFTRESET        );
    case A_MACSRCADDRLO     : return ADDRESS_I(EMAC_MACSRCADDR       , LOIDX);
    case A_MACSRCADDRHI     : return ADDRESS_I(EMAC_MACSRCADDR       , HIIDX);
    case A_MACHASH1         : return ADDRESS_I(EMAC_MACHASH          , LOIDX);
    case A_MACHASH2         : return ADDRESS_I(EMAC_MACHASH          , HIIDX);
    case A_BOFFTEST         : return ADDRESS  (EMAC_BOFFTEST         );
    case A_TPACETEST        : return ADDRESS  (EMAC_TPACETEST        );
    case A_RXPAUSE          : return ADDRESS_I(EMAC_PAUSE            , RXIDX);
    case A_TXPAUSE          : return ADDRESS_I(EMAC_PAUSE            , TXIDX);
    case A_MACADDRLO        : return ADDRESS_I(EMAC_MACADDR          , LOIDX);
    case A_MACADDRHI        : return ADDRESS_I(EMAC_MACADDR          , HIIDX);
    case A_MACINDEX         : return ADDRESS  (EMAC_MACINDEX         );
    }

    if (IN_RANGE(address, AC_RXFLOWTHRESH))
      return ADDRESS_I(EMAC_RXFLOWTHRESH, RANGE_OFF(address, AC_RXFLOWTHRESH));

    if (IN_RANGE(address, AC_RXFREEBUFFER))
      return ADDRESS_I(EMAC_RXFREEBUFFER, RANGE_OFF(address, AC_RXFREEBUFFER));

    if (IN_RANGE(address, AC_TXHDP))
      return ADDRESS_I(EMAC_TXHDP, RANGE_OFF(address, AC_TXHDP));

    if (IN_RANGE(address, AC_RXHDP))
      return ADDRESS_I(EMAC_RXHDP, RANGE_OFF(address, AC_RXHDP));

    if (IN_RANGE(address, AC_TXCP))
      return ADDRESS_I(EMAC_TXCP, RANGE_OFF(address, AC_TXCP));

    if (IN_RANGE(address, AC_RXCP))
      return ADDRESS_I(EMAC_RXCP, RANGE_OFF(address, AC_RXCP));

    if (address >= AC_STATS && address < (EMAC_Stats::NSTATS * 4 + AC_STATS))
      return ADDRESS_I(EMAC_STATS, (address - AC_STATS) >> 2);

    return INVALID;

#undef INVALID
#undef ADDRESS
#undef ADDRESS_I
#undef IN_RANGE
#undef RANGE_OFF
  }

  // ------------------------------------------------------------------
  struct pkhead_s {
    uint32_t  next;
    uint32_t  p_buffer;
    uint16_t  buf_length;
    uint16_t  buf_offset;
    uint16_t  pkg_length;
    uint16_t  flags;
  };

  // ------------------------------------------------------------------
  void EMAC_MOD::_read_pkhead(uint32_t address, struct pkhead_s &pk) {
    PayLoad pl;

    pk.next       = _rd_32(address + PKHEAD_OFF_NEXT      );
    pk.p_buffer   = _rd_32(address + PKHEAD_OFF_P_BUFFER  );
    pk.buf_length = _rd_16(address + PKHEAD_OFF_BUF_LENGTH);
    pk.buf_offset = _rd_16(address + PKHEAD_OFF_BUF_OFFSET);
    pk.pkg_length = _rd_16(address + PKHEAD_OFF_PKG_LENGTH);
    pk.flags      = _rd_16(address + PKHEAD_OFF_FLAGS     );
  }

  // ------------------------------------------------------------------
  EMAC_MOD::EMAC_MOD(sc_core::sc_module_name name, EMAC &emac)
    :TI_AM1x_core <EMAC_MOD>(name, this)
    ,TI_AM1x_oport<EMAC_MOD>(this)
    ,m_EMAC                 (emac)
    ,m_p                    (NULL)
    ,m_transport            (NULL)
  {
    m_p = new EMAC_MOD_Private(*this);
    this->_reset();

    SC_THREAD(_tx_thread);
    SC_THREAD(_rx_thread);
  }

  // ------------------------------------------------------------------
  EMAC_MOD::~EMAC_MOD() {
    if (m_p != NULL)
      delete m_p;
    if (m_transport != NULL)
      delete m_transport;
  }

  // ------------------------------------------------------------------
  void EMAC_MOD::set_transport(IEtherTransport *transport) {
    if (m_transport != NULL)
      abort();
    m_transport = transport;
  }

  // ------------------------------------------------------------------
  void EMAC_MOD::end_of_elaboration() {
    if (m_transport == NULL) {
      warning() << "setting default null transport" << std::endl;
      m_transport = new Null_EtherTransport();
    }

    m_transport->setnonblocking(true);
    m_transport->setrxpad(true);
  }

  // ------------------------------------------------------------------
  uint32_t EMAC_MOD::read_word (uint32_t address) {
    debug()
      << "reading at address " << std::hex << address
      << std::endl;

    const emac_ac_t ac = emac_ac_t::classify(address);

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
  void EMAC_MOD::write_word(uint32_t address, uint32_t value) {
    debug()
      << "writing " << std::hex << value
      << " at address " << std::hex << address
      << std::endl;

    const emac_ac_t ac = emac_ac_t::classify(address);

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
  uint32_t EMAC_MOD::_read_REVID(const emac_ac_t &ac) {
    assert(ac.action == EMAC_REVID);

    if (ac.index == TXIDX) return TX_REVID;
    if (ac.index == RXIDX) return RX_REVID;

    abort();
  }

  // ------------------------------------------------------------------
  uint32_t EMAC_MOD::_read_MACCONFIG(const emac_ac_t &ac) {
    return MACCONFIG;
  }

  // ------------------------------------------------------------------
  uint32_t EMAC_MOD::_read_RXBUFFEROFFSET(const emac_ac_t &ac) {
    return m_p->m_R_rxbufoffset;
  }

  void EMAC_MOD::_write_RXBUFFEROFFSET(const emac_ac_t &ac, uint32_t data) {
    if ((data & 0xFFFF0000)) {
      warning()
        << "RX buffer offset is only 16-bits wide"
        << std::endl;
    }
    m_p->m_R_rxbufoffset = data & 0xFFFF;
  }


  // ------------------------------------------------------------------
  uint32_t EMAC_MOD::_read_RXMAXLEN(const emac_ac_t &ac) {
    return m_p->m_R_rxmaxlen;
  }

  void EMAC_MOD::_write_RXMAXLEN(const emac_ac_t &ac, uint32_t data) {
    if ((data & 0xFFFF0000)) {
      warning()
        << "RX max length is only 16-bits wide"
        << std::endl;
    }
    m_p->m_R_rxmaxlen = data & 0xFFFF;
  }

  // ------------------------------------------------------------------
  uint32_t EMAC_MOD::_read_MACHASH(const emac_ac_t &ac) {
    switch (ac.index) {
    case LOIDX: return (m_p->m_R_machash >>  0) & 0xFFFFFFFF;
    case HIIDX: return (m_p->m_R_machash >> 32) & 0xFFFFFFFF;
    }

    abort();
  }

  void EMAC_MOD::_write_MACHASH(const emac_ac_t &ac, uint32_t data) {
    switch (ac.index) {
    case LOIDX: u64_setlo(m_p->m_R_machash, data); break ;
    case HIIDX: u64_sethi(m_p->m_R_machash, data); break ;

    default: abort();
    }
  }

  // ------------------------------------------------------------------
  void EMAC_MOD::_write_RXUNICASTSET(const emac_ac_t &ac, uint32_t data) {
    for (size_t i = 0; i < NCHANNELS; ++i) {
      if (is_set<uint32_t>(data, i))
        m_p->m_R_channels[i].unicast = true;
    }
  }

  uint32_t EMAC_MOD::_read_RXUNICASTSET(const emac_ac_t &ac) {
    // We expect this function not to be called too often
    uint32_t mask = 0;

    for (size_t i = NCHANNELS; i != 0; --i)
      mask = (mask << 1) | (m_p->m_R_channels[i-1].unicast ? 0x1 : 0x0);
    return mask;
  }

  // ------------------------------------------------------------------
  void EMAC_MOD::_write_RXUNICASTCLEAR(const emac_ac_t &ac, uint32_t data) {
    for (size_t i = 0; i < NCHANNELS; ++i) {
      if (is_set<uint32_t>(data, i))
        m_p->m_R_channels[i].unicast = false;
    }
  }

  // ------------------------------------------------------------------
  void EMAC_MOD::_write_TEARDOWN(const emac_ac_t &ac, uint32_t data) {
    if (data > NCHANNELS) {
      error() << "TEARDOWN: invalid channel: " << data << std::endl;
      return ;
    }

    assert(ac.index == TXIDX || ac.index == RXIDX);

    EMAC_Channel &channel = m_p->m_R_channels[data];
    EMAC_Channel_Half &thehalf = channel.duplex[ac.index];

    if (thehalf.cp != 0)
      _wr_16(thehalf.cp + PKHEAD_OFF_FLAGS,
             PKHEAD_TDOWN | _rd_16(thehalf.cp + PKHEAD_OFF_FLAGS));

    thehalf.hdp = 0;
    thehalf.cp  = 0xfffffffc;

    thehalf.cp_sync_emac = thehalf.cp;
    thehalf.cp_sync_host = 0;

    if (ac.index == TXIDX)
      this->_update_tx_iir(data);
    if (ac.index == RXIDX)
      this->_update_rx_iir(data);
  }

  // ------------------------------------------------------------------
  uint32_t EMAC_MOD::_read_TXHDP(const emac_ac_t &ac) {
    return m_p->m_R_channels[ac.index].tx().hdp;
  }

  void EMAC_MOD::_write_TXHDP(const emac_ac_t &ac, uint32_t data) {
    EMAC_Channel_Half &thehalf = m_p->m_R_channels[ac.index].tx();

    if (thehalf.cp) {
      warning()
        << "cannot write in TXHDP[" << std::hex << ac.index << "] "
        << "when register TXCP is non-zero"
        << std::endl;
      return ;
    }

    thehalf.hdp = data;
    thehalf.cp  = data;

    thehalf.cp_sync_emac = 0;
    thehalf.cp_sync_host = 0;

    this->_tx_event.notify();
  }

  // ------------------------------------------------------------------
  uint32_t EMAC_MOD::_read_RXHDP(const emac_ac_t &ac) {
    return m_p->m_R_channels[ac.index].rx().hdp;
  }

  void EMAC_MOD::_write_RXHDP(const emac_ac_t &ac, uint32_t data) {
    EMAC_Channel_Half &thehalf = m_p->m_R_channels[ac.index].rx();

    if (thehalf.cp) {
      warning()
        << "cannot write in RXHDP[" << std::hex << ac.index << "] "
        << "when register RXCP is non-zero"
        << std::endl;
      return ;
    }

    thehalf.hdp = data;
    thehalf.cp  = data;

    thehalf.cp_sync_emac = 0;
    thehalf.cp_sync_host = 0;
  }

  // ------------------------------------------------------------------
  uint32_t EMAC_MOD::_read_TXCP(const emac_ac_t &ac) {
    return m_p->m_R_channels[ac.index].tx().cp;
  }

  void EMAC_MOD::_write_TXCP(const emac_ac_t &ac, uint32_t data) {
    EMAC_Channel &channel = m_p->m_R_channels[ac.index];
    channel.tx().cp_sync_host = data;
    this->_update_tx_iir(ac.index);
  }

  // ------------------------------------------------------------------
  uint32_t EMAC_MOD::_read_RXCP(const emac_ac_t &ac) {
    return m_p->m_R_channels[ac.index].tx().cp;
  }

  void EMAC_MOD::_write_RXCP(const emac_ac_t &ac, uint32_t data) {
    EMAC_Channel &channel = m_p->m_R_channels[ac.index];
    channel.rx().cp_sync_host = data;
    this->_update_rx_iir(ac.index);
  }

  // ------------------------------------------------------------------
  uint32_t EMAC_MOD::_read_MACSRCADDR(const emac_ac_t &ac) {
    if (ac.index == HIIDX) return m_p->m_R_macsrc.hi_32();
    if (ac.index == LOIDX) return m_p->m_R_macsrc.lo_16();

    abort();
  }

  void EMAC_MOD::_write_MACSRCADDR(const emac_ac_t &ac, uint32_t data) {
    switch (ac.index) {
    case HIIDX:
       m_p->m_R_macsrc.set_hi_32(data); break ;
     case LOIDX:
       if ((data & 0xFFFF0000))
         warning() << "garbage in MACSRCADDRLO value" << std::endl;
       m_p->m_R_macsrc.set_lo_16((uint16_t) data); break ;

     default:
       abort();
     }
   }

   // ------------------------------------------------------------------
   uint32_t EMAC_MOD::_read_MACINDEX(const emac_ac_t &ac) {
     return m_p->m_R_macindex;
   }

   void EMAC_MOD::_write_MACINDEX(const emac_ac_t &ac, uint32_t data) {
     if (data >= NMACS) {
      warning() << "register [MAC INDEX]]: "
                << "invalid mac index: " << std::hex << data
                << std::endl;
      return ;
    }

     m_p->m_R_macindex = data;
   }

   // ------------------------------------------------------------------
   uint32_t EMAC_MOD::_read_MACADDR(const emac_ac_t &ac) {
     const EMAC_MacAddress& mac = m_p->m_R_macs[m_p->m_R_macindex];

     if (ac.index == HIIDX)
       return mac.address.hi_32();
     if (ac.index == LOIDX)
       return ((uint32_t) mac.address.lo_16())
         | (((uint32_t) (mac.isvalid ? 1u : 0u)) << 20)
         | (((uint32_t) (mac.ismatch ? 1u : 0u)) << 19)
         | (((uint32_t) (mac.channel))           << 16);

     abort();
   }

   void EMAC_MOD::_write_MACADDR(const emac_ac_t &ac, uint32_t data) {
     switch (ac.index) {
     case HIIDX:
       for (size_t i = 0; i < NMACS; ++i)
         m_p->m_R_macs[i].address.set_hi_32(data);
       break ;

     case LOIDX:
       for (size_t i = 0; i < NMACS; ++i)
         m_p->m_R_macs[i].address.at(4) = data & 0xFF;
       m_p->m_R_macs[m_p->m_R_macindex].address.at(5) = (data >> 8) & 0xff;
       m_p->m_R_macs[m_p->m_R_macindex].isvalid = (data & (1 << 20));
       m_p->m_R_macs[m_p->m_R_macindex].ismatch = (data & (1 << 19));
       m_p->m_R_macs[m_p->m_R_macindex].channel = (data >> 16) & 0x7;
       break ;

     default:
       abort();
     }
   }

   // ------------------------------------------------------------------
   uint32_t EMAC_MOD::_read_TPACETEST(const emac_ac_t &ac) {
     return 0;
   }

   // ------------------------------------------------------------------
   uint32_t EMAC_MOD::_read_PAUSE(const emac_ac_t &ac) {
     return 0;
   }

   // ------------------------------------------------------------------
   uint32_t EMAC_MOD::_read_BOFFTEST(const emac_ac_t &ac) {
     return 0;
   }

   // ------------------------------------------------------------------
   uint32_t EMAC_MOD::_read_SOFTRESET(const emac_ac_t &ac) {
     return 0;
   }

   void EMAC_MOD::_write_SOFTRESET(const emac_ac_t &ac, uint32_t data) {
     if ((data & 0x1))           // FIXME: reset should not be immediate
       this->_reset();
   }

   // ------------------------------------------------------------------
   void EMAC_MOD::_write_CONTROL(const emac_ac_t &ac, uint32_t data) {
     if (data & 0x01)
       set_bit<uint32_t>(m_p->m_R_control, ac.index);
     else
       unset_bit<uint32_t>(m_p->m_R_control, ac.index);
     this->_tx_event.notify();
   }

   uint32_t EMAC_MOD::_read_CONTROL(const emac_ac_t &ac) {
     return is_set<uint32_t>(m_p->m_R_control, ac.index);
   }

   // ------------------------------------------------------------------
   uint32_t EMAC_MOD::_read_FIFOCONTROL(const emac_ac_t &ac) {
     return m_p->m_R_fifoctrl;
   }

   void EMAC_MOD::_write_FIFOCONTROL(const emac_ac_t &ac, uint32_t data) {
     if ((data & 0xFFFFFF00))
       warning() << "garbage in FIFOCONTROL value" << std::endl;
     data = data & 0xF;
     if (data != 0x2 && data != 0x3)
       warning()
         << "invalid FIFO cell threshold value (!= 2 && != 3)"
         << std::endl;
     else
      m_p->m_R_fifoctrl = data;
  }

  // ------------------------------------------------------------------
  void EMAC_MOD::_write_EMCONTROL(const emac_ac_t &ac, uint32_t data) {
    if ((data & 0xFFFFFFF0))
      warning() << "garbage in EMCONTROL value" << std::endl;
    m_p->m_R_emcontrol = data & 0xF;
  }

  uint32_t EMAC_MOD::_read_EMCONTROL(const emac_ac_t &ac) {
    return m_p->m_R_emcontrol;
  }

  // ------------------------------------------------------------------
  uint32_t EMAC_MOD::_read_MACCONTROL(const emac_ac_t &ac) {
    return m_p->m_R_maccontrol.get();
  }

  void EMAC_MOD::_write_MACCONTROL(const emac_ac_t &ac, uint32_t data) {
    if ((data & ~EMAC_R_MACCTRL::b_MASK))
      warning() << "garbage in MACCONTROL value" << std::endl;
    m_p->m_R_maccontrol.set(data);

    if (m_p->m_R_maccontrol.txpace()) {
      error() << "MACCTRL: TXPACE: unsupported" << std::endl;
      abort();
    }

    if (m_p->m_R_maccontrol.rxbufferflowen()) {
      error() << "MACCTRL: CONTROL FLOW: unsupported" << std::endl;
      abort();
    }

  }

  // ------------------------------------------------------------------
  uint32_t EMAC_MOD::_read_MACSTATUS(const emac_ac_t &ac) {
    return m_p->m_R_macstatus.get();
  }

  // ------------------------------------------------------------------
  uint32_t EMAC_MOD::_read_INTSTATRAW(const emac_ac_t &ac) {
    return m_p->m_R_interrupts.pending_R((emac_regint_e) ac.index);
  }

  // ------------------------------------------------------------------
  uint32_t EMAC_MOD::_read_INTSTATMASKED(const emac_ac_t &ac) {
    return m_p->m_R_interrupts.masked_R((emac_regint_e) ac.index);
  }

  // -----------------------------------------------------------------
  void EMAC_MOD::_write_INTMASKSET(const emac_ac_t &ac, uint32_t data) {
    m_p->m_R_interrupts.set_enabled_mask_R((emac_regint_e) ac.index, data);
    this->_update_iir();
  }

  uint32_t EMAC_MOD::_read_INTMASKSET(const emac_ac_t &ac) {
    return m_p->m_R_interrupts.enabled_R((emac_regint_e) ac.index);
  }

  // ------------------------------------------------------------------
  void EMAC_MOD::_write_INTMASKCLEAR(const emac_ac_t &ac, uint32_t data) {
    m_p->m_R_interrupts.clr_enabled_mask_R((emac_regint_e) ac.index, data);
    this->_update_iir();
  }

  // ------------------------------------------------------------------
  uint32_t EMAC_MOD::_read_RXMBPENABLE(const emac_ac_t &ac) {
    return m_p->m_R_mbpena.get();
  }

  void EMAC_MOD::_write_RXMBPENABLE(const emac_ac_t &ac, uint32_t data) {
    if ((data & ~EMAC_MBPENA::b_MASK))
      warning() << "garbage in RXMBPENABLE value" << std::endl;
    m_p->m_R_mbpena.set(data);

    if (m_p->m_R_mbpena.rx_pass_crc()) {
      error() << "MBPENABLE: PASS CRC: unsupported" << std::endl;
      abort();
    }

    if (m_p->m_R_mbpena.rx_qos()) {
      error() << "MBPENABLE: QOS: unsupported" << std::endl;
      abort();
    }

    if (m_p->m_R_mbpena.rx_no_chain()) {
      error() << "MBPENABLE: NO CHAIN: unsupported" << std::endl;
      abort();
    }
  }

  // ------------------------------------------------------------------
  uint32_t EMAC_MOD::_read_STATS(const emac_ac_t &ac) {
    return m_p->m_R_stats[ac.index];
  }

  void EMAC_MOD::_write_STATS(const emac_ac_t &ac, uint32_t data) {
    if (m_p->m_R_maccontrol.gmiien()) {
      if (data > m_p->m_R_stats[ac.index])
        data = m_p->m_R_stats[ac.index];
      m_p->m_R_stats.set(ac.index, m_p->m_R_stats[ac.index] - data);
    } else
      m_p->m_R_stats.set(ac.index, data);
    this->_update_stats_iir();
  }

  // ------------------------------------------------------------------
  uint32_t EMAC_MOD::_read_RXFILTERLOWTHRESH(const emac_ac_t &ac) {
    return m_p->m_R_rxfilterlowthresh;
  }

  void EMAC_MOD::_write_RXFILTERLOWTHRESH(const emac_ac_t &ac, uint32_t data) {
    if ((data & 0xFFFFFF00))
      warning() << "garbage in RXFILTERLOWTHRESH value" << std::endl;
    m_p->m_R_rxfilterlowthresh = (data & 0xFF);
  }

  // ------------------------------------------------------------------
  uint32_t EMAC_MOD::_read_RXFLOWTHRESH(const emac_ac_t &ac) {
    return m_p->m_R_channels[ac.index].flowthresh;
  }

  void EMAC_MOD::_write_RXFLOWTHRESH(const emac_ac_t &ac, uint32_t data) {
    if (!(data & 0xffff))
      warning() << "garbage in RXFLOWTHRESH value" << std::endl;
    m_p->m_R_channels[ac.index].flowthresh = (data & 0xffff);
  }

  // ------------------------------------------------------------------
  uint32_t EMAC_MOD::_read_RXFREEBUFFER(const emac_ac_t &ac) {
    return m_p->m_R_channels[ac.index].freebufs;
  }

  void EMAC_MOD::_write_RXFREEBUFFER(const emac_ac_t &ac, uint32_t data) {
    if (!(data & 0xffff))
      warning() << "garbage in RXFREEBUFFER value" << std::endl;
    m_p->m_R_channels[ac.index].freebufs += (data & 0xffff);
    m_p->m_R_channels[ac.index].freebufs &= 0xffff;
  }

  // ------------------------------------------------------------------
  uint32_t EMAC_MOD::_read_MACINTVECTOR(const emac_ac_t &ac) {
    return m_p->m_R_interrupts.masked();
  }

  // ------------------------------------------------------------------
  void EMAC_MOD::_write_MACEOIVECTOR(const emac_ac_t &ac, uint32_t data) {
    if (data > 4 * EMAC_CONTROL::NCOREGRPS) {
      warning()
        << "cannot acknowledge unknown interrupt "
        << "[" << std::hex << data << "]"
        << std::endl;
    } else {
      size_t group = data / 4;
      size_t kind  = data % 4;

      if (kind <= 1)
        kind = 1 - kind;        // WARN: swap RX <-> RWTHRESH
      this->m_EMAC.emac_control().acknowledge(group, (emac_intkind_e) kind);
    }
  }

  // ------------------------------------------------------------------
  void EMAC_MOD::_reset() {
    for (size_t i = 0; i < NCHANNELS; ++i)
      this->m_p->m_R_channels[i] = EMAC_Channel();

    this->m_p->m_R_rxbufoffset       = 0;
    this->m_p->m_R_rxmaxlen          = 0x5EE;
    this->m_p->m_R_machash           = 0;
    this->m_p->m_R_control           = 0;
    this->m_p->m_R_fifoctrl          = 0x02;
    this->m_p->m_R_emcontrol         = 0;
    this->m_p->m_R_macindex          = 0;
    this->m_p->m_R_rxfilterlowthresh = 0;

    this->m_p->m_R_macsrc = EtherAddress();

    this->m_p->m_R_maccontrol = EMAC_R_MACCTRL();
    this->m_p->m_R_macstatus  = EMAC_R_MACSTATUS();
    this->m_p->m_R_mbpena     = EMAC_MBPENA();

    this->m_p->m_R_interrupts.reset();

    this->m_p->m_R_stats = EMAC_Stats();
  }

  // ------------------------------------------------------------------
  void EMAC_MOD::_update_iir() {
    for (size_t i = 0; i < NCHANNELS; ++i) {
      this->_update_tx_iir(i);
      this->_update_rx_iir(i);
    }
    this->_update_stats_iir();
  }

  // ------------------------------------------------------------------
  void EMAC_MOD::_update_tx_iir(uint8_t chan) {
    bool status = !m_p->m_R_channels[chan].tx().synced();
    m_p->m_R_interrupts.set_pending(IT_TX, chan, status);
    status = m_p->m_R_interrupts.masked(IT_TX, chan);
    m_EMAC.emac_control().update_tx_for_chan(chan, status);
  }

  // ------------------------------------------------------------------
  void EMAC_MOD::_update_rx_iir(uint8_t chan) {
    bool status = !m_p->m_R_channels[chan].rx().synced();
    m_p->m_R_interrupts.set_pending(IT_RX, chan, status);
    status = m_p->m_R_interrupts.masked(IT_RX, chan);
    m_EMAC.emac_control().update_rx_for_chan(chan, status);
  }

  // ------------------------------------------------------------------
  void EMAC_MOD::_update_stats_iir() {
    bool status = (bool) m_p->m_R_stats.vhalfovf();
    m_p->m_R_interrupts.set_pending(IT_MISC, IT_MC_STATS, status);
    status = m_p->m_R_interrupts.masked(IT_MISC);
    m_EMAC.emac_control().update_mc(IT_MC_STATS, status);
  }

  // ------------------------------------------------------------------
  void EMAC_MOD::_hosterror() { // FIXME
    error()
      << "TI AM1x EMAC MODULE: host error not supported"
      << std::endl;
    abort();
  }


  // ------------------------------------------------------------------
  void EMAC_MOD_Private::update_framesize_stats(size_t pksize) {
    if (pksize == 64)
      m_R_stats.increment(FRAME64);
    else if (pksize <= 127)
      m_R_stats.increment(FRAME65T127);
    else if (pksize <= 255)
      m_R_stats.increment(FRAME128T255);
    else if (pksize <= 511)
      m_R_stats.increment(FRAME256T511);
    else if (pksize <= 1023)
      m_R_stats.increment(FRAME512T1023);
    else if (pksize <= this->m_R_rxmaxlen)
      m_R_stats.increment(FRAME1024TUP);
  }

  // ------------------------------------------------------------------
  void EMAC_MOD_Private::update_rx_stats(bool delivered, size_t pksize,
                                         EtherAddress::kind_e macclass,
                                         pk_rx_error error)
  {
    if (error != PK_RX_CRCERR) {
      m_R_stats.increment(NETOCTETS, pksize);
      this->update_framesize_stats(pksize);
    }

    switch (error) {
    case PK_RX_NOERROR:
      if (delivered) {
        m_R_stats.increment(RXGOODFRAMES);
        m_R_stats.increment(RXOCTETS, pksize);
        if (macclass == EtherAddress::BROADCAST)
          m_R_stats.increment(RXBCASTFRAMES);
        if (macclass == EtherAddress::MULTICAST)
          m_R_stats.increment(RXMCASTFRAMES);
      } else
        m_R_stats.increment(RXFILTERED);
      break ;

    case PK_RX_CRCERR:
      m_R_stats.increment(RXCRCERRORS);
      break ;

    case PK_RX_FRAGMENT:
      m_R_stats.increment(RXFRAGMENTS);

    case PK_RX_JABBER:
      m_R_stats.increment(delivered ? RXJABBER : RXFILTERED);
      break ;

    case PK_RX_OVERSZE:
      m_R_stats.increment(delivered ? RXOVERSIZED : RXFILTERED);
      break ;

    case PK_RX_UNDERSZE:
      m_R_stats.increment(delivered ? RXUNDERSIZED : RXFILTERED);
      break ;
    }
  }

  // ------------------------------------------------------------------
  void EMAC_MOD_Private::update_tx_stats(size_t pksize,
                                         EtherAddress::kind_e macclass)
  {
    m_R_stats.increment(NETOCTETS, pksize);
    m_R_stats.increment(TXGOODFRAMES);
    this->update_framesize_stats(pksize);
  }

  // ------------------------------------------------------------------
#define CHECK_OR_HOSTERROR(C) \
  if (!(C)) { this->_hosterror(); return ; }

  // ------------------------------------------------------------------
  void EMAC_MOD::_try_tx_1() {
    for (size_t i = NCHANNELS; i != 0;) {
      EMAC_Channel &channel = m_p->m_R_channels[--i];

      if (channel.tx().cp == 0)
        continue ;

      struct pkhead_s pkhead;

      this->_read_pkhead(channel.tx().cp, pkhead);

      CHECK_OR_HOSTERROR(pkhead.flags & PKHEAD_SOP);

      std::auto_ptr<EtherBuffer> buffer;

      uint32_t     origaddr = channel.tx().cp;
      uint32_t     address  = channel.tx().cp;
      uint16_t     offset   = pkhead.buf_offset;
      uint32_t     position = 0;

      CHECK_OR_HOSTERROR(pkhead.pkg_length >= 6+6+2); // 2*MAC + ETHER-TYPE

      buffer.reset(new EtherBuffer(pkhead.pkg_length));

      while (true) {
        CHECK_OR_HOSTERROR((buffer->length() - position) >= pkhead.buf_length);
        _rd(buffer->at(position),
            pkhead.p_buffer + offset,
            pkhead.buf_length);
        position += pkhead.buf_length;
        if ((pkhead.flags & PKHEAD_EOP))
          break ;
        CHECK_OR_HOSTERROR((address = pkhead.next) != 0);
        this->_read_pkhead(pkhead.next, pkhead);
      }

      channel.tx().cp_sync_emac = channel.tx().cp;
      channel.tx().cp = pkhead.next;

      CHECK_OR_HOSTERROR(position == buffer->length());

      try {
        m_transport->send(*buffer);
      } catch (EtherTransport_Exn e) {
        error()
          << "transport failure (send): " << e.what()
          << std::endl;
        abort();
      }

      { EtherAddress destination(buffer->at(0));
        m_p->update_tx_stats(buffer->length() + 4, destination.classify()); }

      buffer.release();

      _wr_16(origaddr + PKHEAD_OFF_FLAGS,
             (~PKHEAD_OWN) & _rd_16(origaddr + PKHEAD_OFF_FLAGS));

      if (pkhead.next == 0)
        _wr_16(address + PKHEAD_OFF_FLAGS,
               PKHEAD_EOQ | _rd_16(address + PKHEAD_OFF_FLAGS));

      this->_update_tx_iir(i);

      break ;
    }
  }

  // ------------------------------------------------------------------
  void EMAC_MOD::_try_rx_1(const EtherBuffer &buffer) {
    m_p->m_R_stats.increment(NETOCTETS, buffer.length() + 4);

    int tochannel = -1;
    EtherAddress::kind_e macclass = EtherAddress::UNICAST;

    // Search of a matching channel (disregarding errors)
    if (buffer.length() >= 6+6+2) { // 2*MAC + ETHER-TYPE
      EtherAddress destination(buffer.at(0));

      switch ((macclass = destination.classify())) {
      case EtherAddress::MULTICAST:
        warning()
          << "Ethernet frames with multicast addresses not supported"
          << std::endl;
        return ;

      case EtherAddress::UNICAST:
        for (size_t i = 0; i < NMACS; ++i) {
          EMAC_MacAddress &mac = m_p->m_R_macs[i];

          if (!mac.isvalid || mac.address != destination)
            continue ;
          if (!mac.ismatch)
            break ;
          if (!m_p->m_R_channels[mac.channel].unicast)
            continue ;
          tochannel = mac.channel;
          break ;               // for-break
        }
        break ;                 // case-break

      case EtherAddress::BROADCAST:
        if (m_p->m_R_mbpena.rx_broadcast())
          tochannel = m_p->m_R_mbpena.rx_broadcast_chan();
        break ;
      }
    }

    // Search for errors
    const bool  crcok    = true; // One day, PHY layer will give the CRC
    pk_rx_error rx_error = PK_RX_NOERROR;

    if (buffer.length() < (64-4)) // (NO CRC => -4)
      rx_error = crcok ? PK_RX_UNDERSZE : PK_RX_FRAGMENT;
    else if (buffer.length() > (uint32_t) (m_p->m_R_rxmaxlen-4))
      rx_error = crcok ? PK_RX_OVERSZE : PK_RX_JABBER;
    else if (!crcok)
      rx_error = PK_RX_CRCERR;

    // Finalize routing (based on matching channel and errors)
    bool match   = (tochannel >= 0);
    bool deliver = false;

    if (match || m_p->m_R_mbpena.rx_CAF()) {
      switch (rx_error) {
      case PK_RX_NOERROR:
        deliver = true;
        break ;

      case PK_RX_UNDERSZE:
        deliver = m_p->m_R_mbpena.rx_CSF();
        break ;

      case PK_RX_FRAGMENT:
      case PK_RX_OVERSZE:
      case PK_RX_JABBER:
      case PK_RX_CRCERR:
        deliver = m_p->m_R_mbpena.rx_CEF();
        break ;
      }
    }

    m_p->update_rx_stats(deliver, buffer.length()+4, macclass, rx_error);

    if (!deliver)
      return ;

    if (!match)
      tochannel = m_p->m_R_mbpena.rx_promisc_chan();

    // Next, copy receive frames to selected channel
    assert(tochannel >= 0 && tochannel < (int) NCHANNELS);

    EMAC_Channel &channel = m_p->m_R_channels[tochannel];

    if (channel.rx().cp == 0) {    // Start of frame overrun
      m_p->m_R_stats.increment(RXSOFOVERRUNS);
      m_p->m_R_stats.increment(RXDMAOVERRUNS);
      return ;
    }

    struct pkhead_s pkhead;

    uint32_t lastrxcp = channel.rx().cp;
    uint32_t position = 0;
    uint32_t offset   = m_p->m_R_rxbufoffset;
    uint32_t tocopy   = 0;
    uint32_t blength  = std::min(buffer.length(), (size_t) m_p->m_R_rxmaxlen);

    // Do not copy more than m_R_rxmaxlen
    while (lastrxcp != 0 && position < blength) {
      this->_read_pkhead(lastrxcp, pkhead);

      CHECK_OR_HOSTERROR(offset <= pkhead.buf_length)

      tocopy =
        std::min<uint32_t>(pkhead.buf_length - offset,
                           blength - position);

      this->_wr(buffer.at(0), pkhead.p_buffer + offset, tocopy);
      position += tocopy;
    }

    if (position < blength) { // Middle of frame overrun
      m_p->m_R_stats.increment(RXMOFOVERRUNS);
      m_p->m_R_stats.increment(RXDMAOVERRUNS);
      return ;
    }

    // First header (real length)
    _wr_16(channel.rx().cp + PKHEAD_OFF_PKG_LENGTH, buffer.length());
    // Last header
    _wr_16(lastrxcp + PKHEAD_OFF_BUF_LENGTH, offset + tocopy);

    if (offset != 0)
      _wr_16(channel.rx().cp + PKHEAD_OFF_BUF_OFFSET, offset); // First header

    uint16_t flags = (uint16_t) rx_error;

    flags |= PKHEAD_SOP | PKHEAD_EOP | (pkhead.next ? 0 : PKHEAD_EOQ);
    flags &= ~PKHEAD_OWN;
    _wr_16(channel.rx().cp + PKHEAD_OFF_FLAGS, flags); // First header

    channel.rx().cp_sync_emac = channel.rx().cp;
    channel.rx().cp = pkhead.next;

    this->_update_rx_iir(tochannel);
  }

  // ------------------------------------------------------------------
  void EMAC_MOD::_tx_thread() {
    // FIXME: priority

    while (true) {
      bool txempty = true;

      for (size_t i = 0; i < NCHANNELS; ++i) {
        if (m_p->m_R_channels[i].tx().cp != 0) {
          txempty = false; break ;
        }
      }

      if (txempty) this->wait(_tx_event);
      this->_try_tx_1();
      this->_update_stats_iir();
      this->wait(10, sc_core::SC_US);
    }
  }

  // ------------------------------------------------------------------
  void EMAC_MOD::_rx_thread() {
    EtherBuffer buffer(65535u);

    while (true) {
      sc_core::sc_time towait(30, sc_core::SC_US);

      this->wait(towait);

      bool rr;

      try {
        rr = m_transport->recv(buffer);
      } catch (EtherTransport_Exn e) {
        error()
          << "transport failure (recv): " << e.what()
          << std::endl;
        abort();
      }

      if (rr) {
        this->_try_rx_1(buffer);
        this->_update_stats_iir();
      }
    }
  }

} // namespace TI_AM1x
} // namespace simsoc
