//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include <errno.h>
#include <iomanip>
#include <sys/mman.h>

#include "libsimsoc/processors/arm_v6/arm_v6_processor.hpp"
#include "libsimsoc/processors/arm_v6/arm_v6_translation_page.hpp"
#include "libsimsoc/processors/arm_v6/arm_v6_dyntrans.hpp"
#include "libsimsoc/processors/arm_v6/arm_v6_debugger.hpp"
#include "libsimsoc/processors/arm_v6/arm_v6_printers.hpp"
#include "libsimsoc/processors/arm_v6/simlight/slv6_iss_grouped.h"
#include <libsimsoc/simsoc-config.h>
#include <libsimsoc/processors/iss_exception.hpp>
#include <libsimsoc/processors/llvm_gen_parameters.hpp>

#ifdef SIMSOC_HAVE_LLVM
#include "libsimsoc/processors/arm_v6/arm_v6_llvm_server.hpp"
#endif

using namespace sc_core;
using namespace std;

namespace simsoc {

  static const uint32_t STAT_MAX = (1<<30)-1;

  void exec_bkpt_arm(SLv6_Processor *proc, SLv6_Instruction *instr) {
    if (proc->proc_ptr->debugger())
      proc->proc_ptr->debugger()->notify(Debugger::EV_TRAP);
    else
      slv6_G_BKPT(proc,instr);
  }

  void exec_bkpt_thumb(SLv6_Processor *proc, SLv6_Instruction *instr) {
    if (proc->proc_ptr->debugger())
      proc->proc_ptr->debugger()->notify(Debugger::EV_TRAP);
    else
      slv6_G_Tb_BKPT(proc,instr);
  }

  void ARMv6_Processor::debug_hook() {
    static uint64_t count = 0;
    const uint64_t START = main_context().start;
    const uint64_t PERIOD = main_context().period;
    const uint64_t END = START + PERIOD*main_context().number;
    if (START<=count && count<END) {
      if ((count-START)%PERIOD==0) {
        std::cout <<"STEP #" <<std::dec <<count <<'\n';
        std::cout <<slv6_proc;
      }
    }
    ++count;
  }

  void debug_hook(struct SLv6_Processor *proc) {
    proc->proc_ptr->debug_hook();
  }

  // function called by the simlight code.
  // must be called after any modifications of the I and F flags.
  void update_pending_flags(struct SLv6_Processor *proc) {
    proc->proc_ptr->update_pending_flags();
  }

  void exec_undefined_instruction(SLv6_Processor *proc,
                                  SLv6_Instruction*) {
    proc->proc_ptr->info() <<"raising undefined instruction exception." <<endl;
    proc->spsrs[und] = proc->cpsr;
    set_cpsr_mode(proc, und); // swap the regsiters
    proc->regs[14] = address_of_current_instruction(proc);
    proc->cpsr.T_flag = false;
    proc->cpsr.I_flag = true;
    update_pending_flags(proc);
    proc->cpsr.E_flag = CP15_reg1_EEbit(proc->cp15_ptr);
    set_pc_raw(proc,proc->proc_ptr->vector_start()+4);
  }

  void ARMv6_Processor::prefetch_abort() {
    info() <<"raising prefetch abort exception." <<endl;
    slv6_proc.spsrs[abt] = slv6_proc.cpsr;
    set_cpsr_mode(&slv6_proc, abt); // swap the registers
    slv6_proc.regs[14] = address_of_current_instruction(&slv6_proc)+4;
    slv6_proc.cpsr.T_flag = false;
    slv6_proc.cpsr.I_flag = true;
    slv6_proc.cpsr.A_flag = true;
    update_pending_flags();
    slv6_proc.cpsr.E_flag = CP15_reg1_EEbit(slv6_proc.cp15_ptr);
    set_pc_raw(&slv6_proc,vector_start()+0xC);
    throw ISS_Exception("ARMv6: prefetch abort");
  }

  void ARMv6_Processor::data_abort() {
    info() <<"raising data abort exception." <<endl;
    slv6_proc.spsrs[abt] = slv6_proc.cpsr;
    set_cpsr_mode(&slv6_proc, abt); // swap the registers
    slv6_proc.regs[14] = address_of_current_instruction(&slv6_proc)+8;
    slv6_proc.cpsr.T_flag = false;
    slv6_proc.cpsr.I_flag = true;
    slv6_proc.cpsr.A_flag = true;
    update_pending_flags();
    slv6_proc.cpsr.E_flag = CP15_reg1_EEbit(slv6_proc.cp15_ptr);
    set_pc_raw(&slv6_proc,vector_start()+0x10);
    throw ISS_Exception("ARMv6: data abort");
  }

