//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#if !defined (LIBSIMSOC_TI_AM1X_EMAC_MODULE_P_HPP__)
# define LIBSIMSOC_TI_AM1X_EMAC_MODULE_P_HPP__

# include "libsimsoc/components/ti_am1x_emac.hpp"
# include "libsimsoc/components/ti_am1x_emac_module.hpp"
# include "libsimsoc/network/ethernet/ether-address.hpp"
# include "libsimsoc/network/ethernet/ether-transport.hpp"

namespace simsoc  {
namespace TI_AM1x {

# define NCHANNELS EMAC::NCHANNELS
# define NMACS     EMAC::NMACS

  // ------------------------------------------------------------------
  enum emac_regint_e {
    REGINT_RX = 0x00,
    REGINT_TX = 0x01,
    REGINT_MC = 0x02,
  };

  // ------------------------------------------------------------------
# define PKHEAD_OFF_NEXT       ( 0u)
# define PKHEAD_OFF_P_BUFFER   ( 4u)
# define PKHEAD_OFF_BUF_LENGTH ( 8u)
# define PKHEAD_OFF_BUF_OFFSET (10u)
# define PKHEAD_OFF_PKG_LENGTH (12u)
# define PKHEAD_OFF_FLAGS      (14u)

# define PKHEAD_SOP      (((uint16_t) 1) << 15)
# define PKHEAD_EOP      (((uint16_t) 1) << 14)
# define PKHEAD_OWN      (((uint16_t) 1) << 13)
# define PKHEAD_EOQ      (((uint16_t) 1) << 12)
# define PKHEAD_TDOWN    (((uint16_t) 1) << 11)
# define PKHEAD_PASSCRC  (((uint16_t) 1) << 10)
# define PKHEAD_JABBER   (((uint16_t) 1) <<  9)
# define PKHEAD_OVERSZE  (((uint16_t) 1) <<  8)
# define PKHEAD_FRAGMENT (((uint16_t) 1) <<  7)
# define PKHEAD_UNDERSZE (((uint16_t) 1) <<  6)
# define PKHEAD_CONTROL  (((uint16_t) 1) <<  5)
# define PKHEAD_OVERRUN  (((uint16_t) 1) <<  4)
# define PKHEAD_CODEERR  (((uint16_t) 1) <<  3)
# define PKHEAD_ALGNERR  (((uint16_t) 1) <<  2)
# define PKHEAD_CRCERR   (((uint16_t) 1) <<  1)
# define PKHEAD_NOMATCH  (((uint16_t) 1) <<  0)

  enum pk_rx_error {
    PK_RX_NOERROR  = 0,
    PK_RX_UNDERSZE = PKHEAD_UNDERSZE, // < 64 bytes, no CRC error
    PK_RX_FRAGMENT = PKHEAD_FRAGMENT, // < 64 bytes,    CRC error
    PK_RX_OVERSZE  = PKHEAD_OVERSZE,  // > RXMAXLEN, no CRC error
    PK_RX_JABBER   = PKHEAD_JABBER,   // > EXMAXLEN,    CRC ERROR
    PK_RX_CRCERR   = PKHEAD_CRCERR,   // size ok, but invalid CRC
  };

  // ------------------------------------------------------------------
  class EMAC_INTVEC_Base {
  public:
    static const uint8_t masks[4];

  public:
    EMAC_INTVEC_Base() {
      this->reset();
    }

    virtual ~EMAC_INTVEC_Base() {}

    virtual void reset() {
      memset(m_pending, 0, sizeof(m_pending));
      memset(m_enabled, 0, sizeof(m_enabled));
    }

  public:
    uint32_t enabled() const { return u32_le(m_enabled) & u32_le(masks); }
    uint32_t pending() const { return u32_le(m_pending) & u32_le(masks); }
    uint32_t masked () const { return (enabled() & pending()); }

    uint32_t enabled(emac_intkind_e kind) const
    { return m_enabled[kind] & masks[kind]; }

    uint32_t pending(emac_intkind_e kind) const
    { return m_pending[kind] & masks[kind]; }

    uint32_t masked(emac_intkind_e kind) const
    { return enabled(kind) & pending(kind); }

