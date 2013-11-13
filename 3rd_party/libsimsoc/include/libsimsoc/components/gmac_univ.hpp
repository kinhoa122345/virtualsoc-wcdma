//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef LIBSIMSOC_GMAC_UNIV_HPP
# define LIBSIMSOC_GMAC_UNIV_HPP

# include "libsimsoc/bitwise_operator.hpp"
# include "libsimsoc/module.hpp"
# include "libsimsoc/interfaces/tlm.hpp"
# include "libsimsoc/interfaces/tlm_signal.hpp"
# include "libsimsoc/network/ethernet/ether-transport.hpp"
# include "libsimsoc/network/ethernet/ether-address.hpp"

# include <deque>

namespace simsoc {
  // ------------------------------------------------------------------
  // Bus Mode register
  // ------------------------------------------------------------------
  class BusMode_Reg {
  public:
    enum DMA_Arbtr {
      DMA_A_ROUND_ROBIN = 0x0,
      DMA_A_RX_PRIO     = 0x1,
    };

    uint32_t value() const { return m_value; }

    bool      FixedBurst     () const { return m_FB ; }
    uint8_t   RxTxRatio      () const { return m_PR ; }
    uint8_t   DescrSkipLen   () const { return m_DSL; }
    DMA_Arbtr DMA_Abritation () const { return m_DA ; }
    bool      SoftReset      () const { return m_SWR; }

    void set(uint32_t value) {
      m_value = value;

      m_SWR   = (bool)      bit <uint32_t>(m_value,  0);
      m_DA    = (DMA_Arbtr) bit <uint32_t>(m_value,  1);
      m_DSL   = (uint8_t)   bits<uint32_t>(m_value,  2,  6);
      m_PR    = (uint8_t)   bits<uint32_t>(m_value, 14, 15) + 1;
      m_FB    = (bool)      bit <uint32_t>(m_value, 16);
    }

    void reset() { this->set(0x00000000); }

  private:
    uint32_t m_value;

    bool      m_FB;
    uint8_t   m_PR;
    uint8_t   m_DSL;
    DMA_Arbtr m_DA;
    bool      m_SWR;
  };

  // ------------------------------------------------------------------
  // Frame filter register
  // ------------------------------------------------------------------
  class GMAC_FrameFilterRegister {
  public:
    bool ReceiveAll       () const { return is_set<uint32_t>(m_value, 31); }
    bool SrcAddrFilter    () const { return is_set<uint32_t>(m_value,  9); }
    bool SrcFilterInverted() const { return is_set<uint32_t>(m_value,  8); }
    bool BroadcastDisabled() const { return is_set<uint32_t>(m_value,  5); }
    bool PassAllMulticast () const { return is_set<uint32_t>(m_value,  4); }
    bool DstFilterInverted() const { return is_set<uint32_t>(m_value,  3); }
    bool DAHashUnicast    () const { return is_set<uint32_t>(m_value,  2); }
    bool DAHashMulticast  () const { return is_set<uint32_t>(m_value,  1); }
    bool PromiscMode      () const { return is_set<uint32_t>(m_value,  0); }

    uint32_t value() const { return this->m_value; }

    void set  (uint32_t value) { this->m_value = value; }
    void reset()               { this->set(0x00000000); }

  private:
    uint32_t m_value;
  };

  // ------------------------------------------------------------------
  // Extended MAC addresses registers
  // ------------------------------------------------------------------
  class MAC1_Reg {
  public:
    enum filter_e {
      MAC_F_DA = 0x0,
      MAC_F_SA = 0x1,
    };

    MAC1_Reg() { this->reset(); }

    bool     enabled() const { return m_enabled; }
    filter_e filter () const { return m_filter ; }

    bool filter(const uint8_t *other) const {
      for (size_t i = 0; i < 6; ++i) {
        if (m_macmask[i] && m_mac.at(i) != other[i])
          return false;
      }
      return true;
    }

