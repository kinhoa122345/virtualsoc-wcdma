//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

// implementation of template classes declared in armis_loadstore.hpp

namespace simsoc {

template <class op>
void ARM_LoadStoreImm<op>::exec(ARM_Processor &proc) {
  if (conditionPassed(proc.cpu.cpsr,cond)) {
    uint32_t addr;
    if (p) {
      addr = u? proc.cpu.regs[Rn]+immed: proc.cpu.regs[Rn]-immed;
      op::doAccess(proc,Rd,addr);
      if (w)
        proc.cpu.regs[Rn] = addr;
    } else {
      addr = proc.cpu.regs[Rn];
      op::doAccess(proc,Rd,addr);
      proc.cpu.regs[Rn] = u? proc.cpu.regs[Rn]+immed: proc.cpu.regs[Rn]-immed;
    }
  }
  proc.cpu.regs[ARM_CPU::PC] += 4;
}

template <class op>
std::ostream& ARM_LoadStoreImm<op>::display(std::ostream& os) const {
  if (p)
    return os <<op::name() <<cond <<op::suffix() <<'\t' <<(ARM_AsmId) Rd <<", ["
              <<(ARM_AsmId) Rn <<(u? ", #+": ", #-") <<std::dec <<(int) immed <<(w? "]!": "]");
  else
    return os <<op::name() <<cond <<op::suffix() <<'\t' <<(ARM_AsmId) Rd <<", ["
              <<(ARM_AsmId) Rn <<(u? "], #+": "], #-") <<std::dec <<(int) immed;
}

template <class op>
bool ARM_LoadStoreImm<op>::may_raise_something() const {
  return !is_load_local_data() && Rn!=ARM_CPU::SP && Rn!=ARM_CPU::FP;
}

template <class op>
bool ARM_LoadStoreImm<op>::may_branch() const {
  return Rd==ARM_CPU::PC;
}

template <class op>
bool ARM_LoadStoreImm<op>::is_load_local_data() const {
  return !(Rn!=ARM_CPU::PC || w || !p || Rd==ARM_CPU::PC
           || op::opcode==STR || op::opcode==STRB || op::opcode==LDRT || op::opcode==LDRBT
           || op::opcode==STRT || op::opcode==STRBT || op::opcode==STRH);
}

/******************************************************************************/

template <class op>
void ARM_LoadStoreReg<op>::exec(ARM_Processor &proc) {
  if (conditionPassed(proc.cpu.cpsr,cond)) {
    uint32_t addr;
    if (p) {
      addr = u? proc.cpu.regs[Rn]+proc.cpu.regs[Rm]: proc.cpu.regs[Rn]-proc.cpu.regs[Rm];
      op::doAccess(proc,Rd,addr);
      if (w)
        proc.cpu.regs[Rn] = addr;
    } else {
      addr = proc.cpu.regs[Rn];
      op::doAccess(proc,Rd,addr);
      proc.cpu.regs[Rn] = u? proc.cpu.regs[Rn]+proc.cpu.regs[Rm]: proc.cpu.regs[Rn]-proc.cpu.regs[Rm];
    }
  }
  proc.cpu.regs[ARM_CPU::PC] += 4;
}

template <class op>
std::ostream& ARM_LoadStoreReg<op>::display(std::ostream& os) const {
  if (p)
    return os <<op::name() <<cond <<op::suffix() <<'\t' <<(ARM_AsmId) Rd <<", ["
              <<(ARM_AsmId) Rn <<(u? ", +": ", -") <<(ARM_AsmId) Rm <<(w? "]!": "]");
  else
    return os <<op::name() <<cond <<op::suffix() <<'\t' <<(ARM_AsmId) Rd <<", ["
              <<(ARM_AsmId) Rn <<(u? "], +": "}, -") <<(ARM_AsmId) Rm;
}

template <class op>
bool ARM_LoadStoreReg<op>::may_branch() const {
  return Rd==ARM_CPU::PC;
}

/******************************************************************************/

template <class op>
void ARM_LoadStoreScRg<op>::exec(ARM_Processor &proc) {
  if (conditionPassed(proc.cpu.cpsr,cond)) {
    uint32_t index = 0;
    switch (shift) {
    case LSL: index = valueLSL(proc.cpu.regs[Rm],shift_imm); break;
    case LSR: index = valueLSR(proc.cpu.regs[Rm],shift_imm); break;
    case ASR: index = valueASR(proc.cpu.regs[Rm],shift_imm); break;
    case ROR: index = valueROR(proc.cpu.regs[Rm],shift_imm); break;
    case RRX: index = valueRRX(proc.cpu.regs[Rm],proc.cpu.cpsr.c); break;
    }
    uint32_t addr;
    if (p) {
      addr = u? proc.cpu.regs[Rn]+index: proc.cpu.regs[Rn]-index;
      op::doAccess(proc,Rd,addr);
      if (w)
        proc.cpu.regs[Rn] = addr;
    } else {
      addr = proc.cpu.regs[Rn];
      op::doAccess(proc,Rd,addr);
      proc.cpu.regs[Rn] = u? proc.cpu.regs[Rn]+index: proc.cpu.regs[Rn]-index;
    }
  }
  proc.cpu.regs[ARM_CPU::PC] += 4;
}

template <class op>
std::ostream& ARM_LoadStoreScRg<op>::display(std::ostream& os) const {
  if (p)
    return os <<op::name() <<cond <<op::suffix() <<'\t' <<(ARM_AsmId) Rd <<", ["
              <<(ARM_AsmId) Rn <<(u? ", +": ", -") <<(ARM_AsmId) Rm
              <<", " <<shift <<" #" <<(int) shift_imm
              <<(w? "]!": "]");
  else
    return os <<op::name() <<cond <<op::suffix() <<'\t' <<(ARM_AsmId) Rd <<", ["
              <<(ARM_AsmId) Rn <<(u? "], +": "}, -") <<(ARM_AsmId) Rm
              <<", " <<shift <<" #" <<(int) shift_imm;
}

template <class op>
bool ARM_LoadStoreScRg<op>::may_branch() const {
  return Rd==ARM_CPU::PC;
}

} // namespace simsoc