  void ARMv6_Processor::irq_interrupt() {
    assert(irq_flag());
    info() <<"raising IRQ exception." <<endl;
    slv6_proc.spsrs[irq] = slv6_proc.cpsr;
    set_cpsr_mode(&slv6_proc, irq); // swap the registers
    slv6_proc.regs[14] = address_of_current_instruction(&slv6_proc)+4;
    slv6_proc.cpsr.T_flag = false;
    slv6_proc.cpsr.I_flag = true;
    slv6_proc.cpsr.A_flag = true;
    update_pending_flags();
    slv6_proc.cpsr.E_flag = CP15_reg1_EEbit(slv6_proc.cp15_ptr);
    if (!CP15_reg1_VEbit(slv6_proc.cp15_ptr))
      set_pc_raw(&slv6_proc,vector_start()+0x18);
    else
      TODO("vectored interrupt support");
    slv6_proc.jump = false;
    clear_irq_flag();
  }

  void ARMv6_Processor::fiq_interrupt() {
    assert(fiq_flag());
    info() <<"raising IRQ exception." <<endl;
    slv6_proc.spsrs[fiq] = slv6_proc.cpsr;
    set_cpsr_mode(&slv6_proc, fiq); // swap the registers
    slv6_proc.regs[14] = address_of_current_instruction(&slv6_proc)+4;
    slv6_proc.cpsr.T_flag = false;
    slv6_proc.cpsr.F_flag = true;
    slv6_proc.cpsr.I_flag = true;
    slv6_proc.cpsr.A_flag = true;
    update_pending_flags();
    slv6_proc.cpsr.E_flag = CP15_reg1_EEbit(slv6_proc.cp15_ptr);
    if (!CP15_reg1_VEbit(slv6_proc.cp15_ptr))
      set_pc_raw(&slv6_proc,vector_start()+0x1c);
    else
      TODO("vectored interrupt support");
    slv6_proc.jump = false;
    clear_fiq_flag();
  }

  // constructor
  ARMv6_Processor::ARMv6_Processor(sc_module_name name, int ID, int TILE_ID):
    Processor(name,ARM),
    irq_port(false), fiq_port(false),
    null_coproc("EMPTY_COPROCESSOR_SLOT",this),
    mmu("MMU",this,ID,TILE_ID), cp15("CP15",this,&mmu),
    current_page(NULL),
    pending_flags(0),
    raw_stats(NULL)/*,
    ID(ID)*/
  {
    this->ID = ID;
    this->TILE_ID = TILE_ID;
    //cout << "arm11 creato - ID "<< (int)ID << endl;
    info() << "Constructing ARMv6 processor\n";
    for (size_t n=0; n<15; ++n)
      coprocessors[n] = &null_coproc;
    coprocessors[15] = &cp15;
    #ifndef NO_MMU
    debug_port.register_transport_dbg(this,&ProcessorBase::transport_dbg);
    #endif
    irq_port(*this);
    fiq_port(*this);
    init_Processor(&slv6_proc,&mmu,&cp15);
    slv6_proc.proc_ptr = this;
    mmu.user_mode = slv6_proc.cpsr.mode==usr;
    // FIXME: unpredictable instruction are treated as undefined instruction
    slv6_instruction_functions[UNDEF_OR_UNPRED_ID] = exec_undefined_instruction;
    SC_THREAD(compute);
    set_stack_size(0x100000); // = 1 MB
    // Insert a wrapper around each bkpt instruction
    slv6_instruction_functions[SLV6_BKPT_ID] = exec_bkpt_arm;
    slv6_instruction_functions[SLV6_Tb_BKPT_ID] = exec_bkpt_thumb;
    // Statistics
    if (strcmp(stat_file,"")) {
      mode = INTERPRET;
      raw_stats = new uint32_t[SLV6_INSTRUCTION_COUNT+1];
      memset(raw_stats,'\0',4*(SLV6_INSTRUCTION_COUNT+1));
      ifstream is(stat_file);
      if (!!is) {
        info() <<"read statistics from \"" <<stat_file <<"\"\n";
        for (size_t i = 0; i<SLV6_INSTRUCTION_COUNT; ++i)
          is >>raw_stats[i];
        is.close();
      }
    }

  }

