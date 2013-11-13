//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "armis_dyntrans.hpp"
#include "arm_processor.hpp"
#include "arm_translate.hpp"
#include "thumb_translate.hpp"
#include <cassert>

namespace simsoc {

  static bool may_branch_and_delete(ARM_Instruction *instr, bool &dont_delete) {
    const bool may_branch = instr->may_branch();
    if (!dont_delete)
      delete instr;
    return may_branch;
  }

  ARM32_ExecuteBlock::ARM32_ExecuteBlock():
    ARM32_Instruction(), pis(), count(0) {}

  ARM32_ExecuteBlock::~ARM32_ExecuteBlock() {
    std::vector<ARM_PseudoInstruction>::iterator i = pis.begin();
    const std::vector<ARM_PseudoInstruction>::iterator ei = pis.end();
    do {
      destructPseudo(*i);
      ++i;
    } while (i!=ei);
  }

  void ARM32_ExecuteBlock::push_back(ARM_Processor& proc,
                                     ARM_Instruction *instr,
                                     bool &is_generic_pi) {
    // This function is called just after instr is executed.
    {
      ARM_PseudoInstruction pi;
      pis.push_back(pi);
    }
    ARM_Translate(proc,instr,pis[pis.size()-1]);

    // a "generic" pseudo-instruction takes the ownership of instr.
    is_generic_pi = isPseudoGeneric(pis[pis.size()-1]);
  }

  std::ostream& ARM32_ExecuteBlock::display(std::ostream& os) const {
    return os <<"execute block [size=" <<std::dec <<pis.size()
              <<"; count=" <<count <<"]";
  }

  void ARM32_ExecuteBlock::exec(ARM_Processor& proc) {
    PseudoStatus status;
    ++count;
    std::vector<ARM_PseudoInstruction>::iterator i = pis.begin();
    const std::vector<ARM_PseudoInstruction>::iterator ei = pis.end();
    const std::vector<ARM_PseudoInstruction>::iterator li = ei-1;
    while (i!=li) {
      status = i->f(proc, *i);
      assert(status==OK);
      proc.cpu.regs[ARM_CPU::PC] += 4;
      proc.hook();
      ++i;
    }
    status = i->f(proc, *i);
    if (status==OK)
      proc.cpu.regs[ARM_CPU::PC] += 4;
  }

  ARM32_TranslateBlock ARM32_TranslateBlock::singleton = ARM32_TranslateBlock();

  std::ostream& ARM32_TranslateBlock::display(std::ostream& os) const {
    return os <<"translate block";
  }

  void ARM32_TranslateBlock::exec(ARM_Processor& proc) {
    // FIXME: the block may covers many pages. So, it should be discarded:
    //        - if any of the physical page is modified
    //        - if the virtual page order changes

    ARM32_ExecuteBlock *ebi = new ARM32_ExecuteBlock(); // FIXME: delete if exception
    ARM_Instruction **this_ptr = proc.get_current_instr_ptr_arm32();
    ARM_Instruction *instr;
    bool is_generic_pi = false;
    bool not_may_branch;
    const uint32_t start = proc.cpu.regs[ARM_CPU::PC]-8;
    proc.info() <<"construct arm block starting at address "
                <<std::hex <<start <<".\n";
    do {
      instr = proc.fetch_instruction();
      proc.debug() <<"execute & translate: " <<*instr <<'\n';
      instr->exec(proc);
      ebi->push_back(proc,instr,is_generic_pi);
      not_may_branch = !may_branch_and_delete(instr,is_generic_pi);
      if (not_may_branch)
        proc.hook();
    } while (not_may_branch);
    *this_ptr = ebi; // REMARK: invalidated pages are not destroyed immediately
    proc.info() <<"translated block ends at address "
                <<std::hex <<start+4*ebi->size()-4 <<".\n";
  }

  /****************************************************************************/

  THUMB_ExecuteBlock::THUMB_ExecuteBlock():
    THUMB_Instruction(), pis(), count(0) {}

  THUMB_ExecuteBlock::~THUMB_ExecuteBlock() {
    std::vector<ARM_PseudoInstruction>::iterator i = pis.begin();
    const std::vector<ARM_PseudoInstruction>::iterator ei = pis.end();
    do {
      destructPseudo(*i);
      ++i;
    } while (i!=ei);
  }

  void THUMB_ExecuteBlock::push_back(ARM_Processor& proc,
                                     ARM_Instruction *instr,
                                     bool &is_generic_pi) {
    // This function is called just after instr is executed.
    {
      ARM_PseudoInstruction pi;
      pis.push_back(pi);
    }
    THUMB_Translate(proc,instr,pis[pis.size()-1]);

    // a "generic" pseudo-instruction takes the ownership of instr.
    is_generic_pi = isPseudoGeneric(pis[pis.size()-1]);
  }

  std::ostream& THUMB_ExecuteBlock::display(std::ostream& os) const {
    return os <<"execute block [size=" <<std::dec <<pis.size()
              <<"; count=" <<count <<"]";
  }

  void THUMB_ExecuteBlock::exec(ARM_Processor& proc) {
    assert(pis.size()>=1);
    PseudoStatus status;
    ++count;
    std::vector<ARM_PseudoInstruction>::iterator i = pis.begin();
    const std::vector<ARM_PseudoInstruction>::iterator ei = pis.end();
    const std::vector<ARM_PseudoInstruction>::iterator li = ei-1;
    while (i!=li) {
      status = i->f(proc, *i);
      assert(status==OK);
      proc.cpu.regs[ARM_CPU::PC] += 2;
      proc.hook();
      ++i;
    }
    status = i->f(proc, *i);
    if (status==OK)
      proc.cpu.regs[ARM_CPU::PC] += 2;
  }

  THUMB_TranslateBlock THUMB_TranslateBlock::singleton = THUMB_TranslateBlock();

  std::ostream& THUMB_TranslateBlock::display(std::ostream& os) const {
    return os <<"translate block";
  }

  void THUMB_TranslateBlock::exec(ARM_Processor& proc) {
    // FIXME: the block may covers many pages. So, it should be discarded:
    //        - if any of the physical page is modified
    //        - if the virtual page order changes

    THUMB_ExecuteBlock *ebi = new THUMB_ExecuteBlock(); // FIXME: delete if exception
    ARM_Instruction **this_ptr = proc.get_current_instr_ptr_thumb();
    ARM_Instruction *instr;
    bool is_generic_pi = false;
    const uint32_t start = proc.cpu.regs[ARM_CPU::PC]-4;
    proc.info() <<"construct thumb block starting at address "
                <<std::hex <<start <<".\n";
    do {
      instr = proc.fetch_instruction();
      proc.debug() <<"execute & translate: " <<*instr <<'\n';
      instr->exec(proc);
      ebi->push_back(proc,instr,is_generic_pi);
      proc.hook();
    } while (!may_branch_and_delete(instr,is_generic_pi));
    *this_ptr = ebi; // REMARK: invalidated pages are not destroyed immediately
    proc.info() <<"translated block ends at address "
                <<std::hex <<start+2*ebi->size()-2 <<".\n";
  }

} // namespace simsoc
