//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include "libsimsoc/components/serial_flash_cb.hpp"

using namespace std;
using namespace simsoc;

void Usage(bool error) {
  cout << "Usage: mkserialflash [options] file" <<endl;
  cout << "Options are: --v -s [64|128|256|512|1024] -w [8|16] -p [r|w] -vc vendor_code -dc dev_code -bf bootfile -bs sector -a "
       << endl;
  cout << "Options -s [size in Megabits ] -w [data size] -p [protection] " << endl;
  cout << "Defaults to 64 Megabits, 8 bits width , writeable " << endl;
  cout << "Options -vc international vendor code -dc device code from manufacturer" << endl;
  cout << "Defaults to ST Microelectronics 8 Megabytes M25P64 model" << endl;
  cout << "Options -bf the boot file to be stored in flash at sector specified with -bs" << endl;
  cout << "Beware: boot sector defaults to 1 if unspecified, may erase previous data!"<< endl;
  cout << "Option -a to add a new boot file to an existing flash file\n"
       << "Beware it overwrites existing data\n"
       << endl;
  cout << "Option --v for version" <<endl;
  if (error)
    cout << "No flash image created" << endl;
}

uint16_t set_ST_dev_code(ST_SerialFlashModel model) {
  uint16_t code = 0;

  switch(model) {

  case M25P64:
    code = (uint16_t) model;
    break;


  default:
    cout << "ST flash model not supported \n";
    exit(1);
  }
  return  code;
}


string HandleFileSuffix(const char * name) {
  const char SUFFIX[] = ".sfs";
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
  SerialFlashControlBlock * cb;
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
  cb = (SerialFlashControlBlock *) file_image;
  if (tolower(cb->magic.magic_string[0]) != tolower(SERIAL_FLASH_MAGIC[0])
      || tolower(cb->magic.magic_string[1]) != tolower(SERIAL_FLASH_MAGIC[1])
      || tolower(cb->magic.magic_string[2]) != tolower(SERIAL_FLASH_MAGIC[2])
      || tolower(cb->magic.magic_string[3]) != tolower(SERIAL_FLASH_MAGIC[3]))
    {
      cout << "Error : " << filename << " is not a valid flash file image! "
           << cb->magic.magic_string[0] <<  cb->magic.magic_string[1]
           << cb->magic.magic_string[2] <<  cb->magic.magic_string[3]
           << endl;
      delete[] file_image;
      return 0;
    }
  if ( cb->mem_size == 0
       || cb->mem_offset < sizeof(SerialFlashControlBlock)
       || ! (cb->width == 8 || cb->width == 16)
       || cb->sector_size != (unsigned int) SERIAL_SECTOR_SIZE
 // only supported size in version 1.0
       || file_size != cb->mem_offset + cb->mem_size
       || cb->num_sectors != cb->mem_size / cb->sector_size)
    {
      cout << "Flash file " << filename << " is corrupted...\n"
           << " memory size= " << (unsigned int) cb->mem_size  << " offset=" << (unsigned int) cb->mem_offset
           << " data width= " << (int) cb->width
           << " number of sectors=" << (unsigned int) cb->num_sectors
           << " sector_size= " << (unsigned int) cb->sector_size << endl;
      delete[] file_image;
      return 0;
    }
  cout << "Loaded flash image: " << filename
       << " width= "<<(int)cb->width
       << " man= "<<hex<<(int)cb->vendor_code
       << " dev= "<<hex<<(int)cb->dev_code
       << " size="<<dec<< cb->mem_size/(SERIAL_PAGE_SIZE*SERIAL_PAGES_IN_SECTOR)
       << " blocks" << endl;
  *ret_file_size = file_size;
  *ret_file_image = file_image;
  return 1;
}

