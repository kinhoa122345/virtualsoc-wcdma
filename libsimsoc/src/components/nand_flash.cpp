//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "nand_flash.hpp"
#include "display.hpp"

using namespace std;
using namespace sc_core;

namespace simsoc {

  // debug variables
  static int trace_erase = 0;
  static int trace_write = 0;
  static int trace_copy = 0;
  static int trace_spare = 0;
  static int trace_low = 1;
  static int trace_high = 0;
  static const int TRACE_RW_MAX = 0;
  static const int TRACE_COPY_MAX = 8;
  static int num_errors = 0;

  ParameterStrQueue NAND_Flash::image_files("NAND flash","-nf",
                                            "binary image for the NAND flash component");

  // Debug function
  void NAND_Flash::TraceReadWrite(bool traceread)
  {
    if ((zone == Spare && trace_spare++ < TRACE_RW_MAX)
        || (zone == Low && trace_low++ < TRACE_RW_MAX)
        || (zone == High && trace_high++ < TRACE_RW_MAX))
      {
        int page = target_address / NAND_PAGE_SIZE;
        int offset = target_address - (page*NAND_PAGE_SIZE);
        int num_block = page / NAND_PAGES_IN_BLOCK;
        int page_in_block = page - (num_block * NAND_PAGES_IN_BLOCK);
        debug() << ((traceread == true) ? "Read " : "Write ")
                << "zone " << ((zone == Low) ? "low" :
                               (zone == High) ? "high" : "spare")
                << " in block : " << dec << num_block
                << " page: " << dec << page_in_block
                << " page offset: " << dec << offset
                << "mem offset: " << dec << target_address
                <<  endl;
      }
  }
  // open the flash file image persistent storage

  void NAND_Flash::OpenFlashPersistentStorage(const char * filename) {
    flash_file.open(filename, fstream::in| fstream::out | fstream::binary);
    if (flash_file.fail()) {
      error() <<"failed to open flash file: " << filename << endl;
      exit(1);
    }
    debug() << "Opened NAND flash file" << filename << endl;
    // get size of file
    flash_file.seekg(0,ifstream::end);
    unsigned long size = flash_file.tellg();
    flash_file.seekg(0);

    file_image = new char[size];
    if ( file_image == NULL) {
      error()<< "Cannot allocate flash size: " <<size <<endl;
      exit(1);
    }
    flash_file.read(file_image, size);
    if (flash_file.fail()) {
      error() <<"failed to load flash file: " << filename <<endl;
      exit(1);
    }
    cb = (NAND_FlashControlBlock *) file_image;
    info() << "endian is " << cb->magic.magic_string[0]<< endl;
    if (tolower(cb->magic.magic_string[0]) != tolower(NAND_FLASH_MAGIC[0])
        || tolower(cb->magic.magic_string[1]) != tolower(NAND_FLASH_MAGIC[1])
        || tolower(cb->magic.magic_string[2]) != tolower(NAND_FLASH_MAGIC[2])
        || tolower(cb->magic.magic_string[3]) != tolower(NAND_FLASH_MAGIC[3]))
      {
        error() << filename << " is not a flash file image..." <<endl;
        exit(1);
      }
    if ( cb->mem_size == 0 || cb->mem_offset < sizeof(NAND_FlashControlBlock)
         || ! (cb->width == 8 || cb->width == 16)
         || cb->block_size != 32 // only supported size in version 1.0
         || size != cb->mem_offset + cb->mem_size
         || cb->num_blocks < 1024 ) // smallest value on ST flash
      {
        error() << "Flash file " << filename << " is corrupted...\n"
                << " memory size= " << (unsigned int) cb->mem_size  << " offset=" << (unsigned int) cb->mem_offset
                << " data width= " << (int) cb->width
                << " number of blocks=" << (unsigned int) cb->num_blocks
                << " block_size= " << (unsigned int) cb->block_size << endl;
        exit(1);
      }

    info() << "Loaded flash image: " << filename
           << " ; width= "<<(int)cb->width
           << " ; man= "<<hex<<(int)cb->vendor_code
           << " ; dev= "<<hex<<(int)cb->dev_code
           << " ; size="<<dec<< cb->mem_size/(NAND_PAGE_SIZE*NAND_PAGES_IN_BLOCK)
           << " blocks" << endl;
  }

