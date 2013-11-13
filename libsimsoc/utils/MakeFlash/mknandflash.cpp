//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include <inttypes.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include "libsimsoc/components/nand_flash_cb.hpp"

using namespace std;
using namespace simsoc;

void Usage(bool error) {
  cout << "Usage: make_flash [options] file" <<endl;
  cout << "Options are: -s [128|256|512\1024] -w [8|16] -p [r|w] -vc vendor_code -dc dev_code -bf bootfile -bb block -bp page -vt voltage -a "
       << endl;
  cout << "Option -a to add a new boot file to an existing flash file  "
       << endl;
  cout << "Usage: make_flash --v for version" <<endl;
  if (error)
    cout << "No flash image created" << endl;
}

uint8_t set_ST_dev_code(unsigned int size, Voltage supply,
                        uint8_t w) {
  ST_code code=NO_ID;

  switch(size) {

  case 128:
    switch(supply) {
    case NO_VOLTAGE:
      return 0;

    case S1V :
      code = (w == 8) ? NAND_128MS_1V_8 : NAND_128MS_1V_16;
      break;
    case S3V :
      code = (w == 8) ? NAND_128MS_3V_8 : NAND_128MS_3V_16;
      break ;
    }
    break;

  case 256:
    switch(supply) {
    case NO_VOLTAGE:
      return 0;

    case S1V :
      code = (w == 8) ? NAND_256MS_1V_8 : NAND_256MS_1V_16;
      break;
    case S3V :
      code = (w == 8) ? NAND_256MS_3V_8 : NAND_256MS_3V_16;
      break ;
    }
    break;

  case 512:
    switch(supply) {
    case NO_VOLTAGE:
      return 0;

    case S1V :
      code = (w == 8) ? NAND_512MS_1V_8 : NAND_512MS_1V_16;
      break;
    case S3V :
      code = (w == 8) ? NAND_512MS_3V_8 : NAND_512MS_3V_16;
      break ;
    }
    break;

  case 1024:
    switch(supply) {
    case NO_VOLTAGE:
      return 0;

    case S1V :
      code = (w == 8) ? NAND_1GS_1V_8 : NAND_1GS_1V_16;
      break;
    case S3V :
      code = (w == 8) ? NAND_1GS_3V_8 : NAND_1GS_3V_16;
      break ;

    }
    break;
    /* TO DO support small and large pages

  case 2048:
    switch(supply) {
    case NO_VOLTAGE:
    return 0;

    case 1V :
      code = (w == 8) ? NAND_8 : NAND_16;
      break;
    case :
      code = (w == 8) ? NAND_8 : NAND_16;
      break ;
    case 1VDDP :
      code = (w == 8) ? NAND_8 : NAND_16;
      break;
    case 3VDDP :
      code = (w == 8) ? NAND_8 : NAND_16;
      break;
    }
    break;
  case 4096:
    switch(supply) {
    case NO_VOLTAGE:
    return 0;

    case 1V :
      code = (w == 8) ? NAND_8 : NAND_16;
      break;
    case S3V :
      code = (w == 8) ? NAND_8 : NAND_16;
      break ;
    case 1VDDP :
      code = (w == 8) ? NAND_8 : NAND_16;
      break;
    case 3VDDP :
      code = (w == 8) ? NAND_8 : NAND_16;
      break;
    }
    break;
    */

  default:
    cout << "ST flash model not supported \n";
    exit(1);
  }
  return (uint8_t) code;
}


string HandleFileSuffix(const char * name) {
  const char SUFFIX[] = ".sffs";
  string file_name(name);

  if (file_name.rfind(SUFFIX, file_name.size() ) == string::npos ) {
    file_name.append(SUFFIX);
  } else {
    // cout << "suffix is ok\n";
  }
  return file_name;
}

int OpenFlashFile(char * name, char ** ret_file_image, fstream * flash_file,
                  unsigned int * ret_file_size)
