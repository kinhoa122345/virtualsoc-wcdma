//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

// This header file describes how a SimSoc simulated flash memory
// is stored on disk as a file between two sessions

#include <inttypes.h>
#include <fstream>

namespace simsoc {

  const unsigned char SERIAL_FLASH_MAGIC[4] = { 'S', 'F', 's', '0' };
  const uint32_t SERIAL_FLASH_MAGIC_UI = 0x30734653;

  const  int SERIAL_READ_ONLY = 0;
  const  int SERIAL_WRITEABLE = 1;
  const  int SERIAL_PAGE_DATA_SIZE = 256;
  const  int SERIAL_PAGE_SIZE = SERIAL_PAGE_DATA_SIZE;
  const  int SERIAL_PAGES_IN_SECTOR = 256;
  const  int SERIAL_SECTOR_SIZE = SERIAL_PAGES_IN_SECTOR * SERIAL_PAGE_SIZE;
  const int SERIAL_SECTOR_SHIFT = 16; // 64 k blocks, shift 16 bits

  const  int SERIAL_MAJOR_VERSION = 1;
  const  int SERIAL_MINOR_VERSION = 0;

  const  int SERIAL_DEFAULT_FLASH_SIZE = 64; // smallest is 8 Megabytes
  const  int SERIAL_DEFAULT_NUM_SECTORS = 128; // 128 blocks of 64K bytes
  const  int SERIAL_DEFAULT_WIDTH = 8;

  // SimsoC Serial Flash file simulation know vendors

  typedef enum {SERIAL_NO_VENDOR = 0, SERIAL_STMicro =0x20 } SerialFlashVendor;

  typedef enum {
    SERIAL_NO_ID = 0,
    M25P64 = 0x2017
  } ST_SerialFlashModel;

  const uint8_t SERIAL_DEFAULT_VENDOR = SERIAL_STMicro;
  const uint16_t SERIAL_DEFAULT_DEV_CODE = M25P64;

  typedef struct _flash_ctrl {
    union {
      uint32_t magic_int;
      char magic_string[4];
    } magic;
    uint8_t  major_version; // SimSoC serial flash version major release
    uint8_t  minor_version; // SimSoc serial flash version minor release
    uint8_t  reserved;
    uint8_t  vendor_code; // manufacturer code like found in ST serial flash
    uint32_t dev_code;// device code like found in ST serial flash
    uint32_t mem_offset; // offset in file where the memory contents are stored
    uint32_t mem_size; // memory size in bytes
    uint32_t num_sectors; // number of sectors in the memory
    uint32_t sector_size; // in bytes
    uint32_t width; // 8 or 16
  } SerialFlashControlBlock;

} // namespace simsoc