int CreateFlashFile(uint32_t flash_size, const uint8_t flash_width,
                    const SerialFlashVendor vendor_code, uint8_t dev_code,
                    const char * name, char ** ret_file_image,
                    fstream * flash_file,
                    unsigned int *ret_file_size)
{
  SerialFlashControlBlock cb;
  char *file_image = NULL;
  unsigned int file_size;
  string filename = HandleFileSuffix(name);

  cb.magic.magic_int = SERIAL_FLASH_MAGIC_UI;
  cb.major_version = SERIAL_MAJOR_VERSION;
  cb.minor_version = SERIAL_MINOR_VERSION;
  cb.sector_size = SERIAL_SECTOR_SIZE;
  if (flash_size == 0){
    flash_size = SERIAL_DEFAULT_FLASH_SIZE;
    cb.num_sectors =   SERIAL_DEFAULT_NUM_SECTORS ;
  }
  else {
    int should_be_zero = flash_size % SERIAL_SECTOR_SIZE;
    if (should_be_zero != 0) {
      cout <<"flash size must be an exact number of sectors !\n";
      Usage(true);
      return 0;
    }
    cb.num_sectors =  flash_size / SERIAL_SECTOR_SIZE ;
  }
  cb.width = (flash_width == 0) ?
    SERIAL_DEFAULT_WIDTH : (uint8_t) flash_width;

  // The vendor and model must be consistent
  if (vendor_code == SERIAL_NO_VENDOR) {
    if (dev_code == SERIAL_NO_ID) { // defaults to ST
      cb.vendor_code = SERIAL_DEFAULT_VENDOR ;
      cb.dev_code =  SERIAL_DEFAULT_DEV_CODE;
      cout <<"Default ST Microelectronics M25P64 (64 Mbits size 8 bits data) is used "
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
    case SERIAL_STMicro:
      cb.vendor_code = SERIAL_STMicro;
      if (dev_code == SERIAL_NO_ID) { // defaults
        cb.dev_code = SERIAL_DEFAULT_DEV_CODE;
        cout <<"Default ST Microelectronics M25P64 (64 Mbits size 8 bits data) is used "
          // << hex << cb.dev_code
             << endl;
      }
      else {
        cb.dev_code =  dev_code; // TODO verify code
      }
      break;
    default: //
      if (dev_code != SERIAL_NO_ID) {
        cb.vendor_code = vendor_code ;
        cb.dev_code =  dev_code;
      }
      else {
        cout <<"Must provide device code if vendor code provided!\n";
        Usage(true);
        return 0;
      }
    } // end if vendor
  }
  // Open the file and set the control block values
  flash_file->open(filename.data(), ios::out | ios::trunc | ios::binary);
  if (flash_file->fail()) {
    cout << "Failed to open flash file: " << filename << endl;
    return 0;
  }
  cb.mem_size = cb.num_sectors*SERIAL_SECTOR_SIZE;
  // align offset on 64 bits
  cb.mem_offset = sizeof(SerialFlashControlBlock);
  if ((cb.mem_offset & 0x7) != 0) {
    cb.mem_offset = ((cb.mem_offset >> 3)+1)<<3;
  }
  file_size = cb.mem_offset + cb.mem_size;
  file_image = new char[file_size];
  if ( file_image == NULL) {
    cout << "Cannot allocate flash size: " << file_size <<endl;
    return 0;
  }
  *((SerialFlashControlBlock *) file_image) = cb;
  memset(file_image + cb.mem_offset, 0xFF, cb.mem_size);
  cout << "Flash File " << filename
       << " created with" << endl;
  cout << (int)cb.num_sectors << " sectors of size "
       << (int)cb.sector_size << " items "
       << (int)cb.width << " bits data\n"
       << " vendor code = " << hex << (uint32_t) cb.vendor_code
       << " device code = " << hex << (uint32_t) cb.dev_code
       << endl;
  *ret_file_size = file_size;
  *ret_file_image = file_image;
  return 1;
}
// Copy a file into serial flash memory image
// to the destination sector boot_sector
// Open the file, read it, and then copy it page by page
// start_address is the beginning of the flash file image in memory

int CopyBootFile(SerialFlashControlBlock * cb, fstream & boot_file,
                 unsigned int boot_sector,
                 char * start_address)
{
  char *boot_file_image = NULL; // address of the boot image
  unsigned int boot_file_size = 0;

  // we know the boot file is already opened . get size of file
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
  if (boot_sector > cb->num_sectors ) {
    cout << "Boot sector address larger than memory ...: "
         << boot_sector <<endl;
    return 0;
  }
  // Copy the boot loader page by page and setup the spare data
  unsigned int offset = boot_sector*SERIAL_SECTOR_SIZE;
  char * dst_address = start_address + offset;
  char * src_address = boot_file_image;
  unsigned long upper_bound = (unsigned long) start_address + cb->mem_size;
  unsigned long end_of_file = (unsigned long) dst_address + boot_file_size;

  if ( end_of_file > upper_bound ) {
    cout << "Error boot file size " << dec << boot_file_size
         << " larger than max memory " << cb->mem_size
         << endl;
    return 0;
  }
  unsigned int last_sector = boot_sector +(boot_file_size / SERIAL_SECTOR_SIZE);
  if ((boot_file_size % SERIAL_SECTOR_SIZE) > 0)
    ++last_sector;
  cout << "Copied " <<dec<<boot_file_size << " bytes starting sector " << boot_sector
       << " ending sector." << last_sector << endl;
  memcpy(dst_address, src_address, boot_file_size);
  delete [] boot_file_image;
  boot_file.close();
  return boot_file_size;
}