  NAND_Flash::NAND_Flash(sc_module_name name,  int id, bool be):
    Module(name), big_endian(be),
    //my_fsmc(fsmc),
    my_fsmc_id(id)
  {
    rw_port(*this);  // bind the target port

    const char *filename = image_files.front();
    image_files.pop_front();
    assert(filename);
    if (filename[0]=='\0') { // create a dummy temporary flash
      cb = new NAND_FlashControlBlock;
      cb->num_blocks = NAND_DEFAULT_NUM_BLOCKS;
      cb->vendor_code = NAND_DEFAULT_VENDOR;
      cb->dev_code = NAND_DEFAULT_DEV_CODE;
      cb->width = NAND_DEFAULT_WIDTH;
      cb->block_size = NAND_PAGES_IN_BLOCK;
      cb->major_version = NAND_MAJOR_VERSION;
      cb->minor_version = NAND_MINOR_VERSION;
      cb->protection = NAND_WRITEABLE;
      cb->magic.magic_int = *((uint32_t *)NAND_FLASH_MAGIC);
      cb->mem_size = cb->num_blocks*NAND_BLOCK_SIZE;
      // align offset
      cb->mem_offset = sizeof(NAND_FlashControlBlock);
      // create temporary memory initialized to 0xFF
      file_image = new char[ cb->mem_offset + cb->mem_size];
      memset((char *)file_image+cb->mem_offset, 0xFF, cb->mem_size);  }
    else
      OpenFlashPersistentStorage(filename);
    // memory is the start address where the flash memory contents are stored
    // memory is hence an array of size mem_size
    // It is included inside file_image and starts at offset mem_offset
    memory =  file_image + cb->mem_offset ;
    char *addr = memory;
    unsigned int i;
    for (i = 0; i < cb->mem_size ; i++)
      if ((unsigned char) *addr++ != 0xFF)
        break;
    if (i == cb->mem_size)
      info() << "Flash file contains no data!!" << endl;
    else
      info() << "Memory is 0xff until " <<hex << i << endl ;

    // set the shift to 1 bit if the flash width is 8 bits.
    // See documentation about A8 address bit ignored...
    address_shift = ((int)(cb->width) == 8) ? 1:0;
    ResetAll();

  }

  NAND_Flash::~NAND_Flash() {
    int size = cb->mem_offset + cb->mem_size;
    if (flash_file.good() && flash_file.is_open()) {
      flash_file.seekg(0);
      flash_file.write(file_image, size);
      if (flash_file.fail()) {
        error() <<"failed to write flash file: " <<endl;
      }
      else {
        info() << "Flash file saved properly\n" ;
      }
    }
    delete[] file_image;
    debug() <<"Flash destructor called." <<endl;
  }

  // Function called when an address byte is written on ALE register
  // Each successive byte of the address starting with least significant
  // On smaller flash only 3 bytes are necessary

  // set the mode to idle and reset variables

  void NAND_Flash::ResetAddress() {
  }

  void NAND_Flash::ResetAll() {
    mode = Idle;
    zone = Low;
    page_offset = 0;
    page_id = 0;
    byte_count = 0;
    overflow = false;
    target_address = 0;
    readiness = NotReady;
    status = STATUS_READY;
    addressing = None;
  }

