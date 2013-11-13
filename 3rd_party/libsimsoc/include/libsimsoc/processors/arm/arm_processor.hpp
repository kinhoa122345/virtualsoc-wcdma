//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef ARM_PROCESSOR_HPP
#define ARM_PROCESSOR_HPP

#include <libsimsoc/components/elf_loader.hpp>
#include <libsimsoc/module.hpp>
#include <libsimsoc/processors/iss.hpp>
#include <libsimsoc/processors/processor.hpp>
#include <libsimsoc/translation_table.hpp>
#include <libsimsoc/tools/debugger/debugger.hpp>
#include "arm_condition.hpp"
#include "arm_cpu.hpp"
#include "arm_mmu.hpp"
#include "arm_systemcontrol_coproc.hpp"
#include "arm_translation_page.hpp"
#include "armpi.hpp"

namespace simsoc {

class ARM_Instruction;
class ARM32_Instruction;
class THUMB_Instruction;
class ARM_PseudoInstruction;
class ARM_TranslationPage;
class ARM_UserMode;
class ARM_Coprocessor;
class ARM_Debugger;

class ARM_Processor: public Processor,
                     public SignalTarget<bool>
{
  friend class ARM_Debugger;

public:
  typedef ARM_Instruction Instruction;
  typedef ARM_PseudoInstruction PseudoInstruction;

  static ParameterBool init_high_vector;

  // *** hardware parts:

  SignalTargetPort<bool> irq_port;
  SignalTargetPort<bool> fiq_port;

  ARM_CPU cpu;
  ISS<ARM_Processor> iss;
  ARM_MMU mmu;
  ARM_Coprocessor *coprocessors[16];
  ARM_SystemControl_Coprocessor cp15;
  ARM_Coprocessor null_coproc;

  // *** other data:

  ARM_Instruction *current_instruction;
  ARM_TranslationPage *current_page;

  std::map<uint32_t,uint32_t> statistics;
  size_t instr_size;

  sc_core::sc_event it_event;

  // *** methods:

  ARM_Processor(sc_core::sc_module_name name, int processor_id = 0);

  virtual ~ARM_Processor();

  inline int bus_width() {return 32;}

  // fetching:
  Instruction *fetch_instruction();
  inline Instruction *fetch_instr_from_cache();
  Instruction *fetch_from_cache__nopage();
  Thumb_TranslationPage *fetch_from_cache__decode_thumb(const uint32_t page_id,
                                                        uint32_t *const host_address);
  ARM32_TranslationPage *fetch_from_cache__decode_arm32(const uint32_t page_id,
                                                        uint32_t *const host_address);
  Instruction **get_current_instr_ptr_arm32();
  Instruction **get_current_instr_ptr_thumb();

  // interrupts:
  void set_high_vector(bool value = true);
  uint32_t high_vector();
  void raise_interrupt(); //call irq_interrupt or fiq_interrupt
  void irq_interrupt();
  void fiq_interrupt();
  void undefined_interrupt();
  void prefetch_abort();
  void data_abort();
  void software_interrupt();

  // update it_pending and notify it_event, accordind to irq_port, fiq_port and cpsr.
  void signal(bool b=false); // called by irq_port or fiq_port or when cpsr.i/cpsr.f are set

  void set_mode(ARM_Mode new_mode);
  void set_cpsr(uint32_t new_value, uint8_t mask);
  void spsr_to_cpsr();
  void idle();

  bool user_mode() const;

  // methods for initialization and user-level mode:
  void set_pc(uint64_t pc);
  uint64_t get_pc() const {return cpu.regs[ARM_CPU::PC];}
  void set_sp(uint64_t sp);
  uint64_t get_gp_register(size_t n) const;
  void set_gp_register(size_t n, uint64_t data);

  void set_lr(uint32_t lr);
  uint32_t init_stack(uint32_t argc, char **argv, uint8_t *stack_host_address);

  void set_endian_little();
  void set_endian_big();

  tlm::tlm_initiator_socket<> &get_rw_port();
  SignalTargetPort<bool> &get_it_port();
  const TranslationPage *get_current_page() const {return current_page;}
  SimulationMode max_mode_available() const {return DYN_TRANS_SPEC;}

  // statistics computation:
  void update_statistics(ARM_Instruction *);
  void write_statistics(std::ostream& os = std::cout);
  void read_statistics(std::istream& is);

  // for debug:
  void print_instruction(uint32_t addr, uint32_t n = 1);

  // Architecture dependent code executed after each instruction
  inline void hook() {
    // debug_hook();
  }
  void debug_hook();

  // for debug port
  unsigned int transport_dbg(int, tlm::tlm_generic_payload &payload) {
    return mmu.transport_dbg(payload);
  }

  // GDB interface
  virtual DebugInterface* create_dbi();
};

  // used by the template Core main loop in simple dyn trans  mode
  ARM_Instruction * ARM_Processor::fetch_instr_from_cache() {
    TranslationTableItem *p_page;
    uint32_t *host_address;
    const uint32_t page_id = TranslationPage::pageId(cpu.regs[ARM_CPU::PC]-2*instr_size);
    mmu.fetch_page(page_id, // input
                   host_address, p_page); //output
    if (!p_page)
      return fetch_from_cache__nopage();
    if (cpu.cpsr.t) {
      if (!p_page->thumb)
        p_page->thumb = fetch_from_cache__decode_thumb(page_id, host_address);
      current_page = p_page->thumb;
      assert(current_page);
      return p_page->thumb->locateInstr(cpu.regs[ARM_CPU::PC]);
    } else {
      if (!p_page->arm32)
        p_page->arm32 = fetch_from_cache__decode_arm32(page_id, host_address);
      current_page = p_page->arm32;
      assert(current_page);
      return p_page->arm32->locateInstr(cpu.regs[ARM_CPU::PC]);
    }
  }

} // namespace simsoc

#endif //ARM_PROCESSOR_HPP
