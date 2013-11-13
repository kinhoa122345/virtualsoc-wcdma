//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef ARM_V6_PROCESSOR_HPP
#define ARM_V6_PROCESSOR_HPP

#include "arm_v5_mmu.hpp"
#include "arm_v5_systemcontrol_coproc.hpp"
#include "libsimsoc/processors/processor.hpp"
#include <libsimsoc/tools/debugger/debugger.hpp>
#include "simlight/slv6_processor.h"
#include "simlight/slv6_iss.h"

namespace simsoc {

  struct SLv6_Instruction;
  class ARMv6_TranslationPage;
  class ARMv6_BasicBlock;

  extern void exec_undefined_instruction(SLv6_Processor*, SLv6_Instruction*);

  class ARMv6_Processor: public Processor,
                         public SignalTarget<bool> {

  int ID, TILE_ID;

  public:

    SC_HAS_PROCESS(ARMv6_Processor);
    ARMv6_Processor(sc_core::sc_module_name name, int ID, int TILE_ID);
    ~ARMv6_Processor();

    void set_pc(uint64_t addr);
    uint64_t get_pc() const;
    void set_sp(uint64_t addr);
    uint64_t get_gp_register(size_t n) const;
    void set_gp_register(size_t n, uint64_t data);
    void set_endian_little();
    void set_endian_big();

	unsigned char get_id(){return ID;}

    void raise_interrupt() {abort();} // mandatory but unused

    // for dynamic translation
    const TranslationPage *get_current_page() const;
    SimulationMode max_mode_available() const;

    // statisitics (not implemented yet)
    void write_statistics(std::ostream& os = std::cout);
    void read_statistics(std::istream& is);
#ifndef NO_MMU
    tlm::tlm_initiator_socket<> &get_rw_port();    
#endif    
    SignalTargetPort<bool> &get_it_port();

    SignalTargetPort<bool> irq_port;
    SignalTargetPort<bool> fiq_port;

    inline bool irq_enable() const {return !slv6_proc.cpsr.I_flag;}
    inline bool fiq_enable() const {return !slv6_proc.cpsr.F_flag;}
    inline bool irq_pending() const {return irq_enable() && irq_port.get();}
    inline bool fiq_pending() const {return fiq_enable() && fiq_port.get();}

    // special instruction identifiers
    static const size_t UNDEF_OR_UNPRED_ID = SLV6_UNPRED_OR_UNDEF_ID;
    static const size_t SET_REG_ID = UNDEF_OR_UNPRED_ID+1;
    static const size_t SET_REG_NC_ID = UNDEF_OR_UNPRED_ID+2;
    static const size_t EMPTY_CELL_ID = UNDEF_OR_UNPRED_ID+3;
    static const size_t BASIC_BLOCK_32_ID = UNDEF_OR_UNPRED_ID+4;
    static const size_t BASIC_BLOCK_16_ID = UNDEF_OR_UNPRED_ID+5;
    static const size_t BASIC_BLOCK_32_PROF_ID = UNDEF_OR_UNPRED_ID+6;
    static const size_t BASIC_BLOCK_16_PROF_ID = UNDEF_OR_UNPRED_ID+7;
    static const size_t BASIC_BLOCK_32_SERV_PROF_ID = UNDEF_OR_UNPRED_ID+8;
    static const size_t BASIC_BLOCK_16_SERV_PROF_ID = UNDEF_OR_UNPRED_ID+9;
    static const size_t OPT_BASIC_BLOCK_ID = UNDEF_OR_UNPRED_ID+10;

    // The simlight processor
    SLv6_Processor slv6_proc;

    // The coprocessors
    ARMv6_Coprocessor *coprocessors[16];
    ARMv6_Coprocessor null_coproc;

    // The MMU and the System Control Coprocessor
    ARMv6_MMU mmu;
    ARMv6_SystemCoproc cp15;

    void debug_hook(); // print debug outputs, not related to gdb

    // for the GDB debugger
    virtual DebugInterface *create_dbi();

    // Implementation of the debug socket
    unsigned int transport_dbg(int, tlm::tlm_generic_payload &payload) {
      return mmu.transport_dbg(payload);
    }

  protected:
    // out of page insturciton and translation page
    SLv6_Instruction instruction;
    ARMv6_TranslationPage *current_page;
    
    // The main SystemC thread, and the simulation loops.
    void compute();
    void interpret();
    void dyntrans();

    // return false if decoding failed
    inline SLv6_Instruction* fetch_instr_from_cache();
    SLv6_Instruction* fetch_from_cache__nopage();
    ARMv6_ArmTranslationPage*
    fetch_from_cache__arm_decode(const uint32_t page_id,
                                 uint32_t *const host_address);
    ARMv6_ThumbTranslationPage*
    fetch_from_cache__thumb_decode(const uint32_t page_id,
                                   uint32_t *const host_address);

  public:
    void update_pending_flags();
    uint32_t vector_start() const;

    void prefetch_abort();
    void data_abort();
  protected:
    void irq_interrupt();
    void fiq_interrupt();

    // Implementation of the SignalTarget interface
    void signal(bool);

    void pending_actions();

    uint32_t pending_flags;
    static const uint32_t FIQ_FLAG = 0;
    static const uint32_t IRQ_FLAG = 1;
    inline bool fiq_flag() const {return pending_flags&(1<<FIQ_FLAG);}
    inline bool irq_flag() const {return pending_flags&(1<<IRQ_FLAG);}
    inline void set_fiq_flag() {pending_flags |= 1<<FIQ_FLAG;}
    inline void clear_fiq_flag() {pending_flags &=~ (1<<FIQ_FLAG);}
    inline void set_irq_flag() {pending_flags |= 1<<IRQ_FLAG;}
    inline void clear_irq_flag() {pending_flags &=~ (1<<IRQ_FLAG);}

    // Raw statistics
    uint32_t *raw_stats;
  };

} // namespace simsoc

#endif // ARM_V6_PROCESSOR_HPP