  /*
   * An address is sent with
   * first byte least significant address bits A0-A7
   * second byte is actually A9-A16 because A8 is set otherwise
   * but it is ignored for the moment, shift will be done later
   * third byte is A17-A25,
   * and fourth byte optional remaining bits only if necessary
   * for large flash
   * Except for Erase, where the first byte is not required.
   */
  void NAND_Flash::SetAddress(const uint8_t byte) {
    if (addressing == None) {
      error() << "receive address before command\n";
      exit(1);
    }
    else if (addressing == Start) {
      page_offset = 0;
      // page_id = 0;
      byte_count = 0;
      overflow = false;
      target_address = 0;
      readiness = NotReady;
      status = STATUS_READY;
      addressing = InProgress;
    }
    else if (addressing == Done){
      error() << "received too many address bytes\n";
      exit(1);
    }
    // else if in progress do nothing
    switch(byte_count) {
    case 0:
      // debug() << "1 address byte " << dec <<  (int) byte <<endl;
      input_address =  byte;
      byte_count = 1;
      break;
    case 1:
      // debug() << "2 address byte " << dec <<  (int) byte  <<endl;
      input_address |= byte << 8 ;
      byte_count = 2;
      break;
    case 2:
      // debug() << "3 address byte " << dec <<  (int) byte <<endl;
      input_address |= byte << 16 ;
      byte_count = 3;
      break;
    case 3:
      debug() << "4 address byte " << dec <<  (int) byte  <<endl;
      input_address |= byte << 24 ;
      byte_count = 4;
      addressing = Done;
      break;
    default:
      addressing = Done;
      debug() << "Ignored address byte " << dec <<  (int) byte_count
              << " mode " << mode   << " zone " << zone << endl; ;
    }
  }

  void  NAND_Flash::DoCommand(const Command cmd) {
    switch (cmd) {
    case Reset:
      ResetAll();
      break;

    case SetPointerLow:
      readiness = NotReady;
      addressing = Start;
      mode = Read;
      zone = Low;
      trace_low = 0;
      // debug() << "set zone low" << endl;
      break;

    case SetPointerHigh:
      readiness = NotReady;
      mode = Read;
      zone = High;
      addressing = Start;
      trace_high = 0;
      debug() << "set zone high" << endl;
      break;

    case SetPointerSpare:
      readiness = NotReady;
      mode = Read;
      zone = Spare;
      addressing = Start;
      debug() << "set zone spare " <<hex<< cmd << endl;
      trace_spare = 0;
      break;

    case ReadStatus:
      readiness = Ready;
      // debug() << "read status " << endl;
      break;

    case BlockErase:
      mode = Erase;
      debug() << "erase command"<< endl;
      addressing= Start;
      break;

    case ConfirmErase:
      if (mode != Erase) {
        error() <<"Confirm Erase but not in Erase mode!"<<endl;
        // ?? status = STATUS_ERROR;
      }
      else if (byte_count < 2 || (byte_count == 2 && cb->num_blocks > 4096)) {
        error() <<"Erase with incomplete address "<<endl;
        // ?? status = STATUS_ERROR;
      }
      else {
        // The protocol specifies the block address as multiple of
        // data size (no spare)
        // but we store the pages contiguously including spare size
        int block_number = (input_address << 9)
          / (NAND_PAGES_IN_BLOCK*NAND_PAGE_DATA_SIZE) ;
        target_address = block_number * NAND_BLOCK_SIZE;
        if (target_address > cb->mem_size) {
          error() << "try to erase block out of memory "
                  <<dec << target_address << endl;
        }
        memset((char *)memory + target_address, 0xff, NAND_BLOCK_SIZE);
        debug() << "erased input address: " << (input_address << 9)
                << " block: "  << block_number
                << " at: " << target_address << endl;
      }
      trace_erase = 0;
      status = STATUS_READY;
      mode = Idle;
      addressing = None;
      break;

    case ProgramPage:
      mode = Write;
      status = STATUS_READY;
      addressing = Start;
      trace_write = 0;
      debug() << "Page program command"<< endl;
      break;

    case CopyPage: // should be called after the from address has been specified
      if (byte_count < 3 || (byte_count == 3 && cb->num_blocks > 4096)) {
        error() << "Copy command received with incomplete address" << endl;
        mode = Idle;
      }
      else {
        mode = Copy;
        page_id = input_address >> 8;
        status = STATUS_READY;
      }
      debug() << "Copy Page command"<< endl;
      // be ready for the copy to address
      addressing = Start;
      break;

    case ConfirmWrite:
      if (mode == Write) {
        debug() << "Confirm write " << endl;
        status = STATUS_READY;
      }
      else if (mode == Copy) {
        // page_id contains the source page
        // input_address contains the destination address
        unsigned long src_addr, dst_addr;
        unsigned long dst_page; // absolute page id
        int from_block, to_block;
        int from_page, to_page; // page index within the block

        // debug() << "Copying page\n";
        // page_id at this point contains the source page
        src_addr = page_id * NAND_PAGE_SIZE;
        from_block = page_id / NAND_PAGES_IN_BLOCK;
        from_page = page_id - (from_block * NAND_PAGES_IN_BLOCK);
        dst_page = input_address >> 8;
        to_block = dst_page / NAND_PAGES_IN_BLOCK;
        to_page = dst_page - (to_block * NAND_PAGES_IN_BLOCK);
        if (++trace_copy < TRACE_COPY_MAX) {
          debug() << "Copying from block " << dec<<from_block
                  << " page " << dec<<from_page
                  << " to block "<< dec << to_block
                  << " page " << dec << to_page
                  << ". From absolute page " << page_id
                  << " to absolute page " << dst_page << endl;
        }
        dst_addr = dst_page * NAND_PAGE_SIZE;
        if (dst_addr > cb->mem_size || src_addr > cb->mem_size ) {
          warning() << "Attempt to copy out of memory" << endl;
        }
        memcpy(((char *)memory)+dst_addr, ((char *)memory)+src_addr, NAND_PAGE_SIZE);
        debug() << "Copied page "<< page_id <<" to " << dst_page << endl;
        status = STATUS_READY;
      } // end mode == copy
      else {
        status = STATUS_ERROR;
        error() << "Received invalid Confirm Write"
                << endl;
      }
      mode = Idle;
      zone = Low;
      addressing = None;
      break;

    case ReadSignature:
      debug() << "reading signature " << endl;
      mode = Signature;
      signature_access = 0;
      addressing = Start;
      break;

    default:
      error() << "unspecified command " <<hex<<cmd << endl;
      ResetAll();
      exit(1);
    }
  }

