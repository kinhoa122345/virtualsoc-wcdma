//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "arm_translation_page.hpp"
#include "arm_decode.hpp"
#include "arm_translate.hpp"
#include "thumb_decode.hpp"
#include "thumb_translate.hpp"
#include <libsimsoc/display.hpp>
#include <cstring>

using namespace std;

namespace simsoc {

  /******************************************************************************/
  ARM_TranslationPage::ARM_TranslationPage(uint32_t* host_addr,
                                           bool t):
    TranslationPage(host_addr),
    instr_size(t? 2: 4),
    nb_instr(TR_PAGE_SIZE/instr_size),
    instructions(NULL)
  {
    instructions = new ARM_Instruction*[nb_instr];
    memset(instructions, '\0', nb_instr*sizeof(ARM_Instruction*));
  }

  ARM_TranslationPage::~ARM_TranslationPage() {
    for (unsigned i=0; i<nb_instr; ++i)
      if (instructions[i]->delete_me())
        delete instructions[i];
    delete[] instructions;
  }

  /******************************************************************************/
  // ARM 32

  ARM32_TranslationPage::ARM32_TranslationPage(uint32_t* host_addr):
    ARM_TranslationPage(host_addr,false) {}

  void ARM32_TranslationPage::decode() {
    for (unsigned n = 0; n<TR_PAGE_SIZE/4; ++n) {
      instructions[n] = armDecode(host_address[n]);
    }
  }

  void ARM32_TranslationPage::fill(ARM32_Instruction *inst) {
    for (unsigned n = 0; n<TR_PAGE_SIZE/4; ++n)
      instructions[n] = inst;
  }

  uint32_t ARM32_TranslationPage::getBincode(uint32_t pc) {
    return host_address[((pc-8)&(TR_PAGE_SIZE-1))/4];
  }

  /******************************************************************************/
  // THUMB

  Thumb_TranslationPage::Thumb_TranslationPage(uint32_t* host_addr):
    ARM_TranslationPage(host_addr,true) {}

  void Thumb_TranslationPage::decode() {
    for (unsigned n = 0; n<TR_PAGE_SIZE/2; ++n) {
      instructions[n] = thumbDecode(((uint16_t*) host_address)[n],
                                    ((uint16_t*) host_address)[n+1]);
    }
  }

  void Thumb_TranslationPage::fill(THUMB_Instruction *inst) {
    for (unsigned n = 0; n<TR_PAGE_SIZE/2; ++n)
      instructions[n] = inst;
  }

  uint16_t Thumb_TranslationPage::getBincode(uint32_t pc) {
    return ((uint16_t*) host_address)[((pc-4)&(TR_PAGE_SIZE-1))/2];
  }

} // namespace simsoc
