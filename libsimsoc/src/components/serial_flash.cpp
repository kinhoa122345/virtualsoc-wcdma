//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

/*
 * TLM module implementing flash memory bank.
 * Implements behavior of ST Microelectronics flash memory
 * The bank should be connected to a Serial Memory Controller
 * This controller sets the hardware mode or software mode.
 * In hardware mode, memory words can be read or written directly.
 * Software mode must be used to re-program flash memory
 * Writes can only occur in hardware mode and when no other write
 * is in progress and no erase is in progress.
 * The serial memory controller that controls a memory bank
 * is discovered at end of elaboration.
 */

#include "display.hpp"
#include "serial_flash.hpp"
#include "st_smi.hpp"

using namespace std;
using namespace sc_core;

namespace simsoc {

// debug variables
static int trace_erase = 0;
static int trace_write32 = 0;
static int trace_read32 = 0;
static int trace_write8 = 0;
static int trace_read8 = 0;
static int TRACE8_MAX = 8;
static int TRACE32_MAX = 8;

  ParameterStrQueue SerialFlash::image_files("serial flash","-sf",
                                        "binary image for the Serial flash component");


// Debug function
void SerialFlash::ResetTrace()
{
  trace_write32 = 0;
  trace_read32 = 0;
  trace_write8 = 0;
  trace_read8 = 0;
  trace_erase = 0;
}

// open the flash file image persistent storage
// TODO. This is copy and paste of the NAND flash component
// Should be possible to have one function for the two modules...

void SerialFlash::OpenFlashPersistentStorage(const char * filename) {
  flash_file.open(filename, fstream::in| fstream::out | fstream::binary);
  if (flash_file.fail()) {
    error() <<"failed to open serial flash file: " << filename << endl;
    exit(1);
  }
  debug() << "Opened " << filename << endl;
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
    error() <<"failed to load serial flash file: " << filename <<endl;
    exit(1);
  }
  cb = (SerialFlashControlBlock *) file_image;
  info() << "endian is " << cb->magic.magic_string[0]<< endl;
  if (tolower(cb->magic.magic_string[0]) != tolower(SERIAL_FLASH_MAGIC[0])
      || tolower(cb->magic.magic_string[1]) != tolower(SERIAL_FLASH_MAGIC[1])
      || tolower(cb->magic.magic_string[2]) != tolower(SERIAL_FLASH_MAGIC[2])
      || tolower(cb->magic.magic_string[3]) != tolower(SERIAL_FLASH_MAGIC[3]))
    {
      error() << filename << " is not a serial flash file image..." <<endl;
      exit(1);
    }
  if ( cb->mem_size == 0
       || cb->mem_offset < sizeof(SerialFlashControlBlock)
       || ! (cb->width == 8 || cb->width == 16)
       || cb->sector_size != (unsigned int) SERIAL_SECTOR_SIZE
 // only supported size in version 1.0
       || size != cb->mem_offset + cb->mem_size
       || cb->num_sectors != cb->mem_size / cb->sector_size )
    {
      error() << "Serial flash file " << filename << " is corrupted...\n"
              << " memory size= " << (unsigned int) cb->mem_size  << " offset=" << (unsigned int) cb->mem_offset
              << " data width= " << (int) cb->width
              << " number of blocks=" << (unsigned int) cb->num_sectors
              << " block_size= " << (unsigned int) cb->sector_size << endl;
      exit(1);
    }

  info() << "Loaded serial flash image: " << filename
         << " ; width= "<<(int)cb->width
         << " ; man= "<<hex<<(int)cb->vendor_code
         << " ; dev= "<<hex<<(int)cb->dev_code
         << " ; sectors="<<dec<< cb->mem_size/(SERIAL_PAGE_SIZE*SERIAL_PAGES_IN_SECTOR)
         << " blocks" << endl;
}

