//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include <arpa/inet.h>
#include <errno.h>
#include <iomanip>
#include <sys/mman.h>

#include <libsimsoc/display.hpp>
#include <libsimsoc/processors/arm/arm_processor.hpp>
#include "libsimsoc/processors/arm/arm_debugger.hpp"
#include "libsimsoc/processors/arm/arm_decode.hpp"
#include "libsimsoc/processors/arm/arm_translation_page.hpp"
#include "libsimsoc/processors/arm/armis.hpp"
#include "libsimsoc/processors/arm/armis_dyntrans.hpp"
#include "libsimsoc/processors/arm/thumb_decode.hpp"

using namespace std;
using namespace sc_core;

namespace simsoc {

  ParameterBool ARM_Processor::init_high_vector("ARM processor", "-hv",
                                                "enable high vector addresses");

  void printHexAddress (ostream& stream) {
    stream << std::setfill('0') << std::setw(8) << std::internal << std::hex;
  }

  void printHexAddress (VeryNullStream& stream) {}

  void ARM_Processor::debug_hook() {
    static uint64_t count = 0;
    const uint64_t START = main_context().start;
    const uint64_t PERIOD = main_context().period;
    const uint64_t END = START + PERIOD*main_context().number;
    if (START<=count && count<END) {
      if ((count-START)%PERIOD==0) {
        std::cout <<"STEP #" <<dec <<count <<'\n';
        std::cout <<cpu;
      }
    }
    ++count;
  }

  ARM_Processor::ARM_Processor(sc_module_name name,
                               int coreId):
    Processor(name, ARM),
    irq_port(false), fiq_port(false),
    cpu(this),
    iss("ISS",this,coreId,false),
    mmu("MMU",this),
    coprocessors(),
    cp15("CP15",this, &mmu),
    null_coproc("EMPTY_COPROCESSOR_SLOT",this),
    current_instruction(NULL),
    current_page(NULL),
    instr_size(4)
  {
    info() << "Constructing ARMv5 processor\n";
    #ifndef NO_MMU
    debug_port.register_transport_dbg(this,&ProcessorBase::transport_dbg);
    #endif
    irq_port(*this);
    fiq_port(*this);
    for (unsigned n=0; n<15; ++n)
      coprocessors[n] = &null_coproc;
    coprocessors[15] = &cp15;

    mmu.user_mode = cpu.cpsr.mode==ARM_USER;
    set_high_vector(false);

    if (init_high_vector.get())
      set_high_vector(true);
  }

  ARM_Processor::~ARM_Processor() {
    delete current_instruction;
    if (do_statistics()) {
      ofstream ofs;
      ofs.open(stat_file);
      write_statistics(ofs);
      ofs.close();
    }
    debug() <<"sc_time_stamp() = " <<sc_time_stamp() <<endl;
    debug() <<"Destructor called." <<endl;
  }

  /************************************************************/

  // used by the template Core main loop in interpret mode

  ARM_Instruction * ARM_Processor::fetch_instruction() {
    if (cpu.cpsr.t)
      return thumbDecode(mmu.load_instr_16(cpu.regs[ARM_CPU::PC]-4),
                         mmu.load_instr_16(cpu.regs[ARM_CPU::PC]-2));
    else
      return armDecode(mmu.load_instr_32(cpu.regs[ARM_CPU::PC]-8));
  }

  ARM_Instruction *ARM_Processor::fetch_from_cache__nopage() {
    info() <<"fetch page failed; "
           <<"dynamic translation not used for current instruction (pc="
           <<cpu.regs[ARM_CPU::PC]-2*instr_size <<").\n";
    delete current_instruction;
    current_instruction = NULL; // next instruction may fail
    current_instruction = fetch_instruction();
    return current_instruction;
  }

  Thumb_TranslationPage *ARM_Processor::
  fetch_from_cache__decode_thumb(const uint32_t page_id,
                                 uint32_t *const host_address) {
    info() <<"decode virtual code page " <<hex <<page_id <<" (thumb)" <<endl;
    Thumb_TranslationPage * page = new Thumb_TranslationPage(host_address);
    if (mode>=DYN_TRANS_SPEC) {
      page->fill(THUMB_TranslateBlock::get());
    } else {
      page->decode();
    }
    //change access permission of translated code page
    if (mprotect(host_address, ARM_TranslationPage::TR_PAGE_SIZE,PROT_READ)) {
      error() <<"change access permission of translated code page failed! errmsg = \""
              <<strerror(errno) <<"\"\n";
      exit(1);
    }
    return page;
  }

