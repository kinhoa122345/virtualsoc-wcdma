//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#if !defined (LIBSIMSOC_TI_AM1X_EMAC_MODULE_HPP__)
# define LIBSIMSOC_TI_AM1X_EMAC_MODULE_HPP__

# include "libsimsoc/module.hpp"
# include "libsimsoc/interfaces/tlm.hpp"
# include "libsimsoc/interfaces/tlm_signal.hpp"
# include "libsimsoc/bitwise_operator.hpp"
# include "libsimsoc/components/ti_am1x_core.hpp"
# include "libsimsoc/components/ti_am1x_emac.hpp"

# include <inttypes.h>

namespace simsoc {              // Forward declaration (transport)
  class IEtherTransport;
  class EtherBuffer;
}

namespace simsoc  {
namespace TI_AM1x {

  // --------------------------------------------------------------------
  enum emac_intkind_e {         // Order as MACINTVECTOR register
    IT_RX       = 0x00,
    IT_RXTHRESH = 0x01,
    IT_TX       = 0x02,
    IT_MISC     = 0x03,
  };

  enum emac_intmisc_e {
    IT_MC_LINK  = 0x00,
    IT_MC_USER  = 0x01,
    IT_MC_HOST  = 0x02,
    IT_MC_STATS = 0x03,
  };

  // --------------------------------------------------------------------
  struct pkhead_s;              // Packet descriptor header
  struct emac_ac_t;             // registers accessors function type

  // --------------------------------------------------------------------
  class EMAC_MOD_Private;       // Internal datas

  // --------------------------------------------------------------------
  class EMAC_MOD
    : public TI_AM1x_core<EMAC_MOD>
    , public TI_AM1x_oport<EMAC_MOD>
  {
    SC_HAS_PROCESS(EMAC_MOD);

  public:
    static const uint32_t TX_REVID = 0x4EC0020D;
    static const uint32_t RX_REVID = 0x4EC0020D;

    static const uint32_t MACCONFIG
      = (0x03 << 24)            // TX-FIFO depth
      | (0x03 << 16)            // RX-FIFO depth
      | (0x02 <<  8)            // Address type
      | (0x02 <<  0);           // MACCFIG (board hard-coded)

  public:
    static const size_t NCHANNELS = EMAC::NCHANNELS;
    static const size_t NMACS     = EMAC::NMACS;

  public:
    EMAC_MOD(sc_core::sc_module_name name, EMAC &emac);
    virtual ~EMAC_MOD();

  public:
    void set_transport(IEtherTransport *transport);

  protected:                    // SimSoC
    void end_of_elaboration();

  protected:
    EMAC &m_EMAC;
    EMAC_MOD_Private *m_p;

  protected:                    // TLM interface
    virtual uint32_t read_word (uint32_t address);
    virtual void     write_word(uint32_t address, uint32_t value);

  protected:
    static const size_t ACK_INT_MAX = 0xB; // FIXME: REMOVE

    void _reset();
    void _initiate_txrx();

    void _update_iir();
    void _update_tx_iir(uint8_t chan);
    void _update_rx_iir(uint8_t chan);
    void _update_stats_iir();
    void _hosterror();

    void _tx_thread();
    void _rx_thread();

    void _try_rx_1(const EtherBuffer &buffer);
    void _try_tx_1();

  protected:
    void _read_pkhead(uint32_t address, struct pkhead_s &pk);

  protected:
    sc_core::sc_event  _tx_event;
    IEtherTransport   *m_transport;

  protected:                    // AC <-> REG
    typedef void     (writer_t)(const emac_ac_t &ac, uint32_t data);
    typedef uint32_t (reader_t)(const emac_ac_t &ac);

    writer_t
      /* REVID          */ _write_CONTROL       , _write_TEARDOWN         ,
      /* INTSTATRAW     */ /* INTSTATMASKED    */ _write_INTMASKSET       ,
      _write_INTMASKCLEAR, /* MACINTVECTOR     */ _write_MACEOIVECTOR     ,
      _write_RXMBPENABLE , _write_RXUNICASTSET  , _write_RXUNICASTCLEAR   ,
      _write_RXMAXLEN    , _write_RXBUFFEROFFSET, _write_RXFILTERLOWTHRESH,
      _write_RXFLOWTHRESH, _write_RXFREEBUFFER  , _write_MACCONTROL       ,
      /* MACSTATUS      */ _write_EMCONTROL     , _write_FIFOCONTROL      ,
      /* MACCONFIG      */ _write_SOFTRESET     , _write_MACSRCADDR       ,
      _write_MACHASH     , /* BOFFTEST         */ /* TPACETEST           */
      /* PAUSE          */ _write_MACADDR       , _write_MACINDEX         ,
      _write_TXHDP       , _write_RXHDP         , _write_TXCP             ,
      _write_RXCP        , _write_STATS
    ;

    reader_t
      _read_REVID       , _read_CONTROL       , /* TEARDOWN           */
      _read_INTSTATRAW  , _read_INTSTATMASKED , _read_INTMASKSET       ,
      /* INTMASKCLEAR  */ _read_MACINTVECTOR  , /* MACEOIVECTOR       */
      _read_RXMBPENABLE , _read_RXUNICASTSET  , /* RXUNICASTCLEAR     */
      _read_RXMAXLEN    , _read_RXBUFFEROFFSET, _read_RXFILTERLOWTHRESH,
      _read_RXFLOWTHRESH, _read_RXFREEBUFFER  , _read_MACCONTROL       ,
      _read_MACSTATUS   , _read_EMCONTROL     , _read_FIFOCONTROL      ,
      _read_MACCONFIG   , _read_SOFTRESET     , _read_MACSRCADDR       ,
      _read_MACHASH     , _read_BOFFTEST      , _read_TPACETEST        ,
      _read_PAUSE       , _read_MACADDR       , _read_MACINDEX         ,
      _read_TXHDP       , _read_RXHDP         , _read_TXCP             ,
      _read_RXCP        , _read_STATS
    ;

  protected:                    // ADDRESS <-> REG
    typedef void     (EMAC_MOD::*ptr_writer_t)(const emac_ac_t &ac, uint32_t data);
    typedef uint32_t (EMAC_MOD::*ptr_reader_t)(const emac_ac_t &ac);

    struct ac_access_t {
      ptr_reader_t reader;
      ptr_writer_t writer;
    };

    static const ac_access_t accessors[];
  };

} // namespace TI_AM1x
} // namespace simsoc

#endif // !LIBSIMSOC_TI_AM1X_EMAC_MODULE_HPP__
