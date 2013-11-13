//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#if !defined (LIBSIMSOC_TI_AM1X_TIMER64_HPP__)
# define LIBSIMSOC_TI_AM1X_TIMER64_HPP__

# include "libsimsoc/module.hpp"
# include "libsimsoc/command_line.hpp"
# include "libsimsoc/interfaces/tlm.hpp"
# include "libsimsoc/interfaces/tlm_signal.hpp"
# include "libsimsoc/components/ti_am1x_core.hpp"

namespace simsoc  {
namespace TI_AM1x {

  // ------------------------------------------------------------------
  class Timer64_R_Timer;

  // ------------------------------------------------------------------
  class Timer64: public TI_AM1x_core<Timer64> {
    friend class Timer64_R_Timer;

    SC_HAS_PROCESS(Timer64);

  public:
    static const uint32_t REVID = 0x44720211;

    static const uint32_t RA_REVID      = 0x0000;
    static const uint32_t RA_EMUMGT     = 0x0004;
    static const uint32_t RA_GPINTGPEN  = 0x0008;
    static const uint32_t RA_GPDATGPDIR = 0x000C;
    static const uint32_t RA_TIM12      = 0x0010;
    static const uint32_t RA_TIM34      = 0x0014;
    static const uint32_t RA_PRD12      = 0x0018;
    static const uint32_t RA_PRD34      = 0x001C;
    static const uint32_t RA_TCR        = 0x0020;
    static const uint32_t RA_TGCR       = 0x0024;
    static const uint32_t RA_WDTCR      = 0x0028;
    static const uint32_t RA_REL12      = 0x0034;
    static const uint32_t RA_REL34      = 0x0038;
    static const uint32_t RA_CAP12      = 0x003C;
    static const uint32_t RA_CAP34      = 0x0040;
    static const uint32_t RA_INTCTLSTAT = 0x0044;
    static const uint32_t RA_CMP        = 0x0060;

    static const size_t N_COMPARE_REGS = 8;

  public:
    enum tmpart_e { TM_LO = 0x00, TM_HI = 0x01 };

    typedef signals::SignalInitiatorPort_Level tim_signal_t;
    typedef signals::SignalInitiatorPort_Pulse cmp_signal_t;

    tim_signal_t& get_tim_signal(tmpart_e id);
    cmp_signal_t& get_cmp_signal(size_t   id);

  public:
    Timer64(sc_core::sc_module_name name);
    virtual ~Timer64();

  protected:
    virtual uint32_t read_word (uint32_t address);
    virtual void     write_word(uint32_t address, uint32_t value);

    uint32_t _raw_read_word(uint32_t address);

  protected:
    void ticker();
    void trigger_ticker();
    void arm_ticker();

  protected:
    typedef Timer64_R_Timer timer_t;

    tim_signal_t       m_tim_signals[2];
    cmp_signal_t       m_cmp_signals[N_COMPARE_REGS];
    timer_t           *m_R_timer;
    sc_core::sc_event  m_E_timeout;
    sc_core::sc_time   m_lasttick;
    uint32_t           m_onetick;

  public:
    static ParameterBool nobias;
  };

} // namespace TI_AM1x
} // namespace simsoc

#endif // !LIBSIMSOC_TI_AM1X_TIMER64_HPP__
