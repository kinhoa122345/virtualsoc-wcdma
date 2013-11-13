//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "arm_v6_translation_page.hpp"
#include "arm_v6_processor.hpp"
#include "arm_v6_dyntrans.hpp"
#include <libsimsoc/config.h>
#include <cstring>

namespace simsoc {

  ARMv6_TranslationPage::ARMv6_TranslationPage(uint32_t* host_addr,
                                               int instr_size):
    TranslationPage(host_addr),
    nb_instr(TR_PAGE_SIZE/instr_size)
  {
    instructions = new SLv6_Instruction[nb_instr];
    // init to 0 so no ID can be BASIC_BLOCK_ID or OPT_BASIC_BLOCK_ID
    memset(instructions, '\0', nb_instr*sizeof(SLv6_Instruction));
  }

  ARMv6_TranslationPage::~ARMv6_TranslationPage() {
    for (size_t i = 0; i<nb_instr; ++i) {
      if (instructions[i].args.g0.id==ARMv6_Processor::BASIC_BLOCK_32_ID ||
          instructions[i].args.g0.id==ARMv6_Processor::BASIC_BLOCK_16_ID ||
          instructions[i].args.g0.id==ARMv6_Processor::BASIC_BLOCK_32_PROF_ID ||
          instructions[i].args.g0.id==ARMv6_Processor::BASIC_BLOCK_16_PROF_ID)
        delete instructions[i].args.basic_block.bb;
#ifdef HAVE_LLVM
      if (instructions[i].args.g0.id==ARMv6_Processor::BASIC_BLOCK_32_SERV_PROF_ID ||
          instructions[i].args.g0.id==ARMv6_Processor::BASIC_BLOCK_16_SERV_PROF_ID)
        ARMv6_BasicBlock::try_delete(instructions[i].args.basic_block.bb);
      if (instructions[i].args.g0.id==ARMv6_Processor::OPT_BASIC_BLOCK_ID)
        delete instructions[i].args.opt_basic_block.obb;
#endif
    }
    delete[] instructions;
  }

  void ARMv6_TranslationPage::fill_with_empty_cells() {
    for (size_t n = 0; n<nb_instr; ++n) {
      instructions[n].args.g0.id = ARMv6_Processor::EMPTY_CELL_ID;
      instructions[n].sem_fct = armv6_exec_empty_cell;
    }
  }

  ARMv6_ArmTranslationPage::ARMv6_ArmTranslationPage(uint32_t* host_addr):
    ARMv6_TranslationPage(host_addr,4)
  {}

  void ARMv6_ArmTranslationPage::decode() {
    for (size_t n = 0; n<nb_instr; ++n) {
      arm_decode_and_store(&instructions[n],host_address[n]);
      assert(instructions[n].args.g0.id<=ARMv6_Processor::UNDEF_OR_UNPRED_ID);
      instructions[n].sem_fct = slv6_instruction_functions[instructions[n].args.g0.id];
    }
  }

  ARMv6_ThumbTranslationPage::ARMv6_ThumbTranslationPage(uint32_t* host_addr):
    ARMv6_TranslationPage(host_addr,2)
  {}

  void ARMv6_ThumbTranslationPage::decode() {
    const uint16_t *host_addr = reinterpret_cast<const uint16_t*>(host_address);
    for (size_t n = 0; n<nb_instr; ++n) {
      thumb_decode_and_store(&instructions[n],host_addr[n]);
      assert(instructions[n].args.g0.id<=ARMv6_Processor::UNDEF_OR_UNPRED_ID);
      instructions[n].sem_fct = slv6_instruction_functions[instructions[n].args.g0.id];
    }
  }
  
} // namespace simsoc