  ARM32_TranslationPage *ARM_Processor::
  fetch_from_cache__decode_arm32(const uint32_t page_id,
                                 uint32_t *const host_address) {
    info() <<"create virtual code page " <<hex <<page_id <<" (arm32)" <<endl;
    ARM32_TranslationPage * page = new ARM32_TranslationPage(host_address);
    if (mode>=DYN_TRANS_SPEC) {
      page->fill(ARM32_TranslateBlock::get());
    } else {
      page->decode();
    }
    //change access permission of translated code page
    if (mprotect(host_address, ARM_TranslationPage::TR_PAGE_SIZE,PROT_READ)) {
      error() <<"change access permission of translated code page failed! errmsg = \""
              <<strerror(errno) <<"\"\n";
      exit(1);
    }
    return page;
  }

  // used by ARM32_TranslateBlock::exec(ARM_Processor&)
  ARM_Instruction **ARM_Processor::get_current_instr_ptr_arm32() {
    TranslationTableItem *p_page;
    uint32_t *host_address;
    const uint32_t page_id = TranslationPage::pageId(cpu.regs[ARM_CPU::PC]-8);
    mmu.fetch_page(page_id, // input
                   host_address, p_page); //output
    assert(p_page);
    assert(!cpu.cpsr.t);
    assert(p_page->arm32);
    return p_page->arm32->locateInstrPtr(cpu.regs[ARM_CPU::PC]);
  }

  // used by THUMB_TranslateBlock::exec(ARM_Processor&)
  ARM_Instruction **ARM_Processor::get_current_instr_ptr_thumb() {
    TranslationTableItem *p_page;
    uint32_t *host_address;
    const uint32_t page_id = TranslationPage::pageId(cpu.regs[ARM_CPU::PC]-4);
    mmu.fetch_page(page_id, // input
                   host_address, p_page); //output
    assert(p_page);
    assert(cpu.cpsr.t);
    assert(p_page->thumb);
    return p_page->thumb->locateInstrPtr(cpu.regs[ARM_CPU::PC]);
  }

  /******************************************************************************/

  void ARM_Processor::set_high_vector(bool value) {
    cp15.set_exception_vector(value);
  }

  uint32_t ARM_Processor::high_vector() {
    return cp15.get_exception_vector()? 0xffff0000: 0;
  }

  void ARM_Processor::raise_interrupt() {
    if (fiq_port&&!cpu.cpsr.f)
      fiq_interrupt();
    else if (irq_port&&!cpu.cpsr.i)
      irq_interrupt();
    else
      UNREACHABLE;
  }

  void ARM_Processor::irq_interrupt() {
    info() <<"IRQ exception raised." <<endl;
    ARM_StatusRegister tmp = cpu.cpsr;
    set_mode(ARM_IRQ);
    cpu.banked_spsr[ARM_IRQ] = tmp;
    cpu.regs[14] = cpu.regs[ARM_CPU::PC]-4;
    cpu.unset_thumb_mode();
    cpu.cpsr.i = true;
    signal();
    cpu.regs[ARM_CPU::PC] = high_vector()+0x18+8;
  }

  void ARM_Processor::fiq_interrupt() {
    info() <<"FIQ exception raised." <<endl;
    ARM_StatusRegister tmp = cpu.cpsr;
    set_mode(ARM_FIQ);
    cpu.banked_spsr[ARM_FIQ] = tmp;
    cpu.regs[14] = cpu.regs[ARM_CPU::PC]-4;
    cpu.unset_thumb_mode();
    cpu.cpsr.i = true;
    cpu.cpsr.f = true;
    signal();
    cpu.regs[ARM_CPU::PC] = high_vector()+0x1c+8;
  }

  void ARM_Processor::undefined_interrupt() {
    info() <<"undefined instruction exception raised." <<endl;
    ARM_StatusRegister tmp = cpu.cpsr;
    set_mode(ARM_UND);
    cpu.banked_spsr[ARM_UND] = tmp;
    cpu.regs[14] = cpu.regs[ARM_CPU::PC]-4;
    cpu.unset_thumb_mode();
    cpu.cpsr.i = true;
    signal();
    cpu.regs[ARM_CPU::PC] = high_vector()+0x4+8;
  }

