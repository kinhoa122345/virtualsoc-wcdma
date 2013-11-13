//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef UART_16550_HPP
#define UART_16550_HPP

#include <deque>
#include "libsimsoc/interfaces/tlm.hpp"
#include "libsimsoc/interfaces/tlm_signal.hpp"
#include "libsimsoc/interfaces/RS232.hpp"
#include "libsimsoc/module.hpp"

// Some informations about 16550's uart family are available on this website:
// http://www.lammertbies.nl/comm/info/serial-uart.html

namespace simsoc {

class Uart16550: public Module,
                 public RW_Target,
                 public AbstractRS232_DTE
{
public:
  static const uint32_t NB_REG = 8;
  static const uint32_t LENGTH = NB_REG*4; // '*4' for compatiblity with XLS16550 uart
  static const uint32_t SIZE = LENGTH;
  static const uint32_t FIFO_SIZE = 16;
  static const uint32_t MAX_SPEED = 115200;

  // RBR, receiver buffer register (read-only)
  static const uint32_t RBR = 0x00;
  // value:
  uint8_t rbr;

  // THR, transmitter holding register (write only)
  static const uint32_t THR = 0x0;
  // the value is immediately sent to the dce

  // IER, interrupt enable register
  static const uint32_t IER = 0x1;
  // mask:
  static const uint8_t IER_DATA_AVAILABLE = 1<<0;
  static const uint8_t IER_THR_EMPTY = 1<<1;
  static const uint8_t IER_ERROR = 1<<2;
  static const uint8_t IER_MSR_CHANGE = 1<<3;
  // value:
  uint8_t ier;

  // IIR, interrupt identification register (read-only)
  static const uint32_t IIR = 0x2;
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
  // value:
  uint8_t iir;

  // FCR, FIFO control register (write only)
  static const uint8_t FCR = 0x2;
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
  // value:
  bool fifo_enabled;
  bool dma_mode;
  uint32_t trigger_level;

  // LCR, line control register
  static const uint32_t LCR = 0x3;
  // mask:
  static const uint8_t LCR_WORD_LENGTH = 3<<0;
  static const uint8_t LCR_STOP_BIT = 1<<2;
  static const uint8_t LCR_PARITY_BITS = 7<<3;
  static const uint8_t LCR_BREAK_SIGNAL = 1<<6;
  static const uint8_t LCR_DLAB = 1<<7;
  // value:
  uint8_t lcr;
  bool dlab; // clone of bit lcr[7], fast access is required

  // MCR, modem control register
  static const uint32_t MCR = 0x4;
  // mask:
  static const uint8_t MCR_TERMINAL_READY = 1<<0;
  static const uint8_t MCR_REQUEST_TO_SEND = 1<<1;
  static const uint8_t MCR_AUX_1 = 1<<2;
  static const uint8_t MCR_AUX_2 = 1<<3;
  static const uint8_t MCR_LOOPBACK_MODE = 1<<4;
  static const uint8_t MCR_OTHERS = 7<<5;
  // value:
  uint8_t mcr;

  // LSR, line status register (read-only)
  static const uint32_t LSR = 0x5;
  // mask:
  static const uint8_t LSR_DATA_AVAILABLE = 1<<0;
  static const uint8_t LSR_OVERRUN_ERROR = 1<<1;
  static const uint8_t LSR_PARITY_ERROR = 1<<2;
  static const uint8_t LSR_FRAMING_ERROR = 1<<3;
  static const uint8_t LSR_BREAK_RECEIVED = 1<<4;
  static const uint8_t LSR_THR_EMPTY = 1<<5;
  static const uint8_t LSR_LINE_IDLE = 1<<6;
  static const uint8_t LSR_ERROR_IN_FIFO = 1<<7;
  // value:
  uint8_t lsr;

  // MSR, modem status register (read-only)
  static const uint32_t MSR = 0x6;
  // mask:
  static const uint8_t MSR_CHANGE_CLEAR_TO_SEND = 1<<0;
  static const uint8_t MSR_CHANGE_DATA_SET_READY = 1<<1;
  static const uint8_t MSR_CHANGE_RING_INDICATOR = 1<<2;
  static const uint8_t MSR_CHANGE_CARRIER_DETECT = 1<<3;
  static const uint8_t MSR_CLEAR_TO_SEND = 1<<4;
  static const uint8_t MSR_DATA_SET_READY = 1<<5;
  static const uint8_t MSR_RING_INDICATOR = 1<<6;
  static const uint8_t MSR_CARRIER_DETECT = 1<<7;
  // value:
  uint8_t msr;

  // SCR, scratch register
  static const uint32_t SCR = 0x7;
  // value:
  uint8_t scratch;

  // DLL, divisor latch LSB
  static const uint32_t DLL = 0x0;
  // DLM, divisor latch MSB
  static const uint32_t DLM = 0x1;
  // value:
  uint16_t divisor;

  static uint32_t speed(uint16_t divisor);

  AbstractRS232_DCE *dce;

protected:
  std::deque<uint8_t> receive_fifo;

public:
  RW_TargetPort rw_port;
  SignalInitiatorPort<bool> it_signal;
  bool big_endian; // if used in a word-invariant big-endian system, then the addresses must be fixed.

//   sc_core::sc_event timeout_event;

//   SC_HAS_PROCESS(Uart16550);
  Uart16550(sc_core::sc_module_name name, bool big_endian=false);
  ~Uart16550();
  void end_of_elaboration(); // called by the SystemC kernel

  // for protocol tlm read-write
  uint8_t read_byte(uint32_t addr);
  void write_byte(uint32_t addr, uint8_t data);

  void trans_read_data(PayLoad &pl)
  {
    uint32_t addr = pl.get_address();
    switch (pl.get_data_length()) {
    case 4: {
      debug() <<"read access of size 4 converted to size 1" <<std::endl;
      addr=addr>>2;
      const uint8_t data = read_byte(addr);
      *(uint8_t*)(pl.get_data_ptr()) = data;
    } break;
    case 1: {
      if (big_endian)
        addr = addr^3;
      uint8_t data = read_byte(addr);
      *(uint8_t*)(pl.get_data_ptr()) = data;
    } break;
    default:
      error() <<": read data method is not implemented for data_length = "
              <<pl.get_data_length() <<std::endl;
      exit(1);
    }
  };

  void trans_write_data(PayLoad &pl)
  {
    uint32_t addr = pl.get_address();

    switch (pl.get_data_length()) {
    case 4: {
      debug() <<"write access of size 4 converted to size 1" <<std::endl;
      addr = addr>>2;
      const uint8_t data = *(uint8_t*)(pl.get_data_ptr());
      write_byte(addr,data);
    } break;
    case 1: {
      if (big_endian)
        addr = addr^3;
      const uint8_t data = *(uint8_t*)(pl.get_data_ptr());
      write_byte(addr,data);
    } break;
    default:
      error() <<": write data  method is not implemented for data_length = "
              <<pl.get_data_length() <<std::endl;
      exit(1);
    }
  };

  // for protocol RS-232 DTE
  void receive(uint8_t c);
  void set_cts(bool cts_signal);
  void set_dsr(bool dsr_signal);

  // SC_METHOD
//   void timeout_process();

protected:
  void update_iir();
};

} // namespace simsoc

#endif //UART_16550_HPP
