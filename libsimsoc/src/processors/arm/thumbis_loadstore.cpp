//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "thumbis_loadstore.hpp"
#include "libsimsoc/processors/arm/arm_cpu.hpp"
#include "libsimsoc/processors/arm/arm_processor.hpp"
#include "libsimsoc/bitwise_operator.hpp"
#include "libsimsoc/display.hpp"
#include "libsimsoc/processors/arm/arm_thumb_pi.hpp"

using namespace std;

namespace simsoc {

/*****************************************************************/

THUMB_ldr1::THUMB_ldr1( uint8_t i, uint8_t n, uint8_t d):
  THUMB_Instruction(), immed(i), Rn(n), Rd(d) {}

void THUMB_ldr1::exec(ARM_Processor &proc){
  uint32_t addr = proc.cpu.regs[Rn] + immed;
  uint32_t data;
  if ((addr&3) == 0)
    data = proc.mmu.read_word(addr);
  else{
    proc.error() <<"unpredictable word access to a non-aligned address" <<endl;
    exit(5);
  }
  proc.cpu.regs[Rd] = data;
  proc.cpu.regs[ARM_CPU::PC] += 2;
}

std::ostream& THUMB_ldr1::display(std::ostream& os) const {
  return os <<"ldr\t" <<(ARM_AsmId) Rd <<", [" <<(ARM_AsmId) Rn <<", #" <<(int) immed <<']';
}

/*****************************************************************/

THUMB_ldr2::THUMB_ldr2( uint8_t m, uint8_t n, uint8_t d):
  THUMB_Instruction(), Rm(m), Rn(n), Rd(d) {}

void THUMB_ldr2::exec(ARM_Processor &proc){
  const uint32_t addr = proc.cpu.regs[Rm] + proc.cpu.regs[Rn];
  if ((addr&3) == 0) {
    proc.cpu.regs[Rd] = proc.mmu.read_word(addr);
    proc.cpu.regs[ARM_CPU::PC] += 2;
  } else {
    proc.error() <<"unpredictable word access to a non-aligned address" <<endl;
    exit(5);
  }
}

std::ostream& THUMB_ldr2::display(std::ostream& os) const {
  return os <<"ldr\t" <<(ARM_AsmId) Rd <<", [" <<(ARM_AsmId) Rn <<", " <<(ARM_AsmId) Rm <<']';
}

/****************************************************************/

THUMB_ldr3::THUMB_ldr3( uint8_t d, uint8_t i):
  THUMB_Instruction(), Rd(d), immed(i) {}

void THUMB_ldr3::exec(ARM_Processor &proc){
  uint32_t a = proc.cpu.regs[ARM_CPU::PC];
  uint32_t b = immed;
  uint32_t addr = (a&~3) + b*4;
  proc.cpu.regs[Rd] = proc.mmu.read_word(addr);
  proc.cpu.regs[ARM_CPU::PC] += 2;
}

std::ostream& THUMB_ldr3::display(std::ostream& os) const {
  return os <<"ldr\t" <<(ARM_AsmId) Rd <<", [pc, #" <<(int) immed*4 <<']';
}

/*****************************************************************/

THUMB_ldr4::THUMB_ldr4( uint8_t d, uint8_t i):
  THUMB_Instruction(), Rd(d), immed(i) {}

void THUMB_ldr4::exec(ARM_Processor &proc){
  uint32_t a = proc.cpu.regs[ARM_CPU::SP];
  uint32_t b = immed;
  uint32_t addr = a + b*4;
  uint32_t data;
  if ((addr&3) == 0)
    data = proc.mmu.read_word(addr);
  else{
    proc.error() <<"unpredictable word access to a non-aligned address" <<endl;
    exit(5);
  }
  proc.cpu.regs[Rd] = data;
  proc.cpu.regs[ARM_CPU::PC] += 2;
}

std::ostream& THUMB_ldr4::display(std::ostream& os) const {
  return os <<"ldr\t" <<(ARM_AsmId) Rd <<", [sp, #" <<(int) immed*4 <<']';
}

/*****************************************************************/

THUMB_ldrb1::THUMB_ldrb1( uint8_t i, uint8_t n, uint8_t d):
  THUMB_Instruction(), immed(i), Rn(n), Rd(d) {}

void THUMB_ldrb1::exec(ARM_Processor &proc){
  uint32_t a = proc.cpu.regs[Rn];
  uint32_t b = immed;
  uint32_t addr = a + b;
  proc.cpu.regs[Rd] = proc.mmu.read_byte(addr);
  proc.cpu.regs[ARM_CPU::PC] += 2;
}

std::ostream& THUMB_ldrb1::display(std::ostream& os) const {
  return os <<"ldrb\t" <<(ARM_AsmId) Rd <<", [" <<(ARM_AsmId) Rn <<", #" <<(int) immed <<']';
}

/*****************************************************************/

THUMB_ldrb2::THUMB_ldrb2( uint8_t m, uint8_t n, uint8_t d):
  THUMB_Instruction(), Rm(m), Rn(n), Rd(d) {}

void THUMB_ldrb2::exec(ARM_Processor &proc){
  uint32_t a = proc.cpu.regs[Rn];
  uint32_t b = proc.cpu.regs[Rm];
  uint32_t addr = a + b;
  proc.cpu.regs[Rd] = proc.mmu.read_byte(addr);
  proc.cpu.regs[ARM_CPU::PC] += 2;
}

std::ostream& THUMB_ldrb2::display(std::ostream& os) const {
  return os <<"ldrb\t" <<(ARM_AsmId) Rd <<", [" <<(ARM_AsmId) Rn <<", " <<(ARM_AsmId) Rm <<']';
}

/*****************************************************************/

THUMB_ldrh1::THUMB_ldrh1( uint8_t i, uint8_t n, uint8_t d):
  THUMB_Instruction(), immed(i), Rn(n), Rd(d) {}

void THUMB_ldrh1::exec(ARM_Processor &proc){
  uint32_t a = immed;
  uint32_t b = proc.cpu.regs[Rn];
  uint32_t addr = b + a*2;
  uint32_t data;
  if ((addr&1) == 0)
    data = proc.mmu.read_half(addr);
  else{
    proc.error() <<"unpredictable half_word access to a non-aligned address" <<endl;
    exit(5);
  }
  proc.cpu.regs[Rd] = data;
  proc.cpu.regs[ARM_CPU::PC] += 2;
}

std::ostream& THUMB_ldrh1::display(std::ostream& os) const {
  return os <<"ldrh\t" <<(ARM_AsmId) Rd <<", [" <<(ARM_AsmId) Rn <<", #" <<(int) immed*2 <<']';
}

/*****************************************************************/

THUMB_ldrh2::THUMB_ldrh2( uint8_t m, uint8_t n, uint8_t d):
  THUMB_Instruction(), Rm(m), Rn(n), Rd(d) {}

void THUMB_ldrh2::exec(ARM_Processor &proc){
  uint32_t a = proc.cpu.regs[Rm];
  uint32_t b = proc.cpu.regs[Rn];
  uint32_t addr = b + a;
  uint32_t data;
  if ((addr&1) == 0)
    data = proc.mmu.read_half(addr);
  else{
    proc.error() <<"unpredictable half_word access to a non-aligned address" <<endl;
    exit(5);
  }
  proc.cpu.regs[Rd] = data;
  proc.cpu.regs[ARM_CPU::PC] += 2;
}

std::ostream& THUMB_ldrh2::display(std::ostream& os) const {
  return os <<"ldrh\t" <<(ARM_AsmId) Rd <<", [" <<(ARM_AsmId) Rn <<", " <<(ARM_AsmId) Rm <<']';
}

/*****************************************************************/
THUMB_ldrsb::THUMB_ldrsb( uint8_t m, uint8_t n, uint8_t d):
  THUMB_Instruction(), Rm(m), Rn(n), Rd(d) {}

void THUMB_ldrsb::exec(ARM_Processor &proc){
  uint32_t a = proc.cpu.regs[Rm];
  uint32_t b = proc.cpu.regs[Rn];
  uint32_t addr = b + a;
  proc.cpu.regs[Rd] = (int32_t) (int8_t) proc.mmu.read_byte(addr);
  proc.cpu.regs[ARM_CPU::PC] += 2;
}

std::ostream& THUMB_ldrsb::display(std::ostream& os) const {
  return os <<"ldrsb\t" <<(ARM_AsmId) Rd <<", [" <<(ARM_AsmId) Rn <<", " <<(ARM_AsmId) Rm <<']';
}

/*****************************************************************/
THUMB_ldrsh::THUMB_ldrsh( uint8_t m, uint8_t n, uint8_t d):
  THUMB_Instruction(), Rm(m), Rn(n), Rd(d) {}

void THUMB_ldrsh::exec(ARM_Processor &proc){
  uint32_t a = proc.cpu.regs[Rm];
  uint32_t b = proc.cpu.regs[Rn];
  uint32_t addr = b + a;
  int16_t data;
  if ((addr&1) == 0)
    data = proc.mmu.read_half(addr);
  else{
    proc.error() <<"unpredictable half_word access to a non-aligned address" <<endl;
    exit(5);
  }
  proc.cpu.regs[Rd] = (int32_t) data;
  proc.cpu.regs[ARM_CPU::PC] += 2;
}

std::ostream& THUMB_ldrsh::display(std::ostream& os) const {
  return os <<"ldrsh\t" <<(ARM_AsmId) Rd <<", [" <<(ARM_AsmId) Rn <<", " <<(ARM_AsmId) Rm <<']';
}

/*****************************************************************/

THUMB_str1::THUMB_str1( uint8_t i, uint8_t n, uint8_t d):
  THUMB_Instruction(), immed(i), Rn(n), Rd(d) {}

void THUMB_str1::exec(ARM_Processor &proc){
  uint32_t addr = proc.cpu.regs[Rn]+immed;
  if ((addr&3) == 0)
    proc.mmu.write_word(addr,proc.cpu.regs[Rd]);
  else {
    proc.error() <<"unpredictable word access to a non-aligned address" <<endl;
    exit(5);
  }
  proc.cpu.regs[ARM_CPU::PC] += 2;
}

std::ostream& THUMB_str1::display(std::ostream& os) const {
  return os <<"str\t" <<(ARM_AsmId) Rd <<", [" <<(ARM_AsmId) Rn <<", #" <<(int) immed <<']';
}

/*****************************************************************/

THUMB_str2::THUMB_str2( uint8_t m, uint8_t n, uint8_t d):
  THUMB_Instruction(), Rm(m), Rn(n), Rd(d) {}

void THUMB_str2::exec(ARM_Processor &proc){
  uint32_t a = proc.cpu.regs[Rm];
  uint32_t b = proc.cpu.regs[Rn];
  uint32_t addr = b + a;
  if ((addr&3) == 0)
    proc.mmu.write_word(addr,proc.cpu.regs[Rd]);
  else{
    proc.error() <<"unpredictable word access to a non-aligned address" <<endl;
    exit(5);
  }
  proc.cpu.regs[ARM_CPU::PC] += 2;
}

std::ostream& THUMB_str2::display(std::ostream& os) const {
  return os <<"str\t" <<(ARM_AsmId) Rd <<", [" <<(ARM_AsmId) Rn <<", " <<(ARM_AsmId) Rm <<']';
}

/*****************************************************************/

THUMB_str3::THUMB_str3( uint8_t d, uint8_t i):
  THUMB_Instruction(), Rd(d), immed(i) {}

void THUMB_str3::exec(ARM_Processor &proc){
  uint32_t a = proc.cpu.regs[ARM_CPU::SP];
  uint32_t b = immed;
  uint32_t addr = a + b*4;
  if ((addr&3) == 0)
    proc.mmu.write_word(addr,proc.cpu.regs[Rd]);
  else{
    proc.error() <<"unpredictable word access to a non-aligned address" <<endl;
    exit(5);
  }
  proc.cpu.regs[ARM_CPU::PC] += 2;
}

std::ostream& THUMB_str3::display(std::ostream& os) const {
  return os <<"str\t" <<(ARM_AsmId) Rd <<", [sp, #" <<(int) immed*4 <<']';
}

/*****************************************************************/
THUMB_strb1::THUMB_strb1( uint8_t i, uint8_t n, uint8_t d):
  THUMB_Instruction(), immed(i), Rn(n), Rd(d) {}

void THUMB_strb1::exec(ARM_Processor &proc){
  uint32_t a = proc.cpu.regs[Rn];
  uint32_t b = immed;
  uint32_t addr = a + b;
  proc.mmu.write_byte(addr,proc.cpu.regs[Rd]);
  proc.cpu.regs[ARM_CPU::PC] += 2;
}

std::ostream& THUMB_strb1::display(std::ostream& os) const {
  return os <<"strb\t" <<(ARM_AsmId) Rd <<", [" <<(ARM_AsmId) Rn <<", #" <<(int) immed <<']';
}

/*****************************************************************/
THUMB_strb2::THUMB_strb2( uint8_t m, uint8_t n, uint8_t d):
  THUMB_Instruction(), Rm(m), Rn(n), Rd(d) {}

void THUMB_strb2::exec(ARM_Processor &proc){
  uint32_t a = proc.cpu.regs[Rn];
  uint32_t b = proc.cpu.regs[Rm];
  uint32_t addr = a + b;
  proc.mmu.write_byte(addr,proc.cpu.regs[Rd]&0xFF);
  proc.cpu.regs[ARM_CPU::PC] += 2;
}

std::ostream& THUMB_strb2::display(std::ostream& os) const {
  return os <<"strb\t" <<(ARM_AsmId) Rd <<", [" <<(ARM_AsmId) Rn <<", " <<(ARM_AsmId) Rm <<']';
}

/*****************************************************************/
THUMB_strh1::THUMB_strh1( uint8_t i, uint8_t n, uint8_t d):
  THUMB_Instruction(), immed(i), Rn(n), Rd(d) {}

void THUMB_strh1::exec(ARM_Processor &proc){
  uint32_t a = proc.cpu.regs[Rn];
  uint32_t b = immed;
  uint32_t addr = a + b*2;
  if ((addr&1) == 0)
    proc.mmu.write_half(addr,proc.cpu.regs[Rd]);
  else{
    proc.error() <<"unpredictable half access to a non-aligned address" <<endl;
    exit(5);
  }
  proc.cpu.regs[ARM_CPU::PC] += 2;
}

std::ostream& THUMB_strh1::display(std::ostream& os) const {
  return os <<"strh\t" <<(ARM_AsmId) Rd <<", [" <<(ARM_AsmId) Rn <<", #" <<(int) immed*2 <<']';
}

/*****************************************************************/

THUMB_strh2::THUMB_strh2( uint8_t m, uint8_t n, uint8_t d):
  THUMB_Instruction(), Rm(m), Rn(n), Rd(d) {}

void THUMB_strh2::exec(ARM_Processor &proc){
  uint32_t a = proc.cpu.regs[Rn];
  uint32_t b = proc.cpu.regs[Rm];
  uint32_t addr = a + b;
  if ((addr&1) == 0)
    proc.mmu.write_half(addr,proc.cpu.regs[Rd]);
  else{
    proc.error() <<"unpredictable half access to a non-aligned address" <<endl;
    exit(5);
  }
  proc.cpu.regs[ARM_CPU::PC] += 2;
}

std::ostream& THUMB_strh2::display(std::ostream& os) const {
  return os <<"strh\t" <<(ARM_AsmId) Rd <<", [" <<(ARM_AsmId) Rn <<", " <<(ARM_AsmId) Rm <<']';
}

/*****************************************************************/

THUMB_ldmia::THUMB_ldmia( uint8_t n, uint8_t regs):
  THUMB_Instruction(), Rn(n), registers(regs), nb_reg(numberOfSetBitsIn(regs)) {}

void THUMB_ldmia::exec(ARM_Processor &proc){
  uint32_t start_addr = proc.cpu.regs[Rn];
  uint32_t end_addr = proc.cpu.regs[Rn] + nb_reg*4 -4;
  uint32_t addr = start_addr;
  for (uint8_t i = 0; i<8; ++i)
    if (registers&(1<<i)) {
      proc.cpu.regs[i] = proc.mmu.read_word(addr);
      addr += 4;
    }
  if (end_addr!=addr-4)
    UNREACHABLE;
  if (!(registers&(1<<Rn)))
    proc.cpu.regs[Rn] = proc.cpu.regs[Rn] + nb_reg*4;
  proc.cpu.regs[ARM_CPU::PC] += 2;
}

std::ostream& THUMB_ldmia::display(std::ostream& os) const {
  os <<"ldmia\t" <<(ARM_AsmId) Rn <<"!, {";
  bool first = true;
  for (uint8_t i = 0; i<8; ++i)
    if (registers&(1<<i)) {
      if (first)
        first = false;
      else
        os <<", ";
      os <<(ARM_AsmId) i;
    }
  return os <<'}';
}

/***************************************************************/

THUMB_stmia::THUMB_stmia( uint8_t n, uint8_t regs):
  THUMB_Instruction(), Rn(n), registers(regs), nb_reg(numberOfSetBitsIn(regs)) {}

void THUMB_stmia::exec(ARM_Processor &proc){
  uint32_t start_addr = proc.cpu.regs[Rn];
  uint32_t end_addr = proc.cpu.regs[Rn] + nb_reg*4 -4;
  uint32_t addr = start_addr;
  for (uint8_t i = 0; i<8; ++i)
    if (registers&(1<<i)) {
      proc.mmu.write_word(addr,proc.cpu.regs[i]);
      addr += 4;
    }
  if (end_addr!=addr-4)
    UNREACHABLE;
  proc.cpu.regs[Rn] = proc.cpu.regs[Rn] + nb_reg*4;
  proc.cpu.regs[ARM_CPU::PC] += 2;
}

std::ostream& THUMB_stmia::display(std::ostream& os) const {
  os <<"stmia\t" <<(ARM_AsmId) Rn <<"!, {";
  bool first = true;
  for (uint8_t i = 0; i<8; ++i)
    if (registers&(1<<i)) {
      if (first)
        first = false;
      else
        os <<", ";
      os <<(ARM_AsmId) i;
    }
  return os <<'}';
}

/****************************************************************/

THUMB_pop::THUMB_pop( bool r, uint8_t regs):
  THUMB_Instruction(), R(r), registers(regs), nb_reg(numberOfSetBitsIn(regs)) {}

void THUMB_pop::exec(ARM_Processor &proc){
  uint32_t start_addr = proc.cpu.regs[ARM_CPU::SP];
  uint32_t end_addr = proc.cpu.regs[ARM_CPU::SP] +(R+nb_reg)*4 ;
  uint32_t addr = start_addr;
  for (int i = 0; i<=7; ++i)
    if (registers&(1<<i)) {
      proc.cpu.regs[i] = proc.mmu.read_word(addr); ;
      addr += 4;
    }
  if (R) {
    uint32_t value = proc.mmu.read_word(addr);
    switch (value&3) {
    case 0: // 00
      proc.cpu.unset_thumb_mode();
      proc.cpu.regs[ARM_CPU::PC] = value+8; break;
    case 2: // 10
      proc.error() <<"unpredictable word access to a non-aligned address" <<endl;
      exit(5);
    case 1: // 01
    case 3: // 11
      proc.cpu.regs[ARM_CPU::PC] = (value&~1)+4;
    }
    addr +=4;
    if (end_addr!=addr)
      UNREACHABLE;
    proc.cpu.regs[ARM_CPU::SP] = end_addr;
  } else {
    if (end_addr!=addr)
      UNREACHABLE;
    proc.cpu.regs[ARM_CPU::SP] = end_addr;
    proc.cpu.regs[ARM_CPU::PC] += 2;
  }
}

std::ostream& THUMB_pop::display(std::ostream& os) const {
  os <<"pop\t{";
  bool first = true;
  for (uint8_t i = 0; i<8; ++i)
    if (registers&(1<<i)) {
      if (first)
        first = false;
      else
        os <<", ";
      os <<(ARM_AsmId) i;
    }
  if (R)
    if (first)
      os <<"pc";
    else
      os <<", pc";
  return os <<'}';
}

/****************************************************************/

THUMB_push::THUMB_push( bool r, uint8_t regs):
  THUMB_Instruction(), R(r), registers(regs), nb_reg(numberOfSetBitsIn(regs)) {}

void THUMB_push::exec(ARM_Processor &proc){
  uint32_t start_addr = proc.cpu.regs[ARM_CPU::SP] - (R+nb_reg)*4 ;
  uint32_t end_addr = proc.cpu.regs[ARM_CPU::SP]-4;
  uint32_t addr = start_addr;
  for (int i = 0; i<=7; ++i)
    if (registers&(1<<i)) {
      proc.mmu.write_word(addr,proc.cpu.regs[i]);
      addr += 4;
    }
  if (R) {
    proc.mmu.write_word(addr,proc.cpu.regs[ARM_CPU::LR]); ;
    addr +=4;
  }
  if (end_addr!=addr-4)
    UNREACHABLE;
  proc.cpu.regs[ARM_CPU::SP] = proc.cpu.regs[ARM_CPU::SP] - 4*(R+nb_reg);
  proc.cpu.regs[ARM_CPU::PC] += 2;
}

std::ostream& THUMB_push::display(std::ostream& os) const {
  os <<"push\t{";
  bool first = true;
  for (uint8_t i = 0; i<8; ++i)
    if (registers&(1<<i)) {
      if (first)
        first = false;
      else
        os <<", ";
      os <<(ARM_AsmId) i;
    }
  if (R)
    if (first)
      os <<"lr";
    else
      os <<", lr";
  return os <<'}';
}

} // namespace simsoc
