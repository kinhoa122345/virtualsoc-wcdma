//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#if !defined (LIBSIMSOC_TI_AM1X_AINTC_HPP__)
# define LIBSIMSOC_TI_AM1X_AINTC_HPP__

# include "libsimsoc/interfaces/tlm.hpp"
# include "libsimsoc/interfaces/tlm_signal.hpp"
# include "libsimsoc/module.hpp"
# include "libsimsoc/bitwise_operator.hpp"

# include "libsimsoc/components/ti_am1x_core.hpp"

namespace simsoc {
  class ARM_Processor;
  class ARMv6_Processor;
}

namespace simsoc  {
namespace TI_AM1x {

  // ------------------------------------------------------------------
  class AINTC_R_Int {
  public:
    typedef uint32_t bits_t;
    typedef uint8_t  chan_t;

    static const size_t NINTS_GP    = 23;
    static const size_t NINTERRUPTS = 4 * NINTS_GP;
    static const size_t CK_SIZE     = sizeof (bits_t);
    static const size_t NCHUNKS     = NBLOCKS(NINTERRUPTS, 8*sizeof(bits_t));

  public:
    AINTC_R_Int();

  protected:
    static size_t segment_ck(size_t interrupt);
    static size_t offset_ck (size_t intterupt);

    static bits_t mask_of_ck(size_t chunkid);

  public:
    bool is_enabled   (size_t interrupt);
    bool is_rawpending(size_t interrupt);
    bool is_pending   (size_t interrupt);

    void set_enabled   (size_t interrupt);
    void set_rawpending(size_t interrupt);

    void clear_enabled   (size_t interrupt);
    void clear_rawpending(size_t interrupt);

    bits_t enabled_ck   (size_t chunkid) const;
    bits_t rawpending_ck(size_t chunkid) const;
    bits_t pending_ck   (size_t chunkid) const;

    void set_enabled_ck   (size_t chunkid, bits_t enabled);
    void set_rawpending_ck(size_t chunkid, bits_t pending);

    void clear_enabled_ck   (size_t chunkid, bits_t enabled);
    void clear_rawpending_ck(size_t chunkid, bits_t pending);

    chan_t get_channel(size_t interrupt) const;
    void   set_channel(size_t interrupt, chan_t channel);

    bits_t get_channel_gp(size_t intgroup) const;
    void   set_channel_gp(size_t intgroup, bits_t value);

  private:
    uint32_t m_rawpending[NCHUNKS    ];
    uint32_t m_enabled   [NCHUNKS    ];
    chan_t   m_channels  [NINTERRUPTS];

  private:
    AINTC_R_Int(const AINTC_R_Int&);            // GNI
    AINTC_R_Int& operator=(const AINTC_R_Int&); // GNI
  };

  // ------------------------------------------------------------------
  class AINTC_R_Control {
  protected:
    typedef bits_t<uint32_t, 4, 4> b_NEST;
    typedef bits_t<uint32_t, 3, 2> b_HOLD;

    static const uint32_t MASK = b_NEST::mask | b_HOLD::mask;

  public:
    enum nestmode_e { NM_None, NM_AutoOne, NM_AutoAll, NM_Manual };

  public:
    AINTC_R_Control();

    uint32_t   value   () const;
    bool       holdmode() const;
    nestmode_e nestmode() const;

    void set(uint32_t value);

  private:
    uint32_t m_value;

  private:
    AINTC_R_Control(const AINTC_R_Control&);            // GNI
    AINTC_R_Control& operator=(const AINTC_R_Control&); // GNI
  };

  // ------------------------------------------------------------------
  enum AINTC_idx_interrupts_e {
    IDX_FIQ = 0x00,
    IDX_IRQ = 0x01,
  };

  class AINTC_R_HostInt {
  public:
    AINTC_R_HostInt();

  public:
    uint32_t get() const;
    void     set(uint32_t);

    void enabled_set  (uint32_t value);
    void enabled_clear(uint32_t value);

    bool is_enabled(AINTC_idx_interrupts_e id);

  private:
    uint32_t m_value;

  private:
    AINTC_R_HostInt(const AINTC_R_HostInt&);           // GNI
    AINTC_R_HostInt operator=(const AINTC_R_HostInt&); // GNI
  };

  // ------------------------------------------------------------------
  class AINTC_R_GlobalEnable {
  public:
    AINTC_R_GlobalEnable();

  public:
    bool enabled() const;

    void     set(uint32_t value);
    uint32_t get() const;

  private:
    bool m_enabled;

  private:
    AINTC_R_GlobalEnable(const AINTC_R_GlobalEnable&);            // GNI
    AINTC_R_GlobalEnable& operator=(const AINTC_R_GlobalEnable&); // GNI
  };

  // ------------------------------------------------------------------
  class AINTC_R_Vector {
  public:
    AINTC_R_Vector();

  public:
    uint32_t base() const;
    uint32_t size() const;
    uint32_t null() const;

