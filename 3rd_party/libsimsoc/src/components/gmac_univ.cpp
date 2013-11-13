//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "libsimsoc/components/gmac_univ.hpp"

#include "libsimsoc/display.hpp"
#include "libsimsoc/network/ethernet/ether-address.hpp"
#include "libsimsoc/network/ethernet/ether-transport.hpp"

#include "libsimsoc/random.hpp"

using namespace sc_core;
using namespace std;

namespace simsoc {
  // --------------------------------------------------------------------
  GMAC_Univ::GMAC_Univ(sc_module_name name)
    :Module(name)
    ,m_transport(NULL)
  {
    this->in_port(*this);

    this->GMAC_Reset();
    this->generate_MAC0_address();

    SC_THREAD(_tx_thread);
    SC_THREAD(_rx_thread);
  }

  // --------------------------------------------------------------------
  GMAC_Univ::~GMAC_Univ() {
    if (this->m_transport != NULL)
      delete this->m_transport;
  }

  // ------------------------------------------------------------------
  void GMAC_Univ::set_transport(IEtherTransport *transport) {
    if (m_transport != NULL)
      abort();
    m_transport = transport;
  }

  // ------------------------------------------------------------------
  void GMAC_Univ::end_of_elaboration() {
    if (m_transport == NULL) {
      warning() << "setting default null transport" << std::endl;
      m_transport = new Null_EtherTransport();
    }
    m_transport->setnonblocking(true);
  }

  // --------------------------------------------------------------------
  void GMAC_Univ::generate_MAC0_address() {
    for (size_t i = 0; i < 6; ++i)
      m_R_GMAC_MAC0.at(i) = Random::random(256);
    m_R_GMAC_MAC0.at(0) &= ~((uint8_t) 1); // Clear multicast bit
  }

  // --------------------------------------------------------------------
  uint32_t GMAC_Univ::read_word(uint32_t address)
  {
    if ((address & 0x03)) {
      warning() << "requested address not aligned" << std::endl;
      return 0;
    }

    if (address >= GMAC_MAC1 && address <  GMAC_MAC1 + (MAC1s_count * 8)) {
      // Programmation of an extra MAC address
      bool   islow    = ((address - GMAC_MAC1) >> 2) & 0x01;
      size_t macindex = ((address - GMAC_MAC1) >> 3);

      assert(macindex < MAC1s_count);
      if (islow)
        return m_R_GMAC_MAC1[macindex].mac().hi_32();
      else
        return m_R_GMAC_MAC1[macindex].mac().lo_16();
    }

    switch(address){
    case Dma_BusMode :
      return m_R_dma_BusMode.value();
    case Dma_TxPoll:
      return m_R_dma_TxPoll;
    case Dma_RxPoll:
      return m_R_dma_RxPoll;
    case Dma_RxDescrListAddr:
      return m_R_dma_RxDescrList;
    case Dma_TxDescrListAddr:
      return m_R_dma_TxDescrList;
    case Dma_Stats:
      return m_R_dma_Interrupts.regstate();
    case Dma_OprMode:
      return m_R_dma_OperationMode;
    case Dma_IntEnabled:
      return m_R_dma_Interrupts.regmask();
    case Dma_MissedFrames:
      return m_R_dma_MissedFrames;
    case Dma_CurrHostTxDescrAddr:
      return m_R_dma_CurrentTxDescr;
    case Dma_CurrHostRxDescrAddr:
      return m_R_dma_CurrentRxDescr;
    case Dma_CurrHostTxBuffAddr:
      return m_R_dma_CurrentTxBuffer;
    case Dma_CurrHostRxBuffAddr:
      return m_R_dma_CurrentRxBuffer;

    case GMAC_Configuration:
      return m_R_GMAC_Configuration;
    case GMAC_FrameFilter:
      return m_R_GMAC_FrameFilter.value();
    case GMAC_Hash_Table_HI:
      return m_R_GMAC_HTable_HI;
    case GMAC_Hash_Table_LO:
      return m_R_GMAC_HTable_LO;

    case GMAC_GMII_Address: {
      uint32_t value = m_R_GMAC_GMII_Address;
      m_R_GMAC_GMII_Address &= ~((uint32_t) 1);
      return value;
    }
    case GMAC_GMII_Data: {
      uint32_t value = m_R_GMAC_GMII_Data;
      m_R_GMAC_GMII_Data &= ~((uint32_t) 0x8000);
      return value;
    }
    case GMAC_FlowControl:
      return m_R_GMAC_FlowControl;
    case GMAC_VlanTag:
      return m_R_GMAC_VLan;

    case GMAC_Version:
      return GMAC_VERSION;

    case GMAC_WakeUpFilter:
      error() << "WakeUp register no supported" << std::endl;
      abort();

    case GMAC_PMTCtrl:
      return m_R_GMAC_PMTCtrl;

    case GMAC_MAC0_HI:
      return m_R_GMAC_MAC0.lo_16();
    case GMAC_MAC0_LO:
      return m_R_GMAC_MAC0.hi_32();

    case GMAC_AN_Ctrl:
    case GMAC_AN_Status:
    case GMAC_AN_Advertisement:
    case GMAC_AN_Link_Partner_Ability:
    case GMAC_AN_Expansion:
      error() << "A-N registers not supported" << std::endl;
      abort();

    default:
      warning() << "MMC registers not supported or invalid address" << std::endl;
      return 0x00000000;
    }
  }