    /*-*/ EtherAddress& mac() /*-*/ { return m_mac; }
    const EtherAddress& mac() const { return m_mac; }

    void reset() {
      m_mac.set_as64(0);
      memset(m_macmask, 0, sizeof(m_macmask));
      m_enabled = false;
      m_filter  = MAC_F_DA;
    }

  protected:
    EtherAddress m_mac;
    bool         m_macmask[6];
    bool         m_enabled;
    filter_e     m_filter;
  };

  // ------------------------------------------------------------------
  // Interruptions + interruptions mask registers
  // ------------------------------------------------------------------
  class IRQ_Reg {
  public:
    static const uint32_t NIS_mask = 0x4045; // = 0b0 0100 0000 0100 0101;
    static const uint32_t AIS_mask = 0x27ba; // = 0b0 0010 0111 1011 1010;
    static const uint32_t NIS_bit  = 1 << 16;
    static const uint32_t AIS_bit  = 1 << 15;
    static const uint32_t  IS_mask = NIS_mask | AIS_mask;
    static const uint32_t  IS_bits = NIS_bit  | AIS_bit ;
    static const uint32_t  BE_mask = 7; // = 0b111;

    enum IRQ {
      EarlyReceive      = 1 << 14,
      BusError          = 1 << 13,
      EarlyTransmit     = 1 << 10,
      RxWatchdogTimeout = 1 <<  9,
      RxStopped         = 1 <<  8,
      RxBufUnavailable  = 1 <<  7,
      RxInt             = 1 <<  6,
      Underflow         = 1 <<  5,
      Overflow          = 1 <<  4,
      TxJabberTimeout   = 1 <<  3,
      TxBufUnavailable  = 1 <<  2,
      TxStopped         = 1 <<  1,
      TxInt             = 1 <<  0,
    };

    enum TxState_e {
      TX_STOP             = 0 /* 0b000 */,
      TX_RUN_FetchTxDescr = 1 /* 0b001 */,
      TX_RUN_WaitStatus   = 2 /* 0b010 */,
      TX_RUN_ReadData     = 3 /* 0b011 */,
      TX_SUSP             = 6 /* 0b110 */,
      TX_RUN_ClosDescr    = 7 /* 0b111 */,
    };

    enum RxState_e {
      RX_STOP              = 0 /* 0b000 */,
      RX_RUN_FetchRxDescr  = 1 /* 0b001 */,
      RX_RUN_WaitRecv      = 3 /* 0b011 */,
      RX_SUSP              = 4 /* 0b100 */,
      RX_RUN_ClosDescr     = 5 /* 0b101 */,
      RX_RUN_TransToHost   = 7 /* 0b111 */,
    };

    void setTxState (TxState_e  state) {
      this->m_txstate         = state;
      this->m_regstate_staled = true;
    }

    void setRxState (RxState_e  state) {
      this->m_rxstate         = state;
      this->m_regstate_staled = true;
    }

    void setBusError(uint8_t value) {
      this->m_buserror        = value & BE_mask;
      this->m_regstate_staled = true;
    }

    void setPMT(bool value) {
      this->m_gmac_pmt        = value;
      this->m_regstate_staled = true;
    }

    void setMMC(bool value) {
      this->m_gmac_mmc        = value;
      this->m_regstate_staled = true;
    }

    void setLI(bool value) {
      this->m_gmac_li         = value;
      this->m_regstate_staled = true;
    }

    uint8_t    ExtBusError() const { return m_buserror; }
    TxState_e  TxState    () const { return m_txstate ; }
    RxState_e  RxState    () const { return m_rxstate ; }
    bool       PMT        () const { return m_gmac_pmt; }
    bool       MMC        () const { return m_gmac_mmc; }
    bool       LI         () const { return m_gmac_li ; }

