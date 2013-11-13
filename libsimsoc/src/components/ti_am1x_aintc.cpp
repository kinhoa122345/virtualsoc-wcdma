//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "libsimsoc/components/ti_am1x_aintc.hpp"
#include "libsimsoc/processors/arm/arm_processor.hpp"
#include "libsimsoc/processors/arm_v6/arm_v6_processor.hpp"

namespace simsoc  {
namespace TI_AM1x {

  // ------------------------------------------------------------------
  void AINTC_R_Serving::set_serving(AINTC_idx_interrupts_e id, int sysint) {
    int myoffset = 1 + (int) id;
    if (sysint < 0) {
      m_interrupt[myoffset] = 0x80000000;
      m_vector   [myoffset] = m_intvector.null();

      m_interrupt[0] = m_interrupt[3-myoffset];
      m_vector   [0] = m_vector   [3-myoffset];
    } else {
      m_interrupt[myoffset] = sysint;
      m_vector   [myoffset] = m_intvector.branch_for_irq(sysint);

      switch (id) {
      case IDX_FIQ:
        m_interrupt[0] = m_interrupt[myoffset];
        m_vector   [0] = m_vector   [myoffset];
        break ;

      case IDX_IRQ:
        if (m_interrupt[1+IDX_FIQ] == 0x80000000) {
          m_interrupt[0] = m_interrupt[myoffset];
          m_vector   [0] = m_vector   [myoffset];
        }
        break ;
      }
    }
  }

  // ------------------------------------------------------------------
  enum ac_action {
    AC_REVID  ,                 // REVID
    AC_CONTROL,                 // CR
    AC_GER    ,                 // GER
    AC_HIEISR ,                 // HIEISR
    AC_HIEICR ,                 // HIEICR
    AC_HIER   ,                 // HIER
    AC_SISR   ,                 // SISR
    AC_SICR   ,                 // SICR
    AC_EISR   ,                 // EISR
    AC_EICR   ,                 // EICR
    AC_SRSR   ,                 // SRSRn  [n = ac.index+1]
    AC_SECR   ,                 // SECRn  [n = ac.index+1]
    AC_ESR    ,                 // ESRn   [n = ac.index+1]
    AC_ECR    ,                 // ECRn   [n = ac.index+1]
    AC_NLR    ,                 // GNLR   [when n == 0]
                                // HILNRn [othw, n = ac.index]
    AC_PVR    ,                 // GPVR   [when n == 0]
                                // HIPVRn [othw, n = ac.index]
    AC_PIR    ,                 // GPIR   [when n == 0]
                                // HIPIRn [othw, n = ac.index]
    AC_CMR    ,                 // CMRn   [n = ac.index]
    AC_VBR    ,                 // VBR
    AC_VSR    ,                 // VSR
    AC_VNR    ,                 // VNR
  };

  static enum ac_action AC_INVALID = (enum ac_action) -1;

  // ------------------------------------------------------------------
#define WR_READONLY    AINTC::WR_READONLY
#define WR_INTINDEX    AINTC::WR_INTINDEX
#define WR_RECOMPUTE   AINTC::WR_RECOMPUTE
#define WR_UNSUPPORTED AINTC::WR_UNSUPPORTED

  AINTC::writer_infos_t AINTC::writers[] = {
    { NULL                  , WR_READONLY                }, // AC_REVID
    { &AINTC::_write_CONTROL, WR_RECOMPUTE               }, // AC_CONTROL
    { &AINTC::_write_GER    , WR_RECOMPUTE               }, // AC_GER
    { &AINTC::_write_HIEISR , WR_RECOMPUTE               }, // AC_HIEISR
    { &AINTC::_write_HIEICR , WR_RECOMPUTE               }, // AC_HIEICR
    { &AINTC::_write_HIER   , WR_RECOMPUTE               }, // AC_HIER
    { &AINTC::_write_SISR   , WR_RECOMPUTE | WR_INTINDEX }, // AC_SISR
    { &AINTC::_write_SICR   , WR_RECOMPUTE | WR_INTINDEX }, // AC_SICR
    { &AINTC::_write_EISR   , WR_RECOMPUTE | WR_INTINDEX }, // AC_EISR
    { &AINTC::_write_EICR   , WR_RECOMPUTE | WR_INTINDEX }, // AC_EICR
    { &AINTC::_write_SRSR   , WR_RECOMPUTE               }, // AC_SRSR
    { &AINTC::_write_SECR   , WR_RECOMPUTE               }, // AC_SECR
    { &AINTC::_write_ESR    , WR_RECOMPUTE               }, // AC_ESR
    { &AINTC::_write_ECR    , WR_RECOMPUTE               }, // AC_ECR
    { NULL                  , WR_UNSUPPORTED             }, // AC_NLR
    { NULL                  , WR_READONLY                }, // AC_PVR
    { NULL                  , WR_READONLY                }, // AC_PIR
    { &AINTC::_write_CMR    , WR_RECOMPUTE               }, // AC_CMR
    { &AINTC::_write_VBR    , WR_RECOMPUTE               }, // AC_VBR
    { &AINTC::_write_VSR    , WR_RECOMPUTE               }, // AC_VSR
    { &AINTC::_write_VNR    , WR_RECOMPUTE               }, // AC_VNR
  };