    uint32_t enabled(emac_intkind_e kind, size_t off) const
    { return is_set<uint32_t>(enabled(kind), off); }

    uint32_t pending(emac_intkind_e kind, size_t off) const
    { return is_set<uint32_t>(pending(kind), off); }

    uint32_t masked(emac_intkind_e kind, size_t off) const
    { return is_set<uint32_t>(masked(kind), off); }

  public:
    void set_pending(emac_intkind_e kind, size_t off, bool status) {
      uint8_t mask = ((1 << off) & masks[kind]);

      status
        ? m_pending[kind] |=  mask
        : m_pending[kind] &= ~mask;
    }

    void set_enabled_mask(emac_intkind_e kind, uint8_t value) {
      m_enabled[kind] |= (value & masks[kind]);
    }

    void clr_enabled_mask(emac_intkind_e kind, uint8_t value) {
      m_enabled[kind] &= ~(value & masks[kind]);
    }

  protected:
    uint8_t m_pending[4];
    uint8_t m_enabled[4];
  };

  // ------------------------------------------------------------------
  class EMAC_INTVEC: public EMAC_INTVEC_Base {
  public:
    uint32_t pending_R(emac_regint_e kind) const {
      return _eoi_get(m_pending, kind);
    }

    uint32_t enabled_R(emac_regint_e kind) const {
      return _eoi_get(m_enabled, kind);
    }

    uint32_t masked_R(emac_regint_e kind) const
    { return pending_R(kind) & enabled_R(kind); }

  public:
    void set_enabled_mask_R(emac_regint_e kind, uint32_t mask) {
      this->_eoi_operation_R(&EMAC_INTVEC_Base::set_enabled_mask, kind, mask);
    }

    void clr_enabled_mask_R(emac_regint_e kind, uint32_t mask) {
      this->_eoi_operation_R(&EMAC_INTVEC_Base::clr_enabled_mask, kind, mask);
    }

  protected:
    typedef void (EMAC_INTVEC::*eoi_op_t)(emac_intkind_e, uint8_t);

    static uint32_t _eoi_get(const uint8_t *raw, emac_regint_e kind) {
      switch (kind) {
      case REGINT_RX:
        return
           (((uint32_t) raw[IT_RX      ]) << 0)
          |(((uint32_t) raw[IT_RXTHRESH]) << 8);
      case REGINT_TX: return (uint32_t) raw[IT_TX];
      case REGINT_MC: return (uint32_t) raw[IT_MISC];
      }
      abort();
    }

    void _eoi_operation_R(eoi_op_t call, emac_regint_e kind, uint32_t mask) {
      switch (kind) {
      case REGINT_RX:
        (this->*call)(IT_RX      , (mask >> 0) & 0xff);
        (this->*call)(IT_RXTHRESH, (mask >> 8) & 0xff);
        return ;

      case REGINT_TX:
        (this->*call)(IT_TX, mask & 0xff);
        return ;

      case REGINT_MC:
        (this->*call)(IT_MISC, (mask & 0x3) << 2);
        return ;
      }
      abort();
    }
  };

  // ------------------------------------------------------------------
  enum txrx_e { TXIDX, RXIDX, MACIDX };

  struct EMAC_Channel_Half {
    EMAC_Channel_Half()
      :hdp         (0)
      ,cp          (0)
      ,cp_sync_emac(0)
      ,cp_sync_host(0)
    {}

    bool synced() const
    { return cp_sync_emac == cp_sync_host; }

    uint32_t hdp;
    uint32_t cp;
    uint32_t cp_sync_emac;
    uint32_t cp_sync_host;
  };

  class EMAC_Channel {
  public:
    EMAC_Channel()
      :freebufs  (0)
      ,flowthresh(0)
      ,unicast   (false)
    {}

    EMAC_Channel_Half& rx() { return duplex[RXIDX]; }
    EMAC_Channel_Half& tx() { return duplex[TXIDX]; }

    EMAC_Channel_Half duplex[2];
    uint16_t          freebufs;
    uint16_t          flowthresh;
    bool              unicast;
  };