  void ARM_Processor::prefetch_abort() {
    info() <<"prefetch abort exception raised." <<endl;
    ARM_StatusRegister tmp = cpu.cpsr;
    set_mode(ARM_ABT);
    cpu.banked_spsr[ARM_ABT] = tmp;
    cpu.regs[14] = cpu.regs[ARM_CPU::PC]-4;
    cpu.unset_thumb_mode();
    cpu.cpsr.i = true;
    signal();
    cpu.regs[ARM_CPU::PC] = high_vector()+0xC+8;
    throw(ISS_Exception("prefetch abort"));
  }

  void ARM_Processor::data_abort() {
    info() <<"data abort exception raised." <<endl;
    ARM_StatusRegister tmp = cpu.cpsr;
    set_mode(ARM_ABT);
    cpu.banked_spsr[ARM_ABT] = tmp;
    cpu.regs[14] = cpu.regs[ARM_CPU::PC];
    cpu.unset_thumb_mode();
    cpu.cpsr.i = true;
    signal();
    cpu.regs[ARM_CPU::PC] = high_vector()+0x10+8;
    throw(ISS_Exception("data abort"));
  }

  void ARM_Processor::software_interrupt() {
    info() <<"software interrupt raised." <<endl;
    ARM_StatusRegister tmp = cpu.cpsr;
    set_mode(ARM_SVC);
    cpu.banked_spsr[ARM_SVC] = tmp;
    cpu.regs[14] = cpu.regs[ARM_CPU::PC]-4;
    cpu.unset_thumb_mode();
    cpu.cpsr.i = true;
    signal();
    cpu.regs[ARM_CPU::PC] = high_vector()+0x8+8;
  }

  void ARM_Processor::signal(bool) {
    if (it_pending) {
      // no event notification
      it_pending = !cpu.cpsr.f&&fiq_port || !cpu.cpsr.i&&irq_port;
    } else {
      it_pending = !cpu.cpsr.f&&fiq_port || !cpu.cpsr.i&&irq_port;
      if (it_pending)
        it_event.notify();
    }
    something_pending |= it_pending;
    debug() <<"interrupt set or reset" <<endl;
    debug() <<"IRQ: " <<irq_port.get() <<endl;
    debug() <<"FIQ: " <<fiq_port.get() <<endl;
  }

  void ARM_Processor::set_mode(ARM_Mode new_mode) {
    mmu.user_mode = new_mode==ARM_USER;
    cpu.set_mode_internal(new_mode);
  }

  void ARM_Processor::set_cpsr(uint32_t new_value, uint8_t mask) {
    if (mask&(1<<3)) {
      cpu.cpsr.n = new_value&(1<<31);
      cpu.cpsr.z = new_value&(1<<30);
      cpu.cpsr.c = new_value&(1<<29);
      cpu.cpsr.v = new_value&(1<<28);
      cpu.cpsr.q = new_value&(1<<27);
    }
    if (mask&1) {
      set_mode(arm_mode(new_value&0x1f));
      assert(cpu.cpsr.t==(new_value&(1<<5)));
      cpu.cpsr.f = new_value&(1<<6);
      cpu.cpsr.i = new_value&(1<<7);
      signal();
    }
  }

  void ARM_Processor::spsr_to_cpsr() {
    mmu.user_mode = cpu.spsr().mode==ARM_USER;
    cpu.spsr_to_cpsr_internal();
    signal();
  }

  void ARM_Processor::idle() {
    info() <<"inside idle() with it_pending = " <<it_pending <<std::endl;
    if (!it_pending)
      wait(it_event);
  }

  /******************************************************************************/

  bool ARM_Processor::user_mode() const {
    return cpu.cpsr.mode==ARM_USER;
  }

  /******************************************************************************/

  void ARM_Processor::set_pc(uint64_t pc64) {
#ifndef NDEBUG
    if ((pc64 >> 32))
      warning() << "PC-32 with 32-bits MSW != 0" << std::endl;
#endif
    uint32_t pc = static_cast<uint32_t>(pc64);
    if (pc&1) {
      pc &= ~1;
      debug() <<"PC initialized with value " <<hex <<pc <<" (thumb mode)" <<endl;
      cpu.set_thumb_mode();
      cpu.regs[ARM_CPU::PC] = pc+4;
    } else {
      debug() <<"PC initialized with value " <<hex <<pc <<" (arm32 mode)" <<endl;
      cpu.unset_thumb_mode();
      cpu.regs[ARM_CPU::PC] = pc+8;
    }
  }

  void ARM_Processor::set_lr(uint32_t lr) {
    cpu.regs[ARM_CPU::LR] = lr;
  }

  void ARM_Processor::set_sp(uint64_t sp64) {
    assert(!(sp64>>32));
    cpu.regs[ARM_CPU::SP] = static_cast<uint32_t>(sp64);
  }