  // --------------------------------------------------------------------
  void GMAC_Univ::write_word(uint32_t address, uint32_t data) {
    if ((address & 0x03)) {
      warning() << "requested address not aligned" << std::endl;
      return ;
    }

    if (address >= GMAC_MAC1 && address <  GMAC_MAC1 + (MAC1s_count * 8)) {
      // Programmation of an extra MAC address
      bool   islow    = ((address - GMAC_MAC1) >> 2) & 0x01;
      size_t macindex = ((address - GMAC_MAC1) >> 3);

      assert(macindex < MAC1s_count);
      if (islow)
        m_R_GMAC_MAC1[macindex].mac().set_hi_32(data);
      else
        m_R_GMAC_MAC1[macindex].mac().set_lo_16(data);

      return ;
    }

    switch(address){
    case Dma_BusMode :
      this->m_R_dma_BusMode.set(data);
      if (this->m_R_dma_BusMode.SoftReset())
        GMAC_Reset();
      return;

    case Dma_TxPoll:
      if ((m_R_dma_TxPoll = data)) {
        m_R_dma_Interrupts.setTxState(IRQ_Reg::TX_SUSP);
        this->m_tx_event.notify();
      }
      return;

    case Dma_RxPoll:
      if ((m_R_dma_RxPoll = data))
        m_R_dma_Interrupts.setRxState(IRQ_Reg::RX_SUSP);
      return;

    case Dma_RxDescrListAddr:
      if (m_R_dma_Interrupts.RxState() != IRQ_Reg::RX_STOP)
        warning() << "invalid write of RxDescrListAddr when Rx active";
      else
        m_R_dma_RxDescrList = data;
      return;

    case Dma_TxDescrListAddr:
      if (m_R_dma_Interrupts.TxState() != IRQ_Reg::TX_STOP)
        warning() << "invalid write of TxDescrListAddr when Tx active";
      else
        m_R_dma_TxDescrList = data;
      return;

    case Dma_Stats:
      m_R_dma_Interrupts.set_regstate(data);
      it_port1 = m_R_dma_Interrupts.has_interrupts();
      return;

    case Dma_OprMode:
  #define OPRMODE_SR  (((uint32_t) 1) <<  1)
  #define OPRMODE_ST  (((uint32_t) 1) << 13)
  #define OPRMODE_FTF (((uint32_t) 1) << 20)

      m_R_dma_OperationMode = data & (~OPRMODE_FTF);
      if ((data & OPRMODE_SR)) {
        if (m_R_dma_Interrupts.RxState() == IRQ_Reg::RX_STOP)
          m_R_dma_Interrupts.setRxState(IRQ_Reg::RX_SUSP);
      }
      if ((data & OPRMODE_ST)) {
        if (m_R_dma_Interrupts.TxState() == IRQ_Reg::TX_STOP) {
          m_R_dma_Interrupts.setTxState(IRQ_Reg::TX_SUSP);
          this->m_tx_event.notify();
        }
      }
      return;

    case Dma_IntEnabled:
      m_R_dma_Interrupts.set_regmask(data);
      return;

    case Dma_MissedFrames:
      m_R_dma_MissedFrames = data;
      return;

    case Dma_CurrHostTxDescrAddr:
      error() << "cannot write Dma_CurrHostTxDescrAddr" << std::endl;
      return ;

    case Dma_CurrHostRxDescrAddr:
      error() << "cannot write Dma_CurrHostRxDescrAddr" << std::endl;
      return ;

    case Dma_CurrHostTxBuffAddr:
      error() << "cannot write Dma_CurrHostTxBuffAddr" << std::endl;
      return ;

    case Dma_CurrHostRxBuffAddr:
      error() << "cannot write Dma_CurrHostRxBuffAddr" << std::endl;
      return ;

    case GMAC_Configuration:
      this->m_R_GMAC_Configuration = data;
      return ;

    case GMAC_FrameFilter:
      this->m_R_GMAC_FrameFilter.set(data);
      return ;

    case GMAC_Hash_Table_HI:
      this->m_R_GMAC_HTable_HI = data;
      return ;

    case GMAC_Hash_Table_LO:
      this->m_R_GMAC_HTable_LO = data;
      return ;

    case GMAC_GMII_Address:
      this->m_R_GMAC_GMII_Address = data;
      return ;

    case GMAC_GMII_Data:
      this->m_R_GMAC_GMII_Data = data & 0xFFFF;
      return ;

    case GMAC_FlowControl:
      m_R_GMAC_FlowControl = data;
      return;

    case GMAC_VlanTag:
      m_R_GMAC_VLan = data;
      return;

    case GMAC_Version:
      warning() << "version register is read-only" << std::endl;
      return ;

    case GMAC_WakeUpFilter:
      error() << "WakeUp register not supported" << std::endl;
      abort();

    case GMAC_PMTCtrl:
      m_R_GMAC_PMTCtrl = data;
      return;

    case GMAC_MAC0_HI:
      this->m_R_GMAC_MAC0.set_lo_16(data);
      return;

    case GMAC_MAC0_LO:
      this->m_R_GMAC_MAC0.set_hi_32(data);
      return;

    case GMAC_AN_Ctrl:
    case GMAC_AN_Status:
    case GMAC_AN_Advertisement:
    case GMAC_AN_Link_Partner_Ability:
    case GMAC_AN_Expansion:
      error() << "A-N registers not supported" << std::endl;
      abort();

    default:
      warning() << "MMC register not implemented or invalid address" << std::endl;
      return;
    }// end switch
  }