  // ------------------------------------------------------------------
  class EMAC_MacAddress {
  public:
    EMAC_MacAddress()
      :ismatch(false)
      ,isvalid(false)
      ,channel(0)
    {}

    EtherAddress address;
    bool         ismatch;
    bool         isvalid;
    uint8_t      channel;
  };

  // ------------------------------------------------------------------
  class EMAC_R_MACCTRL {
  public:
    typedef bits_t<uint32_t, 15> b_RMIISPEED;
    typedef bits_t<uint32_t, 14> b_RXOFFLENBLOCK;
    typedef bits_t<uint32_t, 13> b_RXOWNERSHIP;
    typedef bits_t<uint32_t, 11> b_CMDIDLE;
    typedef bits_t<uint32_t, 10> b_TXSHORTGAPEN;
    typedef bits_t<uint32_t,  9> b_TXPTYPE;
    typedef bits_t<uint32_t,  6> b_TXPACE;
    typedef bits_t<uint32_t,  5> b_GMIIEN;
    typedef bits_t<uint32_t,  4> b_TXFLOWLEN;
    typedef bits_t<uint32_t,  3> b_RXBUFFERFLOWEN;
    typedef bits_t<uint32_t,  1> b_LOOPBACK;
    typedef bits_t<uint32_t,  0> b_FULLDUPLEX;

    static const uint32_t b_MASK
      = b_RMIISPEED     ::mask
      | b_RXOFFLENBLOCK ::mask
      | b_RXOWNERSHIP   ::mask
      | b_CMDIDLE       ::mask
      | b_TXSHORTGAPEN  ::mask
      | b_TXPTYPE       ::mask
      | b_TXPACE        ::mask
      | b_GMIIEN        ::mask
      | b_TXFLOWLEN     ::mask
      | b_RXBUFFERFLOWEN::mask
      | b_LOOPBACK      ::mask
      | b_FULLDUPLEX    ::mask;

  public:
    EMAC_R_MACCTRL()
      :m_value(0)
    {}

  public:
    enum rmiispeed_e { RMII_10 = 0x0, RMII_100 = 0x1 };

    rmiispeed_e rmiispeed() const { return (rmiispeed_e) b_RMIISPEED::get(m_value); }

    bool rxofflenblock () const { return b_RXOFFLENBLOCK ::get(m_value); }
    bool rxownership   () const { return b_RXOWNERSHIP   ::get(m_value); }
    bool cmdidle       () const { return b_CMDIDLE       ::get(m_value); }
    bool txshortgapen  () const { return b_TXSHORTGAPEN  ::get(m_value); }
    bool txptype       () const { return b_TXPTYPE       ::get(m_value); }
    bool txpace        () const { return b_TXPACE        ::get(m_value); }
    bool gmiien        () const { return b_GMIIEN        ::get(m_value); }
    bool txflowlen     () const { return b_TXFLOWLEN     ::get(m_value); }
    bool rxbufferflowen() const { return b_RXBUFFERFLOWEN::get(m_value); }
    bool loopback      () const { return b_LOOPBACK      ::get(m_value); }
    bool fullduplex    () const { return b_FULLDUPLEX    ::get(m_value); }

  public:
    void     set(uint32_t value) { m_value = (value & b_MASK); }
    uint32_t get() const { return m_value; }

  private:
    uint32_t m_value;
  };

  // ------------------------------------------------------------------
  class EMAC_R_MACSTATUS {
  public:
    typedef bits_t<uint32_t, 31, 31> b_IDLE;
    typedef bits_t<uint32_t, 23, 20> b_TXERRCODE;
    typedef bits_t<uint32_t, 18, 16> b_TXERRCH;
    typedef bits_t<uint32_t, 15, 12> b_RXERRCODE;
    typedef bits_t<uint32_t, 12, 10> b_RXERRCH;
    typedef bits_t<uint32_t,  2,  2> b_RXQOSACT;
    typedef bits_t<uint32_t,  1,  1> b_RXFLOWACT;
    typedef bits_t<uint32_t,  0,  0> b_TXFLOWACT;

  public:
    EMAC_R_MACSTATUS()
      :m_value(0)
    {}