  ARMv6_Processor::~ARMv6_Processor() {
    if (raw_stats) {
      ofstream os(stat_file);
      if (!os) {
        cerr <<"cannot write to \"" <<stat_file <<"\"\n";
        exit(1);
      }
      info() <<"write statistics to \"" <<stat_file <<"\"\n";
      for (size_t i = 0; i<SLV6_INSTRUCTION_COUNT; ++i)
        os <<raw_stats[i] <<' ';
      os <<std::endl;
      os.close();
      delete raw_stats;
    }
    destruct_Processor(&slv6_proc);
  }

  void ARMv6_Processor::set_pc(uint64_t addr) {
    simsoc::set_pc(&slv6_proc,addr);
    slv6_proc.jump = false;
  }

  uint64_t ARMv6_Processor::get_pc() const {
    return simsoc::get_pc(&slv6_proc);
  }

  void ARMv6_Processor::set_sp(uint64_t addr) {
    set_reg(&slv6_proc,13,addr);
  }

  uint64_t ARMv6_Processor::get_gp_register(size_t n) const {
    assert(n<16);
    return slv6_proc.regs[n];
  }

  void ARMv6_Processor:: set_gp_register(size_t n, uint64_t data) {
    assert(!(data>>32));
    assert(n<16);
    slv6_proc.regs[n] = static_cast<uint32_t>(data);
  }

  void ARMv6_Processor::set_endian_little() {
    info() <<"endianness set to little\n";
    cp15.set_big_endian(false);
  }

  void ARMv6_Processor::set_endian_big() {
    info() <<"endianness set to big\n";
    cp15.set_big_endian(true);
  }

  const TranslationPage *ARMv6_Processor::get_current_page() const {
    return current_page;
  }

  SimulationMode ARMv6_Processor::max_mode_available() const {
#ifdef SIMSOC_HAVE_LLVM
    return DYN_COMP;
#else
    return DYN_TRANS_SPEC;
#endif
  }

  void ARMv6_Processor::write_statistics(std::ostream& os) {
    TODO("write_statistics");
  }

  void ARMv6_Processor::read_statistics(std::istream& is) {
    TODO("read_statistics");
  }
#ifndef NO_MMU
  tlm::tlm_initiator_socket<> &ARMv6_Processor::get_rw_port() {
    return mmu.rw_socket;
  }
#endif
  SignalTargetPort<bool> &ARMv6_Processor::get_it_port() {
    return irq_port;
  }

  void ARMv6_Processor::pending_actions() {
    if (fiq_flag()) fiq_interrupt();
    if (irq_flag()) irq_interrupt();
  }

  void ARMv6_Processor::compute() {
//     if (mode==INTERPRET)
      interpret();
//     else
//       dyntrans();
  }

  void ARMv6_Processor::interpret() {
    info() <<"Dynamic translation is disabled." <<endl;
    SLv6_Instruction instr;
    uint32_t bincode;
    int iq = iquantum;
    bool prefetch_flag = false;
    this->debugger_cycle();
    while (true) {
      try {
        while (true) {
          if (inst_size(&slv6_proc)==4) {
      if(prefetch_flag){
//       	      cout<<"Before reading prefetched instruction" << "@ " << sc_time_stamp()<<endl;
        bincode = mmu.read_from_fifoI();
// 	      cout<<"Prefetched istruction: "<< hex << bincode << "@ " << sc_time_stamp()<<endl;
        prefetch_flag = false;
      }
      else
        bincode = mmu.load_instr_32(address_of_current_instruction(&slv6_proc));
           /*
      cout << "bincode & 0xE000000: "<< hex << (unsigned int)(bincode & 0xE000000) << endl;


      */
      //prefetch executed only if the current instruction is not a load with pc as destination.
      if((((bincode & 0xC000000) == 0x4000000) && ((bincode & 0x10F000)!= 0x10F000)) || ((bincode & 0xE000000) == 0x8000000) && ((bincode & 0x108000)!= 0x108000)){
// 	      cout<<"Memory istruction: "<< hex << bincode << "@ " << sc_time_stamp()<<endl;
        prefetch_flag = true;
        mmu.write_to_fifoI(address_of_next_instruction(&slv6_proc));
// 	      cout<<"Next Instruction: "<< hex << address_of_next_instruction(&slv6_proc)<<endl;
      }
      else{
// 	      cout<<"No Memory istruction: "<< hex << bincode << "@ " << sc_time_stamp()<<endl;
      }

            arm_decode_and_store(&instr,bincode);
          } else {
            bincode = mmu.load_instr_16(address_of_current_instruction(&slv6_proc));
            thumb_decode_and_store(&instr,bincode);
          }
          assert(instr.args.g0.id<=UNDEF_OR_UNPRED_ID);
          debug() <<"execute: \t" <<ARMv6_InstPrinter(instr,bincode) <<endl;
          if (raw_stats && raw_stats[instr.args.g0.id]<STAT_MAX)
            ++raw_stats[instr.args.g0.id];
          slv6_instruction_functions[instr.args.g0.id](&slv6_proc,&instr);
          if (slv6_proc.jump)
            slv6_proc.jump = false;
          else
            increment_pc(&slv6_proc);
          slv6_hook(&slv6_proc);
#ifdef FORCED_WAIT
          if (--iq<=0) {
            debug() <<"enter wait(" <<tquantum <<").\n";
            iq = iquantum;
            wait(tquantum);
          }
#endif
          if (pending_flags) {
            pending_actions();
          }
          this->debugger_cycle();
        }
      } catch (ISS_Exception &e) {
        std::cout <<"processor exception catched! @ " << sc_time_stamp() << endl;
        //info() <<"processor exception catched: " <<e.what() <<".\n";
      }
    }
  }