    void reset() {
      this->m_regstate_staled = false;

      this->m_regstate = 0;
      this->m_regmask  = 0;

      this->m_interrupts = 0;
      this->m_rxstate    = RX_STOP;
      this->m_txstate    = TX_STOP;
      this->m_buserror   = 0;
      this->m_gmac_pmt   = false;
      this->m_gmac_mmc   = false;
      this->m_gmac_li    = false;
    }

    void clear(uint32_t clear) {
      clear &= IS_mask | IS_bits; // Remove garbage

      if ((clear & NIS_mask) && !(clear & NIS_bit))
        warning() << "Clearing normal interrupts without clearing NIS" << std::endl;

      if ((clear & AIS_mask) && !(clear & AIS_bit))
        warning() << "Clearing abnormal interrupts without clearing AIS" << std::endl;

      this->m_interrupts &= ((~clear) & IS_mask);

      if ((m_interrupts & NIS_mask) && (m_regmask & NIS_bit))
        this->m_interrupts |= NIS_bit;
      if ((m_interrupts & AIS_mask) && (m_regmask & AIS_bit))
        this->m_interrupts |= AIS_bit;

      this->m_regstate_staled = true;
    }

    void fire(uint32_t interrupts) {
      interrupts &= m_regmask;  // Fire only masked interrupts
      interrupts &= IS_mask;    // Remove garbage

      if ((interrupts & NIS_mask) && (m_regmask & NIS_bit))
        interrupts |= NIS_bit;
      if ((interrupts & AIS_mask) && (m_regmask & AIS_bit))
        interrupts |= AIS_bit;
      this->m_interrupts |= interrupts;
      this->m_regstate_staled = true;
    }

    bool has_interrupts() const {
      return (bool) this->m_interrupts;
    }

    void set_regmask(uint32_t mask) {
      this->m_regmask = (mask & (IS_mask | IS_bits));
    }

    void set_regstate(uint32_t value) {
      this->clear(value & (IS_mask | IS_bits));
    }

    uint32_t regmask() const {
      return this->m_regmask;
    }

    uint32_t regstate() const {
      if (m_regstate_staled) {
        m_regstate
          = m_interrupts
          | (((uint32_t) m_rxstate ) << 17)
          | (((uint32_t) m_txstate ) << 20)
          | (((uint32_t) m_buserror) << 23);

        if (m_gmac_pmt) m_regstate |= (1 << 28);
        if (m_gmac_mmc) m_regstate |= (1 << 27);
        if (m_gmac_li ) m_regstate |= (1 << 26);

        m_regstate_staled = false;
      }
      return m_regstate;
    }

  public:
    mutable bool     m_regstate_staled;
    mutable uint32_t m_regstate;
    /*---*/ uint32_t m_regmask;

    uint32_t  m_interrupts;
    RxState_e m_rxstate;
    TxState_e m_txstate;
    uint8_t   m_buserror;
    bool      m_gmac_pmt;
    bool      m_gmac_mmc;
    bool      m_gmac_li;
  };

  // ------------------------------------------------------------------
  // Transfer descriptor
  // ------------------------------------------------------------------
  class TxDescriptor {
  public:
    bool OwnedByCPU     () const { return !is_set<uint32_t>(TDES[0], 31); }
    bool IsFirstSegment () const { return  is_set<uint32_t>(TDES[1], 29); }
    bool IsLastSegment  () const { return  is_set<uint32_t>(TDES[1], 30); }
    bool IntOnCompletion() const { return  is_set<uint32_t>(TDES[1], 31); }

    void setOwnedByCPU() { unset_bit<uint32_t>(TDES[0], 31); }

    uint32_t buf1size() const { return bits<uint32_t>(TDES[1], 10,  0); }
    uint32_t buf2size() const { return bits<uint32_t>(TDES[1], 21, 11); }

    uint32_t buf1addr() const { return TDES[2]; }
    uint32_t buf2addr() const { return TDES[3]; }