  // ------------------------------------------------------------------
  class address_class_t {
  public:
    uint32_t  rawaddress;
    ac_action action;
    size_t    index;

  public:
    static address_class_t classify(uint32_t address);

  public:
    address_class_t(uint32_t address)
      :rawaddress(address)
      ,action    (AC_INVALID)
      ,index     (0)
    {}

    address_class_t(uint32_t  address  ,
                    ac_action action   ,
                    size_t    index = 0)
      :rawaddress(address)
      ,action    (action)
      ,index     (index)
    {}

  public:
    static const uint32_t NINTS_GP = AINTC_R_Int::NINTS_GP;

    static const uint32_t A_REVID  = 0x0000;
    static const uint32_t A_CR     = 0x0004;
    static const uint32_t A_GER    = 0x0010;
    static const uint32_t A_GNLR   = 0x001C;
    static const uint32_t A_SISR   = 0x0020;
    static const uint32_t A_SICR   = 0x0024;
    static const uint32_t A_EISR   = 0x0028;
    static const uint32_t A_EICR   = 0x002C;
    static const uint32_t A_HIEISR = 0x0034;
    static const uint32_t A_HIEICR = 0x0038;
    static const uint32_t A_VBR    = 0x0050;
    static const uint32_t A_VSR    = 0x0054;
    static const uint32_t A_VNR    = 0x0058;
    static const uint32_t A_GPIR   = 0x0080;
    static const uint32_t A_GPVR   = 0x0084;
    static const uint32_t A_HIER   = 0x1500;

    static const uint32_t C_SRSR   = 0x0200;
    static const uint32_t C_SECR   = 0x0280;
    static const uint32_t C_ESR    = 0x0300;
    static const uint32_t C_ECR    = 0x0380;
    static const uint32_t C_HIPIR  = 0x0900;
    static const uint32_t C_HINLR  = 0x1100;
    static const uint32_t C_HIPVR  = 0x1600;
  };

  // ------------------------------------------------------------------
  address_class_t address_class_t::classify(uint32_t address) {
    const uint32_t rawaddress = address;

#define INVALID         (address_class_t(rawaddress))
#define ADDRESS(C)      (address_class_t(rawaddress, C))
#define ADDRESS_I(C, I) (address_class_t(rawaddress, C, I))

    if (address >> 16 || (address & 0x3))
      return INVALID;

    // Channel maps registers
    if (((address >> 8) & 0xFF) == 0x04) {
      size_t offset = (address & 0xFF) >> 2;

      if (offset >= NINTS_GP)
        return INVALID;
      return ADDRESS_I(AC_CMR, offset);
    }

    switch (address) {
    case A_REVID  : return ADDRESS(AC_REVID);
    case A_CR     : return ADDRESS(AC_CONTROL);
    case A_GER    : return ADDRESS(AC_GER);
    case A_GNLR   : return ADDRESS(AC_NLR);
    case A_SISR   : return ADDRESS(AC_SISR);
    case A_SICR   : return ADDRESS(AC_SICR);
    case A_EISR   : return ADDRESS(AC_EISR);
    case A_EICR   : return ADDRESS(AC_EICR);
    case A_HIEISR : return ADDRESS(AC_HIEISR);
    case A_HIEICR : return ADDRESS(AC_HIEICR);
    case A_VBR    : return ADDRESS(AC_VBR);
    case A_VSR    : return ADDRESS(AC_VSR);
    case A_VNR    : return ADDRESS(AC_VNR);
    case A_GPIR   : return ADDRESS(AC_PIR);
    case A_GPVR   : return ADDRESS(AC_PVR);
    case A_HIER   : return ADDRESS(AC_HIER);
    }

    size_t offset = (address & 0xF) >> 2;

    switch ((address & 0xFFF0)) {
    case C_SRSR:
      return (offset < NINTS_GP) ? ADDRESS_I(AC_SRSR, offset) : INVALID;
    case C_SECR:
      return (offset < NINTS_GP) ? ADDRESS_I(AC_SECR, offset) : INVALID;
    case C_ESR:
      return (offset < NINTS_GP) ? ADDRESS_I(AC_ESR , offset) : INVALID;
    case C_ECR:
      return (offset < NINTS_GP) ? ADDRESS_I(AC_ECR , offset) : INVALID;
    case C_HIPIR:
      return (offset < 2) ? ADDRESS_I(AC_PIR, offset+1) : INVALID;
    case C_HINLR:
      return (offset < 2) ? ADDRESS_I(AC_NLR, offset+1) : INVALID;
    case C_HIPVR:
      return (offset < 2) ? ADDRESS_I(AC_PVR, offset+1) : INVALID;
    }

    return INVALID;

#undef INVALID
#undef ADDRESS
#undef ADDRESS_I
  }