// ret_file_image is address of the file image to be returned
{
  char *file_image = NULL;
  NAND_FlashControlBlock * cb;
  unsigned int file_size;
  string filename = HandleFileSuffix(name);

  flash_file->open(filename.data(), fstream::in| fstream::out | fstream::binary);
  if (flash_file->fail()) { // try with suffix added
    cout <<"Failed to open flash file: " << filename << endl;
    return 0;
  }
  // get size of file
  flash_file->seekg(0,ifstream::end);
  file_size = flash_file->tellg();
  flash_file->seekg(0);
  file_image = new char[file_size];
  if ( file_image == NULL) {
    cout << "Cannot allocate flash size: " << file_size <<endl;
    return 0;
  }
  flash_file->read(file_image, file_size);
  if (flash_file->fail()) {
    cout <<"Failed to load flash file: " << filename <<endl;
    delete[] file_image;
    return 0;
  }
  cout << "loaded file " << filename << " size " << file_size << " bytes " << endl;
  cb = (NAND_FlashControlBlock *) file_image;
  if (tolower(cb->magic.magic_string[0]) != tolower(NAND_FLASH_MAGIC[0])
      || tolower(cb->magic.magic_string[1]) != tolower(NAND_FLASH_MAGIC[1])
      || tolower(cb->magic.magic_string[2]) != tolower(NAND_FLASH_MAGIC[2])
      || tolower(cb->magic.magic_string[3]) != tolower(NAND_FLASH_MAGIC[3]))
    {
      cout << "Error : " << filename << " is not a valid flash file image! "
           << cb->magic.magic_string[0] <<  cb->magic.magic_string[1]
           << cb->magic.magic_string[2] <<  cb->magic.magic_string[3]
           << endl;
      delete[] file_image;
      return 0;
    }
  if ( cb->mem_size == 0 || cb->mem_offset < sizeof(NAND_FlashControlBlock)
       || ! (cb->width == 8 || cb->width == 16)
       || cb->block_size != 32 // only supported size in version 1.0
       || file_size != cb->mem_offset + cb->mem_size
       || cb->num_blocks < 1024 ) // smallest value on ST flash
    {
      cout << "Flash file " << filename << " is corrupted...\n"
           << " memory size= " << (unsigned int) cb->mem_size  << " offset=" << (unsigned int) cb->mem_offset
           << " data width= " << (int) cb->width
           << " number of blocks=" << (unsigned int) cb->num_blocks
           << " block_size= " << (unsigned int) cb->block_size << endl;
      delete[] file_image;
      return 0;
    }
  cout << "Loaded flash image: " << filename
       << " width= "<<(int)cb->width
       << " man= "<<hex<<(int)cb->vendor_code
       << " dev= "<<hex<<(int)cb->dev_code
       << " size="<<dec<< cb->mem_size/(NAND_PAGE_SIZE*NAND_PAGES_IN_BLOCK)
       << " blocks" << endl;
  *ret_file_size = file_size;
  *ret_file_image = file_image;
  return 1;
}

