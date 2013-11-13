//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include <iostream>
#include <algorithm>

#include "libsimsoc/components/ti_am1x_timer64.hpp"
#include "libsimsoc/bitwise_operator.hpp"
#include "libsimsoc/random.hpp"

// --------------------------------------------------------------------
#define TM_LO ::simsoc::TI_AM1x::Timer64::TM_LO
#define TM_HI ::simsoc::TI_AM1x::Timer64::TM_HI

typedef ::simsoc::TI_AM1x::Timer64::tmpart_e tmpart_e;

// --------------------------------------------------------------------
namespace simsoc  {
namespace TI_AM1x {

#define N_COMPARE_REGS Timer64::N_COMPARE_REGS

  // ------------------------------------------------------------------
  class Timer64_INT {
  public:
    typedef bits_t<uint16_t, 3> b_CAPINT;
    typedef bits_t<uint16_t, 2> b_CAPENA;
    typedef bits_t<uint16_t, 1> b_INT   ;
    typedef bits_t<uint16_t, 0> b_ENA   ;

    uint16_t forpart(tmpart_e id) {
      return (m_value >> (16 * id)) & 0xFFFF;
    }

    void set_forpart(tmpart_e id, uint16_t value) {
      uint32_t mask = 0xFFFF << (16 * id);
      m_value = (m_value & ~mask) | (value << (16 * id));
    }

    void fire(tmpart_e id) {
      uint16_t value = this->forpart(id);

      if (b_ENA::is_set(value))
        b_INT::set(value, 1);
      this->set_forpart(id, value);
    }

    bool pending(tmpart_e id) {
      return b_INT::is_set(this->forpart(id));
    }

  public:
    uint32_t value() { return m_value; }

    void set_value(uint32_t value) {
      m_value = value;
    }

  private:
    uint32_t m_value;
  };

  // ------------------------------------------------------------------
  enum enamode_e {
    TMMD_DISABLE  = 0x00,
    TMMD_ONETIME  = 0x01,
    TMMD_CONTINUE = 0x02,
    TMMD_CPERIOD  = 0x03,
  };

  class Timer64_CTRL {
  public:
    typedef bits_t<uint16_t, 10, 10> b_READRST;
    typedef bits_t<uint16_t,  7,  6> b_ENA;

  public:
    Timer64_CTRL()
      :m_value(0)
    {}

  public:
    uint16_t forpart(tmpart_e id) {
      return (m_value >> (16 * id)) & 0xFFFF;
    }

    bool reset_on_read(tmpart_e id) {
      return b_READRST::is_set(this->forpart(id));
    }

    enamode_e enamode(tmpart_e id) {
      return (enamode_e) b_ENA::get(this->forpart(id));
    }

  public:
    uint32_t value() { return m_value; }

    void set_value(uint32_t value) {
      m_value = value;
    }

  private:
    uint32_t m_value;
  };

  // ------------------------------------------------------------------
  enum timmode_e {
    TM_64BITS           = 0x00,
    TM_32BITS_UNCHAINED = 0x01,
    TM_64BITS_WD        = 0x02,
    TM_32BITS_CHAINED   = 0x03,
  };

  enum feature_e {
    FT_LEGACY   = 0x00,
    FT_EXTENDED = 0x01,
  };

  class Timer64_GLCTRL {
  public:
    typedef bits_t<uint32_t, 15, 12> b_TDDR;
    typedef bits_t<uint32_t, 11,  8> b_PSC ;
    typedef bits_t<uint32_t,  4,  4> b_FEAT;
    typedef bits_t<uint32_t,  3,  2> b_MODE;

    static const uint32_t MASK =
        b_TDDR::mask
      | b_PSC ::mask
      | b_FEAT::mask
      | b_MODE::mask
      | 0x03;                   // reset flags

  public:
    timmode_e mode   () { return (timmode_e) b_MODE::get(m_value); }
    feature_e feature() { return (feature_e) b_FEAT::get(m_value); }

    bool inreset(tmpart_e id) {
      return !is_set(m_value, (size_t) id);
    }

    uint32_t tddr() { return b_TDDR::get(m_value); } // For timer3:4
    uint32_t psc () { return b_PSC ::get(m_value); } // For timer3:4

