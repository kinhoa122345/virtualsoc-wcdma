//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "st_smi.hpp"
#include "display.hpp"
using namespace std;
using namespace sc_core;

namespace simsoc {

  static bool smi_valid_word_address(uint32_t a) {
    return (SMICtrl::SMI_WORD_LOWER_BOUND <= a) &&
      (a <=  SMICtrl::SMI_WORD_UPPER_BOUND );
  }

  /*
   * Constructor and destructor
   */

  SMICtrl::SMICtrl(sc_module_name name, SerialFlash * bank0,
                   SerialFlash * bank1, SerialFlash * bank2,
                   SerialFlash * bank3):
    Module(name)
  {
    if (bank0 == NULL) {
      error() << "Fatal error. Bank0 must be non NULL\n";
      exit(1);
    }
    banks[0] = bank0;
    banks[1] = bank1;
    banks[2] = bank2;
    banks[3] = bank3;
    rw_port(*this);              // bind the target port
    control1= DSEL_TIME | BANK0_ENABLED ;
    control2=0;
    status=0;
    transmit=0;
    receive=0;
    debug() <<"SMICtrl constructor" <<endl;
  }

  SMICtrl::~SMICtrl()
  {
    debug() <<"SMICtrl destructed" << endl;
  }
  /*
   * end of eleboration method. Initialize all banks connected
   */

  void SMICtrl::end_of_elaboration() {
    debug() <<"SMICtrl connects to serial banks" << endl;
    for (int i=0; i< MAX_BANKS; ++i) {
      if (banks[i] != NULL)
        banks[i]->SetController(this);
    }
  }

  /*
   * This function is called by the flash memory simulation to check
   * whether a hardware write is possible.
   * Because the writes are sent first by TLM bus to the flash
   * though in real hardware this is intercepted first by SMI...
   * bank_id must be [0-4].
   * Check the controller is in hardware mode,
   * the bank is write enabled and there is no work in progress,
   * then call the memory write in the flash memory
   */

  void SMICtrl::ForwardWrite(const int bank_id,
                             const uint32_t addr, const uint32_t value) {
    if (control1 & SW_MODE) {
      warning() << "Serial memory direct write is allowed only in hardware mode" << endl;
      status |= ERROR_FLAG1;
      return;
    }
    switch(bank_id) {
    case BANK0:
      if ((status & BANK0_WRITEABLE) == 0) {
        warning() <<"Serial Memory bank 0 is not writeable\n";
        status |= ERROR_FLAG2;
        return ;
      }
      break;
    case BANK1:
      if ((status & BANK1_WRITEABLE) == 0) {
        warning() <<"Serial Memory bank 1 is not writeable\n";
        status |= ERROR_FLAG2;
        return ;
      }
      break;
    case BANK2:
      if ((status & BANK2_WRITEABLE) == 0) {
        warning() <<"Serial Memory bank 2 is not writeable\n";
        status |= ERROR_FLAG2;
        return ;
      }
      break;
    case BANK3:
      if ((status & BANK3_WRITEABLE) == 0) {
        warning() <<"Serial Memory bank 3 is not writeable\n";
        status |= ERROR_FLAG2;
        return ;
      }
      break;
    default:
      error() << "Fatal error non existent serial memory bank "<< bank_id
              << endl;
      exit(1);
      return ; // avoid compiler warning...
    }
    SerialFlash * bank = banks[bank_id];
    int stat = bank->ReadStatus();
    if (stat & WORK_IN_PROGRESS) {
      debug() << "Cannot write when work in progress\n";
      return;
    }
    stat = bank->DoWrite(addr, value); // call the flash memory write
    status = (status & ~STATUS_MASK) | stat;
    control2 |= WRITE_COMPLETED;
    // debug() << "Serial Memory write completed" << endl;
    return;
  }

  /*
   * The TLM read writes
   *
   */

  uint32_t SMICtrl::read_word(uint32_t addr) {
    // debug() << "SMICtrl read word" << endl;

    if (! smi_valid_word_address(addr)) {
      error() << "Invalid read word" << endl;
      exit(1);
    }
    // read register
    switch(addr) {

    case SMI_CONTROL1_OFFSET :
      // debug() << "Read control1 register " << endl;
      return control1;

    case SMI_CONTROL2_OFFSET :
      // debug() << "Read control2 register " << endl;
      return control2;

    case SMI_TRANSMIT_OFFSET :
      if (control1 & SW_MODE == 0)
        warning() << "Read transmit register in hardware mode! " << endl;
      else
        debug() << "Read transmit register " << hex<< transmit << endl;
      return transmit;

    case SMI_RECEIVE_OFFSET :
      if (control1 & SW_MODE == 0)
        warning() << "Read receive register in hardware mode! " << endl;
      else
        debug() << "Read receive register " << hex<<receive << endl;
      return receive;

    case SMI_STATUS_OFFSET:
      // debug() << "Read status register " << endl;
      return status;

    default:
      // should not happen
      error() << "Try to read non existent SMI register " << endl;
      exit(1);
    }
  }

