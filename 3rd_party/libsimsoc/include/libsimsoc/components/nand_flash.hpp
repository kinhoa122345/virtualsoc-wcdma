//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef NAND_FLASH_HPP
#define NAND_FLASH_HPP

/*
 * TLM Model for ST Microelectronics Flash Memory NAND 128/256/512 R/W
 * In the SPEAR SoC the nand flash controller is linked to the
 * Flexible Static Memory Controller FSMC to transmit ECC code
 * Please read ST NAND Flash datasheet for complete information
 */

#include <libsimsoc/context.hpp>
#include "nand_flash_cb.hpp"
#include "libsimsoc/interfaces/tlm.hpp"
#include "libsimsoc/module.hpp"

namespace simsoc {

  class NAND_Flash: public Module,
                    public RW_Target {

    typedef enum { SetPointerLow = 0x0, SetPointerHigh = 0x1, ConfirmWrite = 0x10,
                   SetPointerSpare = 0x50, BlockErase = 0x60, ReadStatus = 0x70,
                   ProgramPage = 0x80, CopyPage = 0x8A,
                   ConfirmErase = 0xD0, ReadSignature = 0x90, Reset = 0xFF
    } Command;

    static ParameterStrQueue image_files;

    // the modes of the state machine
    typedef enum {Idle, Read, Write, Erase, Copy, Signature } Mode;

    // status command override temporarily the mode

    typedef enum  { NotReady = 0, Ready } StatusReady;

    // addressing

    typedef enum  { None = 0, Start, InProgress, Done } Addressing;


    // Flash Zone. ST refers to this as Areas A, B and C
    typedef enum {Low, High, Spare } Zone;

    // Satus register bits
    static const int STATUS_WRITE_PROTECTION = 0x80;
    static const int STATUS_READY = 0x40;
    static const int STATUS_ERROR = 0x01;
    static const int STATUS_BUSY = 0x00;


    // register address
    static const unsigned int WRITE_DATA = 0x0; // Write Data Address
    static const unsigned int READ_DATA = WRITE_DATA;
    static const unsigned int WRITE_ALE = 0x20000; // Address Latch Enable: ALE
    static const unsigned int WRITE_CLE = 0x10000; // Command Latch Enable : CLE
    static const unsigned int WRITE_ATT_BANK0 = 0xA0000; // Attribute command

    static const unsigned int BLOCK_MASK = 0xffff4000; // block mask for page id. block = 16K
    static const unsigned int PAGE_MASK = 0xfffffe00;
    static const unsigned int SPARE_MASK = 0xfffffff0;
    static const unsigned int SPARE_SHIFT = 4;
    static const unsigned int W8_PAGE_SHIFT = 9;
    static const unsigned int W16_PAGE_SHIFT = 8;

    bool big_endian; // if used in a word-invariant big-endian system, then the addresses must be fixed.

    NAND_FlashControlBlock *cb; // to control flash file data
    std::fstream flash_file;
    char * file_image;
    char * memory; // pointer to memory where contents is stored
    //FSMC & my_fsmc; // reference to connected FSMC // FSMC not distributed due to copyright
    int my_fsmc_id; // to store the ECC in the corresponding register
    uint32_t input_address; // the address written on the controller
    uint32_t target_address; // the effective address computed from input
    int32_t source_page; // contains the source address on copy operation
    int32_t page_id; // page address in pages of 512 bytes
    int32_t page_offset; // the offset inside page
    int32_t attribute0; // mystery necessary to boot
    StatusReady readiness;
    Addressing addressing;
    Mode mode; // the current mode
    Mode previous_mode ; //before read status
    Zone zone; // the current zone
    unsigned char byte_count; // how many bytes in the address have been written
    unsigned char status; // status register
    unsigned char signature_access;
    unsigned char address_shift;
    bool overflow;

  public:
    RW_TargetPort rw_port;

    // Size and uint32_tes are given in byte.
    NAND_Flash(sc_core::sc_module_name name, int id, bool big_endian=false);
    ~NAND_Flash();

    uint8_t read_byte(uint32_t addr);
    void write_byte(uint32_t addr, uint8_t data);

    void trans_read_data(PayLoad &pl)
    {
      switch (pl.get_data_length()) {
      case 1: {
        const uint32_t addr = big_endian? pl.get_address()^3: pl.get_address();
        const uint8_t data = read_byte(addr);
        *(pl.get_data_ptr()) = data;
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
      case 1: {
        const uint32_t addr = big_endian? pl.get_address()^3: pl.get_address();
        const uint8_t data = *(pl.get_data_ptr());
        write_byte(addr,data);
      } break;
      default:
        error()<<": write method is not implemented for data_length = "
               <<pl.get_data_length() <<std::endl;
        exit(1);
      }
    };
    //  void dump(uint32_t start, uint32_t length = (1<<addr_shift), std::ostream& os = std::cout);
  protected:
    void OpenFlashPersistentStorage(const char * filename);
    void ResetAll();
    void ResetAddress(); // to reset address variables
    // to execute command receveived on the command address
    void DoCommand(const Command cmd);
    // set the address received with successive bytes
    void SetAddress(const uint8_t byte);
    // validate the address received
    uint32_t ValidateAddress();
    void ComputeECC(int pid);
    // debug function to trace reads and writes
    void TraceReadWrite(bool mode);
  };

} // namespace simsoc

#endif //NAND_FLASH_HPP