    void set_tddr(uint32_t tddr) { b_TDDR::set(m_value, tddr); } // For timer3:4

  public:
    uint32_t value() { return m_value; }

    void set_value(uint32_t value) {
      m_value = (value & MASK);
    }

  private:
    uint32_t m_value;
  };

  // ------------------------------------------------------------------
  enum reset_mode_e { RST_ZERO, RST_PERIOD };

#define IRQEV_PERIOD   0x00000001
#define IRQEV_CMPSHIFT 16
#define IRQEV_CMPMASK  (((uint32_t) (1 << N_COMPARE_REGS)) - 1)

  struct clock_t {
    uint64_t value;
    uint64_t bound;
    uint64_t event;
    uint32_t ekind;
  };

  class Timer64_R_Timer {
  public:
    typedef Timer64        backref_t;
    typedef Timer64_INT    interrupts_t;
    typedef Timer64_CTRL   control_t;
    typedef Timer64_GLCTRL glcontrol_t;

    Timer64_R_Timer(backref_t &backref);

  public:
    uint64_t ticks(uint64_t ticks);

  protected:
    bool state_as_clock(clock_t &clock, tmpart_e id);
    void clock_as_state(uint64_t value, tmpart_e id);
    void reset_clock(tmpart_e id);

  public:
    void set_value(tmpart_e id, uint32_t value) {
      m_R_values[id] = value;
    }

    uint32_t value(tmpart_e id) {
      switch (m_R_glcontrol.mode()) {
      case TM_64BITS:
        if (id == TM_LO) {
          m_R_hi_shadow = m_R_values[TM_HI];
          return m_R_values[TM_LO];
        }
        if (id == TM_HI)
          return m_R_hi_shadow;
        abort();

      case TM_32BITS_UNCHAINED: {
        uint32_t result = m_R_values[id];

        if (m_R_glcontrol.feature() == FT_EXTENDED)
          if (m_R_control.reset_on_read(id)) {
            m_R_captures[id] = m_R_values[id];
            this->reset_clock(id);
          }

        return result;
      }

      case TM_32BITS_CHAINED:
        return m_R_values[id];

      default:
        abort();
      }
    }

    uint32_t period (tmpart_e id) { return m_R_periods [id]; }
    uint32_t reload (tmpart_e id) { return m_R_reloads [id]; }
    uint32_t capture(tmpart_e id) { return m_R_captures[id]; }

    void set_period(tmpart_e id, uint32_t value) {
      m_R_periods[id] = value;
    }

    void set_reload(tmpart_e id, uint32_t value) {
      m_R_reloads[id] = value;
    }

  public:
    uint32_t interrupts() { return m_R_interrupts.value(); }

    void set_interrupts(uint32_t value) {
      m_R_interrupts.set_value(value);
    }

  public:
    uint32_t control() { return m_R_control.value(); }

    void set_control(uint32_t value) {
      m_R_control.set_value(value);
    }

  public:
    uint32_t gl_control() { return m_R_glcontrol.value(); }

    void set_gl_control(uint32_t value) {
      m_R_glcontrol.set_value(value);
    }

  public:
    uint32_t cmp_value(size_t id) { return m_R_CMP[id]; }

    void set_cmp_value(size_t id, uint32_t value) {
      m_R_CMP[id] = value;
    }

  private:
    backref_t   &m_backref;
    uint32_t     m_R_CMP[N_COMPARE_REGS];
    uint32_t     m_R_values  [2];
    uint32_t     m_R_periods [2];
    uint32_t     m_R_reloads [2];
    uint32_t     m_R_captures[2];
    uint32_t     m_R_hi_shadow;
    interrupts_t m_R_interrupts;
    control_t    m_R_control;
    glcontrol_t  m_R_glcontrol;
  };

  // ------------------------------------------------------------------
  Timer64_R_Timer::Timer64_R_Timer(backref_t &backref)
    :m_backref(backref)
  {
    memset(m_R_CMP     , 0, sizeof(m_R_CMP     ));
    memset(m_R_values  , 0, sizeof(m_R_values  ));
    memset(m_R_periods , 0, sizeof(m_R_periods ));
    memset(m_R_reloads , 0, sizeof(m_R_reloads ));
    memset(m_R_captures, 0, sizeof(m_R_captures));
  }