  void SMICtrl::write_word(uint32_t addr, uint32_t d) {
    int bank_id = MAX_BANKS ; // the memory bank target of control operations
    SerialFlash * target_bank ;

    int flag = 0;
    if (! smi_valid_word_address(addr)) {
      error() << "Invalid write word address" << endl;
      exit(1);
    }

    switch (addr) {
    case SMI_CONTROL1_OFFSET :
      if (d & SW_MODE) {
        if (~control1 & SW_MODE) { // switch from HW to SW
          debug() << "SMI reset to software mode" << endl;
        }
      }
      else {
        if (control1 & SW_MODE) { // switch from SW to HW
          debug() << "SMI reset to hardware mode" << endl;
        }
      }
      /* used when debugging
         if (d & BANK0_ENABLED) {
         debug() << "SMI bank 0 enabled " << endl;
         // if (banks[BANK0] == NULL)
         // warning() << "Bank 0 enabled but not present\n";
         }
         if (d & BANK1_ENABLED) {
         debug() << "SMI bank 1 enabled " << endl;
         //      if (banks[BANK1] == NULL)
         //warning() << "Bank 1 enabled but not present\n";
         }
         if (d & BANK2_ENABLED) {
         debug() << "SMI bank 2 enabled " << endl;
         // if (banks[BANK2] == NULL)
         // warning() << "Bank 2 enabled but not present\n";
         }
         if (d & BANK3_ENABLED) {
         debug() << "SMI bank 3 enabled " << endl;
         //      if (banks[BANK3] == NULL)
         // warning() << "Bank 3 enabled but not present\n";
         }
         if (d & ADDRESS_LENGTH_MASK) {
         if (d & ADDR_BANK0)
         debug() << "Bank 0 address length is 2 bytes only" << endl;
         if (d & ADDR_BANK1)
         debug() << "Bank 1 address length is 2 bytes only" << endl;
         if (d & ADDR_BANK2)
         debug() << "Bank 2 address length is 2 bytes only" << endl;
         if (d & ADDR_BANK3)
         debug() << "Bank 3 address length is 2 bytes only" << endl;
         }
      */
      control1 = d;
      return;
      break;

      /* CONTROL2 Register. Check that operation is legal on selected memory bank
       * then do the work, If necessary call the serial memory functions.
       */
    case SMI_CONTROL2_OFFSET :
      bank_id = (int) ((d & BANK_SEL_MASK) >> BANK_SEL_SHIFT);
      // debug() << "Operation on serial memory bank " << dec<<bank_id << endl;
      target_bank = banks[bank_id];
      if (target_bank == NULL) {
        warning() << "Selected memory bank " << dec<<bank_id
                <<  " does not exist" << endl;
        //return;
      }
      if (d & TX_LEN_MASK) {
        debug() << "set transmit length to " << (d & TX_LEN_MASK)
                << endl;
      }
      if (d & RX_LEN_MASK) {
        debug() << "set receive length to " << ((d & RX_LEN_MASK) >> 4)
                << endl;
      }
      if ((control2 & WRITE_COMPLETED) && ((d & WRITE_COMPLETED) == 0))
        debug() << "Write Completed Flag cleared\n" ;

      switch (bank_id) {
      case BANK0:
        flag =  BANK0_ENABLED;
        break;
      case BANK1:
        flag =  BANK1_ENABLED;
        break;
      case BANK2:
        flag =  BANK2_ENABLED;
        break;
      case BANK3:
        flag =  BANK3_ENABLED;
        break;
      }
      if ((control1 & flag) == 0) {
        warning() << "Operation requested on serial memory disabled bank "
                  << dec<<bank_id << endl;
        status |= ERROR_FLAG1;
        /*  not sure ??     control2 = d;
            status |=TFF;
            return; */
      }
      if (d & WRITE_FLAG) {
        switch(bank_id) {
        case BANK0:
          debug() << "set bank 0 write" << endl;
          status |= BANK0_WRITEABLE;
          break;
        case BANK1:
          debug() << "set bank 1 write" << endl;
          status |= BANK1_WRITEABLE ;
          break;
        case BANK2:
          debug() << "set bank 2 write" << endl;
          status |= BANK2_WRITEABLE ;
          break;
        case BANK3:
          debug() << "set bank 3 write" << endl;
          status |= BANK3_WRITEABLE;
          break;
        default:
          error() << "Illegal serial memory bank id " << bank_id << endl;
          return;
        }
        if (target_bank != NULL) {
          status |= target_bank->SetWriteMode(true);
        }
        // bit is reset immediately
        d  &= ~WRITE_FLAG;
      }
      if (d & RD_STATUS_REG) {
        debug() << "read status register from bank " << bank_id << endl;
        status &= ~BANK_STATUS_MASK;
        if (target_bank != NULL)
          status |= target_bank->ReadStatus();
        // reset bit
        d &= ~RD_STATUS_REG;
      }

      if (d & SEND) {
        int stat = 0; // store the serial memory status after command
        if (target_bank == NULL) {
          warning() << "Trying to access non existent serial memory bank "
                    << bank_id << endl ;
        } else {
          SerialCommand cmd = (SerialCommand) (transmit & 0xFF);
          switch(cmd) {
          case READ_ID:
            stat = target_bank->ReadId(&receive);
            debug() << "Read bank " << bank_id << " signature : "
                    << hex << (unsigned int) receive << endl;
            break;
          case READ_STATUS:
            stat |= target_bank->ReadStatus();
            debug() << "Read bank " << bank_id << " status : "
                    << hex << (unsigned int) stat << endl;
            break;
          case PAGE_PROGRAM:
            debug() << "Program bank " << bank_id << " page : "
                    << hex << ((transmit & 0xFFFFFF00) >> 8) <<  endl;
            stat |= target_bank->DoPageProgram((transmit & 0xFFFFFF00)>>8);
            break;

          case SECTOR_ERASE:
            debug() << "Erase bank " << bank_id << " sector : "
                    << hex << ((transmit & 0xFFFFFF00) >> 8) <<  endl;
            stat |= target_bank->DoSectorErase((transmit & 0xFFFFFF00)>>8);
            break;

          case BULK_ERASE:
            debug() << "Erase bank " << bank_id << " completely! "  <<  endl;
            stat |= target_bank->DoBulkErase();
            break;

          default:
            warning() << "Serial memory controller unknown command " << hex << cmd
                      << endl;
          }
        }
        status |= stat ;
      }
      control2 = d;
      status |=TFF;
      return;

      // Transmit Register
    case SMI_TRANSMIT_OFFSET :
      if ((control1 & SW_MODE) == 0) {
        error() << "SMI transmit is allowed only in software mode" << endl;
        exit(1);
      }
      else {
        int bank_id = (control2 & BANK_SEL_MASK) >> BANK_SEL_SHIFT;
        // debug() << "Set transmit register to " << hex<< d << endl;
        transmit = d;
        if (banks[bank_id] == NULL)
          warning() << "Transmit to non existent serial memory bank "
                    << bank_id << endl;
      }
      return;

      // Receive Register

    case SMI_RECEIVE_OFFSET :
      receive = d;
      warning() << "Write receive register should not happen " << endl;
      return;

      // Status Register

    case SMI_STATUS_OFFSET: // The doc says it is RO but it is not !!!
      {     int stat = 0;
        if ((status & BANK0_WRITEABLE) && ((d & BANK0_WRITEABLE) == 0) ) {
          debug() << "Reset bank 0 to read mode\n";
          target_bank = banks[0];
          if (target_bank != NULL)
            stat = target_bank->SetWriteMode(false);
        }
        if ((status & BANK1_WRITEABLE) && ((d & BANK1_WRITEABLE) == 0) ) {
          debug() << "Reset bank 1 to read mode\n";
          target_bank = banks[1];
          if (target_bank != NULL)
            stat = target_bank->SetWriteMode(false);
        }
        if ((status & BANK2_WRITEABLE) && ((d & BANK2_WRITEABLE) == 0) ) {
          debug() << "Reset bank 2 to read mode\n";
          target_bank = banks[2];
          if (target_bank != NULL)
            stat = target_bank->SetWriteMode(false);
        }
        if ((status & BANK3_WRITEABLE) && ((d & BANK3_WRITEABLE) == 0) ) {
          debug() << "Reset bank 3 to read mode\n";
          target_bank = banks[3];
          if (target_bank != NULL)
            stat = target_bank->SetWriteMode(false);
        }
        if ((status & TFF) && ((d & TFF) == 0))
          // debug() << "Transmission Finished Flag cleared\n" ;
          if ((status & ERROR_FLAG1) && ((d & ERROR_FLAG1) == 0))
            debug() << "Error Flag 1 cleared\n" ;

        if ((status & ERROR_FLAG2) && ((d & ERROR_FLAG2) == 0))
          debug() << "Error Flag 2 cleared\n" ;

        status = d | stat;
        return;
      }

    default:
      // should not happen
      error() << "Invalid write SMI register" << endl;
      exit(1);
    }
  }

} // namespace simsoc