    const uint8_t* rawdata() const { return (uint8_t*) TDES; }
    /*-*/ uint8_t* rawdata() /*-*/ { return (uint8_t*) TDES; }

  private:
    uint32_t TDES[4];
  };

  // ------------------------------------------------------------------
  // Reception descriptor
  // ------------------------------------------------------------------
  class RxDescriptor {
  public:
    bool OwnedByCPU     () const { return !is_set<uint32_t>(RDES[0], 31); }
    bool IntOnCompletion() const { return !is_set<uint32_t>(RDES[1], 31); }

    void setOwnedByCPU() { unset_bit<uint32_t>(RDES[0], 31); }

    void SetFirstSegment () { set_bit<uint32_t>(RDES[0], 9); }
    void SetLastSegment  () { set_bit<uint32_t>(RDES[0], 8); }

    const uint8_t* rawdata() const { return (uint8_t*) RDES; }
    /*-*/ uint8_t* rawdata() /*-*/ { return (uint8_t*) RDES; }

    void setLength(size_t size) { RDES[0] |= (size << 16); }

    uint32_t buf1size() const { return bits<uint32_t>(RDES[1], 10,  0); }
    uint32_t buf2size() const { return bits<uint32_t>(RDES[1], 21, 11); }

    uint32_t buf1addr() const { return RDES[2]; }
    uint32_t buf2addr() const { return RDES[3]; }

    void ClearStatus() {
      RDES[0] &= ((uint32_t) 1) << 31;
    }

  private:
    uint32_t RDES[4];
  };

