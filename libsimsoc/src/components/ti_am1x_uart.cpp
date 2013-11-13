//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "libsimsoc/components/ti_am1x_uart.hpp"
#include "libsimsoc/display.hpp"
#include "libsimsoc/interfaces/yield.hpp"

#include <stdexcept>

namespace simsoc  {
namespace TI_AM1x {

  // ------------------------------------------------------------------
  uint32_t Uart::speed(uint16_t divisor) {
    return MAX_SPEED / divisor;
  }

  // ------------------------------------------------------------------
  Uart::Uart(sc_core::sc_module_name name)
    :Module(name)
    ,m_dce(NULL)
  {
    this->_reset();

    this->m_rwport.register_b_transport(this, &Uart::custom_b_transport);

    SC_METHOD(_timeout_entry);
    this->dont_initialize();
    this->sensitive << m_timeout_event;
  }

  // ------------------------------------------------------------------
  Uart::~Uart() {
    if (m_dce != NULL)
      delete m_dce;
  }

  // ------------------------------------------------------------------
  void Uart::_reset() {
    this->m_rbr     = 0;
    this->m_ier     = IER_ERROR;
    this->m_iir     = IIR_FIFO_ENABLED;
    this->m_lcr     = 0;
    this->m_mcr     = 0;
    this->m_lsr     = LSR_THR_EMPTY | LSR_LINE_IDLE;
    this->m_msr     = 0;
    this->m_scratch = 0;
    this->m_divisor = 0x000c;
    this->m_fifoena = false;
    this->m_fifothr = 1;

    m_rxfifo.clear();
  }

  // ------------------------------------------------------------------
  void Uart::end_of_elaboration() {
    if (!this->m_dce) {
      const char *message = "no DCE is connected to UART";
      error() << message << std::endl;
      throw std::runtime_error(message);
    }
  }

  // ------------------------------------------------------------------
  void Uart::set_dce(AbstractRS232_DCE *dce) {
    if (m_dce != NULL)
      delete m_dce;
    m_dce = dce;
  }

  // ------------------------------------------------------------------
  uint8_t Uart::_read_rbr() {
    uint8_t data = m_rbr;

    if (m_fifoena) {
      if (m_rxfifo.size()==0) {
        assert(!(m_lsr & LSR_DATA_AVAILABLE));
        warning()
          << "read access to register RBR but no new character inside"
          << std::endl;
      } else if (m_rxfifo.size()==1) {
        m_rxfifo.pop_front();
        m_lsr &= ~LSR_DATA_AVAILABLE;
      } else {
        m_rxfifo.pop_front();
        m_rbr = m_rxfifo.front();
      }
    } else {
      if (!(m_lsr&LSR_DATA_AVAILABLE))
        warning()
          << "read access to register RBR but no new character inside"
          << std::endl;
      m_lsr &= ~LSR_DATA_AVAILABLE;
    }
    this->update_iir();
    return data;
  }

  // ------------------------------------------------------------------
  uint8_t Uart::_read_lsr() {
    uint8_t data = m_lsr;
    m_lsr &= ~LSR_CLEAR_ON_READ;
    this->update_iir();
    return data;
  }

  // ------------------------------------------------------------------
  uint8_t Uart::_read_msr() {
      uint8_t data = m_msr;
      m_msr &= ~MSR_CLEAR_ON_READ;
      this->update_iir();
      return data;
    }

  // ------------------------------------------------------------------
  uint8_t Uart::read_byte(uint32_t addr) {
    debug() << "reading at address ["
            << std::hex << (uint32_t) addr
            << "]" << std::endl;

    switch (addr) {
    case RBR: return dlab() ? (m_divisor >> 0) & 0xff : this->_read_rbr();
    case IER: return dlab() ? (m_divisor >> 8) & 0xff : m_ier;
    case IIR: return m_iir;
    case LCR: return m_lcr;
    case MCR: return m_mcr;
    case LSR: return _read_lsr();
    case MSR: return _read_msr();
    case SCR: return m_scratch;

    default:
      warning()
        << "invalid read outside range "
        << "(offset = " << std::hex <<addr << ")"
        << std::endl;
      return 0;
    }
  }

