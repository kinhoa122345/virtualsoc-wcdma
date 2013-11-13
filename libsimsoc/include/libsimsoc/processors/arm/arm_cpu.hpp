//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef ARM_CPU_HPP
#define ARM_CPU_HPP

#include <iostream>
#include <systemc>
#include <libsimsoc/processors/arm/arm_status_register.hpp>
#include <libsimsoc/display.hpp>

namespace simsoc {

  // special types to display general purpose register
  struct ARM_AsmId: Printable {
    uint8_t id;
    ARM_AsmId(uint8_t n): id(n) {}
    std::ostream& display(std::ostream& os) const;
  };

  class ARM_Processor;

  class ARM_CPU: public Printable {
  public:
    static const uint8_t PC = 15;
    static const uint8_t LR = 14;
    static const uint8_t SP = 13;
    static const uint8_t IP = 12;
    static const uint8_t FP = 11;
    static const uint8_t SL = 10;

    ARM_CPU(ARM_Processor *proc);

    void set_mode_internal(ARM_Mode new_mode);
    uint32_t& user_regs(uint8_t n);
    void spsr_to_cpsr_internal();
    void set_thumb_mode();
    void unset_thumb_mode();

    // back-link, used only by display functions
    ARM_Processor *const proc;

    // Registers which are visible in the current mode
    ARM_StatusRegister cpsr;    // Current Program Status Register
    uint32_t regs[16];

    // Banked registers
    uint32_t banked_LRs[6]; //FIQ-SYSTEM
    uint32_t banked_SPs[6]; //FIQ-SYSTEM
    uint32_t banked_FIQ_8_12[5]; //FIQ
    uint32_t banked_USR_8_12[5]; // for all modes excepted FIQ
    ARM_StatusRegister banked_spsr[5]; // FIQ, IRQ, ABT, UND and SVC

    ARM_StatusRegister& spsr();
    std::ostream& display(std::ostream& os) const;
  };

} // namespace simsoc

#endif //ARM_CPU_HPP
