//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef SPEAR_SERIAL_FLASH_HPP
#define SPEAR_SERIAL_FLASH_HPP
/*
 * TLM Model for Serial Flash Memory.
 * The memory can be accessed directly or
 * through the Serial Memory Interface SMI controller model ST M25P64
 * When a write is performed directly, the call is transferred to the controller.
 */

#include <libsimsoc/context.hpp>
#include <libsimsoc/interfaces/tlm.hpp>
#include <libsimsoc/module.hpp>
#include "serial_flash_cb.hpp"

/*
 * Values of the status register
 */

namespace simsoc {

  const unsigned int WORK_IN_PROGRESS = 0x1;
  const unsigned int WRITE_ENABLED = 0x1<<1;
  const unsigned int PROTECT1 = 0x1<<2;
  const unsigned int PROTECT2 = 0x1<<3;
  const unsigned int PROTECT3 = 0x1<<4;
  const unsigned int SR_WRITE_PROTECT = 0x1<<7;

  typedef enum {WRITE_DISABLE = 0x4, WRITE_ENABLE=0x6,
                READ_ID=0x9f,
                READ_STATUS = 0x5, WRITE_STATUS= 0x1,
                READ_DATA = 0x3, FAST_READ = 0xB,
                PAGE_PROGRAM = 0x2, SECTOR_ERASE = 0xD8,
                BULK_ERASE=0xC7,
                READ_SIGNATURE = 0xAB,

  } SerialCommand;

  /*
   * The Serial Flash class.
   * There is one instance of this class for each memory bank
   */
  class SMICtrl; // forward declaration

  class SerialFlash: public Module,
                     public RW_Target {

  public:

    static ParameterStrQueue image_files;

    RW_TargetPort rw_port;

    SerialFlash(sc_core::sc_module_name name, const int bank_id);
    ~SerialFlash();

    // TLM read writes
    uint32_t read_word(uint32_t addr);
    void write_word(uint32_t addr, uint32_t data);
    uint8_t read_byte(uint32_t addr);

    void trans_read_data(PayLoad &pl)
    {
      switch (pl.get_data_length()) {
      case 1: {
        uint32_t addr = pl.get_address();
        uint8_t data = read_byte(addr);
        *(pl.get_data_ptr()) = data;
      } break;
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

    void trans_write_data(PayLoad &pl)
    {
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

    // direct access functions from the SMI
    // connects to the serial memory cotroller that controls this bank
    void SetController(SMICtrl * my_controller);

    uint32_t ReadId(uint32_t *ret_val); // returns the serial flash id

    // read status register
    // called by the controller to write in memory, returns the status register
    uint8_t ReadStatus();

    //set write mode, returns the status register
    uint8_t SetWriteMode(const bool on_off);

    // write value to memory, returns the status register
    uint8_t DoWrite(const uint32_t addr, const uint32_t value);

    // called by the controller to erase page, returns the status register
    uint8_t DoPageProgram(const uint32_t addr);

    // called by the controller to erase sector, returns the status register
    uint8_t DoSectorErase(const uint32_t sector);

    // called by the controller to erase all bank, returns the status register
    uint8_t DoBulkErase();


    //debug function to reset trace counters
    void ResetTrace();

  protected:
    typedef enum {Idle =0, Read = 1, Write = 2} SerialState;

    SerialFlashControlBlock *cb; // to control flash file data
    int my_bank_id;
    SMICtrl * controller;
    std::fstream flash_file;
    char * file_image;
    uint32_t * memory; // pointer to memory where contents is stored
    // uint32_t * memory_size_in_bytes; // size
    uint32_t input_address; // the address written on the controller
    uint32_t target_address; // the effective address computed from input
    uint8_t status; // status register
    //  SerialState mode; // current state
    bool protection; // protection activated
    void TraceReadWrite(uint32_t addr, bool rw);
    void OpenFlashPersistentStorage(const char * filename) ;

    // void Reset();
  };

} // namespace simsoc

#endif //Serial Flash
