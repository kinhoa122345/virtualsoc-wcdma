//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef PRIMECELL_VIC_PL190_HPP
#define PRIMECELL_VIC_PL190_HPP

/*
 * TLM Model for Daisy chain of ARM PrimeCell PL190 Vectored Interrupt Controller (VIC)
 * Specification is available for free on the ARM website:
 * http://infocenter.arm.com/help/topic/com.arm.doc.ddi0181e/DDI0181.pdf
 */

#include <stack>
#include <vector>
#include "libsimsoc/interfaces/tlm.hpp"
#include "libsimsoc/interfaces/tlm_signal.hpp"
#include "libsimsoc/module.hpp"

namespace simsoc {

// forward declaration
class ARM_Processor;
class PrimeCell_PL190_VIC_chain;

class PrimeCell_PL190_VIC: public Module,
                           public RW_Target {
public:
  static const uint32_t IRQ_STATUS_ADDR = 0x0;
  static const uint32_t FIQ_STATUS_ADDR = 0x4;
  static const uint32_t RAW_INT_ADDR = 0x8;
  static const uint32_t INT_SELECT_ADDR = 0xC;
  static const uint32_t INT_ENABLE_ADDR = 0x10;
  static const uint32_t INT_EN_CLEAR_ADDR = 0x14;
  static const uint32_t INT_SOFT_ADDR = 0x18;
  static const uint32_t INT_SOFT_CLEAR_ADDR = 0x1C;
  static const uint32_t INT_PROTECT_ADDR = 0x20;

  static const uint32_t CURRENT_ISR_ADDR = 0x30;
  static const uint32_t DEFAULT_VECT_ADDR = 0x34;
  static const uint32_t VECT_ADDR = 0x100;
  static const uint32_t LAST_VECT_ADDR = 0x13C;
  static const uint32_t VECT_CNTL = 0x200;
  static const uint32_t LAST_VECT_CNTL = 0x23C;

  static const uint32_t FIRST_ID_REG = 0xFE0;
  static const uint32_t LAST_ID_REG = 0xFFC;

  static const uint32_t ITCR = 0x300;	//VIC test control register. from linux source code include/asm-arm/arch-spearplus/platform.h

  static const size_t LOWEST_PRIORITY = 16;
  static const size_t HIGHEST_PRIORITY = 0;

  static const int IRQ_ENABLE_SHIFT = 5; // shift to access the enable bit

  RW_TargetPort rw_port;
  PrimeCell_PL190_VIC(sc_core::sc_module_name name, PrimeCell_PL190_VIC_chain * i);
  ~PrimeCell_PL190_VIC();

  // the function called by devices to assert (s=true) or clear an interrupt line
  void signal_interrupt(const size_t line, const bool s);

  //   void reset();
  void set_daisy_chain(PrimeCell_PL190_VIC * next) {daisy_chain = next;};

  // TLM read writes
  uint32_t read_word(uint32_t addr);
  void write_word(uint32_t addr, uint32_t data);

  void trans_read_data(PayLoad &pl);
  void trans_write_data(PayLoad &pl);


protected:
  PrimeCell_PL190_VIC_chain * initiator; // pointer to the parent interrupt initiator
  PrimeCell_PL190_VIC * daisy_chain;    // pointer to the next VIC of higher priority

  // values on input signals
  uint32_t source_status;
  bool chained_irq;
  uint32_t chained_addr;
  bool chained_fiq;

  // VIC registers
  uint32_t irq_status() const; // VICIRQSTATUS read-only, status of the IRQ interrupts
  uint32_t fiq_status() const; // VICFIQSTATUS read-only, status of the FIQ interrupts
  uint32_t raw_status() const; // VICRAWINTR read-only, status of the raw interrupts
  uint32_t select; // VICINTSELECT  RW, tells whether IRQ or FIQ for each line/bit
  uint32_t enabled; // VICINTENABLE RW, the corresponding line is enabled or not
  // VICINTENCLEAR WO, the corresponding line is cleared; no value stored
  uint32_t soft_it; // VICOSFTINT RW the corresponding line is soft it
  // VICSOFTINTCLEAR WO the corresponding line is soft it; no value stored
  bool protection; //VICPROTECTION  RW protects the enable
  uint32_t current_isr; // VICVECTADDR RW. The ISR address of the active interrupt
  uint32_t default_isr; // VICDEFVECTADDR RW. The default ISR address
  std::vector<uint32_t> vi_addresses; // RW contains the 16 vectored ISR addresses
  std::vector<uint32_t> vi_sourceids; // bit mask corresponding to the source of the 16 control registers
  std::vector<bool> vi_enablebits; // enabled bit of the 16 control registers

  uint8_t current_isr_priority; // priority associated with the current isr
  // current_isr_priority < LOWEST_PRIORITY => vectored interrupt
  static const size_t NONVECTORED_SERVED = LOWEST_PRIORITY;
  static const size_t CHAINED_SERVED = LOWEST_PRIORITY+1;
  static const size_t NOTHING_SERVED = LOWEST_PRIORITY+2;

  // the hardware priority register.
  // (likely an 18-bits register on the real hardware, but a stack is more convenient for modeling)
  std::stack<uint8_t> served_priorities;

  // method called by the previous VIC on the daisy chain
  void set_chained_irq(bool value, uint32_t addr);
  void set_chained_fiq(bool value);

  void compute_irq();
  void compute_fiq();
};

class PrimeCell_PL190_VIC_chain: public Module,
                                 public SignalMultiTarget<bool> {
public:

  bool strict;

  std::vector<SignalMultiTargetPort<bool> > in_ports; // the receiving ports
  SignalInitiatorPort<bool> fiq_port; // the port to signal fiqs
  SignalInitiatorPort<bool> irq_port; // the port to signal irqs

  PrimeCell_PL190_VIC_chain(sc_core::sc_module_name name,
                            const int nb_vic,
                            const ARM_Processor *master=NULL);
  // how many VIC's are chained together . 2 for the spearplus
  // the number of VICS determines the number of ports - 32 per VIC
  ~PrimeCell_PL190_VIC_chain();

  void signal(bool b, size_t n);

  PrimeCell_PL190_VIC * operator[](const int i) const {
    return vic_chain[i];
  }

private:
  std::vector<PrimeCell_PL190_VIC*> vic_chain; // the VIC's daisy chain
  friend void PrimeCell_PL190_VIC::write_word(uint32_t, uint32_t);
  friend uint32_t PrimeCell_PL190_VIC::read_word(uint32_t);
  const ARM_Processor *proc;
  bool user_mode() const;
};

} // namespace simsoc

#endif // PRIMECELL_VIC_PL190_HPP
