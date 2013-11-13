//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#if !defined(TI_AM1x_UART_HPP__)
# define TI_AM1x_UART_HPP__

# include <tlm_utils/simple_target_socket.h>

# include "libsimsoc/interfaces/RS232.hpp"
# include "libsimsoc/bitwise_operator.hpp"
# include "libsimsoc/components/ti_am1x_core.hpp"

# include <deque>

namespace simsoc  {
namespace TI_AM1x {

  class Uart
    : public Module
    , public AbstractRS232_DTE
  {
    SC_HAS_PROCESS(Uart);

  public:
    static const uint32_t FIFO_SIZE = 16;
    static const uint32_t MAX_SPEED = 115200;

    static const uint32_t RBR = 0x00; // Read  mode
    static const uint32_t THR = 0x00; // Write mode
    static const uint32_t IER = 0x01;
    static const uint32_t IIR = 0x02;
    static const uint32_t FCR = 0x02;
    static const uint32_t LCR = 0x03;
    static const uint32_t MCR = 0x04;
    static const uint32_t LSR = 0x05;
    static const uint32_t MSR = 0x06;
    static const uint32_t SCR = 0x07;


    Uart(sc_core::sc_module_name name);
    virtual ~Uart();

    typedef signals::SignalInitiatorPort_Level it_signal_t;

    it_signal_t& get_it_signal() { return m_it_signal; }
 
    AbstractRS232_DCE* dce() { return m_dce; }
    void set_dce(AbstractRS232_DCE *dce);

     typedef tlm_utils::simple_target_socket<Uart> inport_t;

    inport_t& get_rw_port() { return m_rwport; }

    static uint32_t speed(uint16_t divisor);

  protected:
    std::deque<uint8_t>  m_rxfifo;
    it_signal_t          m_it_signal;
    AbstractRS232_DCE   *m_dce;
    inport_t             m_rwport;

    bool    m_fifoena;
    uint8_t m_fifothr;

    uint8_t  m_rbr;          // RBR
    uint8_t  m_ier;          // IER, interrupt enable register
    uint8_t  m_iir;          // IIR, interrupt identification register
    uint8_t  m_lcr;          // LCR, line control register
    uint8_t  m_mcr;          // MCR, modem control register
    uint8_t  m_lsr;          // LSR, line status register
    uint8_t  m_msr;          // MSR, modem status register
    uint8_t  m_scratch;      // SCR, scratch register
    uint16_t m_divisor;

    void _reset();
    void _timeout_entry();

    sc_core::sc_event m_timeout_event;

    // SystemC hooks
    virtual void end_of_elaboration();

    // TLM protocol
    uint8_t read_byte (uint32_t addr);
    void    write_byte(uint32_t addr, uint8_t data);

    bool dlab() { return (m_lcr & LCR_DLAB); }

    uint8_t _read_rbr();
    uint8_t _read_lsr();
    uint8_t _read_msr();

    void custom_b_transport(tlm::tlm_generic_payload &payload,
                            sc_core::sc_time &delay_time);

    // RS-232 DTE protocol
    void receive(uint8_t c);
    void set_cts(bool cts_signal);
    void set_dsr(bool dsr_signal);

    void update_iir(bool timeout = false);

    // IER, interrupt enable register
    static const uint8_t IER_DATA_AVAILABLE = 1<<0;
    static const uint8_t IER_THR_EMPTY = 1<<1;
    static const uint8_t IER_ERROR = 1<<2;
    static const uint8_t IER_MSR_CHANGE = 1<<3;

    // IIR, interrupt identification register
    // mask:
    static const uint8_t IIR_IT_PENDING = 1<<0;
    static const uint8_t IIR_ID_BITS = 7<<1;
    static const uint8_t IIR_FIFO_BITS = 3<<6;
    // constant:
    static const uint8_t IIR_MSR_CHANGE = 0<<1;
    static const uint8_t IIR_THR_EMPTY = 1<<1;
    static const uint8_t IIR_DATA_AVAILABLE = 2<<1;
    static const uint8_t IIR_ERROR = 3<<1;
    static const uint8_t IIR_TIMEOUT = 6<<1;
    static const uint8_t IIR_NO_FIFO = 0<<6;
    static const uint8_t IIR_UNUSABLE_FIFO = 2<<6;
    static const uint8_t IIR_FIFO_ENABLED = 3<<6;

    // FCR, FIFO control register
    // mask:
    static const uint8_t FCR_ENABLE_FIFO = 1<<0;
    static const uint8_t FCR_CLEAR_RECEIVE_FIFO = 1<<1;
    static const uint8_t FCR_CLEAR_TRANSMIT_FIFO = 2<<1;
    static const uint8_t FCR_DMA_MODE = 1<<3;
    static const uint8_t FCR_TRIGGER_LEVEL_BITS = 3<<6;
    // constant:
    static const uint8_t FCR_TRIGGER_LEVEL_1 = 0<<6;
    static const uint8_t FCR_TRIGGER_LEVEL_4 = 1<<6;
    static const uint8_t FCR_TRIGGER_LEVEL_8 = 2<<6;
    static const uint8_t FCR_TRIGGER_LEVEL_14 = 3<<6;

    // LCR, line control register
    static const uint8_t LCR_WORD_LENGTH = 3<<0;
    static const uint8_t LCR_STOP_BIT = 1<<2;
    static const uint8_t LCR_PARITY_BITS = 7<<3;
    static const uint8_t LCR_BREAK_SIGNAL = 1<<6;
    static const uint8_t LCR_DLAB = 1<<7;

    // MCR, modem control register
    static const uint8_t MCR_TERMINAL_READY = 1<<0;
    static const uint8_t MCR_REQUEST_TO_SEND = 1<<1;
    static const uint8_t MCR_AUX_1 = 1<<2;
    static const uint8_t MCR_AUX_2 = 1<<3;
    static const uint8_t MCR_LOOPBACK_MODE = 1<<4;
    static const uint8_t MCR_OTHERS = 7<<5;

    // LSR, line status register
    static const uint8_t LSR_DATA_AVAILABLE = 1<<0;
    static const uint8_t LSR_OVERRUN_ERROR = 1<<1;
    static const uint8_t LSR_PARITY_ERROR = 1<<2;
    static const uint8_t LSR_FRAMING_ERROR = 1<<3;
    static const uint8_t LSR_BREAK_RECEIVED = 1<<4;
    static const uint8_t LSR_THR_EMPTY = 1<<5;
    static const uint8_t LSR_LINE_IDLE = 1<<6;
    static const uint8_t LSR_ERROR_IN_FIFO = 1<<7;

    // MSR, modem status register
    static const uint8_t MSR_CHANGE_CLEAR_TO_SEND = 1<<0;
    static const uint8_t MSR_CHANGE_DATA_SET_READY = 1<<1;
    static const uint8_t MSR_CHANGE_RING_INDICATOR = 1<<2;
    static const uint8_t MSR_CHANGE_CARRIER_DETECT = 1<<3;
    static const uint8_t MSR_CLEAR_TO_SEND = 1<<4;
    static const uint8_t MSR_DATA_SET_READY = 1<<5;
    static const uint8_t MSR_RING_INDICATOR = 1<<6;
    static const uint8_t MSR_CARRIER_DETECT = 1<<7;


    // Interrupts masks
    static const uint8_t LSR_IT_MASK
      = LSR_OVERRUN_ERROR
      | LSR_PARITY_ERROR
      | LSR_FRAMING_ERROR
      | LSR_BREAK_RECEIVED;

    static const uint8_t MSR_IT_MASK
      = MSR_CHANGE_CLEAR_TO_SEND
      | MSR_CHANGE_DATA_SET_READY
      | MSR_CHANGE_RING_INDICATOR
      | MSR_CHANGE_CARRIER_DETECT;

    // Clear on read masks
    static const uint8_t MSR_CLEAR_ON_READ
      = MSR_CHANGE_CLEAR_TO_SEND
      | MSR_CHANGE_DATA_SET_READY
      | MSR_CHANGE_RING_INDICATOR
      | MSR_CHANGE_CARRIER_DETECT;

    static const uint8_t LSR_CLEAR_ON_READ
      = LSR_OVERRUN_ERROR
      | LSR_PARITY_ERROR
      | LSR_FRAMING_ERROR
      | LSR_BREAK_RECEIVED;
  };

} // namespace TI_AM1x
} // namespace simsoc

#endif // !TI_AM1x_UART_HPP__
