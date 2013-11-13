//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "arm_v6_printers.hpp"
#include "simlight/slv6_math.h"

namespace simsoc {

  void slv6_print_cond(std::ostream &os, SLv6_Condition cond) {
    os <<condition2string(cond);
  }
  
  void slv6_print_mode(std::ostream &os, SLv6_Mode mode) {
    os <<mode2string(mode);
  }

  void slv6_print_reg(std::ostream &os, uint8_t n) {
    assert(n<16);
    switch (n) {
    case 15: os <<"PC"; return;
    case 14: os <<"LR"; return;
    case 13: os <<"SP"; return;
    default: os <<'R' <<std::dec <<(int) n;
    }
  }

  void slv6_print_reglist(std::ostream &os, uint16_t regs) {
    bool first = true;
    int i;
    os <<'{';
    for (i = 0; i<16; ++i)
      if ((regs>>i)&1) {
        if (first) first = false;
        else os <<", ";
        slv6_print_reg(os,i);
      }
    assert(!first);
    os <<'}';
  }

  uint32_t ARMv6_InstPrinter::thumb_bl_offset;

  std::ostream &ARMv6_InstPrinter::display(std::ostream &os) const {
    if (instr.args.g0.id<SLV6_TABLE_SIZE) {
      if (instr.args.g0.id==SLV6_Tb_BL_ID) {
        if (instr.args.SLV6_Tb_BL_GID.H==2) {
          thumb_bl_offset = SignExtend11(instr.args.SLV6_Tb_BL_GID.offset_11) << 12;
          os <<"prefix of a BL/BLX(1) instruction";
        } else if (instr.args.SLV6_Tb_BL_GID.H==3) {
          uint32_t offset = thumb_bl_offset|(instr.args.SLV6_Tb_BL_GID.offset_11<<1);
          if (offset>>31) os <<"BL\tPC-#" <<std::hex <<-offset;
          else os <<"BL\tPC+#" <<std::hex <<offset;
        } else if (instr.args.SLV6_Tb_BL_GID.H==1) {
          uint32_t offset = thumb_bl_offset|(instr.args.SLV6_Tb_BL_GID.offset_11<<1);
          if (offset>>31) os <<"BLX\tPC-#" <<std::hex <<-offset;
          else os <<"BLX\tPC+#" <<std::hex <<offset;
        } else
          abort();
      } else 
        slv6_print_instr(os,const_cast<SLv6_Instruction*>(&instr),bincode);
    } else {
      os <<slv6_instruction_names[instr.args.g0.id];
    }
    return os;
  }
  
} // namespace simsoc
