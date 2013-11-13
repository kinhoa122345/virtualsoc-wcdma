//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

/*
 * TLM Model for Serial Memory Controller from ST Microlectronics
 *  model M25P64
 * It is connected to a serial flash that it can access directly.
 * The transmit and receive registers are used to hold
 * values to communicate with the flash.
 * The serial flash model transfers writes to perform controls.
 */

#ifndef ST_SMI_CTRL_HPP
#define ST_SMI_CTRL_HPP

#include "libsimsoc/interfaces/tlm.hpp"
#include "libsimsoc/components/serial_flash.hpp"
#include "libsimsoc/module.hpp"

namespace simsoc {

/*
 * The controller manages system Serial Memory Interface
 */

class SMICtrl: public Module,
               public RW_Target {

public:

  static const int BANK0 = 0;
  static const int BANK1 = 1;
  static const int BANK2 = 2;
  static const int BANK3 = 3;
  static const int MAX_BANKS = 4;

  /* STATUS_REG */
  // the low 8 bits are the status of the serial flash
  static const uint32_t STATUS_MASK = 0xFF;
  static const uint32_t INT_WCF_CLR =   0xFFFFFDFF; // clear: WCF clear
  static const uint32_t INT_TFF_CLR =   0xFFFFFEFF; // clear: TFF clear
  static const uint32_t TFF = 0x0100; // Transfer Finished FLag
  static const uint32_t WRITE_COMPLETED = 0x0200; // Write Completed FLag
  static const uint32_t ERROR_FLAG1 = 0x0400; // Error Flag 1
  static const uint32_t ERROR_FLAG2 = 0x0800; // Error Flag 2
  static const uint32_t BANK0_WRITEABLE = 0x1000; // WM Bank 0
  static const uint32_t BANK1_WRITEABLE = 0x2000; // WM Bank 1
  static const uint32_t BANK2_WRITEABLE = 0x4000; // WM Bank 2
  static const uint32_t BANK3_WRITEABLE = 0x8000; // WM Bank 3

  // CONTROL REG 1
  static const uint32_t BANK_EN =       0x000F; // enables all banks
  static const uint32_t BANK0_ENABLED = 0x0001; // enable bank 0
  static const uint32_t BANK1_ENABLED = 0x0002; // enable bank 1
  static const uint32_t BANK2_ENABLED = 0x0004; // enable bank 2
  static const uint32_t BANK3_ENABLED = 0x0008; // enable bank 3
  static const uint32_t ADDRESS_LENGTH_MASK = 0xF00000;
  static const uint32_t ADDR_BANK0 = 0x100000;
  static const uint32_t ADDR_BANK1 = 0x200000;
  static const uint32_t ADDR_BANK2 = 0x400000;
  static const uint32_t ADDR_BANK3 = 0x800000;
  static const uint32_t ADDRESS_LENGTH_SHIFT = 24;
  static const uint32_t DSEL_TIME = 0x0050; // Deselect time initial value
  static const uint32_t PRESCAL5 =      0x0500; // AHB_CK prescaling value
  static const uint32_t PRESCALA =      0x0A00; // AHB_CK prescaling value
  static const uint32_t SW_MODE =       0x10000000; // enables SW Mode
  static const uint32_t WB_MODE =       0x20000000; // Write Burst Mode
  static const uint32_t FAST_MODE =     0x00008000; // Fast Mode

  // CONTROL REG 2
  static const uint32_t RD_STATUS_REG = 0x00000400; // reads status reg
  static const uint32_t WRITE_FLAG =    0x00000800; // Write Enable
  static const uint32_t BANK0_SEL =     0x00000000; // Select Banck0
  static const uint32_t BANK1_SEL =     0x00001000; // Select Banck1
  static const uint32_t BANK2_SEL =     0x00002000; // Select Banck2
  static const uint32_t BANK3_SEL =     0x00003000; // Select Banck3
  static const uint32_t BANK_SEL_MASK =      0x00003000;
  static const uint32_t BANK_SEL_SHIFT =    12; // bits to shift to get bank selection
  static const uint32_t SEND =          0x00000080; // Send data
  static const uint32_t TX_LEN_1 =      0x00000001; // data length = 1 byte
  static const uint32_t TX_LEN_2 =      0x00000002; // data length = 2 byte
  static const uint32_t TX_LEN_3 =      0x00000003; // data length = 3 byte
  static const uint32_t TX_LEN_4 =      0x00000004; // data length = 4 byte
  static const uint32_t TX_LEN_MASK	 = 0x00000007;
  static const uint32_t RX_LEN_1 =      0x00000010; // data length = 1 byte
  static const uint32_t RX_LEN_2 =      0x00000020; // data length = 2 byte
  static const uint32_t RX_LEN_3 =      0x00000030; // data length = 3 byte
  static const uint32_t RX_LEN_4 =      0x00000040; // data length = 4 byte
  static const uint32_t RX_LEN_MASK = 0x00000070;
  static const uint32_t TFIE = 0x00000100; // Transmission Flag Interrupt Enable
  static const uint32_t WCIE = 0x00000200; // Write Complete Interrupt Enable

  // legal values
  static const uint32_t  SMI_WORD_LOWER_BOUND  = 0x00;
  static const uint32_t  SMI_WORD_UPPER_BOUND  = 0x10;
  // memory addresses of registers
  static const uint32_t  SMI_CONTROL1_OFFSET = 0x00;
  static const uint32_t  SMI_CONTROL2_OFFSET = 0x04;
  static const uint32_t  SMI_STATUS_OFFSET   = 0x08;
  static const uint32_t  SMI_TRANSMIT_OFFSET = 0x0C;
  static const uint32_t  SMI_RECEIVE_OFFSET  = 0x10;
  // bit masks
  static const uint32_t WRITE_MODE_MASK    = 0xF000;
  static const uint32_t ERROR1_MASK        = 0x800;
  static const uint32_t ERROR2_MASK        = 0x400;
  static const uint32_t WRITE_FLAG_MASK    = 0x200;
  static const uint32_t TRANSFER_FLAG_MASK = 0x100;
  static const uint32_t BANK_STATUS_MASK = 0xFF;

  RW_TargetPort rw_port;
  SerialFlash * banks[MAX_BANKS]; // can handle max 4 serial memory banks
  uint32_t control1; // control register
  uint32_t control2; // control register 2
  uint32_t status; // status register
  uint32_t transmit; // transmit to the flash
  uint32_t receive; //received from the flash

  SMICtrl(sc_core::sc_module_name name,
          SerialFlash * bank0, SerialFlash * bank1,
          SerialFlash * bank2, SerialFlash * bank3);
  ~SMICtrl();

  // TLM read writes
  uint32_t read_word(uint32_t addr);
  void write_word(uint32_t addr, uint32_t data);

   void trans_read_data(PayLoad &pl) {
     switch (pl.get_data_length()) {
     case 4: {
       uint32_t addr = pl.get_address();
       uint32_t data = read_word(addr);
       *(uint32_t*)(pl.get_data_ptr()) = data;
     } break;
     default:
       error() <<": read data method is not implemented for data_length = "
               <<pl.get_data_length() <<std::endl;
       exit(1);
     }
   };

  void trans_write_data(PayLoad &pl) {
    switch (pl.get_data_length()) {
    case 4: {
      uint32_t addr = pl.get_address();
      uint32_t data = *(uint32_t*)(pl.get_data_ptr());
      write_word(addr,data);
    } break;
    default:
      error() <<": write data method is not implemented for data_length = "
              <<pl.get_data_length() <<std::endl;
      exit(1);
    }
  };

  // other methods
  void end_of_elaboration(); // called by the SystemC kernel
  void ForwardWrite(const int bank_id,
                    const uint32_t addr, const uint32_t value);
  // called by serial memory

protected:
  // void Reset();
};

} // namespace simsoc

#endif //SMI