  // ------------------------------------------------------------------
  uint64_t b32x2_to_b64(uint32_t hi, uint32_t lo) {
    return ((uint64_t) hi) << 32 | ((uint64_t) lo);
  }

  // ------------------------------------------------------------------
  bool Timer64_R_Timer::state_as_clock(clock_t &clock, tmpart_e id) {
    if (!(m_R_glcontrol.value() & (1 << id)))
      return false;

    switch (m_R_glcontrol.mode()) {
    case TM_64BITS:
      if (id != TM_LO)
        return false;
      clock.value = b32x2_to_b64(m_R_values [TM_LO], m_R_values [TM_HI]);
      clock.bound = b32x2_to_b64(m_R_periods[TM_LO], m_R_periods[TM_HI]);
      clock.event = clock.bound - clock.value;
      clock.ekind = IRQEV_PERIOD;
      break ;

    case TM_32BITS_CHAINED: {
      if (id != TM_LO)
        return false;
      uint64_t hilen64 = 1 + (uint64_t) m_R_periods[TM_HI];
      uint64_t lolen64 = 1 + (uint64_t) m_R_periods[TM_LO];

      clock.value
        = hilen64 * ((uint64_t) m_R_values[TM_LO])
        + (uint64_t) m_R_values[TM_HI];
      clock.bound = hilen64 * lolen64;
      clock.event = clock.bound - clock.value;
      clock.ekind = IRQEV_PERIOD;
      return true;
    }

    case TM_32BITS_UNCHAINED:
      if (id == TM_HI) {
        uint64_t psclen64 = 1 + (uint64_t) m_R_glcontrol.psc();
        uint64_t hilen64  = 1 + (uint64_t) m_R_periods[TM_LO];

        clock.value
          = psclen64 * ((uint64_t) m_R_glcontrol.tddr())
          + (uint64_t) m_R_values[TM_HI];
        clock.bound = psclen64 * hilen64;
        clock.event = clock.bound - clock.value;
        clock.ekind = IRQEV_PERIOD;
        return true;
      }

      if (id == TM_LO) {
        clock.value = m_R_values [TM_LO];
        clock.bound = m_R_periods[TM_LO];
        clock.event = clock.bound - clock.value;
        clock.ekind = IRQEV_PERIOD;

        uint32_t cmpevent = 0;
        uint32_t cmpmin   = (uint32_t) -1;

        for (size_t i = 0; i < N_COMPARE_REGS; ++i) {
#if 0
          if (m_R_CMP[i] == 0)
            continue ;
#endif

          uint32_t tocmp = m_R_CMP[i] - clock.value;

          if (tocmp > cmpmin) continue ;
          if (tocmp < cmpmin) cmpevent = 0;

          cmpevent |= 1 << i;
          cmpmin    = tocmp;
        }

        clock.ekind = 0;
        if (clock.event <= cmpmin)
          clock.ekind |= IRQEV_PERIOD;
        if (clock.event >= cmpmin)
          clock.ekind |= (cmpevent << IRQEV_CMPSHIFT);

        clock.event = std::min(clock.event, (uint64_t) cmpmin);

        return true;
      }

    default:
      abort();
    }

    return false;
  }

  // ------------------------------------------------------------------
  void Timer64_R_Timer::clock_as_state(uint64_t value, tmpart_e id) {
    switch (m_R_glcontrol.mode()) {
    case TM_64BITS:
      if (id != TM_LO)
        abort();
      m_R_values[TM_HI] = (value >> 32) & 0XFFFFFFFF;
      m_R_values[TM_LO] = (value >>  0) & 0xFFFFFFFF;
      break ;

    case TM_32BITS_CHAINED: {
      if (id != TM_LO)
        abort();

      uint64_t hilen64 = 1 + (uint64_t) m_R_periods[TM_HI];

      m_R_values[TM_LO] = value % hilen64;
      m_R_values[TM_HI] = value / hilen64;
      break ;
    }

    case TM_32BITS_UNCHAINED:
      if (id == TM_HI) {
        uint64_t psclen64 = 1 + (uint64_t) m_R_glcontrol.psc();

        m_R_values[TM_HI] = value / psclen64;
        m_R_glcontrol.set_tddr(value % psclen64);
        break ;
      }

      if (id == TM_LO) {
        m_R_values[TM_LO] = value;
        break ;
      }

    default:
      abort();
    }
  }