  // --------------------------------------------------------------------
  void GMAC_Univ::interrupts_fire(uint32_t interrupts) {
    m_R_dma_Interrupts.fire(interrupts);
    it_port1 = m_R_dma_Interrupts.has_interrupts();
  }

  // --------------------------------------------------------------------
  void GMAC_Univ::GMAC_Reset() {
    m_R_dma_BusMode         .reset();
    m_R_dma_TxPoll          = 0x00000000;
    m_R_dma_RxPoll          = 0x00000000;
    m_R_dma_RxDescrList     = 0x00000000;
    m_R_dma_TxDescrList     = 0x00000000;
    m_R_dma_Interrupts      .reset();
    m_R_dma_OperationMode   = 0x00000000;
    m_R_dma_MissedFrames    = 0x00000000;
    m_R_dma_CurrentTxDescr  = 0x00000000;
    m_R_dma_CurrentRxDescr  = 0x00000000;
    m_R_dma_CurrentTxBuffer = 0x00000000;
    m_R_dma_CurrentRxBuffer = 0x00000000;

    m_R_GMAC_Configuration = 0x00000000;
    m_R_GMAC_FrameFilter   . reset();
    m_R_GMAC_HTable_LO     = 0x00000000;
    m_R_GMAC_HTable_HI     = 0x00000000;
    m_R_GMAC_GMII_Address  = 0x00000000;
    m_R_GMAC_GMII_Data     = 0x00000000;
    m_R_GMAC_FlowControl   = 0x00000000;
    m_R_GMAC_VLan          = 0x00000000;
    m_R_GMAC_PMTCtrl       = 0x00000000;
    m_R_GMAC_MAC0          . set_as64(0);

    for (size_t i = 0; i < MAC1s_count; ++i)
      m_R_GMAC_MAC1[i].reset();
  }

  // --------------------------------------------------------------------
  bool GMAC_Univ::read_tx_descriptor(TxDescriptor &descriptor) {
    if (!m_R_dma_CurrentTxDescr)
      m_R_dma_CurrentTxDescr = m_R_dma_TxDescrList;

    uint32_t *data = (uint32_t*) descriptor.rawdata();

    for (size_t i = 0; i < 4; ++i) {
      PayLoad pl;

      pl.set_payload(m_R_dma_CurrentTxDescr + i*sizeof(uint32_t),
                     (uint8_t*) &data[i], sizeof(uint32_t));
      this->out_port->trans_read_data(pl);
    }

    if (descriptor.OwnedByCPU())
      return false;

    return true;
  }

  // --------------------------------------------------------------------
  bool GMAC_Univ::read_rx_descriptor(RxDescriptor &descriptor) {
    if (!m_R_dma_CurrentRxDescr)
      m_R_dma_CurrentRxDescr = m_R_dma_RxDescrList;

    uint32_t *data = (uint32_t*) descriptor.rawdata();

    for (size_t i = 0; i < 4; ++i) {
      PayLoad pl;

      pl.set_payload(m_R_dma_CurrentRxDescr + i*sizeof(uint32_t),
                     (uint8_t*) &data[i], sizeof(uint32_t));
      this->out_port->trans_read_data(pl);
    }
    descriptor.ClearStatus();

    if (descriptor.OwnedByCPU())
      return false;

    return true;
  }