int CreateFlashFile(uint32_t flash_size, const uint8_t flash_width,
                    const FlashVendor vendor_code, uint8_t dev_code,
                    const Voltage supply, const uint8_t protection,
                    const char * name, char ** ret_file_image, fstream * flash_file,
                    unsigned int *ret_file_size)
{
  NAND_FlashControlBlock cb={{0},0,0,0,0,0,0,0,NAND_NO_VENDOR,NO_ID,0};
  char *file_image = NULL;
  unsigned int file_size;
  string filename = HandleFileSuffix(name);

  cb.magic.magic_int = NAND_FLASH_MAGIC_UI;
  cb.major_version = NAND_MAJOR_VERSION;
  cb.minor_version = NAND_MINOR_VERSION;
  cb.block_size = NAND_PAGES_IN_BLOCK;
  cb.protection = protection;
  if (flash_size == 0){
    flash_size = NAND_DEFAULT_FLASH_SIZE;
    cb.num_blocks =   NAND_DEFAULT_NUM_BLOCKS ;
  }
  else
    cb.num_blocks =  (flash_size << NAND_BLOCK_SHIFT);

  cb.width = (flash_width == 0) ?
    NAND_DEFAULT_WIDTH : (uint8_t) flash_width;

  // The vendor and model must be consistent
  if (vendor_code == NAND_NO_VENDOR) {
    if (dev_code == NO_ID) { // defaults to ST 128 Megs
      cb.vendor_code = NAND_DEFAULT_VENDOR ;
      cb.dev_code =  NAND_DEFAULT_DEV_CODE;
      cout <<"Default ST Microelectronics 128 M 8 bits is used "
        // << hex << cb.dev_code
           << endl;
    }
    else {
      cout <<"Must provide vendor code if device code provided!\n";
      Usage(true);
      return 0;
      }
  } else {
    switch(vendor_code) {
    case NAND_STMicro:
      cb.vendor_code = NAND_STMicro;
      dev_code = set_ST_dev_code(flash_size, supply, cb.width);
      break;
    default: //
      if (dev_code != NO_ID) {
        cb.vendor_code = vendor_code ;
        cb.dev_code =  dev_code;
      }
      else {
        cout <<"Must provide device code if vendor code provided!\n";
        Usage(true);
        return 0;
      }
    }
  } // end if vendor

  // Open the file and set the control block values
  flash_file->open(filename.data(), ios::out | ios::trunc | ios::binary);
  if (flash_file->fail()) {
    cout << "Failed to open flash file: " << filename << endl;
    return 0;
  }
  cb.mem_size = cb.num_blocks*NAND_BLOCK_SIZE;
  // align offset on 64 bits
  cb.mem_offset = sizeof(NAND_FlashControlBlock);
  if ((cb.mem_offset & 0x7) != 0) {
    cb.mem_offset = ((cb.mem_offset >> 3)+1)<<3;
  }
  file_size = cb.mem_offset + cb.mem_size;
  file_image = new char[file_size];
  if ( file_image == NULL) {
    cout << "Cannot allocate flash size: " << file_size <<endl;
    return 0;
  }
  *((NAND_FlashControlBlock *) file_image) = cb;
  memset(file_image + cb.mem_offset, 0xFF, cb.mem_size);
  cout << "Flash File " << filename
       << " created with" << endl;
  cout << (int)cb.num_blocks << " blocks of "
       << (int)cb.block_size << " pages of " << (int)cb.width << " bits data\n"
       << " vendor code = " << hex << (uint32_t) cb.vendor_code
       << " device code = " << hex << (uint32_t) cb.dev_code
       << " as " << ((cb.protection==NAND_READ_ONLY) ? "read only" : "writeable")
       << endl;
  *ret_file_size = file_size;
  *ret_file_image = file_image;
  return 1;
}
// Copy a file into flash memory image
// to the destination page boot_page in block boot_block
// Each page of data is followed by spare data
// Open the file, read it, and then copy it page by page
// start_address is the beginning of the flash file image in memory

