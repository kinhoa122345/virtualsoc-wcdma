//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "primecell_vic_pl190.hpp"
#include "libsimsoc/processors/arm/arm_processor.hpp"
#include "libsimsoc/interfaces/yield.hpp"
#include "libsimsoc/display.hpp"

using namespace std;
using namespace sc_core;

namespace simsoc {

/*
 * Create as many VICS as specified.
 * Create as many interrupt lines (32 for each VIC) as necessary
 * Create the Initiator port to report interrupts
 * Create the multi target ports such that they all end up
 * calling the routing method with the port number
 */

PrimeCell_PL190_VIC_chain::PrimeCell_PL190_VIC_chain(sc_module_name name,
                                                     const int nb_vic,
                                                     const ARM_Processor *master):
  Module(name),
  strict(true),
  in_ports(nb_vic*32, SignalMultiTargetPort<bool>(this,false)), proc(master)
{
  int i;
  PrimeCell_PL190_VIC * next = NULL;
  vic_chain.reserve(nb_vic);
  for (i = 0; i < nb_vic; ++i) {
    // Create a VIC and set the daisy chain so that each VIC points
    // to the next higher priority VIC, and the highest priority
    // points to NULL, and this is the first element in the vector
    PrimeCell_PL190_VIC * vic = new PrimeCell_PL190_VIC((string("VIC")+string_of<int>(i)).c_str(),
                                                        this);
    vic_chain.push_back(vic);
    vic->set_daisy_chain(next);
    next = vic;
  }
}

PrimeCell_PL190_VIC_chain::~PrimeCell_PL190_VIC_chain() {
  debug() <<"destructor called\n";
  for (size_t i=0; i<vic_chain.size(); ++i)
    delete vic_chain[i];
}

/*
 * Method to route the interrupt to the corresponding priority VIC.
 */
void PrimeCell_PL190_VIC_chain::signal(bool s, size_t line) {
  unsigned int vic_index = line / 32;
  debug() <<"interrupt " <<dec <<line <<(s? " set":" reset") <<endl;

  if (vic_index >= vic_chain.size())
    error() << "Unreachable VIC\n";
  else {
    vic_chain[vic_index]->signal_interrupt(line%32, s);
  }
}

bool PrimeCell_PL190_VIC_chain::user_mode() const {
  return proc->user_mode();
}



/******************************************************************************/

PrimeCell_PL190_VIC::PrimeCell_PL190_VIC(sc_module_name name,
                                         PrimeCell_PL190_VIC_chain * i):
  Module(name), initiator(i),
  source_status(0), chained_irq(false), chained_addr(0), chained_fiq(false),
  select(0), enabled(0), soft_it(0), protection(false),
  current_isr(0), default_isr(0),
  vi_addresses(LOWEST_PRIORITY,0),
  vi_sourceids(LOWEST_PRIORITY,0),
  vi_enablebits(LOWEST_PRIORITY,false),
  current_isr_priority(NOTHING_SERVED),
  served_priorities()
{
  served_priorities.push(NOTHING_SERVED);
  rw_port(*this);  // bind the target port
}

PrimeCell_PL190_VIC::~PrimeCell_PL190_VIC()
{
  debug() << "destructor called\n";
}

// void PrimeCell_PL190_VIC::reset()
// {
//   debug() << "Interrupt Controller reset\n";
//   source_status = 0;
//   select = enabled = soft_it = 0;
//   protection = 0;
//   current_isr = default_isr = 0;
//   memset(vi_addresses, 0, LOWEST_PRIORITY*sizeof(uint32_t));
//   memset(vi_sourceids, 0, LOWEST_PRIORITY*sizeof(uint32_t));
//   memset(vi_enablebits, 0, LOWEST_PRIORITY*sizeof(bool));
// }

uint32_t PrimeCell_PL190_VIC::irq_status() const {
  return raw_status() & enabled & ~select;
}

uint32_t PrimeCell_PL190_VIC::fiq_status() const {
  return raw_status() & enabled & select;
}

uint32_t PrimeCell_PL190_VIC::raw_status() const {
  return source_status|soft_it;
}

void PrimeCell_PL190_VIC::set_chained_irq(bool value, uint32_t addr) {
  if (value!=chained_irq||addr!=chained_addr) {
    chained_irq = value;
    chained_addr = addr;
    compute_irq();
  }
}

void PrimeCell_PL190_VIC::set_chained_fiq(bool value) {
  if (value!=chained_fiq) {
    chained_fiq = value;
    compute_fiq();
  }
}

// update the IRQ port and the CURRENT_ISR regoister
void PrimeCell_PL190_VIC::compute_irq() {
  if (irq_status()) {
    // check if vectored
    size_t priority;
    for (priority = HIGHEST_PRIORITY; priority < LOWEST_PRIORITY; ++priority) {
      if (vi_enablebits[priority] &&
          (irq_status()&(1<<vi_sourceids[priority])))
        break;
    }
    // check if the vic is already serving an interrupt of same or higher priority
    if (priority>=served_priorities.top()) {
      if (daisy_chain) {
        daisy_chain->set_chained_irq(false,0);
      } else {
        initiator->irq_port = false;
      }
      return;
    }
    // update current_isr register
    if (priority==LOWEST_PRIORITY) {// non-vectored interrupt
      current_isr = default_isr;
      current_isr_priority = NONVECTORED_SERVED;
    } else { // vectored interrupt
      current_isr = vi_addresses[priority];
      current_isr_priority = priority;
    }
    // send the conclusion
    if (daisy_chain) {
      daisy_chain->set_chained_irq(true,current_isr);
    } else {
      initiator->irq_port = true;
    }

  } else { // transfer from previous VIC
    // check if the vic is already serving an interrupt of same or higher priority
    if (CHAINED_SERVED>=served_priorities.top()) {
      if (daisy_chain) {
        daisy_chain->set_chained_irq(false,0);
      } else {
        initiator->irq_port = false;
      }
      return;
    }
    // update current_isr register
    if (chained_irq) {
      current_isr = chained_addr;
      current_isr_priority = CHAINED_SERVED;
    }
    // send the conclusion
    if (daisy_chain) {
      daisy_chain->set_chained_irq(chained_irq,current_isr);
    } else {
      initiator->irq_port = chained_irq;
    }
  }
}

// update the FIQ port
void PrimeCell_PL190_VIC::compute_fiq() {
  if (daisy_chain)
    daisy_chain->set_chained_fiq(fiq_status()||chained_fiq);
  else
    initiator->fiq_port = fiq_status()||chained_fiq;
}


// set the source status and update the fiq or irq signals if necessary
void PrimeCell_PL190_VIC::signal_interrupt(const size_t line,
                                           const bool s) {
  debug() <<"interrupt " <<dec <<line <<(s? " set":" reset") <<endl;
  if (s) // set interrupt
    source_status |= (1<<line);
  else // clear interrupt
    source_status &= ~(1<<line);

  if (enabled&(1<<line))
    if (select&(1<<line))
      compute_fiq();
    else
      compute_irq();
}

/*
 * Read a VIC register
 */

uint32_t PrimeCell_PL190_VIC::read_word(uint32_t addr) {
  if (protection&&initiator->user_mode()) {
    warning() << "read access to interrupt controller denied\n";
    return 0;
  }
  switch(addr) {
  case IRQ_STATUS_ADDR:
    YIELD();
    return irq_status();

  case FIQ_STATUS_ADDR:
    YIELD();
    return fiq_status();

  case RAW_INT_ADDR:
    YIELD();
    return raw_status();

  case INT_SELECT_ADDR :
    return select;

  case INT_ENABLE_ADDR :
    return enabled;

  case INT_EN_CLEAR_ADDR :
    warning() << "reading write only register clear enabled interrupt\n";
    break;

  case INT_SOFT_ADDR :
    return soft_it;

  case INT_SOFT_CLEAR_ADDR :
    warning() << "reading write only register clear soft interrupt\n";
    break;

  case INT_PROTECT_ADDR :
    return (uint32_t) protection;

  case CURRENT_ISR_ADDR : // reading this register enables priority handling
    {
      if (current_isr_priority>=served_priorities.top()) {
        if (initiator->strict) {
          error() <<"error in priority logic, or invalid read of the current ISR\n";
          exit(1);
        } else
          break;
      }
      served_priorities.push(current_isr_priority);
      uint32_t tmp = current_isr;
      compute_irq();
      return tmp;
    }

  case DEFAULT_VECT_ADDR :
    return default_isr;
    break;

  default:
    if (VECT_ADDR <= addr && addr <= LAST_VECT_ADDR) {
      size_t index = (addr-VECT_ADDR) >> 2;
      return vi_addresses[index];
    }
    if (VECT_CNTL <= addr && addr <= LAST_VECT_CNTL) {
      size_t index = (addr-VECT_CNTL) >> 2; // a number in 0 .. 15
      return vi_sourceids[index] | (vi_enablebits[index]? (1<<IRQ_ENABLE_SHIFT): 0);
    }
    error() << "Invalid read acces at offset " <<hex <<addr << endl;
    exit(1);
  }
  return 0;
}

void PrimeCell_PL190_VIC::write_word(uint32_t addr, uint32_t d) {
  if (protection&&initiator->user_mode()) {
    error() << "Write access to interrupt controller denied\n";
    exit(1);
  }
  switch(addr) {
  case IRQ_STATUS_ADDR :
    if (initiator->strict) {
      error() <<"writing read only register irq status\n";
      exit(1);
    } else
      warning() <<"writing read only register irq status\n";
    break;

  case FIQ_STATUS_ADDR :
    if (initiator->strict) {
      error() << "writing read only register fiq status\n";
      exit(1);
    } else
      warning() << "writing read only register fiq status\n";
    break;

  case RAW_INT_ADDR :
    error() << "writing read only register raw status\n";
    exit(1);
    break;

  case INT_SELECT_ADDR :
    select = d;
    compute_fiq();
    compute_irq();
    break;

  case INT_ENABLE_ADDR :
    enabled |= d;
    if (raw_status()&d) {
      compute_fiq();
      compute_irq();
    }
    break;

  case INT_EN_CLEAR_ADDR : // disable corresponding interrupts
    enabled &= ~d;
    if (raw_status()&d) {
      compute_fiq();
      compute_irq();
    }
    break;

  case INT_SOFT_ADDR :
    soft_it |= d;
    compute_fiq();
    compute_irq();
    break;

  case INT_SOFT_CLEAR_ADDR : // clear the software interrupts
    soft_it &= ~d;
    compute_fiq();
    compute_irq();
    break;

 case INT_PROTECT_ADDR :
   if (initiator->proc) {
     protection = d&1;
   } else {
     if (d&1)
       warning() <<"the protected mode is not supported" <<endl;
   }
   break;

  case CURRENT_ISR_ADDR :
    // writing this register clears current interrupt and
    // reactivates pending interrupt
    if (served_priorities.top()==NOTHING_SERVED) {
      if (initiator->strict) {
        error() <<"write to CURRENT_ISR register, but no interrupt is being served\n";
        exit(1);
      } else
        break;
    }
    served_priorities.pop();
    compute_irq();
    break;

  case DEFAULT_VECT_ADDR :
    default_isr = d;
    compute_irq();
    break;

  case ITCR:
	  break;

  default:
    if (VECT_ADDR <= addr && addr <= LAST_VECT_ADDR) {
      size_t index = (addr - VECT_ADDR) >> 2;
      vi_addresses[index] = d ;
      compute_irq();
    } else if (VECT_CNTL <= addr && addr <= LAST_VECT_CNTL) {
      size_t index = (addr - VECT_CNTL) >> 2; // must be [0..15]
      vi_sourceids[index] = d & 0x1F; // only consider last 5 bits
      vi_enablebits[index] = d & (1<<IRQ_ENABLE_SHIFT);
      compute_irq();
    } else {
      error() << "Invalid write access at offset " <<hex <<addr << endl;
      exit(1);
    }
  }
}


void PrimeCell_PL190_VIC::trans_read_data(PayLoad &pl){
      switch (pl.get_data_length()) {
      case 4: {
        uint32_t addr = pl.get_address();
          uint32_t data = read_word(addr);
          *(uint32_t*)(pl.get_data_ptr()) = data;
      } break;
      default:
        error() <<": b_transport method is not implemented for data_length = "
        <<pl.get_data_length() <<std::endl;
        assert(false);
      }
}

void PrimeCell_PL190_VIC::trans_write_data(PayLoad &pl){
      switch (pl.get_data_length()) {
      case 4: {
        uint32_t addr = pl.get_address();
          uint32_t data = *(uint32_t*)(pl.get_data_ptr());
          write_word(addr,data);
        } break;
      default:
        error() <<": b_transport method is not implemented for data_length = "
        <<pl.get_data_length() <<std::endl;
        assert(false);
      }
}

} // namespace simsoc