  // ------------------------------------------------------------------
  AINTC::AINTC(sc_core::sc_module_name name)
    :TI_AM1x_core<AINTC>(name, this)
    ,m_in_ports         ()
    ,m_R_control        ()
    ,m_R_GER            ()
    ,m_R_hostint        ()
    ,m_R_interrupts     ()
    ,m_R_vector         ()
    ,m_R_serving        (m_R_vector)
  {
    m_in_ports.reserve(NINTERRUPTS);
    for (size_t i = 0; i < NINTERRUPTS; ++i)
      m_in_ports.push_back(new signal_t(*this, i));
  }

  AINTC::~AINTC() {
    for (size_t i = 0; i < m_in_ports.size(); ++i)
      delete m_in_ports[i];
  }

  // ------------------------------------------------------------------
  void AINTC::connect(ARM_Processor &processor) {
    this->m_irq_port(processor.irq_port);
    this->m_fiq_port(processor.fiq_port);
  }

  void AINTC::connect(ARMv6_Processor &processor) {
    this->m_irq_port(processor.irq_port);
    this->m_fiq_port(processor.fiq_port);
  }

  AINTC::signal_t& AINTC::get_irq_port(unsigned port) {
    assert(port < NINTERRUPTS);
    return *this->m_in_ports[port];
  }

  // ------------------------------------------------------------------
  uint32_t AINTC::_RW_register(uint32_t address) {
    warning()
      << "trying to read from a RW register at address "
      << std::hex << address
      << std::endl;
    return 0;
  }

  // ------------------------------------------------------------------
  uint32_t AINTC::read_word(uint32_t address) {
    debug()
      << "reading at address " << std::hex << address
      << std::endl;

    if ((address & 0x3)) {
      warning() << "address not properly aligned" << std::endl;
      return 0;
    }

    const address_class_t ac = address_class_t::classify(address);

    if (ac.action == AC_INVALID) {
      warning()
        << "invalid address: "
        << std::hex << address << std::endl;
      return 0;
    }

    switch (ac.action) {
    case AC_REVID  : return REVISION;
    case AC_CONTROL: return m_R_control.value();

    case AC_GER    : return m_R_GER.get();

    case AC_HIEISR : return _RW_register(address);
    case AC_HIEICR : return _RW_register(address);
    case AC_HIER   : return m_R_hostint.get();

    case AC_SISR   : return _RW_register(address);
    case AC_SICR   : return _RW_register(address);
    case AC_EISR   : return _RW_register(address);
    case AC_EICR   : return _RW_register(address);

    case AC_SRSR   : return m_R_interrupts.rawpending_ck(ac.index);
    case AC_SECR   : return m_R_interrupts.pending_ck   (ac.index);
    case AC_ESR    : return m_R_interrupts.enabled_ck   (ac.index);
    case AC_ECR    : return m_R_interrupts.enabled_ck   (ac.index);

    case AC_NLR    : return m_R_serving.get_nesting  ((hirq_idx_e) ac.index);
    case AC_PVR    : return m_R_serving.get_vector   ((hirq_idx_e) ac.index);
    case AC_PIR    : return m_R_serving.get_interrupt((hirq_idx_e) ac.index);

    case AC_CMR    : return m_R_interrupts.get_channel_gp(ac.index);

    case AC_VBR    : return m_R_vector.base();
    case AC_VSR    : return m_R_vector.size();
    case AC_VNR    : return m_R_vector.null();
    }

    abort();
  }

  // ------------------------------------------------------------------
  void AINTC::write_word(uint32_t address, uint32_t data) {
    debug()
      << "writing "     << std::hex << data
      << " at address " << std::hex << address
      << std::endl;

    const address_class_t ac = address_class_t::classify(address);

    if (ac.action == AC_INVALID) {
      warning() << "invalid address: "
                << std::hex << address << std::endl;
      return ;
    }
 
    const writer_infos_t &writer = this->writers[ac.action];

    if ((writer.flags & WR_UNSUPPORTED))
      return ;

    if ((writer.flags & WR_READONLY)) {
      warning()
        << "trying to write to a RO register at address "
        << std::hex << address << std::endl;
      return ;
    }

    if ((writer.flags & WR_INTINDEX)) {
      if (data >= AINTC_R_Int::NINTERRUPTS) {
        warning()
          << "while writing to address " << std::hex << address
          << ": invalid interrupt: " << data
          << std::endl;
        return ;
      }
    }

    (this->*writer.wr_callback)(ac, data);
    if ((writer.flags & WR_RECOMPUTE))
      this->_compute();
  }