int CopyBootFile(NAND_FlashControlBlock * cb, fstream & boot_file,
                 unsigned int boot_block, unsigned int boot_page ,
                 char * start_address)
{
  char *boot_file_image = NULL; // address of the boot image
  unsigned int boot_file_size = 0;

  // we know the file is already opened . get size of file
  boot_file.seekg(0,ifstream::end);
  boot_file_size = boot_file.tellg();
  boot_file.seekg(0);

  boot_file_image = new char[boot_file_size];
  if (boot_file_image == NULL) {
    cout << "Cannot allocate boot buffer: " << boot_file_size <<endl;
    return 0;
  }
  boot_file.read(boot_file_image, boot_file_size);
  if (boot_file.fail()) {
    cout << "Failed to read boot file! " << endl;
    return 0;
  }
  if (boot_block > cb->num_blocks ) {
    cout << "Boot block address larger than memory ...: "
         << boot_block <<endl;
    return 0;
    }
  if (boot_page > cb->block_size) {
    cout << "Boot page address larger than block size ...: "
         << boot_page <<endl;
    return 0;
  }
  // Copy the boot loader page by page and setup the spare data
  unsigned int offset = boot_block*NAND_BLOCK_SIZE + boot_page*NAND_PAGE_SIZE;
  char * dst_address = start_address + offset;
  char * src_address = boot_file_image;
  int remaining = boot_file_size;
  char * upper_bound = start_address + cb->mem_size;

  cout << "Copying file to block " << dec << boot_block
       << " page " << boot_page << " offset " << offset
       << " max memory " << cb->mem_size
       << endl;
  // for all pages, fill the page, then fill the spare
  while (remaining > 0) {
    if (dst_address > upper_bound) {
      cout << "Boot file too big to fit into flash size ... " << endl;
      cout << "BEWARE: File may be corrupted!. " << endl;
      boot_file.close();
      return 0;
    }
    if (remaining >= NAND_PAGE_DATA_SIZE)
      memcpy(dst_address, src_address, NAND_PAGE_DATA_SIZE);
    else
      memcpy(dst_address, src_address, remaining);
    dst_address += NAND_PAGE_DATA_SIZE;
    src_address += NAND_PAGE_DATA_SIZE;
    remaining -= NAND_PAGE_DATA_SIZE;
    // TODO initialize the spare properly with ECC
    memset(dst_address, 0xFF, NAND_SPARE_SIZE);
    dst_address +=  NAND_SPARE_SIZE;
  }
  delete [] boot_file_image;
  boot_file.close();

  return boot_file_size;
}

