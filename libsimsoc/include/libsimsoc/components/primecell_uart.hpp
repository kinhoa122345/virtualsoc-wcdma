//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef PRIMECELL_UART_HPP
#define PRIMECELL_UART_HPP

#include <queue>
#include "libsimsoc/module.hpp"
#include "libsimsoc/interfaces/tlm.hpp"
#include "libsimsoc/interfaces/RS232.hpp"
#include "libsimsoc/interfaces/tlm_signal.hpp"

namespace simsoc {

class PrimeCellUart: public Module,
                     public RW_Target,
                     public AbstractRS232_DTE {
public:
  static const uint16_t NB_REG = 22;
  static const uint16_t LENGTH = 16;
  static const uint16_t FIFO_SIZE = 16;
  static const uint32_t MAX_SPEED = 115200;

  // UARTDR, RW register (read and write)
  static const uint16_t DR = 0x0;
  // mask:
  static const uint16_t DR_DATA = 255<<0;
  static const uint16_t DR_FE = 1<<8;// Framing error
  static const uint16_t DR_PE = 1<<9;// Parity error
  static const uint16_t DR_BE = 1<<10;// Break error
  static const uint16_t DR_OE = 1<<11;// Overrun error
  // value:
  uint16_t dr;

  // UARTRSR, Receive Status register (read only; write means ECR)
  static const uint8_t RSR = 0x04;
  // mask:
  static const uint8_t RSR_FE = 1<<0;// Framing error
  static const uint8_t RSR_PE = 1<<1;// Parity error
  static const uint8_t RSR_BE = 1<<2;// Break error
  static const uint8_t RSR_OE = 1<<3;// Overrun error
  // value:
  uint16_t rsr;

  // UARTECR, Error Clear register (write only; read means RSR)
  static const uint16_t ECR = 0x04;

  // UARTFR, Flag register(read only)
  static const uint16_t FR = 0x18;
  // mask:
  static const uint16_t FR_CTS = 1<<0;// Clear to send
  static const uint16_t FR_DSR = 1<<1;// Data set ready
  static const uint16_t FR_DCD = 1<<2;// Data carrier detect
  static const uint16_t FR_BUSY = 1<<3;// UART busy
  static const uint16_t FR_RXFE = 1<<4;// Receive FIFO empty
  static const uint16_t FR_TXFF = 1<<5;// Transmit FIFO full
  static const uint16_t FR_RXFF = 1<<6;// Receive FIFO full
  static const uint16_t FR_TXFE = 1<<7;// Transmit FIFO empty
  static const uint16_t FR_RI = 1<<8;// Ring indicator
  // value:
  uint16_t fr;

  // UARTILPR, IrDA Low-Power Counter register(read and write)
  static const uint32_t ILPR = 0x20;

  // UARTIBRD, Integer Baud Rate Divisor register(read and write)
  static const uint32_t IBRD = 0x24;
  uint16_t ibrd;

  // UARTFBRD, Fractional Baud Rate Divisor register(read and write)
  static const uint32_t FBRD = 0x28;
  static const uint32_t FBRD_MSK = 0x3f;
  uint8_t fbrd;

  // UARTLCR_H, Line Control register(read and write)
  static const uint16_t LCR_H = 0x2C;
  // mask:
  static const uint16_t LCR_H_BRK = 1;// Send break
  static const uint16_t LCR_H_PEN = 1<<1;// Parity select
  static const uint16_t LCR_H_EPS = 1<<2;// Even parity select
  static const uint16_t LCR_H_STP2 = 1<<3;// Two stop bit select
  static const uint16_t LCR_H_FEN = 1<<4;// Enable FIFOs
  static const uint16_t LCR_H_WLEN = 3<<5;// Word length
  static const uint16_t LCR_H_SPS = 1<<7;// Stick parity select
  // value:
  uint16_t lcr_h;
  bool fifo_enabled;

  // UARTCR, Control register(read and write)
  static const uint16_t CR = 0x30;
  // mask:
  static const uint16_t CR_UARTEN = 1<<0;// UART enable
  static const uint16_t CR_SIREN = 1<<1;// IrDA SIR enable
  static const uint16_t CR_SIRLP = 1<<2;// IrDA SIR low power mode
  static const uint16_t CR_LBE = 1<<7;// Loop back enable
  static const uint16_t CR_TXE = 1<<8;// Transmit enable
  static const uint16_t CR_RXE = 1<<9;// Receive enable
  static const uint16_t CR_DTR = 1<<10;// Data transmit ready
  static const uint16_t CR_RTS = 1<<11;// Request to send
  static const uint16_t CR_Out1 = 1<<12;// Output
  static const uint16_t CR_Out2 = 1<<13;// Output
  static const uint16_t CR_RTSEn = 1<<14;// RTS hardware flow control enable
  static const uint16_t CR_CTSEn = 1<<15;// CTS hardware flow control enable
  // value:
  uint16_t cr;

  // UARTIFLS, Interrupt FIFO Level Select register(read and write)
  static const uint16_t IFLS = 0x34;
  // mask:
  static const uint16_t IFLS_TXIFLSEL = 7<<0;// Transmit interrupt FIFO level select
  static const uint16_t IFLS_RXIFLSEL = 7<<3;// Receive interrupt FIFO level select
  // constant:
  static const uint16_t IFLS_TXIFLSEL_TRIGGER_LEVEL_2 = 0<<0;
  static const uint16_t IFLS_TXIFLSEL_TRIGGER_LEVEL_4 = 1<<0;
  static const uint16_t IFLS_TXIFLSEL_TRIGGER_LEVEL_8 = 1<<1;
  static const uint16_t IFLS_TXIFLSEL_TRIGGER_LEVEL_12 = 3<<0;
  static const uint16_t IFLS_TXIFLSEL_TRIGGER_LEVEL_14 = 1<<2;
  static const uint16_t IFLS_RXIFLSEL_TRIGGER_LEVEL_2 = 0<<3;
  static const uint16_t IFLS_RXIFLSEL_TRIGGER_LEVEL_4 = 1<<3;
  static const uint16_t IFLS_RXIFLSEL_TRIGGER_LEVEL_8 = 1<<4;
  static const uint16_t IFLS_RXIFLSEL_TRIGGER_LEVEL_12 = 3<<3;
  static const uint16_t IFLS_RXIFLSEL_TRIGGER_LEVEL_14 = 1<<5;
  // value:
  uint16_t ifls;
  uint16_t transmit_trigger_level;
  uint16_t receive_trigger_level;

  // UARTIMSC, Interrupt Mask Set/Clear register(read and write)
  static const uint16_t IMSC = 0x38;
  // mask:
  static const uint16_t IMSC_RIMIM = 0<<0;// nUARTRI modem interrupt mask
  static const uint16_t IMSC_CTSMIM = 1<<1;// nUARTCTS modem interrupt mask
  static const uint16_t IMSC_DCDSMIM = 1<<2;// nUARTDCD modem interrupt mask
  static const uint16_t IMSC_DSRMIM = 1<<3;// nUARTDSR modem interrupt mask
  static const uint16_t IMSC_RXIM = 1<<4;// Receive interrupt mask
  static const uint16_t IMSC_TXIM = 1<<5;// Transmit interrupt mask
  static const uint16_t IMSC_RTIM = 1<<6;// Receive timeout interrupt mask
  static const uint16_t IMSC_FEIM = 1<<7;// Framing error interrupt mask
  static const uint16_t IMSC_PEIM = 1<<8;// Parity error interrupt mask
  static const uint16_t IMSC_BEIM = 1<<9;// Break eeror interrupt mask
  static const uint16_t IMSC_OEIM = 1<<10;// Overrun error interrupt mask
  // value:
  uint16_t imsc;

  // UARTRIS, Raw Interrupt Status register(read only)
  static const uint16_t RIS = 0x3C;
  // mask:
  static const uint16_t RIS_RIRMIS = 0<<0;// nUARTRI modem raw interrupt status
  static const uint16_t RIS_CTSRMIS = 1<<1;// nUARTCTS modem raw interrupt status
  static const uint16_t RIS_DCDRMIS = 1<<2;// nUARTDCD modem raw interrupt status
  static const uint16_t RIS_DSRRMIS = 1<<3;// nUARTDSR modem raw interrupt status
  static const uint16_t RIS_RXRIS = 1<<4;// Receive raw interrupt status
  static const uint16_t RIS_TXRIS = 1<<5;// Transmit raw interrupt status
  static const uint16_t RIS_RTRIS = 1<<6;// Receive timeout raw interrupt status
  static const uint16_t RIS_FERIS = 1<<7;// Framing error raw interrupt status
  static const uint16_t RIS_PERIS = 1<<8;// Parity error raw interrupt status
  static const uint16_t RIS_BERIS = 1<<9;// Break eeror raw interrupt status
  static const uint16_t RIS_OERIS = 1<<10;// Overrun error raw interrupt status
  static const uint16_t RIS_ERRORS = RIS_FERIS|RIS_PERIS|RIS_BERIS|RIS_OERIS;
  // value:
  uint16_t ris;

  // UARTMIS, Masked Interrupt Status register(read only)
  static const uint16_t MIS = 0x40;
  // value:
  uint16_t mis() const;

  // UARTICR, Interrupt Clear register(write only)
  static const uint16_t ICR = 0x44;
  // mask:
  static const uint16_t ICR_RIMIC = 0<<0;// nUARTRI modem  interrupt clear
  static const uint16_t ICR_CTSMIC = 1<<1;// nUARTCTS modem interrupt clear
  static const uint16_t ICR_DCDMIC = 1<<2;// nUARTDCD modem interrupt clear
  static const uint16_t ICR_DSRMIC = 1<<3;// nUARTDSR modem  interrupt clear
  static const uint16_t ICR_RXIC = 1<<4;// Receive interrupt clear
  static const uint16_t ICR_TXIC = 1<<5;// Transmit interrupt clear
  static const uint16_t ICR_RTIC = 1<<6;// Receive timeout interrupt clear
  static const uint16_t ICR_FEIC = 1<<7;// Framing error interrupt clear
  static const uint16_t ICR_PEIC = 1<<8;// Parity error interrupt clear
  static const uint16_t ICR_BEIC = 1<<9;// Break error interrupt clear
  static const uint16_t ICR_OEIC = 1<<10;// Overrun error interrupt clear
  // value: nothing stored
  uint16_t icr;

  //UARTDMACR, DMA Control register(read and write)
  static const uint16_t DMACR = 0x48;
  // mask:
  static const uint16_t DMACR_RXDMAE = 0<<0;// Receive DMA enable
  static const uint16_t DMACR_TXDMAE = 1<<1;// Transmit DMA enable
  static const uint16_t DMACR_DMAONERR = 1<<2;// DMA on error
  // value:
  uint32_t dmacr;

  //UARTPeriphID0 (read only)
  static const uint32_t UARTPeriphID0 = 0xFE0;

  //UARTPeriphID1 (read only)
  static const uint32_t UARTPeriphID1 = 0xFE4;

  //UARTPeriphID2 (read only)
  static const uint32_t UARTPeriphID2 = 0x0FE8;

  //UARTPeriphID3 (read only)
  static const uint32_t UARTPeriphID3 = 0xFEC;

  //UARTPcellID0 (read only)
  static const uint32_t UARTPcellID0 = 0xFF0;

  //UARTPcellID1 (read only)
  static const uint32_t UARTPcellID1 = 0xFF4;

  //UARTPcellID2 (read only)
  static const uint32_t UARTPcellID2 = 0xFF8;

  //UARTPcellID3 (read only)
  static const uint32_t UARTPcellID3 = 0xFFC;

  static uint32_t speed(uint32_t divisor);

  AbstractRS232_DCE *dce;

  sc_core::sc_event cts_event;

protected:
  std::queue<uint8_t> transmit_fifo;
  std::queue<uint16_t> receive_fifo;

public:

  SC_HAS_PROCESS(PrimeCellUart);
  PrimeCellUart(sc_core::sc_module_name name);
  ~PrimeCellUart();

  RW_TargetPort rw_port;
  SignalInitiatorPort<bool> it_signal;

  void end_of_elaboration(); // called by the SystemC kernel

  bool rts_signal() const;
  bool cts_signal() const;

  // for protocol tlm read-write
  uint16_t read_half(uint32_t addr);
  void write_half(uint32_t addr, uint16_t data);

  void trans_read_data(PayLoad &pl)
  {
      switch (pl.get_data_length()) {
      case 4:
        //warning()<<"read size of 4 changed to size of 1"<<std::endl;
      case 2: {
        uint32_t addr = pl.get_address();
        uint16_t data = read_half(addr);
        *(uint16_t*)(pl.get_data_ptr()) = data;
      } break;
      default:
        error() <<": read data method is not implemented for data_length = "
        <<pl.get_data_length() <<std::endl;
        exit(1);
      }
  };

  void trans_write_data(PayLoad &pl)
  {
      switch (pl.get_data_length()) {
      case 4:
        //warning()<<"write size of 4 changed to size of 1"<<std::endl;
      case 2: {
        uint32_t addr = pl.get_address();
        uint16_t data = *(uint16_t*)(pl.get_data_ptr());
        write_half(addr,data);
      } break;
      default:
        error() <<": write data method is not implemented for data_length = "
        <<pl.get_data_length() <<std::endl;
        exit(1);
      }
  };

  bool uart_receive_enabled() const;
  bool uart_transmit_enabled() const;

  // for protocol RS-232 DTE
  void receive(uint8_t c);
  void set_cts(bool cts_signal1);
  void set_dsr(bool dsr_signal);

  void compute();

  sc_core::sc_event timeout_event;
  const sc_core::sc_time timeout_duration; // value defined in the constructor
  void compute_timeout();

  void update_it_signal();
};

} // namespace simsoc

#endif //PRIMECELL_UART_HPP