  // --------------------------------------------------------------------
  void GMAC_Univ::write_tx_descriptor(const TxDescriptor &descriptor) {
    const uint32_t *data = (uint32_t*) descriptor.rawdata();

    for (size_t i = 0; i < 4; ++i) {
      PayLoad pl;

      pl.set_payload(m_R_dma_CurrentTxDescr + i*sizeof(uint32_t),
                     (uint8_t*) &data[i], sizeof(uint32_t));
      this->out_port->trans_write_data(pl);
    }
  }

  // --------------------------------------------------------------------
  void GMAC_Univ::write_rx_descriptor(const RxDescriptor &descriptor) {
    const uint32_t *data = (uint32_t*) descriptor.rawdata();

    for (size_t i = 0; i < 4; ++i) {
      PayLoad pl;

      pl.set_payload(m_R_dma_CurrentRxDescr + i*sizeof(uint32_t),
                     (uint8_t*) &data[i], sizeof(uint32_t));
      this->out_port->trans_write_data(pl);
    }
  }

  // --------------------------------------------------------------------
  bool GMAC_Univ::_try_tx_1() {
    TxDescriptor descriptor;

    if (m_R_dma_Interrupts.TxState() != IRQ_Reg::TX_SUSP) {
      warning()
        << "entering transmit routine without being in SUSP mode"
        << std::endl;
      return false;
    }

    m_R_dma_Interrupts.setTxState(IRQ_Reg::TX_RUN_FetchTxDescr);

    if (!this->read_tx_descriptor(descriptor)) {
      m_R_dma_Interrupts.setTxState(IRQ_Reg::TX_SUSP);
      interrupts_fire(IRQ_Reg::TxBufUnavailable);
      return false;
    }

    if (!descriptor.IsFirstSegment()) {
      warning()
        << "first descriptor is not marked as being the first segment"
        << std::endl;
      m_R_dma_Interrupts.setTxState(IRQ_Reg::TX_SUSP);
      return false;
    }

    if (!descriptor.IsLastSegment()) {
      warning()
        << "packets descriptor layout not supported"
        << std::endl;
      abort();
    }

    m_R_dma_Interrupts.setTxState(IRQ_Reg::TX_RUN_ReadData);

    uint32_t dataaddr = descriptor.buf1addr();
    uint32_t datalen  = descriptor.buf1size();

    if (datalen < 6+6+2) {	// 2*MAC + ETHER-TYPE
      warning()
        << "ethernet buffer size too small"
        << std::endl;
      m_R_dma_Interrupts.setTxState(IRQ_Reg::TX_SUSP);
      return false;
    }

    std::auto_ptr<EtherBuffer> buffer;

    buffer.reset(new EtherBuffer(datalen));

    for (size_t i = 0; i < datalen; ++i) {
      PayLoad  payload;

      payload.set_payload(dataaddr+i, buffer->at(i), 1);
      this->out_port->trans_read_data(payload);
    }

    this->m_transport->send(*buffer);

    m_R_dma_Interrupts.setTxState(IRQ_Reg::TX_RUN_ClosDescr);

    descriptor.setOwnedByCPU();
    this->write_tx_descriptor(descriptor);
    m_R_dma_CurrentTxDescr = descriptor.buf2addr();

    if (descriptor.IntOnCompletion())
      interrupts_fire(IRQ_Reg::TxInt);

    m_R_dma_Interrupts.setTxState(IRQ_Reg::TX_SUSP);
    return true;
  }