SerialFlash::SerialFlash(sc_module_name name, const int bank_id):
  Module(name), my_bank_id(bank_id)
{
  char * addr;
  unsigned int i;
  controller = NULL;
  rw_port(*this);  // bind the target port

  const char *filename = image_files.front();
  image_files.pop_front();
  assert(filename);
  if (filename[0]=='\0') { // create a dummy temporary flash
    cb = new SerialFlashControlBlock;
    cb->num_sectors = SERIAL_DEFAULT_NUM_SECTORS;
    cb->vendor_code = SERIAL_DEFAULT_VENDOR;
    cb->dev_code = SERIAL_DEFAULT_DEV_CODE;
    cb->width = SERIAL_DEFAULT_WIDTH;
    cb->sector_size = SERIAL_SECTOR_SIZE;
    cb->major_version = SERIAL_MAJOR_VERSION;
    cb->minor_version = SERIAL_MINOR_VERSION;
    cb->magic.magic_int = *((uint32_t *)SERIAL_FLASH_MAGIC);
    cb->mem_size = cb->num_sectors*SERIAL_SECTOR_SIZE;
    // align offset
    cb->mem_offset = sizeof(SerialFlashControlBlock);
    // create temporary memory initialized to 0xFF
    file_image = new char[ cb->mem_offset + cb->mem_size];
    memset((char *)file_image+cb->mem_offset, 0xFF, cb->mem_size);
    info() << "No serial flash provided. Creates dummy. Size="
           << dec << (cb->mem_size >> 20) << " Mega bytes. "
           << " Contents will not be saved on disk..." << endl;
}
  else
    OpenFlashPersistentStorage(filename);
  // At this point file_image must be correctly initialized
  // memory is the start address where the flash memory contents are stored
  // memory is hence an array of size mem_size bytes
  // It is included inside file_image and starts at offset mem_offset
  addr = file_image + cb->mem_offset;
  memory =  (uint32_t *) addr ;
  /* DEBUG: check if serial memory is empty to avoid boot failure */
  for (i = 0; i < cb->mem_size ; i++)
    if ((unsigned char) *addr++ != 0xFF)
      break;
  if (i == cb->mem_size)
    info() << "Flash file contains no data!!" << endl;
  else
    info() << "Memory is 0xff until " <<hex << i << endl ;
}