  uint64_t ARM_Processor::get_gp_register(size_t n) const {
    assert(n<16);
    return cpu.regs[n];
  }

  void ARM_Processor:: set_gp_register(size_t n, uint64_t data) {
    assert(!(data>>32));
    assert(n<16);
    cpu.regs[n] = static_cast<uint32_t>(data);
  }

  uint32_t ARM_Processor::init_stack(uint32_t argc, char **argv, uint8_t *bytes) {
    uint32_t base = cpu.regs[ARM_CPU::SP];
    uint32_t *words = (uint32_t*) bytes;
    words[0] = argc;
    // fill r1 with argc
    cpu.regs[1] = argc;
    // fill r2 with argv
    uint32_t index = 4;
    cpu.regs[2] = base+index;
    index += 4*argc;
    // add a null pointer just after the end of argv
    words[index/4] = 0;
    index += 4;
    // add another null pointer that specifies an empty environment
    words[index/4] = 0;
    index += 4;
    // copy the strings
    for (unsigned int i = 0; i<argc; ++i) {
      // fill argv[i]
      words[i+1] = base+index;
      // copy string to argv[i]
      uint8_t *c = (uint8_t*) argv[i]-1;
      do {
        bytes[index++] = *(++c);
      } while (*c);
    }
    return base+((index+3)&~3);
  }

  void ARM_Processor::set_endian_little() {
    info() <<"endianness set to little\n";
    cp15.set_big_endian(false);
  }

  void ARM_Processor::set_endian_big() {
    info() <<"endianness set to big\n";
    cp15.set_big_endian(true);
  }
#ifndef NO_MMU
  tlm::tlm_initiator_socket<> &ARM_Processor::get_rw_port() {
    return mmu.rw_socket;
  }
#endif
  SignalTargetPort<bool> &ARM_Processor::get_it_port() {
    return irq_port;
  }

  /******************************************************************************/

  void ARM_Processor::print_instruction(uint32_t addr, uint32_t n) {
    for (uint32_t a = addr; a<addr+4*n; a+=4)
      std::cout <<hex <<a <<'\t'
                <<mmu.memory_read_word(a) <<'\t'
                <<*armDecode(mmu.memory_read_word(a)) <<endl;
  }

  /*******************************************************************************/
  // TODO VJ This code should be generic

  void ARM_Processor::update_statistics(ARM_Instruction*) {
    if (cpu.cpsr.t) {
      TODO("statistics generation for thumb instructions");
    } else {
      uint32_t bincode = static_cast<ARM32_TranslationPage*>(current_page)->
        getBincode(cpu.regs[ARM_CPU::PC]);
      statistics[bincode] += 1;
    }
  }

  void ARM_Processor::read_statistics(istream& is) {
    uint32_t sum, noc;
    string bincode;
    string asm_instr;
    assert(statistics.empty());

    if (do_statistics()) {
      ifstream ifs;
      ifs.open(stat_file);
      if (! ifs.is_open()) {
        error() << "Error reading statistics file\n";
        return;
      }
      is >>sum >>noc >>bincode;
      getline(is,asm_instr);
      while (!!is) {
        statistics[strtoul(bincode.c_str(), NULL, 16)] = noc;
        is >>sum >>noc >>bincode;
        getline(is,asm_instr);
      }
      ifs.close();
    }
  }

  void ARM_Processor::write_statistics(ostream& os) {
    multimap<uint32_t, uint32_t, greater<uint32_t> > s;
    for (map<uint32_t, uint32_t, greater<uint32_t> >::iterator i = statistics.begin();
         i!=statistics.end(); ++i)
      s.insert(pair<uint32_t,uint32_t>(i->second,i->first));
    unsigned int sum = 0;
    for (multimap<uint32_t, uint32_t>::iterator i = s.begin(); i!=s.end(); ++i) {
      ARM_Instruction * instr = armDecode(i->second);
      os.setf(ios::right);
      os.width(10);
      sum += i->first;
      os <<sum;
      os.setf(ios::right);
      os.width(10);
      os <<i->first <<'\t';
      os.flags(ios::hex);
      os.width(9);
      os <<i->second;
      os.flags(ios::dec);
      os <<'\t' <<*instr <<endl;
      delete instr;
    }
  }

  // ------------------------------------------------------------------
  // Debugger interface
  // ------------------------------------------------------------------
  DebugInterface* ARM_Processor::create_dbi() {
    return new ARM_Debugger(*this);
  }

} // namespace simsoc