int main(int argc, char *argv[])
{
  SerialFlashControlBlock * cb;
  fstream flash_file;
  fstream boot_file;
  int count = --argc;
  char **args = &argv[1];
  unsigned int flash_file_size = 0;
  char *flash_file_image = NULL; // address of the file image
  char flash_filename[256] = "";;
  char boot_filename[256] = "";
  bool copy_boot = false;
  SerialFlashVendor vendor_code = SERIAL_NO_VENDOR;
  uint8_t dev_code = 0;
  uint32_t flash_size = 0; // flash size in Megs
  uint8_t flash_width = 0; // 8 or 16
  bool new_file = true;
  unsigned  int boot_sector = 1; // default to sector 1

  // cout << count << " arguments\n";
  if (count == 0) {
    cout << "Error -- Must specify at least one file argument" << endl;
    Usage(true);
    exit(1);
  }
  // arguments are paired "-name" "value". Therefore must be count > 1
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
      else if (name.compare("-h")== 0) {
        Usage(false);
        exit(1);
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
          exit(EXIT_SUCCESS);
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
      } else if (name.compare("-bs") == 0) {
        boot_sector  = strtoul(args[1], NULL, 0);
        count -=2;
        args = &args[2];
      } else if (name.compare("-vc") == 0) {
        vendor_code = (SerialFlashVendor) strtoul(args[1], NULL, 16);
        // cout << "manuf code" << vendor_code << endl;
        if (vendor_code == SERIAL_NO_VENDOR) {
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
      }
      else { // s[0] == '-' followed by unknown
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
  // The remaining argument is the file name or an option without value or illegal
  if (count == 1) {
    string name(args[0]);
    if (name.compare("--v")== 0) { // version option
      cout << "Make Serial Flash Utility Version 1.0" << endl;
      exit(EXIT_SUCCESS);
    }
    else if (name.compare("-h")== 0) { // help option
      Usage(false);
      exit(EXIT_SUCCESS);
    }
    else if (args[0][0] ==  '-') {
      cout << "Illegal option : " << name << endl;
      exit(1);
    }
    else cout << "Flash Image : " << name << endl;
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
                          flash_filename,
                          &flash_file_image, &flash_file, &flash_file_size);
  else
    ret = OpenFlashFile(flash_filename, &flash_file_image, &flash_file, &flash_file_size);
  if (ret == 0 || flash_file_image == NULL) {
    cout << "Fatal Error. No flash file was opened." << endl;
    exit(1);
  }

  // now fill the contents of the flash simulation file
  cb = (SerialFlashControlBlock *) flash_file_image;

  // copy the boot file at address specified
  if (copy_boot) {
    int copied = CopyBootFile(cb, boot_file, boot_sector,
                              flash_file_image + cb->mem_offset);
    if ( copied == 0) {
      flash_file.close();
      cout <<"Failed to copy boot file: " << boot_filename << endl;
    }
  }
  else {
    cout << "Nothing to load into file" << endl;
  }
  // Write now the flash file image from memory to storage
  flash_file.seekg(0);
  flash_file.write(flash_file_image, flash_file_size);
  if (flash_file.fail()) {
    cout <<"Failed to write the serial flash file: " <<endl;
  } else {
    cout << "Wrote " << dec << flash_file_size << " bytes to file" << endl;
  }
  flash_file.close();
  if (flash_file.fail()) {
    cout <<"Failed to close the serial flash file properly. " << endl;
  } else {
    cout << "Flash File Image OK. "  << endl;
    delete[] flash_file_image;
    exit(EXIT_SUCCESS);
  }
}