  // ------------------------------------------------------------------
  void Timer64_R_Timer::reset_clock(tmpart_e id) {
    switch (m_R_glcontrol.mode()) {
    case TM_64BITS:
    case TM_32BITS_CHAINED:
      if (id != TM_LO)
        abort();
      m_R_values[TM_LO] = m_R_values[TM_HI] = 0;
      if (m_R_glcontrol.feature() == FT_EXTENDED) {
        m_R_periods[TM_LO] = m_R_reloads[TM_LO];
        m_R_periods[TM_HI] = m_R_reloads[TM_HI];
      }
      break ;

    case TM_32BITS_UNCHAINED:
      m_R_values[id] = 0;
      if (m_R_control.enamode(id) == TMMD_CPERIOD) {
        if (m_R_glcontrol.feature() == FT_EXTENDED)
          m_R_periods[id] = m_R_reloads[id];
        else
          error() << "Period reload requested but PLUSEN bit not set";
      }
      if (id == TM_HI)
        m_R_glcontrol.set_tddr(0);
      break ;

    default:
      abort();
    }
  }

  // ------------------------------------------------------------------
  uint64_t Timer64_R_Timer::ticks(uint64_t nticks) {
    uint64_t maxticks = (uint64_t) -1;
    clock_t  clock;

    for (size_t i = 0; i < 2; ++i) {
      const tmpart_e id = (tmpart_e) i;

      if (m_R_control.enamode(id) == TMMD_DISABLE)
        continue ;
      if (!this->state_as_clock(clock, id))
        continue ;

      if (nticks == 0) {
        maxticks = std::min(maxticks, clock.event);
        continue ;
      }

      if (clock.event < nticks && nticks > 1) {
        error() << "::ticks: [nticks] too high" << std::endl;
        abort();
      }

      if (clock.event > 0) {
        if (clock.event == nticks) {
          maxticks = 0;
          if (clock.ekind & IRQEV_PERIOD) {
            m_R_interrupts.fire(id);
            m_backref.m_tim_signals[id] = m_R_interrupts.pending(id);
          }

          uint32_t cmpevent = (clock.ekind >> IRQEV_CMPSHIFT) & IRQEV_CMPMASK;

          if (cmpevent) {
            for (size_t i = 0; i < N_COMPARE_REGS; ++i)
              if (cmpevent & (1 << i))
                m_backref.m_cmp_signals[i].pulse();
          }
        }
        this->clock_as_state(clock.value + nticks, id);
      } else {
        assert(nticks == 1);
        if (clock.value == clock.bound) {
          if (m_R_control.enamode(id) != TMMD_ONETIME) {
            this->reset_clock(id);
            maxticks = 0;
          }
        } else {
          this->clock_as_state(clock.value + 1, id);
          maxticks = 0;
        }
      }
    }

    return maxticks;
  }

  // ------------------------------------------------------------------
  ParameterBool Timer64::nobias
  ("TI AM1x Timer", "-time-nobias", "Do not add a bias to timer");

  // ------------------------------------------------------------------
  Timer64::Timer64(sc_core::sc_module_name name)
    :TI_AM1x_core<Timer64>(name, this)
    ,m_R_timer            (NULL)
  {
    this->m_R_timer = new Timer64_R_Timer(*this);

    // Captain age + random bias
    if (nobias.get())
      m_onetick  = 10000;
    else
      m_onetick  = (uint64_t) (9800 + Random::random(400));

    SC_METHOD(ticker);
    this->sensitive << m_E_timeout;
    this->dont_initialize();
  }

  // ------------------------------------------------------------------
  Timer64::~Timer64() {
    if (m_R_timer)
      delete m_R_timer;
  }

  // ------------------------------------------------------------------
  Timer64::tim_signal_t& Timer64::get_tim_signal(tmpart_e id) {
    return m_tim_signals[(int) id];
  }

  // ------------------------------------------------------------------
  Timer64::cmp_signal_t& Timer64::get_cmp_signal(size_t id) {
    return m_cmp_signals[id];
  }

  // ------------------------------------------------------------------
  uint32_t Timer64::read_word(uint32_t address) {
    this->trigger_ticker();
    uint32_t result = this->_raw_read_word(address);
    this->arm_ticker();
    return result;
  }