  // ------------------------------------------------------------------
  void Uart::write_byte(uint32_t addr, uint8_t data) {
    debug() << "writing byte "
            << std::hex << (uint32_t) data
            << " at address " << std::hex << addr
            << std::endl;

    switch (addr) {
    case THR:
      if (dlab()) // not THR, but DLL
        m_divisor = (m_divisor&0xff00)|data;
      else {
        m_dce->send(data);
        YIELD();
      }
      break ;

    case IER:
      if (dlab()) { // not THR, but DLM
        m_divisor = (m_divisor&0xff)|((uint16_t)data<<8);
      } else {
        m_ier = data;
        this->update_iir();
      }
      break ;

    case FCR:
      m_fifoena = data & FCR_ENABLE_FIFO;
      if ((data & FCR_CLEAR_RECEIVE_FIFO))
        m_rxfifo.clear();
      switch ((data & FCR_TRIGGER_LEVEL_BITS)) {
      case FCR_TRIGGER_LEVEL_1 : m_fifothr = 1; break;
      case FCR_TRIGGER_LEVEL_4 : m_fifothr = 4; break;
      case FCR_TRIGGER_LEVEL_8 : m_fifothr = 8; break;
      case FCR_TRIGGER_LEVEL_14: m_fifothr = 14; break;
      default: UNREACHABLE;
      }
      this->update_iir();
      break ;

    case LCR:
      m_lcr = data;
      break ;

    case MCR:
      if ((data & MCR_TERMINAL_READY) != (m_mcr & MCR_TERMINAL_READY))
        m_dce->set_dtr(data & MCR_TERMINAL_READY);

      if ((data & MCR_REQUEST_TO_SEND) != (m_mcr & MCR_REQUEST_TO_SEND))
        m_dce->set_rts(data & MCR_REQUEST_TO_SEND);

      if ((data & (MCR_AUX_1|MCR_AUX_2))) {
        debug() << "auxiliary output signals not implemented" << std::endl;
        data &=~ (MCR_AUX_1|MCR_AUX_2);
      }
      if ((data & MCR_LOOPBACK_MODE)) {
        warning() << "loopback mode not implemented" << std::endl;
        data &=~ MCR_LOOPBACK_MODE;
      }
      if ((data & MCR_OTHERS))
        warning() << "bits 5:7 of MCR register should be zero" << std::endl;

      m_mcr = data;
      break ;

    case LSR:
      error() << "invalid write access to LSR register" << std::endl;
      break ;
    case MSR:
      error() << "invalid write access to MSR register" << std::endl;
      break ;

    case SCR:
      m_scratch = data;
      break ;

    default:
      warning()
        << "invalid write access outside range "
        << "(offset = " << std::hex <<addr << ")"
        << std::endl;
      break ;
    }
  }

  // ------------------------------------------------------------------
  void Uart::receive(uint8_t c) {
    m_timeout_event.cancel();
    m_timeout_event.notify(8*YIELD_DURATION);

    if (m_fifoena) {
      if (m_rxfifo.size() >= FIFO_SIZE) {
        assert(m_lsr & LSR_DATA_AVAILABLE);
        warning()
          << "overrun detected (fifo enabled); new character discarded"
          << std::endl;
        m_lsr |= LSR_OVERRUN_ERROR;
      } else if (m_rxfifo.size() == 0) {
        m_rxfifo.push_back(c);
        m_rbr  = c;
        m_lsr |= LSR_DATA_AVAILABLE;
      } else {
        assert(m_lsr & LSR_DATA_AVAILABLE);
        m_rxfifo.push_back(c);
      }
    } else {
      if (m_lsr & LSR_DATA_AVAILABLE) {
        warning()
          << "overrun detected (fifo disabled); new character discarded"
          << std::endl;
        m_lsr |= LSR_OVERRUN_ERROR;
      } else {
        m_rbr = c;
        m_lsr |= LSR_DATA_AVAILABLE;
      }
    }
    this->update_iir();
  }

