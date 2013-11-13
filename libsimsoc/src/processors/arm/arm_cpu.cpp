//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "arm_cpu.hpp"
#include "libsimsoc/processors/arm/arm_processor.hpp"

using namespace std;
using namespace sc_core;

namespace simsoc {

ARM_CPU::ARM_CPU(ARM_Processor *p):
  proc(p),
  cpsr()
{
  for (unsigned n=0; n<15; ++n)
    regs[n] = 0;
  regs[PC] = 0x8;
  for (unsigned n=0; n<6; ++n) {
    banked_LRs[n] = 0;
    banked_SPs[n] = 0;
  }
  for (unsigned n=0; n<5; ++n) {
    banked_FIQ_8_12[n] = 0;
    banked_USR_8_12[n] = 0;
  }
}

void ARM_CPU::set_mode_internal(ARM_Mode new_mode) {
  switch (cpsr.mode) {

  case ARM_FIQ:
    switch (new_mode) {
    case ARM_FIQ: break;
    case ARM_IRQ:
    case ARM_ABT:
    case ARM_UND:
    case ARM_SVC:
      for (unsigned i = 0; i<5; ++i) {
        banked_FIQ_8_12[i] = regs[8+i];
        regs[8+i] = banked_USR_8_12[i];
      }
      banked_LRs[ARM_FIQ] = regs[LR];
      banked_SPs[ARM_FIQ] = regs[SP];
      regs[LR] = banked_LRs[new_mode];
      regs[SP] = banked_SPs[new_mode];
      break;
    case ARM_SYSTEM:
    case ARM_USER:
      for (unsigned i = 0; i<5; ++i) {
        banked_FIQ_8_12[i] = regs[8+i];
        regs[8+i] = banked_USR_8_12[i];
      }
      banked_LRs[ARM_FIQ] = regs[LR];
      banked_SPs[ARM_FIQ] = regs[SP];
      regs[LR] = banked_LRs[ARM_SYSTEM];
      regs[SP] = banked_SPs[ARM_SYSTEM];
      break;
    default:
      UNREACHABLE;
    }
    break;

  case ARM_IRQ:
  case ARM_ABT:
  case ARM_UND:
  case ARM_SVC:
    banked_LRs[cpsr.mode] = regs[LR];
    banked_SPs[cpsr.mode] = regs[SP];
    switch (new_mode) {
    case ARM_FIQ:
      for (unsigned i = 0; i<5; ++i) {
        banked_USR_8_12[i] = regs[8+i];
        regs[8+i] = banked_FIQ_8_12[i];
      }
      regs[LR] = banked_LRs[ARM_FIQ];
      regs[SP] = banked_SPs[ARM_FIQ];
      break;
    case ARM_IRQ:
    case ARM_ABT:
    case ARM_UND:
    case ARM_SVC:
      regs[LR] = banked_LRs[new_mode];
      regs[SP] = banked_SPs[new_mode];
      break;
    case ARM_SYSTEM:
    case ARM_USER:
      regs[LR] = banked_LRs[ARM_SYSTEM];
      regs[SP] = banked_SPs[ARM_SYSTEM];
      break;
    default:
      UNREACHABLE;
    }
    break;

  case ARM_SYSTEM:
  case ARM_USER:
    switch (new_mode) {
    case ARM_FIQ:
      for (unsigned i = 0; i<5; ++i) {
        banked_USR_8_12[i] = regs[8+i];
        regs[8+i] = banked_FIQ_8_12[i];
      }
      banked_LRs[ARM_SYSTEM] = regs[LR];
      banked_SPs[ARM_SYSTEM] = regs[SP];
      regs[LR] = banked_LRs[ARM_FIQ];
      regs[SP] = banked_SPs[ARM_FIQ];
      break;
    case ARM_IRQ:
    case ARM_ABT:
    case ARM_UND:
    case ARM_SVC:
      banked_LRs[ARM_SYSTEM] = regs[LR];
      banked_SPs[ARM_SYSTEM] = regs[SP];
      regs[LR] = banked_LRs[new_mode];
      regs[SP] = banked_SPs[new_mode];
      break;
    case ARM_SYSTEM:
    case ARM_USER:
      break;
    default:
      UNREACHABLE;
    }
    break;

  default:
    UNREACHABLE;
  }

  cpsr.mode = new_mode;
}

uint32_t& ARM_CPU::user_regs(uint8_t n) {
  if (n<8||n==PC)
    return regs[n];
  else if (n<SP)
    if (cpsr.mode==ARM_FIQ)
      return banked_USR_8_12[n-8];
    else
      return regs[n];
  else if (cpsr.mode<ARM_SYSTEM)
    if (n==SP)
      return banked_SPs[ARM_SYSTEM];
    else
      return banked_LRs[ARM_SYSTEM];
  else
    return regs[n];
}

void ARM_CPU::spsr_to_cpsr_internal() {
  const ARM_Mode old_mode = cpsr.mode;
  set_mode_internal(spsr().mode);
  cpsr = banked_spsr[old_mode];
  proc->instr_size = cpsr.t?2:4;
}

void ARM_CPU::set_thumb_mode() {
  if (cpsr.t)
    return;
  proc->info() <<"enter thumb mode" <<endl;
  cpsr.t = true;
  proc->instr_size = 2;
}

void ARM_CPU::unset_thumb_mode() {
  if (!cpsr.t)
    return;
  proc->info() <<"exit thumb mode" <<endl;
  cpsr.t = false;
  proc->instr_size = 4;
}

ARM_StatusRegister& ARM_CPU::spsr() {
  if (cpsr.mode==ARM_SYSTEM) {
    proc->error() <<"invalid access to spsr while in SYSTEM mode" <<endl;
    exit(4);
  } else if (cpsr.mode==ARM_USER) {
    proc->error() <<"invalid access to spsr while in USER mode" <<endl;
    exit(4);
  }
  return banked_spsr[cpsr.mode];
}