  // ------------------------------------------------------------------
  uint32_t Timer64::_raw_read_word(uint32_t address) {
    if ((address & 0x3)) {
      warning() << "address not properly aligned: "
                << std::hex << address
                << std::endl;
      return 0;
    }

    if (address >= RA_CMP && address < RA_CMP + 4 * N_COMPARE_REGS)
      return m_R_timer->cmp_value((address - RA_CMP) >> 2);

    switch (address) {
    case RA_REVID:      return REVID;
    case RA_TIM12:      return m_R_timer->value(TM_LO);
    case RA_TIM34:      return m_R_timer->value(TM_HI);
    case RA_PRD12:      return m_R_timer->period(TM_LO);
    case RA_PRD34:      return m_R_timer->period(TM_HI);
    case RA_TCR:        return m_R_timer->control();
    case RA_TGCR:       return m_R_timer->gl_control();
    case RA_REL12:      return m_R_timer->reload(TM_LO);
    case RA_REL34:      return m_R_timer->reload(TM_HI);
    case RA_CAP12:      return m_R_timer->capture(TM_LO);
    case RA_CAP34:      return m_R_timer->capture(TM_HI);
    case RA_INTCTLSTAT: return m_R_timer->interrupts();
    }

    warning()
      << "invalid R-address: " << std::hex << address
      << std::endl;
    return 0;
  }

  // ------------------------------------------------------------------
  void Timer64::write_word(uint32_t address, uint32_t value) {
    debug()
      << "writing [" << std::hex << value
      << "] at address [" << std::hex << address
      << "]" << std::endl;

    this->trigger_ticker();

    if ((address & 0x3)) {
      warning() << "address not properly aligned: "
                << std::hex << address
                << std::endl;
    } else {
      if (address >= RA_CMP && address < RA_CMP + 4 * N_COMPARE_REGS) {
        this->m_R_timer->set_cmp_value((address - RA_CMP) >> 2, value);
      } else {
        switch (address) {
        case RA_TIM12:      m_R_timer->set_value(TM_LO, value)  ; break ;
        case RA_TIM34:      m_R_timer->set_value(TM_HI, value)  ; break ;
        case RA_PRD12:      m_R_timer->set_period(TM_LO, value) ; break ;
        case RA_PRD34:      m_R_timer->set_period(TM_HI, value) ; break ;
        case RA_TCR:        m_R_timer->set_control(value)       ; break ;
        case RA_TGCR:       m_R_timer->set_gl_control(value)    ; break ;
        case RA_REL12:      m_R_timer->set_reload(TM_LO, value) ; break ;
        case RA_REL34:      m_R_timer->set_reload(TM_HI, value) ; break ;
        case RA_INTCTLSTAT: m_R_timer->set_interrupts(value)    ; break ;

        default:
          warning()
            << "invalid W-address: " << std::hex << address
            << std::endl;
          break ;
        }
      }
    }

    this->arm_ticker();
  }

  // ------------------------------------------------------------------
  void Timer64::ticker() {
    this->trigger_ticker();
    this->arm_ticker();
  }

  // ------------------------------------------------------------------
  void Timer64::trigger_ticker() {
    sc_core::sc_time current = sc_core::sc_time_stamp();
    sc_core::sc_time elapsed = current - m_lasttick;

    m_E_timeout.cancel();

    if (elapsed.value() >= m_onetick) {
      uint64_t nticks = elapsed.value() / m_onetick;

      m_R_timer->ticks(nticks);
      m_lasttick += sc_core::sc_time((sc_dt::uint64)nticks * m_onetick, false);
    }
  }

  // ------------------------------------------------------------------
  void Timer64::arm_ticker() {
    uint64_t towait = m_R_timer->ticks(0);

    switch (towait) {
    case ((uint64_t) -1):
      return ;

    case 0:
      towait = 1;

    default:
      towait = std::min(towait, (uint64_t) 0xFFFFFFFF);

      debug() << "Waiting " << towait << " tick(s)" << std::endl;

      m_E_timeout.cancel();
      m_E_timeout.notify(sc_core::sc_time((sc_dt::uint64)towait * m_onetick, false));
    }
  }

} // namespace TI_AM1x
} // namespace simsoc