  // ------------------------------------------------------------------
  void AINTC::_write_CONTROL(const address_class_t &ac, uint32_t data) {
    m_R_control.set(data);
    if (m_R_control.holdmode()) {
      error() << "HOLDMODE unsupported" << std::endl;
      abort();
    }
    if (m_R_control.nestmode() != AINTC_R_Control::NM_None) {
      error() << "NESTMODE unsupporte (!= NM_None)" << std::endl;
      abort();
    }
  }

  void AINTC::_write_GER(const address_class_t &ac, uint32_t data) {
    this->m_R_GER.set(data);
  }

  void AINTC::_write_HIEISR(const address_class_t &ac, uint32_t data) {
    m_R_hostint.enabled_set(data);
  }

  void AINTC::_write_HIEICR(const address_class_t &ac, uint32_t data) {
    m_R_hostint.enabled_clear(data);
  }

  void AINTC::_write_HIER(const address_class_t &ac, uint32_t data) {
    m_R_hostint.set(data);
  }

  void AINTC::_write_SISR(const address_class_t &ac, uint32_t data) {
    m_R_interrupts.set_rawpending(data);
  }

  void AINTC::_write_SICR(const address_class_t &ac, uint32_t data) {
    m_R_interrupts.clear_rawpending(data);
  }

  void AINTC::_write_EISR(const address_class_t &ac, uint32_t data) {
    m_R_interrupts.set_enabled(data);
  }

  void AINTC::_write_EICR(const address_class_t &ac, uint32_t data) {
    m_R_interrupts.clear_enabled(data);
  }

  void AINTC::_write_SRSR(const address_class_t &ac, uint32_t data) {
    m_R_interrupts.set_rawpending_ck(ac.index, data);
  }

  void AINTC::_write_SECR(const address_class_t &ac, uint32_t data) {
    m_R_interrupts.clear_rawpending_ck(ac.index, data);
  }

  void AINTC::_write_ESR(const address_class_t &ac, uint32_t data) {
    m_R_interrupts.set_enabled_ck(ac.index, data);
  }

  void AINTC::_write_ECR(const address_class_t &ac, uint32_t data) {
    m_R_interrupts.clear_enabled_ck(ac.index, data);
  }

  void AINTC::_write_CMR(const address_class_t &ac, uint32_t data) {
    m_R_interrupts.set_channel_gp(ac.index, data);
  }

  void AINTC::_write_VBR(const address_class_t &ac, uint32_t data) {
    m_R_vector.set_base(data);
  }

  void AINTC::_write_VSR(const address_class_t &ac, uint32_t data) {
    m_R_vector.set_size(data);
  }

  void AINTC::_write_VNR(const address_class_t &ac, uint32_t data) {
    m_R_vector.set_null(data);
  }

  // ------------------------------------------------------------------
  void AINTC::_compute() {
    int fiq_hi = -1;
    int irq_hi = -1;

    for (size_t i = 0; i < AINTC_R_Int::NINTERRUPTS; ++i) {
      if (!m_R_interrupts.is_pending(i))
        continue ;

      uint8_t mychannel = m_R_interrupts.get_channel(i);
      int    &currenthi = mychannel < 2 ? fiq_hi : irq_hi;

      if (currenthi < 0
          || m_R_interrupts.get_channel(currenthi) > mychannel)
          currenthi = i;
    }

    m_R_serving.set_serving(IDX_FIQ, fiq_hi);
    m_R_serving.set_serving(IDX_IRQ, irq_hi);

#ifndef NDEBUG
    debug()
      << "FIQ: "
      << (m_R_GER.enabled()
          && fiq_hi >= 0
          && m_R_hostint.is_enabled(IDX_FIQ))
      << std::endl;

    debug()
      << "IRQ: "
      << (m_R_GER.enabled()
          && irq_hi >= 0
          && m_R_hostint.is_enabled(IDX_IRQ))
      << std::endl;
#endif

    m_fiq_port
      =  m_R_GER.enabled()
      && fiq_hi >= 0
      && m_R_hostint.is_enabled(IDX_FIQ);
    m_irq_port
      =  m_R_GER.enabled()
      && irq_hi >= 0
      && m_R_hostint.is_enabled(IDX_IRQ);
  }

  // ------------------------------------------------------------------
  void AINTC::pulse(size_t line) {
    debug() << "PULSE: " << line << std::endl;
    m_R_interrupts.set_rawpending(line);
    this->_compute();
  }

} // namespace TI_AM1x
} // namespace simsoc