  ostream& ARM_AsmId::display(ostream& os) const {
    switch (id) {
    case simsoc::ARM_CPU::PC: return os << "pc";
    case simsoc::ARM_CPU::LR: return os << "lr";
    case simsoc::ARM_CPU::SP: return os << "sp";
    case simsoc::ARM_CPU::IP: return os << "ip";
    case simsoc::ARM_CPU::FP: return os << "fp";
    case simsoc::ARM_CPU::SL: return os << "sl";
    default: return os << 'r' <<dec <<(int) id;
    }
  }

  ostream& ARM_CPU::display(ostream &os) const {
    os <<"CPSR = " <<cpsr <<endl;
    for (unsigned n=0; n<12; n+=4)
      os <<dec <<simsoc::ARM_AsmId(n) <<" = " <<hex <<regs[n] <<", "
         <<dec <<simsoc::ARM_AsmId(n+1) <<" = " <<hex <<regs[n+1] <<", "
         <<dec <<simsoc::ARM_AsmId(n+2) <<" = " <<hex <<regs[n+2] <<", "
         <<dec <<simsoc::ARM_AsmId(n+3) <<" = " <<hex <<regs[n+3] <<endl;
    const uint32_t o = cpsr.t ? 4 : 8;
    os <<dec <<simsoc::ARM_AsmId(12) <<" = " <<hex <<regs[12] <<", "
       <<dec <<simsoc::ARM_AsmId(13) <<" = " <<hex <<regs[13] <<", "
       <<dec <<simsoc::ARM_AsmId(14) <<" = " <<hex <<regs[14] <<", "
       <<dec <<simsoc::ARM_AsmId(15) <<" = " <<hex <<regs[15]-o <<"+" <<dec <<o <<endl;
    return os;
  }

} // namespace simsoc