  public:
    enum rxerr_e {
      RXE_NONE   = 0x00,
      RXE_EINSOP = 0x01,
      RXE_ZEROBP = 0x04,
    };

    enum txerr_e {
      TXE_NONE     = 0x00,
      TXE_EINSOP   = 0x01,
      TXE_MISOWNER = 0x02,
      TXE_ZEROBP   = 0x04,
      TXE_ZEROLEN  = 0x05,
      TXE_WRONGLEN = 0x06,
    };

  public:
    rxerr_e rxerrcode() const { return (rxerr_e) b_RXERRCODE::get(m_value); }
    txerr_e txerrcode() const { return (txerr_e) b_TXERRCODE::get(m_value); }

    uint8_t rxerrch() const { return b_RXERRCH::get(m_value); }
    uint8_t txerrch() const { return b_TXERRCH::get(m_value); }

    bool idle     () const { return b_IDLE     ::get(m_value); }
    bool rxqosact () const { return b_RXQOSACT ::get(m_value); }
    bool rxflowact() const { return b_RXFLOWACT::get(m_value); }
    bool txflowact() const { return b_RXFLOWACT::get(m_value); }

  public:
    bool haserrors() const {
      return (rxerrcode() != RXE_NONE) || (txerrcode() != TXE_NONE);
    }

    void set_rxerror(uint8_t chan, rxerr_e code) {
      b_RXERRCODE::set(m_value, code);
      b_RXERRCH  ::set(m_value, chan);
    }

    void set_txerror(uint8_t chan, txerr_e code) {
      b_TXERRCODE::set(m_value, code);
      b_TXERRCH  ::set(m_value, chan);
    }

  public:
    uint32_t get() const { return m_value; }

  private:
    uint32_t m_value;
  };

  // ------------------------------------------------------------------
  class EMAC_MBPENA {
  public:
    typedef bits_t<uint32_t, 30> b_RXPASSCRC;
    typedef bits_t<uint32_t, 29> b_RXQOSEN;
    typedef bits_t<uint32_t, 28> b_RXNOCHAIN;
    typedef bits_t<uint32_t, 24> b_RXCMFEN;
    typedef bits_t<uint32_t, 23> b_RXCSFEN;
    typedef bits_t<uint32_t, 22> b_RXCEFEN;
    typedef bits_t<uint32_t, 21> b_RXCAFEN;
    typedef bits_t<uint32_t, 13> b_RXBROAEN;
    typedef bits_t<uint32_t,  5> b_RXMULTEN;

    typedef bits_t<uint32_t, 18, 16> b_RXPROMCH;
    typedef bits_t<uint32_t, 10,  8> b_RXBROADCH;
    typedef bits_t<uint32_t,  2,  0> b_RXMULTCH;

    static const uint32_t b_MASK
      = b_RXPASSCRC::mask
      | b_RXQOSEN  ::mask
      | b_RXNOCHAIN::mask
      | b_RXCMFEN  ::mask
      | b_RXCSFEN  ::mask
      | b_RXCEFEN  ::mask
      | b_RXCAFEN  ::mask
      | b_RXBROAEN ::mask
      | b_RXMULTEN ::mask
      | b_RXPROMCH ::mask
      | b_RXBROADCH::mask
      | b_RXMULTCH ::mask;

  public:
    EMAC_MBPENA()
      :m_value(0)
    {}

    bool rx_pass_crc () const { return b_RXPASSCRC::get(m_value); }
    bool rx_qos      () const { return b_RXQOSEN  ::get(m_value); }
    bool rx_no_chain () const { return b_RXNOCHAIN::get(m_value); }
    bool rx_CMF      () const { return b_RXCMFEN  ::get(m_value); }
    bool rx_CSF      () const { return b_RXCSFEN  ::get(m_value); }
    bool rx_CEF      () const { return b_RXCEFEN  ::get(m_value); }
    bool rx_CAF      () const { return b_RXCAFEN  ::get(m_value); }
    bool rx_broadcast() const { return b_RXBROAEN ::get(m_value); }
    bool rx_multicast() const { return b_RXMULTEN ::get(m_value); }

