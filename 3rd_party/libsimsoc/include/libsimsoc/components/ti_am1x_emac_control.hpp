//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#if !defined (LIBSIMSOC_TI_AM1X_EMAC_CONTROL_HPP__)
# define LIBSIMSOC_TI_AM1X_EMAC_CONTROL_HPP__

# include "libsimsoc/module.hpp"
# include "libsimsoc/interfaces/tlm.hpp"
# include "libsimsoc/interfaces/tlm_signal.hpp"
# include "libsimsoc/bitwise_operator.hpp"

# include "libsimsoc/components/ti_am1x_core.hpp"
# include "libsimsoc/components/ti_am1x_emac.hpp"
# include "libsimsoc/components/ti_am1x_emac_module.hpp"

# include <inttypes.h>

namespace simsoc  {
namespace TI_AM1x {

  // ------------------------------------------------------------------
  struct emac_ctrl_ac_t;        // registers accessors function type

  // --------------------------------------------------------------------
  class EMAC_CONTROL_Private;   // Internal datas

  // ------------------------------------------------------------------
  class EMAC_CONTROL
    : public TI_AM1x_core<EMAC_CONTROL>
  {
  public:
    static const uint32_t REVID = 0x4EC80100;

  public:
    EMAC_CONTROL(sc_core::sc_module_name name);
    virtual ~EMAC_CONTROL();

  public:
    static const size_t NCOREGRPS = 3;

  public:
    typedef signals::SignalInitiatorPort_Level outsignal_t;

    outsignal_t& get_signal(size_t group, emac_intkind_e kind);

  public:
    void update_tx_for_chan(uint8_t chan, bool status);
    void update_rx_for_chan(uint8_t chan, bool status);
    void update_mc(emac_intmisc_e it, bool status);
    void acknowledge(size_t group, emac_intkind_e kind);

  protected:
    void _reset();

  protected:
    virtual uint32_t read_word (uint32_t address);
    virtual void     write_word(uint32_t address, uint32_t value);

  protected:
    EMAC_CONTROL_Private *m_p;

  protected:
    typedef void     (writer_t)(const emac_ctrl_ac_t &ac, uint32_t data);
    typedef uint32_t (reader_t)(const emac_ctrl_ac_t &ac);

    writer_t
      /* REVID  */ _wr_SOFTRESET, _wr_INTCONTROL,
      _wr_CENABLE, /* CSTAT    */ _wr_CRXIMAX   ,
      _wr_CTXIMAX;

    reader_t
      _rd_REVID  , _rd_SOFTRESET, _rd_INTCONTROL,
      _rd_CENABLE, _rd_CSTAT    , _rd_CRXIMAX   ,
      _rd_CTXIMAX;

  protected:
    typedef void     (EMAC_CONTROL::*ptr_writer_t)(const emac_ctrl_ac_t &ac, uint32_t data);
    typedef uint32_t (EMAC_CONTROL::*ptr_reader_t)(const emac_ctrl_ac_t &ac);

    struct ac_access_t {
      ptr_reader_t reader;
      ptr_writer_t writer;
    };

    static const ac_access_t accessors[];
  };

} // namespace TI_AM1x
} // namespace simsoc

#endif // !LIBSIMSOC_TI_AM1X_EMAC_CONTROL_HPP__
