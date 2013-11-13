//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

// This header file describes how a SimSoc simulated flash memory
// is stored on disk as a file between two sessions

#include <inttypes.h>
#include <fstream>

namespace simsoc {

const unsigned char NAND_FLASH_MAGIC[4] = { 'S', 'F', 'f', 's' };
const uint32_t NAND_FLASH_MAGIC_UI = 0x73664653;

const  int NAND_READ_ONLY = 0;
const  int NAND_WRITEABLE = 1;
const  int NAND_PAGE_DATA_SIZE = 512;
const  int NAND_SPARE_SIZE = 16;
const  int NAND_PAGE_HALF_DATA_SIZE = 256;
const  int NAND_PAGE_SIZE = NAND_PAGE_DATA_SIZE + NAND_SPARE_SIZE;
const  int NAND_PAGES_IN_BLOCK = 32;
const  int NAND_BLOCK_SIZE = NAND_PAGES_IN_BLOCK * NAND_PAGE_SIZE;
// Multiply the size in Megabits by 8 to obtain the number of blocks of 32 pages
const  int NAND_BLOCK_SHIFT = 3;
const  int NAND_PAGE_MASK = 0xFFFFFF00;

const  int NAND_MAJOR_VERSION = 1;
const  int NAND_MINOR_VERSION = 0;

const  int NAND_DEFAULT_FLASH_SIZE = 128; // smallest is 128 Megabits
const  int NAND_DEFAULT_NUM_BLOCKS = NAND_DEFAULT_FLASH_SIZE <<NAND_BLOCK_SHIFT;
const  int NAND_DEFAULT_WIDTH = 8;

// SimsoC Flash file simulation SFfs is reversed with opposite endianness
typedef enum {NAND_NO_VENDOR = 0, NAND_STMicro =0x20 } FlashVendor;
typedef enum {NO_VOLTAGE =0, S1V, S3V} Voltage;

typedef enum {
  NO_ID = 0,
  NAND_128MS_1V_8 =0x33, NAND_128MS_1V_16 =0x43,
  NAND_128MS_3V_8 =0x73, NAND_128MS_3V_16 =0x53,
  NAND_256MS_1V_8 =0x35, NAND_256MS_1V_16 =0x45,
  NAND_256MS_3V_8 =0x75, NAND_256MS_3V_16 =0x55,
  NAND_512MS_1V_8 =0x36, NAND_512MS_1V_16 =0x46,
  NAND_512MS_3V_8 =0x76, NAND_512MS_3V_16 =0x56,
  NAND_1GS_1V_8 =0x40, NAND_1GS_1V_16 =0x49,
  NAND_1GS_3V_8 =0x79, NAND_1GS_3V_16 =0x59
  /* TODO The large page devices
  512M
    NAND_512ML_1V_8		= 0xA2,
    NAND_512ML_1V_16	= 0xB2,
    NAND_512ML_3V_8		= 0xF2,
    NAND_512ML_3V_16	= 0xC2,
      1G
    NAND_1GL_1V_8		= 0xA1,
    NAND_1GL_1V_16		= 0xB1,
    NAND_1GL_3V_8		= 0xF1,
    NAND_1GL_3V_16		= 0xC1,
      2G
    NAND_2GL_1V_8		= 0xAA,
    NAND_2GL_3V_8		= 0xDA,
    NAND_2GL_1V_16		= 0xBA,
    NAND_2GL_3V_16		= 0xCA,
      4G
    NAND_4GL_1V_8		= 0xAC,
    NAND_4GL_3V_8		= 0xDC,
    NAND_4GL_1V_16		= 0xBC,
    NAND_4GL_3V_16		= 0xCC,
      8G
    NAND_8GL_1V_8		= 0xA3,
    NAND_8GL_3V_8		= 0xD3,
    NAND_8GL_1V_16		= 0xB3,
    NAND_8GL_3V_16		= 0xC3,
      8G
    NAND_16GL_1V_8		= 0xA5,
    NAND_16GL_3V_8		= 0xD5,
    NAND_16GL_1V_16		= 0xB5,
    NAND_16GL_3V_16		= 0xC5,
   */
} ST_code;

const uint8_t NAND_DEFAULT_VENDOR = NAND_STMicro;
const uint8_t NAND_DEFAULT_DEV_CODE = NAND_128MS_1V_8;

typedef struct nand_flash_ctrl {
  union {
    uint32_t magic_int;
    char magic_string[4];
  } magic;
  uint8_t  major_version; // SimSoC flash version major release
  uint8_t  minor_version; // SimSoc flash version minor release
  uint32_t mem_offset; // offset in file where the memory contents are stored
  uint32_t mem_size; // memory size in bytes
  uint32_t num_blocks; // number of blocks in the memory
  uint32_t block_size; // number of pages in block
  uint32_t width; // 8 or 16
  uint8_t  vendor_code; // manufacturer code like found in ST NAND flash
  uint8_t  dev_code;// device code like found in ST NAND flash
  uint8_t  protection; // read , write for now
} NAND_FlashControlBlock;

} // namespace simsoc