  // ------------------------------------------------------------------
  void Uart::update_iir(bool timeout) {
    m_iir &= ~IIR_ID_BITS;
    if ((m_ier & IER_ERROR) && (m_lsr & LSR_IT_MASK)) {
      m_iir |= IIR_ERROR;
    } else if ((m_ier & IER_DATA_AVAILABLE) &&
               (m_lsr & LSR_DATA_AVAILABLE) &&
               (!m_fifoena||timeout||m_rxfifo.size()>=m_fifothr)) {
      debug() << "data available" << std::endl;
      m_iir |= (m_fifoena && timeout) ? IIR_TIMEOUT : IIR_DATA_AVAILABLE;
    } else if ((m_ier & IER_THR_EMPTY) && (m_lsr & LSR_THR_EMPTY)) {
      m_iir |= IIR_THR_EMPTY;
    } else if ((m_ier & IER_MSR_CHANGE) && (m_msr & MSR_IT_MASK)) {
      m_iir |= IIR_MSR_CHANGE;
    }

    bool pending = m_iir & IIR_ID_BITS;

    if (pending)
      m_iir &= ~IIR_IT_PENDING;
    else
      m_iir |= IIR_IT_PENDING;
    m_it_signal = pending;
  }

  // ------------------------------------------------------------------
  void Uart::set_cts(bool new_val) {
    bool old_val = m_msr&MSR_CLEAR_TO_SEND;
    if (old_val!=new_val)
      m_msr |= MSR_CHANGE_CLEAR_TO_SEND;
    if (new_val)
      m_msr |= MSR_CLEAR_TO_SEND;
    else
      m_msr &= ~MSR_CLEAR_TO_SEND;
    this->update_iir();
  }

  // ------------------------------------------------------------------
  void Uart::set_dsr(bool new_val) {
    bool old_val = m_msr&MSR_DATA_SET_READY;
    if (old_val!=new_val)
      m_msr |= MSR_CHANGE_DATA_SET_READY;
    if (new_val)
      m_msr |= MSR_DATA_SET_READY;
    else
      m_msr &= ~MSR_DATA_SET_READY;
    this->update_iir();
  }

  // ------------------------------------------------------------------
  void Uart::_timeout_entry() {
    this->update_iir(true);
  }


  // ------------------------------------------------------------------
  void Uart::custom_b_transport(tlm::tlm_generic_payload &payload,
                                sc_core::sc_time &delay_time)
  {
    assert(payload.get_response_status() == tlm::TLM_INCOMPLETE_RESPONSE);

    if (payload.get_streaming_width() != sizeof(uint32_t)) {
      warning()
        << "received transaction with invalid streaming width"
        << std::endl;
      payload.set_response_status(tlm::TLM_BURST_ERROR_RESPONSE);
      return ;
    }

    if (payload.get_byte_enable_ptr()) {
      warning()
        << "byte enable not supported"
        << std::endl;
      payload.set_response_status(tlm::TLM_BYTE_ENABLE_ERROR_RESPONSE);
      return ;
    }

    uint32_t address = (uint32_t) payload.get_address() >> 2;
    size_t   dlength = payload.get_data_length();

    if (dlength != 1 && dlength != 4) {
      warning()
        << "received transaction with invalid data length (should be 1 or 4)"
        << std::endl;
      payload.set_response_status(tlm::TLM_BURST_ERROR_RESPONSE);
      return ;
    }

    switch (payload.get_command()) {
    case tlm::TLM_WRITE_COMMAND:
      if (dlength == 1) {
        write_byte(address, (uint8_t) *payload.get_data_ptr());
      } else {
        uint32_t *buffer;
        buffer = reinterpret_cast<uint32_t*>(payload.get_data_ptr());
        write_byte(address, *buffer & 0xff);
      }
      payload.set_response_status(tlm::TLM_OK_RESPONSE);
      break ;

    case tlm::TLM_READ_COMMAND:
      if (dlength == 1) {
        *((uint8_t*) payload.get_data_ptr()) = read_byte(address);
      } else {
        uint32_t *buffer;
        buffer = reinterpret_cast<uint32_t*>(payload.get_data_ptr());
        *buffer = (uint32_t) read_byte(address);
      }
      payload.set_response_status(tlm::TLM_OK_RESPONSE);
      break ;

    default:
      warning() << "command not supported" << std::endl;
      payload.set_response_status(tlm::TLM_COMMAND_ERROR_RESPONSE);
    }
  }

} // namespace TI_AM1x
} // namespace simsoc