    uint8_t rx_promisc_chan  () const { return b_RXPROMCH ::get(m_value); }
    uint8_t rx_broadcast_chan() const { return b_RXBROADCH::get(m_value); }
    uint8_t rx_multicast_chan() const { return b_RXMULTCH ::get(m_value); }

  public:
    uint32_t get() const { return m_value; }
    void set(uint32_t value) { m_value = (value & b_MASK); }

  private:
    uint32_t m_value;
  };

  // ------------------------------------------------------------------
  enum emac_stat {
    RXGOODFRAMES     ,
    RXBCASTFRAMES    ,
    RXMCASTFRAMES    ,
    RXPAUSEFRAMES    ,
    RXCRCERRORS      ,
    RXALIGNCODEERRORS,
    RXOVERSIZED      ,
    RXJABBER         ,
    RXUNDERSIZED     ,
    RXFRAGMENTS      ,
    RXFILTERED       ,
    RXQOSFILTERED    ,
    RXOCTETS         ,
    TXGOODFRAMES     ,
    TXBCASTFRAMES    ,
    TXMCASTFRAMES    ,
    TXPAUSEFRAMES    ,
    TXDEFERRED       ,
    TXCOLLISION      ,
    TXSINGLECOLL     ,
    TXMULTICOLL      ,
    TXEXCESSIVECOLL  ,
    TXLATECOLL       ,
    TXUNDERRUN       ,
    TXCARRIERSENSE   ,
    TXOCTETS         ,
    FRAME64          ,
    FRAME65T127      ,
    FRAME128T255     ,
    FRAME256T511     ,
    FRAME512T1023    ,
    FRAME1024TUP     ,
    NETOCTETS        ,
    RXSOFOVERRUNS    ,
    RXMOFOVERRUNS    ,
    RXDMAOVERRUNS    ,
  };

  // --------------------------------------------------------------------
  class EMAC_Stats {
  public:
    static const size_t NSTATS = 36u;

    EMAC_Stats()
      :m_vhalfovf(0)
    {
      memset(m_stats, 0, sizeof(m_stats));
    }

  public:
    uint32_t operator[](unsigned idx) {
      return this->m_stats[idx];
    }

    void set(unsigned idx, uint32_t value) {
      int hov1 = (m_stats[idx] & 0x8000000) ? 1 : 0;
      this->m_stats[idx] = value;
      int hov2 = (m_stats[idx] & 0x8000000) ? 1 : 0;
      m_vhalfovf += hov2 - hov1;
    }

    void increment(unsigned idx, uint32_t incr = 1) {
      this->set(idx, m_stats[idx]+incr);
    }

    unsigned vhalfovf() const { return m_vhalfovf; }

  protected:
    uint32_t m_stats[NSTATS];
    unsigned m_vhalfovf;
  };


  class EMAC_MOD_Private {
  public:
    EMAC_MOD_Private(EMAC_MOD &d)
      :m_d(d)
    {}

    EMAC_MOD        &m_d;
    EMAC_Channel     m_R_channels[NCHANNELS];
    EMAC_MacAddress  m_R_macs[NMACS];
    uint16_t         m_R_rxbufoffset;
    uint16_t         m_R_rxmaxlen;
    uint64_t         m_R_machash;
    uint32_t         m_R_control;
    uint32_t         m_R_fifoctrl;
    uint32_t         m_R_emcontrol;
    uint32_t         m_R_macindex;
    uint8_t          m_R_rxfilterlowthresh;
    EtherAddress     m_R_macsrc;
    EMAC_R_MACCTRL   m_R_maccontrol;
    EMAC_R_MACSTATUS m_R_macstatus;
    EMAC_INTVEC      m_R_interrupts;
    EMAC_MBPENA      m_R_mbpena;
    EMAC_Stats       m_R_stats;

  public:
    void update_rx_stats(bool delivered, size_t pksize,
                         EtherAddress::kind_e macclass,
                         pk_rx_error error);

    void update_tx_stats(size_t pksize,
                         EtherAddress::kind_e macclass);

    void update_framesize_stats(size_t pksize);
  };

} // namespace TI_AM1x
} // namespace simsoc

#endif // !LIBSIMSOC_TI_AM1X_EMAC_MODULE_P_HPP__
