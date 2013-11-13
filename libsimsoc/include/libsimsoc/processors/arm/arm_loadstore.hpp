//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef ARM_LOADSTORE_HPP
#define ARM_LOADSTORE_HPP

#include <ostream>

namespace simsoc {

typedef enum {LDR,    // 0
              LDRB,   // 1
              STR,    // 2
              STRB,   // 3
              LDRT,   // 4
              LDRBT,  // 5
              STRT,   // 6
              STRBT,  // 7
              LDRH,   // 8
              LDRSB,  // 9
              LDRSH,  // 10
              STRH,   // 11
              LDRD,   // 12
              STRD    // 13
} LoadStoreOpcode;

LoadStoreOpcode& operator++(LoadStoreOpcode& op);

const LoadStoreOpcode FIRST_LSOP=LDR;
const LoadStoreOpcode LAST_LSOP=STRD;
const LoadStoreOpcode FIRST_LSOP_ADMODE2_9=LDR;

const LoadStoreOpcode FIRST_LSOP_ADMODE2_3=LDRT;

const LoadStoreOpcode FIRST_LSOP_ADMODE3_6=LDRH;

typedef enum {immediate_ls,
              register_source_ls,
              logical_shift_left_reg_ls,
              logical_shift_right_reg_ls,
              arithmetic_shift_reg_ls,
              rotate_shift_reg_ls,
              rotate_shift_extend_ls
} LSOperandMode;

LSOperandMode &operator++ (LSOperandMode &m);

// values of first and last
const LSOperandMode FIRST_OP_MODE_LS = immediate_ls;
const LSOperandMode LAST_OP_MODE_NSH_LS = register_source_ls;
const LSOperandMode LAST_OP_MODE_LS = rotate_shift_reg_ls;

typedef enum {arm32_offset, // 0 index not added/sub to base
              arm32_pre_index, // 1 index added/sub to base before
              arm32_post_index, // 2 index added/sub to base after
} AddressingMode;

std::ostream& operator<<(std::ostream &os,LoadStoreOpcode  op);
extern const char * LOADSTORE_OPCODE_NAMES[14];

} // namespace simsoc

#endif //ARM_LOADSTORE_HPP