  void ARMv6_Processor::dyntrans() {
    info() <<"Dynamic translation is enabled." <<endl;
    if (mode>=DYN_TRANS_SPEC)
      init_dyntrans();
    int iq = iquantum;
    while (true) {
      try {
        while (true) {
          SLv6_Instruction *instr = fetch_instr_from_cache();
          assert(instr->args.g0.id<=OPT_BASIC_BLOCK_ID);
          debug() <<"execute: \t" <<slv6_instruction_names[instr->args.g0.id] <<endl;
          instr->sem_fct(&slv6_proc,instr);
          if (slv6_proc.jump)
            slv6_proc.jump = false;
          else
            increment_pc(&slv6_proc);
          slv6_hook(&slv6_proc);
          if (--iq<=0) {
            debug() <<"enter wait(" <<tquantum <<").\n";
            iq = iquantum;
            wait(tquantum);
#ifdef SIMSOC_HAVE_LLVM
            if (DT3_server.get()) {
              ARMv6_LLVM_Server::get().synchronize();
            }
#endif
          }
          if (pending_flags) {
            pending_actions();
          }
        }
      } catch (ISS_Exception &e) {
        info() <<"processor exception catched: " <<e.what() <<".\n";
      }
    }
  }

  DebugInterface *ARMv6_Processor::create_dbi() {
    return new ARMv6_Debugger(*this);
  }

  SLv6_Instruction* ARMv6_Processor::fetch_instr_from_cache() {
    TranslationTableItem *p_page;
    uint32_t *host_address;
    if (slv6_proc.cpsr.T_flag) {
      const uint32_t page_id =
        TranslationPage::pageId(addr_of_current_instr_arm16(&slv6_proc));
      mmu.fetch_page(page_id,host_address,p_page);
      if (!p_page)
      return fetch_from_cache__nopage();
      if (!(p_page->thumb_v6))
        p_page->thumb_v6 = fetch_from_cache__thumb_decode(page_id,host_address);
      current_page = p_page->thumb_v6;
      assert(current_page);
      return p_page->thumb_v6->locateInstr(simsoc::get_pc(&slv6_proc));
    } else {
      const uint32_t page_id =
        TranslationPage::pageId(addr_of_current_instr_arm32(&slv6_proc));
      mmu.fetch_page(page_id,host_address,p_page);
      if (!p_page)
      return fetch_from_cache__nopage();
      if (!(p_page->arm_v6))
        p_page->arm_v6 = fetch_from_cache__arm_decode(page_id,host_address);
      current_page = p_page->arm_v6;
      assert(current_page);
      return p_page->arm_v6->locateInstr(simsoc::get_pc(&slv6_proc));
    }
  }

  SLv6_Instruction* ARMv6_Processor::fetch_from_cache__nopage() {
    info() <<"fetch page failed; "
          <<"dynamic translation not used for current instruction (pc="
          <<simsoc::get_pc(&slv6_proc)-2*inst_size(&slv6_proc) <<").\n";
    if (slv6_proc.cpsr.T_flag) {
      const uint16_t bincode =
        mmu.load_instr_16(address_of_current_instruction(&slv6_proc));
      thumb_decode_and_store(&instruction,bincode);
    } else {
      const uint32_t bincode =
        mmu.load_instr_32(address_of_current_instruction(&slv6_proc));
      arm_decode_and_store(&instruction,bincode);
    }
    assert(instruction.args.g0.id<=ARMv6_Processor::UNDEF_OR_UNPRED_ID);
    instruction.sem_fct = slv6_instruction_functions[instruction.args.g0.id];
    return &instruction;
  }