  // --------------------------------------------------------------------
  bool GMAC_Univ::_try_rx_1(const EtherBuffer &buffer) {
    if (buffer.length() < 6+6+2) // 2*MAC + ETHER-TYPE
      return false;

    RxDescriptor descriptor;

    if (m_R_dma_Interrupts.RxState() != IRQ_Reg::RX_SUSP) {
      warning()
        << "entering receive routine without being in SUSP mode"
        << std::endl;
      return false;
    }

    m_R_dma_Interrupts.setRxState(IRQ_Reg::RX_RUN_FetchRxDescr);

    if (!this->read_rx_descriptor(descriptor)) {
      m_R_dma_Interrupts.setRxState(IRQ_Reg::RX_SUSP);
      interrupts_fire(IRQ_Reg::RxBufUnavailable);
      return false;
    }

    m_R_dma_Interrupts.setRxState(IRQ_Reg::RX_RUN_TransToHost);

    if (descriptor.buf1size() < buffer.length()) {
      warning() << "RX buffer too small" << std::endl;
      return false;
    }

    for (size_t i = 0; i < buffer.length(); ++i) {
      PayLoad  payload;

      payload.set_payload
        (descriptor.buf1addr()+i, (uint8_t*) buffer.at(i), 1);
      this->out_port->trans_write_data(payload);
    }

    m_R_dma_Interrupts.setRxState(IRQ_Reg::RX_RUN_ClosDescr);
    descriptor.SetFirstSegment();
    descriptor.SetLastSegment();
    descriptor.setLength(buffer.length() + 4);
    descriptor.setOwnedByCPU();
    this->write_rx_descriptor(descriptor);
    m_R_dma_CurrentRxDescr = descriptor.buf2addr();

    if (descriptor.IntOnCompletion())
      interrupts_fire(IRQ_Reg::RxInt);

    m_R_dma_Interrupts.setRxState(IRQ_Reg::RX_SUSP);
    return true;
  }

  // --------------------------------------------------------------------
  bool GMAC_Univ::filter_da(const uint8_t *destination) {
    const EtherAddress address(destination);

    switch (address.classify()) {
    case EtherAddress::BROADCAST:
      return !m_R_GMAC_FrameFilter.BroadcastDisabled();

    case EtherAddress::MULTICAST:
      if (m_R_GMAC_FrameFilter.PassAllMulticast())
        return true;
      if (m_R_GMAC_FrameFilter.DAHashMulticast()) {
        error() << "DA multicast addresses w.r.t. hashtable unsupported" << endl;
        return false;
      }
      break ;

    case EtherAddress::UNICAST:
      if (m_R_GMAC_FrameFilter.DAHashUnicast()) {
        error() << "DA unicast addresses w.r.t. hashtable unsupported" << endl;
        return false;
      }
      break ;

    default:
      abort();
    }

    if (address == m_R_GMAC_MAC0)
      return true;

    for (size_t i = 0; i < MAC1s_count; ++i) {
      const MAC1_Reg &mac = this->m_R_GMAC_MAC1[i];

      if (!mac.enabled())
        continue;
      if (mac.filter() != MAC1_Reg::MAC_F_DA)
        continue ;

      if (mac.filter(destination))
        return (!m_R_GMAC_FrameFilter.DstFilterInverted());
    }

    return m_R_GMAC_FrameFilter.DstFilterInverted();
  }

  // --------------------------------------------------------------------
  bool GMAC_Univ::filter_sa(const uint8_t *source) {
    for (size_t i = 0; i < MAC1s_count; ++i) {
      const MAC1_Reg &mac = this->m_R_GMAC_MAC1[i];

      if (!mac.enabled())
        continue;
      if (mac.filter() != MAC1_Reg::MAC_F_SA)
        continue ;

      if (mac.filter(source))
        return (!m_R_GMAC_FrameFilter.SrcFilterInverted());
    }

    return m_R_GMAC_FrameFilter.SrcFilterInverted();
  }


  // ------------------------------------------------------------------
  void GMAC_Univ::_tx_thread() {
    while (true) {
      this->wait(this->m_tx_event);
      if (m_R_dma_Interrupts.TxState() != IRQ_Reg::TX_STOP)
        this->_try_tx_1();
    }
  }

  // ------------------------------------------------------------------
  void GMAC_Univ::_rx_thread() {
    EtherBuffer buffer(1518u);

    while (true) {
      sc_core::sc_time towait(10, sc_core::SC_US);

      this->wait(towait);
      if (m_transport->recv(buffer)) {
        if(m_R_dma_Interrupts.RxState() != IRQ_Reg::RX_STOP)
          this->_try_rx_1(buffer);
      }
    }
  }

  // --------------------------------------------------------------------
  void GMAC_Univ::trans_read_data(PayLoad &pl) {
    if (pl.get_data_length() != 4) {
      error() << "can only read 4 bytes length data" << std::endl;
      abort();
    }
    uint32_t data = read_word((uint32_t) pl.get_address());
    *((uint32_t*)(pl.get_data_ptr())) = data;
  }

  void GMAC_Univ::trans_write_data(PayLoad &pl) {
    if (pl.get_data_length() != 4) {
      error() << "can only write 4 bytes length data" << std::endl;
      abort();
    }

    uint32_t addr = pl.get_address();
    uint32_t data = *((uint32_t*)(pl.get_data_ptr()));
    write_word(addr, data);
  }

} // namespace simsoc