  // ------------------------------------------------------------------
  // Ethernet controller
  // ------------------------------------------------------------------
  class GMAC_Univ
    : public Module
    , public RW_Target
  {
    friend void* simsoc::__recv_thread(void*);

  public:
    SC_HAS_PROCESS(GMAC_Univ);

  public:
    GMAC_Univ(sc_core::sc_module_name name);
    virtual ~GMAC_Univ();

  public:
    void set_transport(IEtherTransport *transport);

  protected:                    // SimSoC
    void end_of_elaboration();

  public:                         // TLM interface
    void trans_read_data (PayLoad &pl);
    void trans_write_data(PayLoad &pl);

    uint32_t read_word (uint32_t address);
    void     write_word(uint32_t address, uint32_t data);

  protected:
    void generate_MAC0_address();
    void GMAC_Reset();

  protected:                      // Filtering
    bool filter_da(const uint8_t *destination);
    bool filter_sa(const uint8_t *source);

  protected:                       // Interrupts
    void interrupts_fire (uint32_t interrupts);
    void interrupts_clear(uint32_t interrupts);

  public:
    RW_TargetPort             in_port;
    RW_InitiatorPort          out_port;
    SignalInitiatorPort<bool> it_port0, it_port1;

  protected:
    sc_core::sc_event  m_tx_event;
    IEtherTransport   *m_transport;

  protected:
    bool read_tx_descriptor(TxDescriptor &output);
    void write_tx_descriptor(const TxDescriptor &input);

    bool read_rx_descriptor(RxDescriptor &output);
    void write_rx_descriptor(const RxDescriptor &input);

    bool _try_tx_1();
    bool _try_rx_1(const EtherBuffer &buffer);

    void _tx_thread();
    void _rx_thread();

  protected:                    // DMA registers
    static const uint32_t Dma_BusMode             = 0x1000;
    static const uint32_t Dma_TxPoll              = 0x1004;
    static const uint32_t Dma_RxPoll              = 0x1008;
    static const uint32_t Dma_RxDescrListAddr     = 0x100C;
    static const uint32_t Dma_TxDescrListAddr     = 0x1010;
    static const uint32_t Dma_Stats               = 0x1014;
    static const uint32_t Dma_OprMode             = 0x1018;
    static const uint32_t Dma_IntEnabled          = 0x101C;
    static const uint32_t Dma_MissedFrames        = 0x1020;
    static const uint32_t Dma_CurrHostTxDescrAddr = 0x1048;
    static const uint32_t Dma_CurrHostRxDescrAddr = 0x104C;
    static const uint32_t Dma_CurrHostTxBuffAddr  = 0x1050;
    static const uint32_t Dma_CurrHostRxBuffAddr  = 0x1054;

    BusMode_Reg m_R_dma_BusMode;         // DMA  0
    uint32_t    m_R_dma_TxPoll;          // DMA  1
    uint32_t    m_R_dma_RxPoll;          // DMA  2
    uint32_t    m_R_dma_RxDescrList;     // DMA  3
    uint32_t    m_R_dma_TxDescrList;     // DMA  4
    IRQ_Reg     m_R_dma_Interrupts;      // DMA  5/7
    uint32_t    m_R_dma_OperationMode;   // DMA  6
    uint32_t    m_R_dma_MissedFrames;    // DMA  8
    uint32_t    m_R_dma_CurrentTxDescr;  // DMA 18
    uint32_t    m_R_dma_CurrentRxDescr;  // DMA 19
    uint32_t    m_R_dma_CurrentTxBuffer; // DMA 20
    uint32_t    m_R_dma_CurrentRxBuffer; // DMA 21

  protected:                    // GMAC registers
    static const uint32_t GMAC_VERSION = 0X0010;

    static const uint32_t GMAC_Configuration           = 0x0000;
    static const uint32_t GMAC_FrameFilter             = 0x0004;
    static const uint32_t GMAC_Hash_Table_HI           = 0x0008;
    static const uint32_t GMAC_Hash_Table_LO           = 0x000C;
    static const uint32_t GMAC_GMII_Address            = 0x0010;
    static const uint32_t GMAC_GMII_Data               = 0x0014;
    static const uint32_t GMAC_FlowControl             = 0x0018;
    static const uint32_t GMAC_VlanTag                 = 0x001C;
    static const uint32_t GMAC_Version                 = 0x0020;
    static const uint32_t GMAC_WakeUpFilter            = 0x0028;
    static const uint32_t GMAC_PMTCtrl                 = 0x002C;
    static const uint32_t GMAC_AN_Ctrl                 = 0x00C0;
    static const uint32_t GMAC_AN_Status               = 0x00C4;
    static const uint32_t GMAC_AN_Advertisement        = 0x00C8;
    static const uint32_t GMAC_AN_Link_Partner_Ability = 0x00CC;
    static const uint32_t GMAC_AN_Expansion            = 0x00D0;
    static const uint32_t GMAC_MAC0_HI                 = 0x0040;
    static const uint32_t GMAC_MAC0_LO                 = 0x0044;
    static const uint32_t GMAC_MAC1                    = 0x0048;

    static const uint32_t MAC1s_count  = 15;

    uint32_t                 m_R_GMAC_Configuration    ; // GMAC  0
    GMAC_FrameFilterRegister m_R_GMAC_FrameFilter      ; // GMAC  1
    uint32_t                 m_R_GMAC_HTable_HI        ; // GMAC  2
    uint32_t                 m_R_GMAC_HTable_LO        ; // GMAC  3
    uint32_t                 m_R_GMAC_GMII_Address     ; // GMAC  4
    uint32_t                 m_R_GMAC_GMII_Data        ; // GMA   5
    uint32_t                 m_R_GMAC_FlowControl      ; // GMA   6
    uint32_t                 m_R_GMAC_VLan             ; // GMA   7
    uint32_t                 m_R_GMAC_PMTCtrl          ; // GMA  11
    EtherAddress             m_R_GMAC_MAC0             ; // GMAC 16/17
    MAC1_Reg                 m_R_GMAC_MAC1[MAC1s_count]; // GMAC 18/19-44/45
  };

}

#endif // LIBSIMSOC_GMAC_UNIV_HPP