  ARMv6_ArmTranslationPage*
  ARMv6_Processor::fetch_from_cache__arm_decode(const uint32_t page_id,
                                                uint32_t *const host_address) {
    info() <<"create virtual code page " <<hex <<page_id <<" (arm32)" <<endl;
    ARMv6_ArmTranslationPage *page = new ARMv6_ArmTranslationPage(host_address);
    if (mode>=DYN_TRANS_SPEC) {
      page->fill_with_empty_cells();
    } else {
      page->decode();
    }
    //change access permission of translated code page
    if (mprotect(host_address,TranslationPage::TR_PAGE_SIZE,PROT_READ)) {
      error() <<"change access permission of translated code page failed! errmsg = \""
              <<strerror(errno) <<"\"\n";
      exit(1);
    }
    return page;
  }

  ARMv6_ThumbTranslationPage*
  ARMv6_Processor::fetch_from_cache__thumb_decode(const uint32_t page_id,
                                                  uint32_t *const host_address) {
    info() <<"create virtual code page " <<hex <<page_id <<" (thumb)" <<endl;
    ARMv6_ThumbTranslationPage *page = new ARMv6_ThumbTranslationPage(host_address);
    if (mode>=DYN_TRANS_SPEC) {
      page->fill_with_empty_cells();
    } else {
      page->decode();
    }
    //change access permission of translated code page
    if (mprotect(host_address,TranslationPage::TR_PAGE_SIZE,PROT_READ)) {
      error() <<"change access permission of translated code page failed! errmsg = \""
              <<strerror(errno) <<"\"\n";
      exit(1);
    }
    return page;
  }

  void ARMv6_Processor::update_pending_flags() {
    if (irq_pending()!=irq_flag()) {
      if (irq_flag()) {
        clear_irq_flag();
        info() <<"pending flags: IRQ cleared\n";
      } else {
        set_irq_flag();
        info() <<"pending flags: IRQ set\n";
      }
    }
    if (fiq_pending()!=fiq_flag()) {
      if (fiq_flag()) {
        clear_fiq_flag();
        info() <<"pending flags: FIQ cleared\n";
      } else {
        set_fiq_flag();
        info() <<"pending flags: FIQ set\n";
      }
    }
  }

  void ARMv6_Processor::signal(bool) {
    update_pending_flags();
  }

  uint32_t ARMv6_Processor::vector_start() const {
    return cp15.get_exception_vector() ? 0xffff0000 : 0;
  }

  static const char *regnames[16] =
    {"r0","r1","r2","r3","r4","r5","r6","r7",
    "r8","r9","sl","fp","ip","sp","lr","pc"};
  static const char *modenames[7] =
    {"FIQ","IRQ","SVC","ABT","UND","System","User"};

  std::ostream& operator<<(std::ostream &os, const SLv6_StatusRegister &sr) {
    return os <<(sr.N_flag?'N':'n') <<(sr.Z_flag?'Z':'z') <<(sr.C_flag?'C':'c')
              <<(sr.V_flag?'V':'v') <<", " <<(sr.Q_flag?'Q':'q') <<", "
              <<(sr.I_flag?'I':'i') <<(sr.F_flag?'F':'f') <<(sr.T_flag?'T':'t') <<", "
              <<modenames[(int)sr.mode];
  }

  std::ostream& operator<<(std::ostream &os, const SLv6_Processor &proc) {
    os <<"CPSR = " <<proc.cpsr <<endl;
    for (unsigned n=0; n<12; n+=4)
      os <<dec <<regnames[n] <<" = " <<hex <<proc.regs[n] <<", "
        <<dec <<regnames[n+1] <<" = " <<hex <<proc.regs[n+1] <<", "
        <<dec <<regnames[n+2] <<" = " <<hex <<proc.regs[n+2] <<", "
        <<dec <<regnames[n+3] <<" = " <<hex <<proc.regs[n+3] <<endl;
    const uint32_t o = proc.cpsr.T_flag ? 4 : 8;
    os <<dec <<regnames[12] <<" = " <<hex <<proc.regs[12] <<", "
      <<dec <<regnames[13] <<" = " <<hex <<proc.regs[13] <<", "
      <<dec <<regnames[14] <<" = " <<hex <<proc.regs[14] <<", "
      <<dec <<regnames[15] <<" = " <<hex <<proc.regs[15]-o <<"+" <<dec <<o <<endl;
    return os;
  }

} // namespace simsoc
