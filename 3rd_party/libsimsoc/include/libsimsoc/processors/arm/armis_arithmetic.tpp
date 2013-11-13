//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "libsimsoc/display.hpp"
#include "libsimsoc/bitwise_operator.hpp"
#include "libsimsoc/processors/arm/arm_processor.hpp"

namespace simsoc {

/******************************************************************************/

template <class op>
ARM_NumericIS<op>::ARM_NumericIS(ARM_Condition c, bool s_, uint8_t d, uint8_t n,
                                 uint8_t sa, uint8_t z, uint8_t m):
  ARM_DPI_ShiftImm(c,sa,z,m), s(s_), Rd(d), Rn(n) {}

template <class op>
uint32_t ARM_NumericIS<op>::computeShift(ARM_Processor &proc, uint32_t m) {
  switch (shift) {
  case LSL:
    return valueLSL(m,shift_amount);
  case LSR:
    return valueLSR(m,shift_amount);
  case ASR:
    return valueASR(m,shift_amount);
  case ROR:
    return valueROR(m,shift_amount);
  case RRX:
    return valueRRX(m,proc.cpu.cpsr.c);
  }
  UNREACHABLE;
  return 0;
}

template <class op>
void ARM_NumericIS<op>::exec(ARM_Processor &proc) {
  if (conditionPassed(proc.cpu.cpsr,cond)) {
    uint32_t a = proc.cpu.regs[Rn];
    uint32_t m = proc.cpu.regs[Rm];
    uint32_t b = computeShift(proc,m);
    if (Rd==ARM_CPU::PC) {
      proc.cpu.regs[ARM_CPU::PC] = op::result(a,b,proc.cpu.cpsr.c) + 4;
      if (s)
        proc.spsr_to_cpsr();
    } else {
      proc.cpu.regs[Rd] = op::result(a,b,proc.cpu.cpsr.c);
      if (s){
        proc.cpu.cpsr.n = proc.cpu.regs[Rd]&(1<<31);
        proc.cpu.cpsr.z = !proc.cpu.regs[Rd];
        op::updateCV(proc.cpu.cpsr,a,b,proc.cpu.regs[Rd]);
      }
    }
  }
  proc.cpu.regs[ARM_CPU::PC] += 4;
}

template <class op>
std::ostream& ARM_NumericIS<op>::display(std::ostream& os) const {
  os <<op::opcode <<cond <<(s? "S":"") <<'\t'
     <<(ARM_AsmId) Rd <<", " <<(ARM_AsmId) Rn <<", "
     <<(ARM_AsmId) Rm;
  if (shift_amount!=0 || shift!=LSL) {
    os <<", " <<shift;
    if (shift!=RRX)
      os <<" #" <<(int) shift_amount;
  }
  return os;
}

/******************************************************************************/

template <class op>
ARM_NumericRS<op>::ARM_NumericRS(ARM_Condition c, bool s_, uint8_t d, uint8_t n,
                                 uint8_t sa, uint8_t z, uint8_t m):
  ARM_DPI_ShiftReg(c,sa,z,m), s(s_), Rd(d), Rn(n) {}

template <class op>
uint32_t ARM_NumericRS<op>::computeShift(ARM_Processor &proc, uint32_t m) {
  uint8_t sa = proc.cpu.regs[Rs];
  switch (shift) {
  case LSL:
    return valueLSL(m,sa);
  case LSR:
    return valueLSR(m,sa);
  case ASR:
    return valueASR(m,sa);
  case ROR:
    return valueROR(m,sa);
  case RRX:
    UNREACHABLE;
  }
  UNREACHABLE;
  return 0;
}

template <class op>
void ARM_NumericRS<op>::exec(ARM_Processor &proc) {
  if (conditionPassed(proc.cpu.cpsr,cond)) {
    uint32_t a = proc.cpu.regs[Rn];
    uint32_t b = computeShift(proc,proc.cpu.regs[Rm]);
    proc.cpu.regs[Rd] = op::result(a,b,proc.cpu.cpsr.c);
    if (s){
      proc.cpu.cpsr.n = proc.cpu.regs[Rd]&(1<<31);
      proc.cpu.cpsr.z = !proc.cpu.regs[Rd];
      op::updateCV(proc.cpu.cpsr,a,b,proc.cpu.regs[Rd]);
    }
  }
  proc.cpu.regs[ARM_CPU::PC] += 4;
}

template <class op>
std::ostream& ARM_NumericRS<op>::display(std::ostream& os) const {
  return os <<op::opcode <<cond <<(s? "S":"") <<'\t'
            <<(ARM_AsmId) Rd <<", " <<(ARM_AsmId) Rn <<", "
            <<(ARM_AsmId) Rm <<", " <<shift <<' ' <<(ARM_AsmId) Rs;
}

/******************************************************************************/

template <class op>
ARM_NumericImm<op>::ARM_NumericImm(ARM_Condition c, bool s_, uint8_t d, uint8_t n,
                                   uint8_t ra, uint8_t i):
  ARM_DPI_Imm(c,ra,i), s(s_), Rd(d), Rn(n) {}

template <class op>
void ARM_NumericImm<op>::exec(ARM_Processor &proc) {
  if (conditionPassed(proc.cpu.cpsr,cond)) {
    uint32_t a = proc.cpu.regs[Rn];
    uint32_t b = rotateRight(immed,rotate_amount);
    if (Rd==ARM_CPU::PC) {
      proc.cpu.regs[ARM_CPU::PC] = op::result(a,b,proc.cpu.cpsr.c) + 4;
      if (s)
        proc.spsr_to_cpsr();
    } else {
      proc.cpu.regs[Rd] = op::result(a,b,proc.cpu.cpsr.c);
      if (s){
        proc.cpu.cpsr.n = proc.cpu.regs[Rd]&(1<<31);
        proc.cpu.cpsr.z = !proc.cpu.regs[Rd];
        op::updateCV(proc.cpu.cpsr,a,b,proc.cpu.regs[Rd]);
      }
    }
  }
  proc.cpu.regs[ARM_CPU::PC] += 4;
}

template <class op>
std::ostream& ARM_NumericImm<op>::display(std::ostream& os) const {
  uint32_t i = rotateRight(immed,rotate_amount);
  return os <<op::opcode <<cond <<(s? "S":"") <<'\t'
            <<(ARM_AsmId) Rd <<", " <<(ARM_AsmId) Rn
            <<", #" <<std::dec <<i <<"\t; " <<std::hex <<i;
}

/******************************************************************************/

template <class op>
ARM_BooleanIS<op>::ARM_BooleanIS(ARM_Condition c, bool s_, uint8_t d, uint8_t n,
                                 uint8_t sa, uint8_t z, uint8_t m):
  ARM_DPI_ShiftImm(c,sa,z,m), s(s_), Rd(d), Rn(n) {}

template <class op>
uint32_t ARM_BooleanIS<op>::computeShift(ARM_Processor &proc, uint32_t m) {
  switch (shift) {
  case LSL:
    if (s && (Rd!=ARM_CPU::PC))
      carryLSL(proc.cpu.cpsr,m,shift_amount);
    return valueLSL(m,shift_amount);
  case LSR:
    if (s && (Rd!=ARM_CPU::PC))
      carryLSR(proc.cpu.cpsr,m,shift_amount);
    return valueLSR(m,shift_amount);
  case ASR:
    if (s && (Rd!=ARM_CPU::PC))
      carryASR(proc.cpu.cpsr,m,shift_amount);
    return valueASR(m,shift_amount);
  case ROR:
    if (s && (Rd!=ARM_CPU::PC))
      carryROR(proc.cpu.cpsr,m,shift_amount);
    return valueROR(m,shift_amount);
  case RRX:
    {
      bool tmp = proc.cpu.cpsr.c;
      if (s && (Rd!=ARM_CPU::PC))
        carryRRX(proc.cpu.cpsr,m);
      return valueRRX(m,tmp);
    }
  }
  UNREACHABLE;
  return 0;
}

template <class op>
void ARM_BooleanIS<op>::exec(ARM_Processor &proc) {
  if (conditionPassed(proc.cpu.cpsr,cond)) {
    uint32_t a = proc.cpu.regs[Rn];
    uint32_t m = proc.cpu.regs[Rm];
    uint32_t b = computeShift(proc,m);
    if (Rd==ARM_CPU::PC) {
      proc.cpu.regs[ARM_CPU::PC] = op::result(a,b,proc.cpu.cpsr.c) + 4;
      if (s)
        proc.spsr_to_cpsr();
    } else {
      proc.cpu.regs[Rd] = op::result(a,b,proc.cpu.cpsr.c);
      if (s){
        proc.cpu.cpsr.n = proc.cpu.regs[Rd]&(1<<31);
        proc.cpu.cpsr.z = !proc.cpu.regs[Rd];
      }
    }
  }
  proc.cpu.regs[ARM_CPU::PC] += 4;
}

template <class op>
std::ostream& ARM_BooleanIS<op>::display(std::ostream& os) const {
  os <<op::opcode <<cond <<(s? "S":"") <<'\t' <<(ARM_AsmId) Rd <<", " <<(ARM_AsmId) Rn <<", "
     <<(ARM_AsmId) Rm;
  if (shift_amount!=0 || shift!=LSL) {
    os <<", " <<shift;
    if (shift!=RRX)
      os <<" #" <<(int) shift_amount;
  }
  return os;
}

/******************************************************************************/

template <class op>
ARM_BooleanRS<op>::ARM_BooleanRS(ARM_Condition c, bool s_, uint8_t d, uint8_t n,
                                 uint8_t sa, uint8_t z, uint8_t m):
  ARM_DPI_ShiftReg(c,sa,z,m), s(s_), Rd(d), Rn(n) {}

template <class op>
uint32_t ARM_BooleanRS<op>::computeShift(ARM_Processor &proc, uint32_t m) {
  uint8_t sa = proc.cpu.regs[Rs];
  switch (shift) {
  case LSL:
    if (s)
      carryLSL(proc.cpu.cpsr,m,sa);
    return valueLSL(m,sa);
  case LSR:
    if (s)
      carryLSR(proc.cpu.cpsr,m,sa);
    return valueLSR(m,sa);
  case ASR:
    if (s)
      carryASR(proc.cpu.cpsr,m,sa);
    return valueASR(m,sa);
  case ROR:
    if (s)
      carryROR(proc.cpu.cpsr,m,sa);
    return valueROR(m,sa);
  case RRX:
    UNREACHABLE;
  }
  UNREACHABLE;
  return 0;
}

template <class op>
void ARM_BooleanRS<op>::exec(ARM_Processor &proc) {
  if (conditionPassed(proc.cpu.cpsr,cond)) {
    uint32_t a = proc.cpu.regs[Rn];
    uint32_t b = computeShift(proc,proc.cpu.regs[Rm]);
    proc.cpu.regs[Rd] = op::result(a,b,proc.cpu.cpsr.c);
    if (s){
      proc.cpu.cpsr.n = proc.cpu.regs[Rd]&(1<<31);
      proc.cpu.cpsr.z = !proc.cpu.regs[Rd];
    }
  }
  proc.cpu.regs[ARM_CPU::PC] += 4;
}

template <class op>
std::ostream& ARM_BooleanRS<op>::display(std::ostream& os) const {
  return os <<op::opcode <<cond <<(s? "S":"") <<'\t'
            <<(ARM_AsmId) Rd <<", " <<(ARM_AsmId) Rn <<", "
            <<(ARM_AsmId) Rm <<", " <<shift <<' ' <<(ARM_AsmId) Rs;
}

/******************************************************************************/

template <class op>
ARM_BooleanImm<op>::ARM_BooleanImm(ARM_Condition c, bool s_, uint8_t d, uint8_t n,
                                   uint8_t ra, uint8_t i):
  ARM_DPI_Imm(c,ra,i), s(s_), Rd(d), Rn(n) {}

template <class op>
void ARM_BooleanImm<op>::exec(ARM_Processor &proc) {
  if (conditionPassed(proc.cpu.cpsr,cond)) {
    uint32_t a = proc.cpu.regs[Rn];
    uint32_t b = rotateRight(immed,rotate_amount);
    if (s && (Rd!=ARM_CPU::PC) && rotate_amount)
      proc.cpu.cpsr.c = b&(1<<31);
    if (Rd==ARM_CPU::PC) {
      proc.cpu.regs[ARM_CPU::PC] = op::result(a,b,proc.cpu.cpsr.c) + 4;
      if (s)
        proc.spsr_to_cpsr();
    } else {
      proc.cpu.regs[Rd] = op::result(a,b,proc.cpu.cpsr.c);
      if (s){
        proc.cpu.cpsr.n = proc.cpu.regs[Rd]&(1<<31);
        proc.cpu.cpsr.z = !proc.cpu.regs[Rd];
      }
    }
  }
  proc.cpu.regs[ARM_CPU::PC] += 4;
}

template <class op>
std::ostream& ARM_BooleanImm<op>::display(std::ostream& os) const {
  uint32_t i = rotateRight(immed,rotate_amount);
  return os <<op::opcode <<cond <<(s? "S":"") <<'\t'
            <<(ARM_AsmId) Rd <<", " <<(ARM_AsmId) Rn
            <<", #" <<std::dec <<i <<"\t; " <<std::hex <<i;
}

/******************************************************************************/

template <class op>
ARM_CompareIS<op>::ARM_CompareIS(ARM_Condition c, uint8_t n,
                                 uint8_t sa, uint8_t z, uint8_t m):
  ARM_DPI_ShiftImm(c,sa,z,m), Rn(n) {}

template <class op>
void ARM_CompareIS<op>::exec(ARM_Processor &proc) {
  if (conditionPassed(proc.cpu.cpsr,cond)) {
    uint32_t a = proc.cpu.regs[Rn];
    uint32_t m = proc.cpu.regs[Rm];
    uint32_t b = 0;
    switch (shift) {
    case LSL: b = valueLSL(m,shift_amount); break;
    case LSR: b = valueLSR(m,shift_amount); break;
    case ASR: b = valueASR(m,shift_amount); break;
    case ROR: b = valueROR(m,shift_amount); break;
    case RRX: b = valueRRX(m,proc.cpu.cpsr.c); break;
    }
    uint32_t r = op::result(a,b);
    proc.cpu.cpsr.n = r&(1<<31);
    proc.cpu.cpsr.z = !r;
    op::updateCV(proc.cpu.cpsr,a,b,r);
  }
  proc.cpu.regs[ARM_CPU::PC] += 4;
}

template <class op>
std::ostream& ARM_CompareIS<op>::display(std::ostream& os) const {
  os <<op::opcode <<cond <<'\t' <<(ARM_AsmId) Rn <<", " <<(ARM_AsmId) Rm;
  if (shift_amount!=0 || shift!=LSL) {
    os <<", " <<shift;
    if (shift!=RRX)
      os <<" #" <<(int) shift_amount;
  }
  return os;
}

/******************************************************************************/

template <class op>
ARM_CompareRS<op>::ARM_CompareRS(ARM_Condition c, uint8_t n,
                                 uint8_t sa, uint8_t z, uint8_t m):
  ARM_DPI_ShiftReg(c,sa,z,m), Rn(n) {}

template <class op>
void ARM_CompareRS<op>::exec(ARM_Processor &proc) {
  if (conditionPassed(proc.cpu.cpsr,cond)) {
    uint32_t a = proc.cpu.regs[Rn];
    uint32_t b = 0;
    switch (shift) {
    case LSL: b = valueLSL(proc.cpu.regs[Rm],proc.cpu.regs[Rs]); break;
    case LSR: b = valueLSR(proc.cpu.regs[Rm],proc.cpu.regs[Rs]); break;
    case ASR: b = valueASR(proc.cpu.regs[Rm],proc.cpu.regs[Rs]); break;
    case ROR: b = valueROR(proc.cpu.regs[Rm],proc.cpu.regs[Rs]); break;
    case RRX: UNREACHABLE;
    }
    uint32_t r = op::result(a,b);
    proc.cpu.cpsr.n = r&(1<<31);
    proc.cpu.cpsr.z = !r;
    op::updateCV(proc.cpu.cpsr,a,b,r);
  }
  proc.cpu.regs[ARM_CPU::PC] += 4;
}

template <class op>
std::ostream& ARM_CompareRS<op>::display(std::ostream& os) const {
  return os <<op::opcode <<cond <<'\t' <<(ARM_AsmId) Rn <<", "
            <<(ARM_AsmId) Rm <<", " <<shift <<' ' <<(ARM_AsmId) Rs;
}

/******************************************************************************/

template <class op>
ARM_CompareImm<op>::ARM_CompareImm(ARM_Condition c, uint8_t n,
                                   uint8_t ra, uint8_t i):
  ARM_DPI_Imm(c,ra,i), Rn(n) {}

template <class op>
void ARM_CompareImm<op>::exec(ARM_Processor &proc) {
  if (conditionPassed(proc.cpu.cpsr,cond)) {
    uint32_t a = proc.cpu.regs[Rn];
    uint32_t b = rotateRight(immed,rotate_amount);
    uint32_t r = op::result(a,b);
    proc.cpu.cpsr.n = r&(1<<31);
    proc.cpu.cpsr.z = !r;
    op::updateCV(proc.cpu.cpsr,a,b,r);
  }
  proc.cpu.regs[ARM_CPU::PC] += 4;
}

template <class op>
std::ostream& ARM_CompareImm<op>::display(std::ostream& os) const {
  uint32_t i = rotateRight(immed,rotate_amount);
  return os <<op::opcode <<cond <<'\t' <<(ARM_AsmId) Rn
            <<", #" <<std::dec <<i <<"\t; " <<std::hex <<i;
}

/******************************************************************************/

template <class op>
ARM_TestIS<op>::ARM_TestIS(ARM_Condition c, uint8_t n,
                           uint8_t sa, uint8_t z, uint8_t m):
  ARM_DPI_ShiftImm(c,sa,z,m), Rn(n) {}

template <class op>
void ARM_TestIS<op>::exec(ARM_Processor &proc) {
  if (conditionPassed(proc.cpu.cpsr,cond)) {
    uint32_t a = proc.cpu.regs[Rn];
    uint32_t m = proc.cpu.regs[Rm];
    uint32_t b = 0;
    switch (shift) {
    case LSL:
      b = valueLSL(m,shift_amount);
      carryLSL(proc.cpu.cpsr,m,shift_amount);
      break;
    case LSR:
      b = valueLSR(m,shift_amount);
      carryLSR(proc.cpu.cpsr,m,shift_amount);
      break;
    case ASR:
      b = valueASR(m,shift_amount);
      carryASR(proc.cpu.cpsr,m,shift_amount);
      break;
    case ROR:
      b = valueROR(m,shift_amount);
      carryROR(proc.cpu.cpsr,m,shift_amount);
      break;
    case RRX:
      b = valueRRX(m,proc.cpu.cpsr.c);
      carryRRX(proc.cpu.cpsr,m);
      break;
    }
    uint32_t r = op::result(a,b);
    proc.cpu.cpsr.n = r&(1<<31);
    proc.cpu.cpsr.z = !r;
  }
  proc.cpu.regs[ARM_CPU::PC] += 4;
}

template <class op>
std::ostream& ARM_TestIS<op>::display(std::ostream& os) const {
  os <<op::opcode <<cond <<'\t' <<(ARM_AsmId) Rn <<", " <<(ARM_AsmId) Rm;
  if (shift_amount!=0 || shift!=LSL) {
    os <<", " <<shift;
    if (shift!=RRX)
      os <<" #" <<(int) shift_amount;
  }
  return os;
}

/******************************************************************************/

template <class op>
ARM_TestRS<op>::ARM_TestRS(ARM_Condition c, uint8_t n,
                           uint8_t sa, uint8_t z, uint8_t m):
  ARM_DPI_ShiftReg(c,sa,z,m), Rn(n) {}

template <class op>
void ARM_TestRS<op>::exec(ARM_Processor &proc) {
  if (conditionPassed(proc.cpu.cpsr,cond)) {
    uint32_t a = proc.cpu.regs[Rn];
    uint32_t b = 0;
    switch (shift) {
    case LSL:
      carryLSL(proc.cpu.cpsr,proc.cpu.regs[Rm],proc.cpu.regs[Rs]);
      b = valueLSL(proc.cpu.regs[Rm],proc.cpu.regs[Rs]);
      break;
    case LSR:
      carryLSR(proc.cpu.cpsr,proc.cpu.regs[Rm],proc.cpu.regs[Rs]);
      b = valueLSR(proc.cpu.regs[Rm],proc.cpu.regs[Rs]);
      break;
    case ASR:
      carryASR(proc.cpu.cpsr,proc.cpu.regs[Rm],proc.cpu.regs[Rs]);
      b = valueASR(proc.cpu.regs[Rm],proc.cpu.regs[Rs]);
      break;
    case ROR:
      carryROR(proc.cpu.cpsr,proc.cpu.regs[Rm],proc.cpu.regs[Rs]);
      b = valueROR(proc.cpu.regs[Rm],proc.cpu.regs[Rs]);
      break;
    case RRX: UNREACHABLE;
    }
    uint32_t r = op::result(a,b);
    proc.cpu.cpsr.n = r&(1<<31);
    proc.cpu.cpsr.z = !r;
  }
  proc.cpu.regs[ARM_CPU::PC] += 4;
}

template <class op>
std::ostream& ARM_TestRS<op>::display(std::ostream& os) const {
  return os <<op::opcode <<cond <<'\t' <<(ARM_AsmId) Rn <<", "
            <<(ARM_AsmId) Rm <<", " <<shift <<' ' <<(ARM_AsmId) Rs;
}

/******************************************************************************/

template <class op>
ARM_TestImm<op>::ARM_TestImm(ARM_Condition c, uint8_t n, uint8_t ra, uint8_t i):
  ARM_DPI_Imm(c,ra,i), Rn(n) {}

template <class op>
void ARM_TestImm<op>::exec(ARM_Processor &proc) {
  if (conditionPassed(proc.cpu.cpsr,cond)) {
    uint32_t a = proc.cpu.regs[Rn];
    uint32_t b = rotateRight(immed,rotate_amount);
    uint32_t r = op::result(a,b);
    proc.cpu.cpsr.n = r&(1<<31);
    proc.cpu.cpsr.z = !r;
    if (rotate_amount)
      proc.cpu.cpsr.c = b&(1<<31);
  }
  proc.cpu.regs[ARM_CPU::PC] += 4;
}

template <class op>
std::ostream& ARM_TestImm<op>::display(std::ostream& os) const {
  uint32_t i = rotateRight(immed,rotate_amount);
  return os <<op::opcode <<cond <<'\t' <<(ARM_AsmId) Rn
            <<", #" <<std::dec <<i <<"\t; " <<std::hex <<i;
}

/******************************************************************************/

template <class op>
ARM_MoveIS<op>::ARM_MoveIS(ARM_Condition c, bool s_, uint8_t d,
                           uint8_t sa, uint8_t z, uint8_t m):
  ARM_DPI_ShiftImm(c,sa,z,m), s(s_), Rd(d) {}

template <class op>
uint32_t ARM_MoveIS<op>::computeShift(ARM_Processor &proc, uint32_t m) {
  switch (shift) {
  case LSL:
    if (s && (Rd!=ARM_CPU::PC))
      carryLSL(proc.cpu.cpsr,m,shift_amount);
    return valueLSL(m,shift_amount);
  case LSR:
    if (s && (Rd!=ARM_CPU::PC))
      carryLSR(proc.cpu.cpsr,m,shift_amount);
    return valueLSR(m,shift_amount);
  case ASR:
    if (s && (Rd!=ARM_CPU::PC))
      carryASR(proc.cpu.cpsr,m,shift_amount);
    return valueASR(m,shift_amount);
  case ROR:
    if (s && (Rd!=ARM_CPU::PC))
      carryROR(proc.cpu.cpsr,m,shift_amount);
    return valueROR(m,shift_amount);
  case RRX:
    {
      bool tmp = proc.cpu.cpsr.c;
      if (s && (Rd!=ARM_CPU::PC))
        carryRRX(proc.cpu.cpsr,m);
      return valueRRX(m,tmp);
    }
  }
  UNREACHABLE;
  return 0;
}

template <class op>
void ARM_MoveIS<op>::exec(ARM_Processor &proc) {
  if (conditionPassed(proc.cpu.cpsr,cond)) {
    uint32_t m = proc.cpu.regs[Rm];
    uint32_t b = computeShift(proc,m);
    if (Rd==ARM_CPU::PC) {
      proc.cpu.regs[ARM_CPU::PC] = op::result(b) + 4;
      if (s)
        proc.spsr_to_cpsr();
    } else {
      proc.cpu.regs[Rd] = op::result(b);
      if (s){
        proc.cpu.cpsr.n = proc.cpu.regs[Rd]&(1<<31);
        proc.cpu.cpsr.z = !proc.cpu.regs[Rd];
      }
    }
  }
  proc.cpu.regs[ARM_CPU::PC] += 4;
}

template <class op>
std::ostream& ARM_MoveIS<op>::display(std::ostream& os) const {
  os <<op::opcode <<cond <<(s? "S":"") <<'\t' <<(ARM_AsmId) Rd <<", " <<(ARM_AsmId) Rm;
  if (shift_amount!=0 || shift!=LSL) {
    os <<", " <<shift;
    if (shift!=RRX)
      os <<" #" <<(int) shift_amount;
  }
  return os;
}

/******************************************************************************/

template <class op>
ARM_MoveRS<op>::ARM_MoveRS(ARM_Condition c, bool s_, uint8_t d,
                           uint8_t sa, uint8_t z, uint8_t m):
  ARM_DPI_ShiftReg(c,sa,z,m), s(s_), Rd(d) {}

template <class op>
uint32_t ARM_MoveRS<op>::computeShift(ARM_Processor &proc, uint32_t m) {
  uint8_t sa = proc.cpu.regs[Rs];
  switch (shift) {
  case LSL:
    if (s)
      carryLSL(proc.cpu.cpsr,m,sa);
    return valueLSL(m,sa);
  case LSR:
    if (s)
      carryLSR(proc.cpu.cpsr,m,sa);
    return valueLSR(m,sa);
  case ASR:
    if (s)
      carryASR(proc.cpu.cpsr,m,sa);
    return valueASR(m,sa);
  case ROR:
    if (s)
      carryROR(proc.cpu.cpsr,m,sa);
    return valueROR(m,sa);
  case RRX:
    UNREACHABLE;
  }
  UNREACHABLE;
  return 0;
}

template <class op>
void ARM_MoveRS<op>::exec(ARM_Processor &proc) {
  if (conditionPassed(proc.cpu.cpsr,cond)) {
    uint32_t b = computeShift(proc,proc.cpu.regs[Rm]);
    proc.cpu.regs[Rd] = op::result(b);
    if (s){
      proc.cpu.cpsr.n = proc.cpu.regs[Rd]&(1<<31);
      proc.cpu.cpsr.z = !proc.cpu.regs[Rd];
    }
  }
  proc.cpu.regs[ARM_CPU::PC] += 4;
}

template <class op>
std::ostream& ARM_MoveRS<op>::display(std::ostream& os) const {
  return os <<op::opcode <<cond <<(s? "S":"") <<'\t' <<(ARM_AsmId) Rd <<", "
            <<(ARM_AsmId) Rm <<", " <<shift <<' ' <<(ARM_AsmId) Rs;
}

/******************************************************************************/

template <class op>
ARM_MoveImm<op>::ARM_MoveImm(ARM_Condition c, bool s_, uint8_t d,
                             uint8_t ra, uint8_t i):
  ARM_DPI_Imm(c,ra,i), s(s_), Rd(d) {}

template <class op>
void ARM_MoveImm<op>::exec(ARM_Processor &proc) {
  if (conditionPassed(proc.cpu.cpsr,cond)) {
    uint32_t b = rotateRight(immed,rotate_amount);
    if (s && (Rd!=ARM_CPU::PC) && rotate_amount)
      proc.cpu.cpsr.c = b&(1<<31);
    if (Rd==ARM_CPU::PC) {
      proc.cpu.regs[ARM_CPU::PC] = op::result(b) + 4;
      if (s)
        proc.spsr_to_cpsr();
    } else {
      proc.cpu.regs[Rd] = op::result(b);
      if (s){
        proc.cpu.cpsr.n = proc.cpu.regs[Rd]&(1<<31);
        proc.cpu.cpsr.z = !proc.cpu.regs[Rd];
      }
    }
  }
  proc.cpu.regs[ARM_CPU::PC] += 4;
}

template <class op>
std::ostream& ARM_MoveImm<op>::display(std::ostream& os) const {
  uint32_t i = rotateRight(immed,rotate_amount);
  return os <<op::opcode <<cond <<(s? "S":"") <<'\t' <<(ARM_AsmId) Rd
            <<", #" <<std::dec <<i <<"\t; " <<std::hex <<i;
}

/******************************************************************************/

template <class op>
void ARM_longmult<op>::exec(ARM_Processor &proc) {
  if (conditionPassed(proc.cpu.cpsr,cond)) {
    op::compute(proc.cpu.regs[RdHi],proc.cpu.regs[RdLo],
                proc.cpu.regs[Rm],proc.cpu.regs[Rs]);
    if (s) {
      proc.cpu.cpsr.n = proc.cpu.regs[RdHi]&(1<<31);
      proc.cpu.cpsr.z = !proc.cpu.regs[RdHi] && !proc.cpu.regs[RdLo];
    }
  }
  proc.cpu.regs[ARM_CPU::PC] += 4;
}

template <class op>
std::ostream& ARM_longmult<op>::display(std::ostream& os) const {
  return os <<op::name() <<cond <<(s? "S":"") <<'\t' <<(ARM_AsmId) RdHi <<", "
            <<(ARM_AsmId) RdLo <<", " <<(ARM_AsmId) Rm <<", " <<(ARM_AsmId) Rs;
}

} // namespace simsoc