  /*
   * Compute the destination address for reads and writes
   * If target_address is NULL, the input address has been sent before the command
   * and the effective address must be computed
   * The effective address must remain within the same page.
   * So we keep the page_id constant.
   * Return 0 on error, else 1, with side effect to modify target_address
   */

  uint32_t NAND_Flash::ValidateAddress() {

    if (byte_count < 3 || (byte_count == 3 && cb->num_blocks > 4096)) {
      if (++num_errors < TRACE_RW_MAX)
        warning() << "Read/Write received with incomplete address"
                  << (int) byte_count << endl;
      mode = Idle;
      return false;
    }
    if (overflow) {
      error() << "Overflow in page access " << page_id << endl;
      halt();
      return false;
    }
    if (target_address == 0) {
      page_id = input_address >> 8;
      switch(zone) {
      case Low:
        page_offset = input_address & 0xFF;
        break;

      case High:
        page_offset = (input_address & 0xFF) + NAND_PAGE_HALF_DATA_SIZE  ;
        break;

      case Spare:
        page_offset = (input_address & 0xF) + NAND_PAGE_DATA_SIZE  ;
        break;

      default: UNREACHABLE ; // should not happen
      }
    }
    target_address = (page_id * NAND_PAGE_SIZE) + page_offset;
    if (zone == Spare && trace_spare++ < NAND_SPARE_SIZE)
      {
        int num_block;
        int page_in_block;
        num_block = page_id / NAND_PAGES_IN_BLOCK;
        page_in_block = page_id - (num_block * NAND_PAGES_IN_BLOCK);
        debug() << "Reading spare : " << dec << input_address
                << " block : "<< dec << num_block
                << " page: " << dec<<page_in_block
                << " offset in page: " << dec<<page_offset
                << " offset in file: " << dec << target_address + cb->mem_offset
                << endl;
      }

    if (target_address > cb->mem_size ) {
      error() << "Try to access data over memory size" << endl;
      exit(1);
      return false;
    }
    if (++page_offset >= NAND_PAGE_SIZE) {
      debug() << "Will overflow next read in page " << page_id << endl;
      overflow = true;
    }
    return true;
  }