SerialFlash::~SerialFlash() {
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

/*
 * This function is called at end of elaboration when the Serial Memory Controller
 * that controls this bank is establishing connection.
 */

void  SerialFlash::SetController(SMICtrl * my_controller ) {
  controller = my_controller;
}

/*
 * Read manufacturer code
 */
uint32_t SerialFlash::ReadId(uint32_t *ret_val) {
  *ret_val = ((cb->dev_code<<16) & 0xFF0000) | (cb->dev_code & 0xFF00)
    | cb->vendor_code ;
  return status;
}

uint8_t SerialFlash::ReadStatus() {
  return status;
}

/*
 * One byte is read/written
 */
uint8_t SerialFlash::read_byte(uint32_t addr) {
  char * byte_memory = (char *) memory;
  if (addr > cb->mem_size) {
    warning() << "Read address out of serial memory bank\n";
    return 0;
  }
  //  debug() << "Serial memory read byte at " << hex<<addr;
  if (trace_read8++ < TRACE8_MAX) {
    int sector = addr / SERIAL_SECTOR_SIZE;
    int offset = addr - (sector * SERIAL_SECTOR_SIZE);
    debug() << " is sector " << dec<<sector << " byte offset " << offset
            << " value " << hex<<(int) byte_memory[addr] << endl;
  }
  return byte_memory[addr];
}

/*
 * One word
 */

uint32_t SerialFlash::read_word(uint32_t addr) {
  unsigned int index = addr >> 2; // address in bytes, convert to int32
  if (addr > cb->mem_size) {
    error() << "Read address out of serial memory bank\n";
    return 0;
  }
  if (trace_read32++ < TRACE32_MAX) {
    debug() << "Serial memory read word at " << hex<<addr;
    int sector = addr / SERIAL_SECTOR_SIZE;
    int offset = addr - (sector * SERIAL_SECTOR_SIZE);
    debug() << " is sector " << dec<<sector << " byte offset " << offset
            << " value " << hex<< memory[index] << endl;
  }
  return memory[index];
}

void SerialFlash::write_word(uint32_t addr, uint32_t d) {
  if (addr > cb->mem_size) {
    warning() << "Read address out of serial memory bank\n";
    return;
  }
  controller->ForwardWrite(my_bank_id, addr, d);
}

/*
 * Function called from the SMI controller to transmit a read command to
 * the bank
 */

uint8_t SerialFlash::DoWrite(const uint32_t addr, const uint32_t value) {
  unsigned int index = addr >> 2; // adndress in bytes, convert to int32
  if (status &  WRITE_ENABLED) {
    memory[index] = value;
    if (trace_write32++ < TRACE32_MAX) {
      int sector = addr / SERIAL_SECTOR_SIZE;
      int offset = addr - (sector * SERIAL_SECTOR_SIZE);
      debug() << "Serial memory write word at " << hex<<addr
         << " is sector " << dec<<sector << " byte offset " << offset
         << " value " << hex << memory[index] << endl;
    }
  }
  else {
    error() << "Try to write in serial memory but write is not enabled\n";
  }
  return status;
}


/*
 * Function called from the SMI controller to set write mode
 *
 */

uint8_t SerialFlash::SetWriteMode(const bool on_off) {
  debug() << "Setting the write enable bit" << endl;
  if (on_off)
    status |= WRITE_ENABLED;
  else
    status &= ~WRITE_ENABLED;
  return status;
}

/*
 * Function called from the SMI controller to do a page erase to
 * the bank. This function should not be called because the ST driver
 * does not implement page write...
 */

uint8_t SerialFlash::DoPageProgram(const uint32_t addr) {
  if ((status &  WRITE_ENABLED) == 0) {
    error() << "Trying to write page but write is disabled\n";
    return status;
  }
  int page = addr / SERIAL_PAGE_SIZE;
  int offset = addr - (page * SERIAL_PAGE_SIZE);
  if (offset != 0) {
    warning() << "Serial Memory page write is not aligned on page address \n";
    return status;
  }
  warning() << "Page Write not yet implemented\n";
  return status;
}

/*
 * Function called from the SMI controller to transmit a erase command to
 * the bank
 */

uint8_t SerialFlash::DoSectorErase(const uint32_t addr) {
  /* the specs from ST says it is a 3 byte address but the ST driver
     is passing a 1 byte sector id .... *
  debug() << "Erasing sector at address : " << addr << endl;
  if (trace_erase++ < TRACE32_MAX) {
    int sector = addr / SERIAL_SECTOR_SIZE;
    int offset = addr - (sector * SERIAL_SECTOR_SIZE);
    if (offset != 0) {
      error() << "ERROR : Erase address is not a sector address\n";
    }
    else { */

  /* debug() << "Erase sector " << dec<<(int) addr << endl;
  char * sector_addr = (char *) memory; // memset works on bytes
  sector_addr += addr << SERIAL_SECTOR_SHIFT; // in bytes
  memset(sector_addr, SERIAL_SECTOR_SIZE, 0xff);
  */

  if ((status &  WRITE_ENABLED) == 0) {
    error() << "Trying to erase sector but write is disabled\n";
    return status;
  }
  int index = addr <<  (SERIAL_SECTOR_SHIFT - 2) ; // SERIAL_SECTOR_SHIFT in words
  int size =  SERIAL_SECTOR_SIZE >> 2;
  debug() << "Erase sector " << dec<<addr << " from " << dec<<index << " on " << size << " words." << endl;
  // write 32 bits words
  // is it faster than memset ?
  for (int i=0 ; i < size ; ++i) {
    memory[index++] = 0xFFFFFFFF;
  }
  return status;
}

/*
 * Function called from the SMI controller to erase entirely the bank
 */

uint8_t SerialFlash::DoBulkErase() {
  debug() << "Erasing complete serial memory bank" << endl;
  memset(memory, cb->mem_size, 0xFF);
  return status;
}

} // namespace simsoc
