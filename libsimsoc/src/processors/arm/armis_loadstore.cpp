//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "armis_loadstore.hpp"
#include "libsimsoc/display.hpp"

using namespace std;

namespace simsoc {

/******************************************************************************/

void ARM_ldr::doAccess(ARM_Processor &proc, uint8_t Rd, uint32_t addr) {
  if (Rd==ARM_CPU::PC) {
    uint32_t value = rotateRight(proc.mmu.read_word(addr), 8*(addr&3));
    switch (value&3) {
    case 0: // 00
      proc.cpu.regs[ARM_CPU::PC] = value+4; break;
    case 2: // 10
      proc.error() <<"unpredictable branching to a non-aligned address" <<endl;
      exit(5);
    case 1: // 01
    case 3: // 11
      proc.cpu.regs[ARM_CPU::PC] = value&~1;
      proc.cpu.set_thumb_mode();
    }
  } else {
    if (addr&3) {
      proc.cpu.regs[Rd] = rotateRight(proc.mmu.read_word(addr),8*(addr&3));
    } else
      proc.cpu.regs[Rd] = proc.mmu.read_word(addr);
  }
}

void ARM_ldrb::doAccess(ARM_Processor &proc, uint8_t Rd, uint32_t addr) {
  proc.cpu.regs[Rd] = proc.mmu.read_byte(addr);
}

void ARM_str::doAccess(ARM_Processor &proc, uint8_t Rd, uint32_t addr) {
  proc.mmu.write_word(addr&~3,proc.cpu.regs[Rd]);
}

void ARM_strb::doAccess(ARM_Processor &proc, uint8_t Rd, uint32_t addr) {
  proc.mmu.write_byte(addr,proc.cpu.regs[Rd]);
}

void ARM_ldrt::doAccess(ARM_Processor &proc, uint8_t Rd, uint32_t addr) {
  //TODO("LDRT instruction");
  if(!proc.mmu.user_mode){
    proc.mmu.user_mode = true;
    if(addr&3){
      proc.cpu.regs[Rd] = rotateRight(proc.mmu.read_word(addr),8*(addr&3));
    }else
      proc.cpu.regs[Rd] = proc.mmu.read_word(addr);
    proc.mmu.user_mode = false;
  }else{
    if(addr&3){
      proc.cpu.regs[Rd] = rotateRight(proc.mmu.read_word(addr),8*(addr&3));
    }else
      proc.cpu.regs[Rd] = proc.mmu.read_word(addr);
  }
}

void ARM_ldrbt::doAccess(ARM_Processor &proc, uint8_t Rd, uint32_t addr) {
  //TODO("LDRBT instruction");
  if(!proc.mmu.user_mode){
    proc.mmu.user_mode = true;
    proc.cpu.regs[Rd] = proc.mmu.read_byte(addr);
    proc.mmu.user_mode = false;
  }else{
    proc.cpu.regs[Rd] = proc.mmu.read_byte(addr);
  }
}

void ARM_strt::doAccess(ARM_Processor &proc, uint8_t Rd, uint32_t addr) {
  if (!proc.mmu.user_mode){
    proc.mmu.user_mode=true;
    proc.mmu.write_word(addr&~3,proc.cpu.regs[Rd]);
    proc.mmu.user_mode=false;
  } else
    proc.mmu.write_word(addr&~3,proc.cpu.regs[Rd]);
}

void ARM_strbt::doAccess(ARM_Processor &proc, uint8_t Rd, uint32_t addr) {
  if (!proc.mmu.user_mode){
    proc.mmu.user_mode=true;
    proc.mmu.write_byte(addr,proc.cpu.regs[Rd]);
    proc.mmu.user_mode=false;
  } else
    proc.mmu.write_byte(addr,proc.cpu.regs[Rd]);
}

/******************************************************************************/

void ARM_ldrh::doAccess(ARM_Processor &proc, uint8_t Rd, uint32_t addr) {
  // Prior to ARMv6, if the memory address is not halfword aligned,
  // the data read from memory is UNPREDICTABLE.
  if (addr&1) {
    // However, SPEAr's Linux do it, so we just generate a warning
    proc.warning() <<"half read access at an odd address (UNPREDICTABLE)\n";
  }
  proc.cpu.regs[Rd] = proc.mmu.read_half(addr);
}

void ARM_ldrsb::doAccess(ARM_Processor &proc, uint8_t Rd, uint32_t addr) {
  proc.cpu.regs[Rd] = (int8_t) proc.mmu.read_byte(addr);
}

void ARM_ldrsh::doAccess(ARM_Processor &proc, uint8_t Rd, uint32_t addr) {
  // Prior to ARMv6, if the memory address is not halfword aligned,
  // the data read from memory is UNPREDICTABLE.
  if (addr&1) {
    // However, SPEAr's Linux do it, so we just generate a warning
    proc.warning() <<"half read access at an odd address (UNPREDICTABLE)\n";
  }
  proc.cpu.regs[Rd] = (int16_t) proc.mmu.read_half(addr);
}

void ARM_strh::doAccess(ARM_Processor &proc, uint8_t Rd, uint32_t addr) {
  // Prior to ARMv6, if the memory address is not halfword aligned,
  // the data written to memory is UNPREDICTABLE.
  if (addr&1) {
    // However, SPEAr's Linux do it, so we just generate a warning
    proc.warning() <<"half write access at an odd address (UNPREDICTABLE)\n";
  }
  proc.mmu.write_half(addr&~1,proc.cpu.regs[Rd]);
}

void ARM_ldrd::doAccess(ARM_Processor &proc, uint8_t Rd, uint32_t addr) {
  // FIXME: check alignment according to ARMv5 rules
  proc.cpu.regs[Rd] = proc.mmu.read_word(addr);
  proc.cpu.regs[Rd+1] = proc.mmu.read_word(addr+4);
}

void ARM_strd::doAccess(ARM_Processor &proc, uint8_t Rd, uint32_t addr) {
  // FIXME: check alignment according to ARMv5 rules
  proc.mmu.write_word(addr,proc.cpu.regs[Rd]);
  proc.mmu.write_word(addr+4,proc.cpu.regs[Rd+1]);
}

/******************************************************************************/

ostream& ARM_lsm::display(ostream& os) const {
  os <<opname() <<cond <<suffix() <<" \t" <<(ARM_AsmId) Rn <<(w?"!, {":", {");
  for (uint8_t i=0; i<16; ++i)
    if (registers&(1<<i)) {
      os <<(ARM_AsmId) i;
      if (registers>>(i+1))
        os <<',';
      else
        break;
    }
  return os <<(special()? "}^": "}");
}

void ARM_lsm::compute_addresses(ARM_Processor &proc,
                                uint32_t& start, uint32_t& end, uint32_t& new_Rn) {
  uint32_t Rn_val = proc.cpu.regs[Rn]&~3;
  switch (am) {
  case IA:
    start = Rn_val;
    end = Rn_val + nb_reg*4 - 4;
    new_Rn = w? Rn_val + nb_reg*4: Rn_val;
    break;
  case IB:
    start = Rn_val+4;
    end = Rn_val+nb_reg*4;
    new_Rn = w? end: Rn_val;
    break;
  case DA:
    start = Rn_val - nb_reg*4 + 4;
    end = Rn_val;
    new_Rn = w? Rn_val - nb_reg*4: Rn_val;
    break;
  case DB:
    start = Rn_val - nb_reg*4;
    end = Rn_val - 4;
    new_Rn = w? start: Rn_val;
    break;
  default:
    UNREACHABLE;
  }
}

void ARM_lsm::update_Rn_offset(ARM_Processor &proc)
{
  uint32_t Rn_val = proc.cpu.regs[Rn]&~3;
  switch (am) {
  case IA:
    proc.cpu.regs[Rn] = Rn_val + nb_reg*4;
    break;
  case IB:
    proc.cpu.regs[Rn] = Rn_val+nb_reg*4;
    break;
  case DA:
    proc.cpu.regs[Rn] = Rn_val - nb_reg*4;
    break;
  case DB:
    proc.cpu.regs[Rn] = Rn_val - nb_reg*4;
    break;
  default:
    UNREACHABLE;
  }
}

/******************************************************************************/

const char * ARM_ldm::suffix() const {
  switch (am) {
  case DA: return (Rn==ARM_CPU::SP)? "FA": "DA";
  case IA: return (Rn==ARM_CPU::SP)? "FD": "IA";
  case DB: return (Rn==ARM_CPU::SP)? "EA": "DB";
  case IB: return (Rn==ARM_CPU::SP)? "ED": "IB";
  }
  UNREACHABLE;
  return "";
}

void ARM_ldm::exec(ARM_Processor &proc) {
  if (conditionPassed(proc.cpu.cpsr,cond)) {
    uint32_t addr=0;
    uint32_t end_addr=0;
    uint32_t new_Rn=0;
    compute_addresses(proc,addr,end_addr,new_Rn);
    for (int i = 0; i<ARM_CPU::PC; ++i)
      if (registers&(1<<i)) {
        proc.cpu.regs[i] = proc.mmu.read_word(addr);
        addr += 4;
      }
    if (registers&(1<<ARM_CPU::PC)) {
      uint32_t value = proc.mmu.read_word(addr);
      switch (value&3) {
      case 0: // 00
        proc.cpu.regs[ARM_CPU::PC] = value+4; break;
      case 2: // 10
        proc.error() <<"unpredictable branching to a non-aligned address.";
        exit(5);
      case 1: // 01
      case 3: // 11
        proc.cpu.regs[ARM_CPU::PC] = value&~1;
        // TODO("Thumb mode");
        proc.cpu.set_thumb_mode();
      }
      addr += 4;
    }
    if (end_addr!=addr-4)
      UNREACHABLE;
    if (w)
      update_Rn_offset(proc);
  }
  proc.cpu.regs[ARM_CPU::PC] += 4;
}

void ARM_ldm_2::exec(ARM_Processor &proc) {
  if (conditionPassed(proc.cpu.cpsr,cond)) {
    uint32_t addr=0;
    uint32_t end_addr=0;
    uint32_t new_Rn=0;
    compute_addresses(proc,addr,end_addr,new_Rn);
    for (int i = 0; i<ARM_CPU::PC; ++i)
      if (registers&(1<<i)) {
        proc.cpu.user_regs(i) = proc.mmu.read_word(addr);
        addr += 4;
      }
    if (end_addr!=addr-4)
      UNREACHABLE;
  }
  proc.cpu.regs[ARM_CPU::PC] += 4;
}

void ARM_ldm_3::exec(ARM_Processor &proc) {
  if (conditionPassed(proc.cpu.cpsr,cond)) {
    uint32_t addr=0;
    uint32_t end_addr=0;
    uint32_t new_Rn=0;
    compute_addresses(proc,addr,end_addr,new_Rn);
    for (int i = 0; i<ARM_CPU::PC; ++i)
      if (registers&(1<<i)) {
        proc.cpu.regs[i] = proc.mmu.read_word(addr);
        addr += 4;
      }
   if (w)
      update_Rn_offset(proc);
    proc.spsr_to_cpsr();
    uint32_t value = proc.mmu.read_word(addr);
    addr += 4;
    if (proc.cpu.cpsr.t == 1) {
      value = value&0xFFFFFFFE ;
      proc.cpu.set_thumb_mode();
      proc.cpu.regs[ARM_CPU::PC] = value+4;
    } else {
      if(value & 2){
         proc.error() <<"unpredictable branching to a non-aligned address" <<endl;
         exit(5);
       }
      value = value&0xFFFFFFFC;
      proc.cpu.regs[ARM_CPU::PC] = value+8;
    }
    if (end_addr!=addr-4)
      UNREACHABLE;
  } else
    proc.cpu.regs[ARM_CPU::PC] += 4;
}

/******************************************************************************/

const char * ARM_stm::suffix() const {
  switch (am) {
  case DA: return (Rn==ARM_CPU::SP)? "ED": "DA";
  case IA: return (Rn==ARM_CPU::SP)? "ED": "IA";
  case DB: return (Rn==ARM_CPU::SP)? "FD": "DB";
  case IB: return (Rn==ARM_CPU::SP)? "FA": "IB";
  }
  UNREACHABLE;
  return "";
}

void ARM_stm::exec(ARM_Processor &proc) {
  if (conditionPassed(proc.cpu.cpsr,cond)) {
    uint32_t addr=0;
    uint32_t end_addr=0;
    uint32_t new_Rn=0;
    compute_addresses(proc,addr,end_addr,new_Rn);
    for (int i = 0; i<16; ++i)
      if (registers&(1<<i)) {
        proc.mmu.write_word(addr,proc.cpu.regs[i]);
        addr += 4;
      }
    if (end_addr!=addr-4)
      UNREACHABLE;
    if (w)
      update_Rn_offset(proc);
  }
  proc.cpu.regs[ARM_CPU::PC] += 4;
}

void ARM_stm_2::exec(ARM_Processor &proc) {
  if (conditionPassed(proc.cpu.cpsr,cond)) {
    uint32_t addr=0;
    uint32_t end_addr=0;
    uint32_t new_Rn=0;
    compute_addresses(proc,addr,end_addr,new_Rn);
    for (int i = 0; i<16; ++i)
      if (registers&(1<<i)) {
        proc.mmu.write_word(addr,proc.cpu.user_regs(i));
        addr += 4;
      }
    if (end_addr!=addr-4)
      UNREACHABLE;
//    proc.cpu.regs[Rn] = new_Rn;
  }
  proc.cpu.regs[ARM_CPU::PC] += 4;
}

/******************************************************************************/

void ARM_swp::exec(ARM_Processor &proc) {
  if (conditionPassed(proc.cpu.cpsr,cond)) {
    const uint32_t addr = proc.cpu.regs[Rn];
    const uint32_t tmp = proc.cpu.regs[Rm];
    const uint32_t data = proc.mmu.read_word(addr);
    proc.cpu.regs[Rd] = data;
    proc.mmu.write_word(addr,tmp);
  }
  proc.cpu.regs[ARM_CPU::PC] += 4;
}

std::ostream& ARM_swp::display(std::ostream& os) const {
  return os <<"SWP" <<cond <<'\t' <<(ARM_AsmId) Rd <<", " <<(ARM_AsmId) Rm
            <<", " <<(ARM_AsmId) Rn;
}

void ARM_swpb::exec(ARM_Processor &proc) {
  if (conditionPassed(proc.cpu.cpsr,cond)) {
    const uint32_t addr = proc.cpu.regs[Rn];
    const uint32_t tmp = proc.cpu.regs[Rm];
    const uint32_t data = proc.mmu.read_byte(addr);
    proc.cpu.regs[Rd] = data;
    proc.mmu.write_byte(addr,tmp);
  }
  proc.cpu.regs[ARM_CPU::PC] += 4;
}

std::ostream& ARM_swpb::display(std::ostream& os) const {
  return os <<"SWP" <<cond <<"B\t" <<(ARM_AsmId) Rd <<", " <<(ARM_AsmId) Rm <<", "
            <<(ARM_AsmId) Rn;
}

/******************************************************************************/

std::ostream& ARM_pld_imm::display(std::ostream& os) const {
  return os <<"PLD\t["
            <<(ARM_AsmId) Rn <<(u? ", #+": ", #-") <<std::dec <<(int) immed <<']';
}

std::ostream& ARM_pld_reg::display(std::ostream& os) const {
  return os <<"PLD\t["
            <<(ARM_AsmId) Rn <<(u? ", +": ", -") <<(ARM_AsmId) Rm <<']';
}

std::ostream& ARM_pld_scrg::display(std::ostream& os) const {
  return os <<"PLD\t["
            <<(ARM_AsmId) Rn <<(u? ", +": ", -") <<(ARM_AsmId) Rm
            <<", " <<shift <<" #" <<(int) shift_imm
            <<']';
}

} // namespace simsoc