  /*
   * One byte is read. Check first that it is legal register address.
   * The same address is actually used to read several registers
   * corresponding to current mode. Return register corresponding to mode.
   * In standard Read mode, the address is the current address
   * held in variable target_adress. On the first read (after a read command,)
   * this variable must be initialized,
   * It is incremented by 1 after the read.
   * The spec is unclear about overflow
   */
  uint8_t NAND_Flash::read_byte(uint32_t addr) {
    if (addr != READ_DATA) {
      warning() << "Invalid register read ??" << endl;
      // ?? ST spec unclear status = STATUS_ERROR;
      return 0;
    }
    if (readiness == Ready) {
      // debug() << "NAND Flash status read " <<hex<<(int)status << endl ;
      return status;
      status = STATUS_READY;
    }
    else if (mode == Signature) {
      if (signature_access == 0) {
        debug() << "read vendor id "<<hex<<cb->vendor_code << endl ;
        ++signature_access;
        return cb->vendor_code;
      }
      else if (signature_access == 1){
        debug() << "read device code "<<hex<<cb->dev_code << endl ;
        ++signature_access;
        return cb->dev_code;
      } else {
        warning()<< "useless signature access "<< byte_count << endl ;
        // after 2 reads ST specs says ignore
        return 0;
      }
    } else if (mode != Read) {
      error() << "read attempt before read command" << mode << endl ;
      exit(1);
      status = STATUS_ERROR;
      return 0;
    }
    // Must be in data read mode. return value at effective address
    if (ValidateAddress()) {
      TraceReadWrite(true);
      return memory[target_address];
    } else {
      warning() << "Bad address value "<< 0  << " read from flash\n";
      return 0;
    }
  }
  /*
   * TODO: Compute the error correction code on writes
   */

  void  NAND_Flash::ComputeECC(int pid)
  {
    uint32_t code = 1;
    // my_fsmc.set_ecc(my_fsmc_id, code); FSMC not distributed due to copyright
  }

  void NAND_Flash::write_byte(uint32_t addr, uint8_t d) {

    switch(addr) {
    case WRITE_DATA:
      if (cb->protection != NAND_WRITEABLE) {
        warning() << "Attempt to write in protected memory\n" << endl;
        status = STATUS_ERROR;
      } else if ( mode != Write) {
        error() << "illegal write in mode:" << (int) mode << endl;
        exit(1);
        status = STATUS_ERROR;
        return;
      }
      if (ValidateAddress()) {
        TraceReadWrite(false);
        memory[target_address] = d;
        status = STATUS_READY;
      }
      else
        status = STATUS_ERROR;
      break;

    case WRITE_ALE:
      if (mode == Idle) {
        warning() << "Should not set address before any command\n" << endl;
      }
      else
        SetAddress(d);
      break;
    case WRITE_CLE:
      // debug() << "Command received " << hex << (uint32_t) d << endl;
      DoCommand((Command) d);
      break;

    case WRITE_ATT_BANK0:
      warning() << "Writing undocumented attribute bank 0 \n" << endl;
      attribute0 = d;
      break;


    default:
      error() << "Invalid flash memory write byte at address " << hex << addr
              << " value " << dec << d << endl;
      exit(1);
    }
  }

} // namespace simsoc