int main(int argc, char *argv[])
{
  NAND_FlashControlBlock * cb;
  fstream flash_file;
  fstream boot_file;
  int count = --argc;
  char **args = &argv[1];
  unsigned int flash_file_size = 0;
  char *flash_file_image = NULL; // address of the file image
  char flash_filename[256] = "";;
  char boot_filename[256] = "";
  bool copy_boot = false;
  FlashVendor vendor_code = NAND_NO_VENDOR;
  Voltage supply = NO_VOLTAGE; // flash voltage
  uint8_t dev_code = 0;
  uint32_t flash_size = 0; // flash size in Megs
  uint8_t protection = NAND_WRITEABLE;
  uint8_t flash_width = 0; // 8 or 16
  bool new_file = true;
  unsigned  int boot_block = 1; // default to block 1
  unsigned  int boot_page = 0; // page 0


  if (count == 0) {
    cout << "Error -- Must specify at least one file argument" << endl;
    Usage(true);
    exit(1);
  }

  while (count > 1 ) {
    string name(args[0]);
    if (args[0][0]=='-') {
      if (name.compare("-a")== 0) {
        new_file = false;
        count -= 1;
        args = &args[1];
      }
      else if (name.compare("--v")== 0) {
        cout << "Make Flash Utility Version 1.0" << endl;
        count -= 1;
        args = &args[1];
      }
      else if (name.compare("-s")== 0) {
        flash_size = strtoul(args[1], NULL, 0);
        if (flash_size == 128 || flash_size == 256
            || flash_size == 512 || flash_size == 1024
            // TODO || flash_size == 2048 || flash_size == 4096
            ) {
          // TODO
          count -=2;
          args = &args[2];
        } else {
          cout << "Error --  size argument must be 128|256|512|1024|2048|4096 : "
               << endl;
          Usage(true);
          exit( 1);
        }
      } else if (name.compare("-w")==0) {
        flash_width = strtoul(args[1], NULL, 0);
        if (flash_width != 8 || flash_width != 16) {
          // cout << "flash flash_width is : "<<flash_width<<endl;
          cout << "Error --  width argument must be 8 or 16" << endl;
          Usage(true);
          exit(1);
        }
        count -=2;
        args = &args[2];
      } else if (name.compare("-bf") == 0) {
        strcpy(boot_filename, args[1]);
        // Open the file and set the control block values
        boot_file.open(boot_filename, ios::in | ios::binary);
        if (boot_file.fail()) {
          cout << "Error -- Failed to open boot file: " << boot_filename << endl;
          exit(1);
        }
        copy_boot = true;
        count -=2;
        args = &args[2];
      } else if (name.compare("-bb") == 0) {
        boot_block  = strtoul(args[1], NULL, 0);
        count -=2;
        args = &args[2];
      } else if (name.compare("-bp") == 0) {
        boot_page = strtoul(args[1], NULL, 0);
        count -=2;
        args = &args[2];
      } else if (name.compare("-vc") == 0) {
        vendor_code = (FlashVendor) strtoul(args[1], NULL, 16);
        // cout << "manuf code" << vendor_code << endl;
        if (vendor_code == NAND_NO_VENDOR) {
          cout << "Error --  Vendor code must be positive "
               << vendor_code << endl;
          exit( 1);
        }
        count -=2;
        args = &args[2];
      } else if (name.compare("-dc") == 0) {
        dev_code = strtoul(args[1], NULL, 16);
        if (dev_code == 0) {
          cout << "Error --  device code must be positive " << dev_code << endl;
          exit( 1);
        }
        count -=2;
        args = &args[2];
      } else if (name.compare("-vt")==0) {
        string volt = args[1];
        if (volt.compare("1V") == 0 )
          supply = S1V;
        else if (volt.compare("3V") == 0)
          supply = S3V;
        else {
          cout << "Error --  Only 1V and 3V supported in this version "
               << vendor_code << endl;
          exit( 1);
        }
        count -=2;
        args = &args[2];
      } else if (name.compare("-p")==0) {
        if (args[1][0] == 'r') {
          cout << "Creating read-only flash" << endl;
          protection = NAND_READ_ONLY;
        } else {
          protection = NAND_WRITEABLE;
          cout << "Creating writeable flash" << endl;
        }
        count -=2;
        args = &args[2];
      } else { // s[0] == '-' followed by unknown
        cout <<"Error -- parsing command line unrecognized option : " << name <<endl;
        Usage(true);
        exit( 1);
      }
    } else { // s[0] != '-'
      cout <<"Error --  options must start with '-' character : " << name <<endl;
      Usage(true);
      exit( 1);
    }
  } // end while

  if (count == 1) {
    string name(args[0]);
    if (name.compare("--v")== 0) {
      cout << "Make Flash Utility Version 1.0" << endl;
      exit(1);
    }
  }
  else {
    cout << "Error -- No file image specified..." << endl;
    Usage(true);
    exit( 1);
  }
  strcpy(flash_filename, args[0]);
  // The arguments have been parsed correctly. Now process
  int ret;
  if (new_file)
    ret = CreateFlashFile(flash_size, flash_width, vendor_code, dev_code,
                          supply, protection, flash_filename,
                          &flash_file_image, &flash_file, &flash_file_size);
  else
    ret = OpenFlashFile(flash_filename, &flash_file_image, &flash_file, &flash_file_size);
  if (ret == 0 || flash_file_image == NULL) {
    cout << "Fatal Error. No flash file was opened." << endl;
    exit(1);
  }

  // now fill the contents of the flash simulation file
  cb = (NAND_FlashControlBlock *) flash_file_image;

  // copy the boot file at address specified
  if (copy_boot) {
    int copied = CopyBootFile(cb, boot_file, boot_block, boot_page,
                              flash_file_image + cb->mem_offset);
    if ( copied == 0) {
      flash_file.close();
      cout <<"Failed to copy boot file: " << boot_filename << endl;
    }
    else
      cout << "Copied " << copied
           << " bytes from file to page " << boot_page
           << " of block " << boot_block
           << " at file offset " << cb->mem_offset
           << endl;
  }
  else {
    cout << "Nothing to load into file" << endl;
  }
  // Write now the flash file image from memory to storage
  flash_file.seekg(0);
  flash_file.write(flash_file_image, flash_file_size);
  if (flash_file.fail()) {
    cout <<"Failed to write the flash file: " <<endl;
  } else {
    cout << "Wrote " << flash_file_size << " bytes to file" << endl;
  }
  flash_file.close();
  if (flash_file.fail()) {
    cout <<"Failed to close the flash file properly. " << endl;
  } else {
    cout << "Flash File Image OK. "  << endl;
    delete[] flash_file_image;
    exit( 0);
  }
}