    void set_base(uint32_t value);
    void set_size(uint32_t value);
    void set_null(uint32_t value);

  public:
    uint32_t branch_for_irq(size_t interrupt) const;

  private:
    uint32_t m_base;
    uint32_t m_size;
    uint32_t m_null;

  private:
    AINTC_R_Vector(const AINTC_R_Vector&);           // GNI
    AINTC_R_Vector operator=(const AINTC_R_Vector&); // GNI
  };

  // ------------------------------------------------------------------
  enum hirq_idx_e {
    HINT_ALL = 0x00,
    HINT_FIQ = 0x01,
    HINT_IRQ = 0x02,
  };

  class AINTC_R_Serving {
  public:
    AINTC_R_Serving(const AINTC_R_Vector &intvector);

  public:
    uint32_t get_nesting  (hirq_idx_e index) const { return m_nesting  [index]; }
    uint32_t get_vector   (hirq_idx_e index) const { return m_vector   [index]; }
    uint32_t get_interrupt(hirq_idx_e index) const { return m_interrupt[index]; }

  public:
    void set_serving(AINTC_idx_interrupts_e id, int sysint);

  private:
    const AINTC_R_Vector &m_intvector;

    uint32_t m_nesting  [1+2];
    uint32_t m_vector   [1+2];
    uint32_t m_interrupt[1+2];

  private:
    AINTC_R_Serving(const AINTC_R_Serving&);           // GNI
    AINTC_R_Serving operator=(const AINTC_R_Serving&); // GNI
  };

  // ------------------------------------------------------------------
  class address_class_t;

  // ------------------------------------------------------------------
  class AINTC
    : public TI_AM1x_core<AINTC>
    , public signals::SignalMultiTarget
  {
  public:
    static const uint32_t NINTERRUPTS = AINTC_R_Int::NINTERRUPTS;

    static const uint32_t REVISION = 0x4E82A900;
    static const uint32_t SIZE     = 0x00002000;

    static const uint32_t SRSR_BASE = 0x0200;

  public:
    AINTC(sc_core::sc_module_name name);
    virtual ~AINTC();

  public:
    void pulse(size_t line);

  protected:
    void _compute();

  protected:
    uint32_t read_word (uint32_t address);
    void     write_word(uint32_t address, uint32_t value);

  protected:
    typedef void (AINTC::*writer_t)(const address_class_t &ac, uint32_t data);

    struct writer_infos_t {
      writer_t wr_callback;
      uint32_t flags;
    };

    static const uint32_t WR_RECOMPUTE   = (1 << 0);
    static const uint32_t WR_INTINDEX    = (1 << 1);
    static const uint32_t WR_READONLY    = (1 << 2);
    static const uint32_t WR_UNSUPPORTED = (1 << 3);

    static writer_infos_t writers[];

    void _write_CONTROL(const address_class_t &ac, uint32_t data);
    void _write_GER    (const address_class_t &ac, uint32_t data);
    void _write_HIEISR (const address_class_t &ac, uint32_t data);
    void _write_HIEICR (const address_class_t &ac, uint32_t data);
    void _write_HIER   (const address_class_t &ac, uint32_t data);
    void _write_SISR   (const address_class_t &ac, uint32_t data);
    void _write_SICR   (const address_class_t &ac, uint32_t data);
    void _write_EISR   (const address_class_t &ac, uint32_t data);
    void _write_EICR   (const address_class_t &ac, uint32_t data);
    void _write_SRSR   (const address_class_t &ac, uint32_t data);
    void _write_SECR   (const address_class_t &ac, uint32_t data);
    void _write_ESR    (const address_class_t &ac, uint32_t data);
    void _write_ECR    (const address_class_t &ac, uint32_t data);
    void _write_CMR    (const address_class_t &ac, uint32_t data);
    void _write_VBR    (const address_class_t &ac, uint32_t data);
    void _write_VSR    (const address_class_t &ac, uint32_t data);
    void _write_VNR    (const address_class_t &ac, uint32_t data);

  protected:
    uint32_t _RW_register(uint32_t address);

  public:
    typedef signals::SignalMultiTargetPort signal_t;

    void      connect(ARM_Processor &processor);
    void      connect(ARMv6_Processor &processor);
    signal_t& get_irq_port(unsigned irq);

  protected:
    std::vector<signal_t*>     m_in_ports;
    SignalInitiatorPort<bool>  m_fiq_port;
    SignalInitiatorPort<bool>  m_irq_port;

  private:
    AINTC_R_Control      m_R_control;
    AINTC_R_GlobalEnable m_R_GER;
    AINTC_R_HostInt      m_R_hostint;
    AINTC_R_Int          m_R_interrupts;
    AINTC_R_Vector       m_R_vector;
    AINTC_R_Serving      m_R_serving;
  };
}
}

# include "libsimsoc/components/ti_am1x_aintc.hxx"

#endif // !LIBSIMSOC_TI_AM1X_AINTC_HPP__
