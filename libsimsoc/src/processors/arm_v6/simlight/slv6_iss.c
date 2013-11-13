#include "slv6_iss_c_prelude.h"

const char *slv6_instruction_names[SLV6_TABLE_SIZE] = {
  "LDR -- Load and Store Word or Unsigned Byte - Immediate offset",
  "STR -- Load and Store Word or Unsigned Byte - Immediate offset",
  "B, BL (L=1)",
  "B, BL (L=0)",
  "SUB -- Data processing operands - Immediate (S=1)",
  "SUB -- Data processing operands - Immediate (S=0)",
  "CMP -- Data processing operands - Register",
  "ADD -- Data processing operands - Immediate (S=1)",
  "ADD -- Data processing operands - Immediate (S=0)",
  "ADD -- Data processing operands - Register (S=1)",
  "ADD -- Data processing operands - Register (S=0)",
  "EOR -- Data processing operands - Register (S=1)",
  "EOR -- Data processing operands - Register (S=0)",
  "AND -- Data processing operands - Immediate (S=1)",
  "AND -- Data processing operands - Immediate (S=0)",
  "MOV -- Data processing operands - Logical shift right by immediate (S=1)",
  "MOV -- Data processing operands - Logical shift right by immediate (S=0)",
  "CPY",
  "MOV -- Data processing operands - Logical shift left by immediate (S=1)",
  "MOV -- Data processing operands - Logical shift left by immediate (S=0)",
  "MOV -- Data processing operands - Immediate (S=1)",
  "MOV -- Data processing operands - Immediate (S=0)",
  "LDM (1) -- Load and Store Multiple - Increment after (W=1)",
  "LDM (1) -- Load and Store Multiple - Increment after (W=0)",
  "CMP -- Data processing operands - Immediate",
  "LDR -- Load and Store Word or Unsigned Byte - Scaled register offset (U=1)",
  "LDR -- Load and Store Word or Unsigned Byte - Scaled register offset (U=0)",
  "BX",
  "ADD -- Data processing operands - Logical shift left by immediate (S=1)",
  "ADD -- Data processing operands - Logical shift left by immediate (S=0)",
  "LDRB -- Load and Store Word or Unsigned Byte - Immediate offset",
  "ORR -- Data processing operands - Register (S=1)",
  "ORR -- Data processing operands - Register (S=0)",
  "MOV -- Data processing operands - Rotate right by immediate (S=1)",
  "MOV -- Data processing operands - Rotate right by immediate (S=0)",
  "LDR -- Load and Store Word or Unsigned Byte - Immediate post indexed",
  "EOR -- Data processing operands - Rotate right by immediate (S=1)",
  "EOR -- Data processing operands - Rotate right by immediate (S=0)",
  "AND -- Data processing operands - Register (S=1)",
  "AND -- Data processing operands - Register (S=0)",
  "STR -- Load and Store Word or Unsigned Byte - Immediate pre indexed",
  "STRB -- Load and Store Word or Unsigned Byte - Immediate offset",
  "ORR -- Data processing operands - Logical shift left by immediate (S=1)",
  "ORR -- Data processing operands - Logical shift left by immediate (S=0)",
  "ADC -- Data processing operands - Register (S=1)",
  "ADC -- Data processing operands - Register (S=0)",
  "LDRB -- Load and Store Word or Unsigned Byte - Register offset (U=1)",
  "LDRB -- Load and Store Word or Unsigned Byte - Register offset (U=0)",
  "RSB -- Data processing operands - Register (S=1)",
  "RSB -- Data processing operands - Register (S=0)",
  "BIC -- Data processing operands - Immediate (S=1)",
  "BIC -- Data processing operands - Immediate (S=0)",
  "MVN -- Data processing operands - Immediate (S=1)",
  "MVN -- Data processing operands - Immediate (S=0)",
  "ORR -- Data processing operands - Logical shift right by immediate (S=1)",
  "ORR -- Data processing operands - Logical shift right by immediate (S=0)",
  "EOR -- Data processing operands - Logical shift right by immediate (S=1)",
  "EOR -- Data processing operands - Logical shift right by immediate (S=0)",
  "LDR -- Load and Store Word or Unsigned Byte - Register offset (U=1)",
  "LDR -- Load and Store Word or Unsigned Byte - Register offset (U=0)",
  "MOV -- Data processing operands - Logical shift right by register (S=1)",
  "MOV -- Data processing operands - Logical shift right by register (S=0)",
  "STRB -- Load and Store Word or Unsigned Byte - Register offset (U=1)",
  "STRB -- Load and Store Word or Unsigned Byte - Register offset (U=0)",
  "STR -- Load and Store Word or Unsigned Byte - Scaled register offset (U=1)",
  "STR -- Load and Store Word or Unsigned Byte - Scaled register offset (U=0)",
  "CMN -- Data processing operands - Register",
  "STR -- Load and Store Word or Unsigned Byte - Register post indexed (U=1)",
  "STR -- Load and Store Word or Unsigned Byte - Register post indexed (U=0)",
  "STR -- Load and Store Word or Unsigned Byte - Register offset (U=1)",
  "STR -- Load and Store Word or Unsigned Byte - Register offset (U=0)",
  "EOR -- Data processing operands - Logical shift left by immediate (S=1)",
  "EOR -- Data processing operands - Logical shift left by immediate (S=0)",
  "RSB -- Data processing operands - Immediate (S=1)",
  "RSB -- Data processing operands - Immediate (S=0)",
  "MOV -- Data processing operands - Arithmetic shift right by immediate (S=1)",
  "MOV -- Data processing operands - Arithmetic shift right by immediate (S=0)",
  "ADD -- Data processing operands - Rotate right by immediate (S=1)",
  "ADD -- Data processing operands - Rotate right by immediate (S=0)",
  "RSB -- Data processing operands - Logical shift left by immediate (S=1)",
  "RSB -- Data processing operands - Logical shift left by immediate (S=0)",
  "STRB -- Load and Store Word or Unsigned Byte - Immediate post indexed",
  "STM (1) -- Load and Store Multiple - Increment after (W=1)",
  "STM (1) -- Load and Store Multiple - Increment after (W=0)",
  "TST -- Data processing operands - Immediate",
  "STM (1) -- Load and Store Multiple - Decrement before (W=1)",
  "STM (1) -- Load and Store Multiple - Decrement before (W=0)",
  "MVN -- Data processing operands - Register (S=1)",
  "MVN -- Data processing operands - Register (S=0)",
  "STM (1) -- Load and Store Multiple - Increment before (W=1)",
  "STM (1) -- Load and Store Multiple - Increment before (W=0)",
  "ADD -- Data processing operands - Logical shift right by immediate (S=1)",
  "ADD -- Data processing operands - Logical shift right by immediate (S=0)",
  "STR -- Load and Store Word or Unsigned Byte - Immediate post indexed",
  "LDRB -- Load and Store Word or Unsigned Byte - Scaled register offset (U=1)",
  "LDRB -- Load and Store Word or Unsigned Byte - Scaled register offset (U=0)",
  "SUB -- Data processing operands - Logical shift left by immediate (S=1)",
  "SUB -- Data processing operands - Logical shift left by immediate (S=0)",
  "LDM (1) -- Load and Store Multiple - Increment before (W=1)",
  "LDM (1) -- Load and Store Multiple - Increment before (W=0)",
  "LDRH -- Miscellaneous Loads and Stores - Immediate offset (U=1)",
  "LDRH -- Miscellaneous Loads and Stores - Immediate offset (U=0)",
  "LDR -- Load and Store Word or Unsigned Byte - Immediate pre indexed",
  "SMULL (S=1)",
  "SMULL (S=0)",
  "RSB -- Data processing operands - Arithmetic shift right by immediate (S=1)",
  "RSB -- Data processing operands - Arithmetic shift right by immediate (S=0)",
  "TST -- Data processing operands - Register",
  "EOR -- Data processing operands - Immediate (S=1)",
  "EOR -- Data processing operands - Immediate (S=0)",
  "ORR -- Data processing operands - Arithmetic shift right by immediate (S=1)",
  "ORR -- Data processing operands - Arithmetic shift right by immediate (S=0)",
  "ORR -- Data processing operands - Immediate (S=1)",
  "ORR -- Data processing operands - Immediate (S=0)",
  "SUB -- Data processing operands - Arithmetic shift right by immediate (S=1)",
  "SUB -- Data processing operands - Arithmetic shift right by immediate (S=0)",
  "MOV -- Data processing operands - Logical shift left by register (S=1)",
  "MOV -- Data processing operands - Logical shift left by register (S=0)",
  "MUL (S=1)",
  "MUL (S=0)",
  "CMN -- Data processing operands - Immediate",
  "ADC -- Data processing operands - Immediate",
  "ADC -- Data processing operands - Logical shift left by immediate",
  "ADC -- Data processing operands - Logical shift left by register",
  "ADC -- Data processing operands - Logical shift right by immediate",
  "ADC -- Data processing operands - Logical shift right by register",
  "ADC -- Data processing operands - Arithmetic shift right by immediate",
  "ADC -- Data processing operands - Arithmetic shift right by register",
  "ADC -- Data processing operands - Rotate right by immediate",
  "ADC -- Data processing operands - Rotate right by register",
  "ADC -- Data processing operands - Rotate right with extend",
  "ADD -- Data processing operands - Logical shift left by register",
  "ADD -- Data processing operands - Logical shift right by register",
  "ADD -- Data processing operands - Arithmetic shift right by immediate",
  "ADD -- Data processing operands - Arithmetic shift right by register",
  "ADD -- Data processing operands - Rotate right by register",
  "ADD -- Data processing operands - Rotate right with extend",
  "AND -- Data processing operands - Logical shift left by immediate",
  "AND -- Data processing operands - Logical shift left by register",
  "AND -- Data processing operands - Logical shift right by immediate",
  "AND -- Data processing operands - Logical shift right by register",
  "AND -- Data processing operands - Arithmetic shift right by immediate",
  "AND -- Data processing operands - Arithmetic shift right by register",
  "AND -- Data processing operands - Rotate right by immediate",
  "AND -- Data processing operands - Rotate right by register",
  "AND -- Data processing operands - Rotate right with extend",
  "BIC -- Data processing operands - Register",
  "BIC -- Data processing operands - Logical shift left by immediate",
  "BIC -- Data processing operands - Logical shift left by register",
  "BIC -- Data processing operands - Logical shift right by immediate",
  "BIC -- Data processing operands - Logical shift right by register",
  "BIC -- Data processing operands - Arithmetic shift right by immediate",
  "BIC -- Data processing operands - Arithmetic shift right by register",
  "BIC -- Data processing operands - Rotate right by immediate",
  "BIC -- Data processing operands - Rotate right by register",
  "BIC -- Data processing operands - Rotate right with extend",
  "BKPT",
  "BLX (1)",
  "BLX (2)",
  "BXJ",
  "CDP",
  "CLZ",
  "CMN -- Data processing operands - Logical shift left by immediate",
  "CMN -- Data processing operands - Logical shift left by register",
  "CMN -- Data processing operands - Logical shift right by immediate",
  "CMN -- Data processing operands - Logical shift right by register",
  "CMN -- Data processing operands - Arithmetic shift right by immediate",
  "CMN -- Data processing operands - Arithmetic shift right by register",
  "CMN -- Data processing operands - Rotate right by immediate",
  "CMN -- Data processing operands - Rotate right by register",
  "CMN -- Data processing operands - Rotate right with extend",
  "CMP -- Data processing operands - Logical shift left by immediate",
  "CMP -- Data processing operands - Logical shift left by register",
  "CMP -- Data processing operands - Logical shift right by immediate",
  "CMP -- Data processing operands - Logical shift right by register",
  "CMP -- Data processing operands - Arithmetic shift right by immediate",
  "CMP -- Data processing operands - Arithmetic shift right by register",
  "CMP -- Data processing operands - Rotate right by immediate",
  "CMP -- Data processing operands - Rotate right by register",
  "CMP -- Data processing operands - Rotate right with extend",
  "CPS",
  "EOR -- Data processing operands - Logical shift left by register",
  "EOR -- Data processing operands - Logical shift right by register",
  "EOR -- Data processing operands - Arithmetic shift right by immediate",
  "EOR -- Data processing operands - Arithmetic shift right by register",
  "EOR -- Data processing operands - Rotate right by register",
  "EOR -- Data processing operands - Rotate right with extend",
  "LDC -- Load and Store Coprocessor - Immediate offset",
  "LDC -- Load and Store Coprocessor - Immediate pre indexed",
  "LDC -- Load and Store Coprocessor - Immediate post indexed",
  "LDC -- Load and Store Coprocessor - Unindexed",
  "LDM (1) -- Load and Store Multiple - Decrement after",
  "LDM (1) -- Load and Store Multiple - Decrement before",
  "LDM (2) -- Load and Store Multiple - Increment after",
  "LDM (2) -- Load and Store Multiple - Increment before",
  "LDM (2) -- Load and Store Multiple - Decrement after",
  "LDM (2) -- Load and Store Multiple - Decrement before",
  "LDM (3) -- Load and Store Multiple - Increment after",
  "LDM (3) -- Load and Store Multiple - Increment before",
  "LDM (3) -- Load and Store Multiple - Decrement after",
  "LDM (3) -- Load and Store Multiple - Decrement before",
  "LDR -- Load and Store Word or Unsigned Byte - Register pre indexed",
  "LDR -- Load and Store Word or Unsigned Byte - Scaled register pre indexed",
  "LDR -- Load and Store Word or Unsigned Byte - Register post indexed",
  "LDR -- Load and Store Word or Unsigned Byte - Scaled register post indexed",
  "LDRB -- Load and Store Word or Unsigned Byte - Immediate pre indexed",
  "LDRB -- Load and Store Word or Unsigned Byte - Register pre indexed",
  "LDRB -- Load and Store Word or Unsigned Byte - Scaled register pre indexed",
  "LDRB -- Load and Store Word or Unsigned Byte - Immediate post indexed",
  "LDRB -- Load and Store Word or Unsigned Byte - Register post indexed",
  "LDRB -- Load and Store Word or Unsigned Byte - Scaled register post indexed",
  "LDRBT -- Load and Store Word or Unsigned Byte - Immediate post indexed",
  "LDRBT -- Load and Store Word or Unsigned Byte - Register post indexed",
  "LDRBT -- Load and Store Word or Unsigned Byte - Scaled register post indexed",
  "LDRD -- Miscellaneous Loads and Stores - Immediate offset",
  "LDRD -- Miscellaneous Loads and Stores - Register offset",
  "LDRD -- Miscellaneous Loads and Stores - Immediate pre indexed",
  "LDRD -- Miscellaneous Loads and Stores - Register pre indexed",
  "LDRD -- Miscellaneous Loads and Stores - Immediate post indexed",
  "LDRD -- Miscellaneous Loads and Stores - Register post indexed",
  "LDREX",
  "LDRH -- Miscellaneous Loads and Stores - Register offset",
  "LDRH -- Miscellaneous Loads and Stores - Immediate pre indexed",
  "LDRH -- Miscellaneous Loads and Stores - Register pre indexed",
  "LDRH -- Miscellaneous Loads and Stores - Immediate post indexed",
  "LDRH -- Miscellaneous Loads and Stores - Register post indexed",
  "LDRSB -- Miscellaneous Loads and Stores - Immediate offset",
  "LDRSB -- Miscellaneous Loads and Stores - Register offset",
  "LDRSB -- Miscellaneous Loads and Stores - Immediate pre indexed",
  "LDRSB -- Miscellaneous Loads and Stores - Register pre indexed",
  "LDRSB -- Miscellaneous Loads and Stores - Immediate post indexed",
  "LDRSB -- Miscellaneous Loads and Stores - Register post indexed",
  "LDRSH -- Miscellaneous Loads and Stores - Immediate offset",
  "LDRSH -- Miscellaneous Loads and Stores - Register offset",
  "LDRSH -- Miscellaneous Loads and Stores - Immediate pre indexed",
  "LDRSH -- Miscellaneous Loads and Stores - Register pre indexed",
  "LDRSH -- Miscellaneous Loads and Stores - Immediate post indexed",
  "LDRSH -- Miscellaneous Loads and Stores - Register post indexed",
  "LDRT -- Load and Store Word or Unsigned Byte - Immediate post indexed",
  "LDRT -- Load and Store Word or Unsigned Byte - Register post indexed",
  "LDRT -- Load and Store Word or Unsigned Byte - Scaled register post indexed",
  "MCR",
  "MCRR",
  "MLA",
  "MOV -- Data processing operands - Register",
  "MOV -- Data processing operands - Arithmetic shift right by register",
  "MOV -- Data processing operands - Rotate right by register",
  "MOV -- Data processing operands - Rotate right with extend",
  "MRC",
  "MRRC",
  "MRS",
  "MSRimm",
  "MSRreg",
  "MVN -- Data processing operands - Logical shift left by immediate",
  "MVN -- Data processing operands - Logical shift left by register",
  "MVN -- Data processing operands - Logical shift right by immediate",
  "MVN -- Data processing operands - Logical shift right by register",
  "MVN -- Data processing operands - Arithmetic shift right by immediate",
  "MVN -- Data processing operands - Arithmetic shift right by register",
  "MVN -- Data processing operands - Rotate right by immediate",
  "MVN -- Data processing operands - Rotate right by register",
  "MVN -- Data processing operands - Rotate right with extend",
  "ORR -- Data processing operands - Logical shift left by register",
  "ORR -- Data processing operands - Logical shift right by register",
  "ORR -- Data processing operands - Arithmetic shift right by register",
  "ORR -- Data processing operands - Rotate right by immediate",
  "ORR -- Data processing operands - Rotate right by register",
  "ORR -- Data processing operands - Rotate right with extend",
  "PKHBT",
  "PKHTB",
  "PLD -- Load and Store Word or Unsigned Byte - Immediate offset",
  "PLD -- Load and Store Word or Unsigned Byte - Register offset",
  "PLD -- Load and Store Word or Unsigned Byte - Scaled register offset",
  "QADD",
  "QADD16",
  "QADD8",
  "QADDSUBX",
  "QDADD",
  "QDSUB",
  "QSUB",
  "QSUB16",
  "QSUB8",
  "QSUBADDX",
  "REV",
  "REV16",
  "REVSH",
  "RFE -- Load and Store Multiple - Increment after",
  "RFE -- Load and Store Multiple - Increment before",
  "RFE -- Load and Store Multiple - Decrement after",
  "RFE -- Load and Store Multiple - Decrement before",
  "RSB -- Data processing operands - Logical shift left by register",
  "RSB -- Data processing operands - Logical shift right by immediate",
  "RSB -- Data processing operands - Logical shift right by register",
  "RSB -- Data processing operands - Arithmetic shift right by register",
  "RSB -- Data processing operands - Rotate right by immediate",
  "RSB -- Data processing operands - Rotate right by register",
  "RSB -- Data processing operands - Rotate right with extend",
  "RSC -- Data processing operands - Immediate",
  "RSC -- Data processing operands - Register",
  "RSC -- Data processing operands - Logical shift left by immediate",
  "RSC -- Data processing operands - Logical shift left by register",
  "RSC -- Data processing operands - Logical shift right by immediate",
  "RSC -- Data processing operands - Logical shift right by register",
  "RSC -- Data processing operands - Arithmetic shift right by immediate",
  "RSC -- Data processing operands - Arithmetic shift right by register",
  "RSC -- Data processing operands - Rotate right by immediate",
  "RSC -- Data processing operands - Rotate right by register",
  "RSC -- Data processing operands - Rotate right with extend",
  "SADD16",
  "SADD8",
  "SADDSUBX",
  "SBC -- Data processing operands - Immediate",
  "SBC -- Data processing operands - Register",
  "SBC -- Data processing operands - Logical shift left by immediate",
  "SBC -- Data processing operands - Logical shift left by register",
  "SBC -- Data processing operands - Logical shift right by immediate",
  "SBC -- Data processing operands - Logical shift right by register",
  "SBC -- Data processing operands - Arithmetic shift right by immediate",
  "SBC -- Data processing operands - Arithmetic shift right by register",
  "SBC -- Data processing operands - Rotate right by immediate",
  "SBC -- Data processing operands - Rotate right by register",
  "SBC -- Data processing operands - Rotate right with extend",
  "SEL",
  "SETEND",
  "SHADD16",
  "SHADD8",
  "SHADDSUBX",
  "SHSUB16",
  "SHSUB8",
  "SHSUBADDX",
  "SMLA<x><y>",
  "SMLAD",
  "SMLAL",
  "SMLAL<x><y>",
  "SMLALD",
  "SMLAW<y>",
  "SMLSD",
  "SMLSLD",
  "SMMLA",
  "SMMLS",
  "SMMUL",
  "SMUAD",
  "SMUL<x><y>",
  "SMULW<y>",
  "SMUSD",
  "SRS -- Load and Store Multiple - Increment after",
  "SRS -- Load and Store Multiple - Increment before",
  "SRS -- Load and Store Multiple - Decrement after",
  "SRS -- Load and Store Multiple - Decrement before",
  "SSAT",
  "SSAT16",
  "SSUB16",
  "SSUB8",
  "SSUBADDX",
  "STC -- Load and Store Coprocessor - Immediate offset",
  "STC -- Load and Store Coprocessor - Immediate pre indexed",
  "STC -- Load and Store Coprocessor - Immediate post indexed",
  "STC -- Load and Store Coprocessor - Unindexed",
  "STM (1) -- Load and Store Multiple - Decrement after",
  "STM (2) -- Load and Store Multiple - Increment after",
  "STM (2) -- Load and Store Multiple - Increment before",
  "STM (2) -- Load and Store Multiple - Decrement after",
  "STM (2) -- Load and Store Multiple - Decrement before",
  "STR -- Load and Store Word or Unsigned Byte - Register pre indexed",
  "STR -- Load and Store Word or Unsigned Byte - Scaled register pre indexed",
  "STR -- Load and Store Word or Unsigned Byte - Scaled register post indexed",
  "STRB -- Load and Store Word or Unsigned Byte - Scaled register offset",
  "STRB -- Load and Store Word or Unsigned Byte - Immediate pre indexed",
  "STRB -- Load and Store Word or Unsigned Byte - Register pre indexed",
  "STRB -- Load and Store Word or Unsigned Byte - Scaled register pre indexed",
  "STRB -- Load and Store Word or Unsigned Byte - Register post indexed",
  "STRB -- Load and Store Word or Unsigned Byte - Scaled register post indexed",
  "STRBT -- Load and Store Word or Unsigned Byte - Immediate post indexed",
  "STRBT -- Load and Store Word or Unsigned Byte - Register post indexed",
  "STRBT -- Load and Store Word or Unsigned Byte - Scaled register post indexed",
  "STRD -- Miscellaneous Loads and Stores - Immediate offset",
  "STRD -- Miscellaneous Loads and Stores - Register offset",
  "STRD -- Miscellaneous Loads and Stores - Immediate pre indexed",
  "STRD -- Miscellaneous Loads and Stores - Register pre indexed",
  "STRD -- Miscellaneous Loads and Stores - Immediate post indexed",
  "STRD -- Miscellaneous Loads and Stores - Register post indexed",
  "STREX",
  "STRH -- Miscellaneous Loads and Stores - Immediate offset",
  "STRH -- Miscellaneous Loads and Stores - Register offset",
  "STRH -- Miscellaneous Loads and Stores - Immediate pre indexed",
  "STRH -- Miscellaneous Loads and Stores - Register pre indexed",
  "STRH -- Miscellaneous Loads and Stores - Immediate post indexed",
  "STRH -- Miscellaneous Loads and Stores - Register post indexed",
  "STRT -- Load and Store Word or Unsigned Byte - Immediate post indexed",
  "STRT -- Load and Store Word or Unsigned Byte - Register post indexed",
  "STRT -- Load and Store Word or Unsigned Byte - Scaled register post indexed",
  "SUB -- Data processing operands - Register",
  "SUB -- Data processing operands - Logical shift left by register",
  "SUB -- Data processing operands - Logical shift right by immediate",
  "SUB -- Data processing operands - Logical shift right by register",
  "SUB -- Data processing operands - Arithmetic shift right by register",
  "SUB -- Data processing operands - Rotate right by immediate",
  "SUB -- Data processing operands - Rotate right by register",
  "SUB -- Data processing operands - Rotate right with extend",
  "SWI",
  "SWP",
  "SWPB",
  "SXTAB",
  "SXTAB16",
  "SXTAH",
  "SXTB",
  "SXTB16",
  "SXTH",
  "TEQ -- Data processing operands - Immediate",
  "TEQ -- Data processing operands - Register",
  "TEQ -- Data processing operands - Logical shift left by immediate",
  "TEQ -- Data processing operands - Logical shift left by register",
  "TEQ -- Data processing operands - Logical shift right by immediate",
  "TEQ -- Data processing operands - Logical shift right by register",
  "TEQ -- Data processing operands - Arithmetic shift right by immediate",
  "TEQ -- Data processing operands - Arithmetic shift right by register",
  "TEQ -- Data processing operands - Rotate right by immediate",
  "TEQ -- Data processing operands - Rotate right by register",
  "TEQ -- Data processing operands - Rotate right with extend",
  "TST -- Data processing operands - Logical shift left by immediate",
  "TST -- Data processing operands - Logical shift left by register",
  "TST -- Data processing operands - Logical shift right by immediate",
  "TST -- Data processing operands - Logical shift right by register",
  "TST -- Data processing operands - Arithmetic shift right by immediate",
  "TST -- Data processing operands - Arithmetic shift right by register",
  "TST -- Data processing operands - Rotate right by immediate",
  "TST -- Data processing operands - Rotate right by register",
  "TST -- Data processing operands - Rotate right with extend",
  "UADD16",
  "UADD8",
  "UADDSUBX",
  "UHADD16",
  "UHADD8",
  "UHADDSUBX",
  "UHSUB16",
  "UHSUB8",
  "UHSUBADDX",
  "UMAAL",
  "UMLAL",
  "UMULL",
  "UQADD16",
  "UQADD8",
  "UQADDSUBX",
  "UQSUB16",
  "UQSUB8",
  "UQSUBADDX",
  "USAD8",
  "USADA8",
  "USAT",
  "USAT16",
  "USUB16",
  "USUB8",
  "USUBADDX",
  "UXTAB",
  "UXTAB16",
  "UXTAH",
  "UXTB",
  "UXTB16",
  "UXTH",
  "LDR (1)",
  "CPY",
  "STR (1)",
  "B (1)",
  "LSL (1)",
  "ADD (3)",
  "MOV (1)",
  "CMP (2)",
  "LDR (3)",
  "EOR",
  "SUB (2)",
  "MOV (2)",
  "ADD (2)",
  "LDR (4)",
  "AND",
  "LSR (1)",
  "LDR (2)",
  "ADD (4)",
  "CMP (1)",
  "ORR",
  "STR (3)",
  "ROR",
  "BL, BLX (1)",
  "B (2)",
  "NEG",
  "LDRB (1)",
  "PUSH",
  "POP",
  "CMP (3)",
  "SUB (4)",
  "ADD (7)",
  "ADD (6)",
  "BX",
  "STRB (1)",
  "LDRB (2)",
  "ADC",
  "SUB (3)",
  "SUB (1)",
  "LSR (2)",
  "STR (2)",
  "STRB (2)",
  "LDMIA",
  "STMIA",
  "ADD (1)",
  "MUL",
  "ASR (1)",
  "MVN",
  "LDRH (1)",
  "TST",
  "BIC",
  "LSL (2)",
  "ADD (5)",
  "ASR (2)",
  "BKPT",
  "BLX (2)",
  "CMN",
  "CPS",
  "LDRH (2)",
  "LDRSB",
  "LDRSH",
  "REV",
  "REV16",
  "REVSH",
  "SBC",
  "SETEND",
  "STRH (1)",
  "STRH (2)",
  "SWI",
  "SXTB",
  "SXTH",
  "UXTB",
  "UXTH",
  "LDR -- Load and Store Word or Unsigned Byte - Immediate offset (no cond)",
  "STR -- Load and Store Word or Unsigned Byte - Immediate offset (no cond)",
  "B, BL (L=1) (no cond)",
  "B, BL (L=0) (no cond)",
  "SUB -- Data processing operands - Immediate (S=1) (no cond)",
  "SUB -- Data processing operands - Immediate (S=0) (no cond)",
  "CMP -- Data processing operands - Register (no cond)",
  "ADD -- Data processing operands - Immediate (S=1) (no cond)",
  "ADD -- Data processing operands - Immediate (S=0) (no cond)",
  "ADD -- Data processing operands - Register (S=1) (no cond)",
  "ADD -- Data processing operands - Register (S=0) (no cond)",
  "EOR -- Data processing operands - Register (S=1) (no cond)",
  "EOR -- Data processing operands - Register (S=0) (no cond)",
  "AND -- Data processing operands - Immediate (S=1) (no cond)",
  "AND -- Data processing operands - Immediate (S=0) (no cond)",
  "MOV -- Data processing operands - Logical shift right by immediate (S=1) (no cond)",
  "MOV -- Data processing operands - Logical shift right by immediate (S=0) (no cond)",
  "CPY (no cond)",
  "MOV -- Data processing operands - Logical shift left by immediate (S=1) (no cond)",
  "MOV -- Data processing operands - Logical shift left by immediate (S=0) (no cond)",
  "MOV -- Data processing operands - Immediate (S=1) (no cond)",
  "MOV -- Data processing operands - Immediate (S=0) (no cond)",
  "LDM (1) -- Load and Store Multiple - Increment after (W=1) (no cond)",
  "LDM (1) -- Load and Store Multiple - Increment after (W=0) (no cond)",
  "CMP -- Data processing operands - Immediate (no cond)",
  "LDR -- Load and Store Word or Unsigned Byte - Scaled register offset (U=1) (no cond)",
  "LDR -- Load and Store Word or Unsigned Byte - Scaled register offset (U=0) (no cond)",
  "BX (no cond)",
  "ADD -- Data processing operands - Logical shift left by immediate (S=1) (no cond)",
  "ADD -- Data processing operands - Logical shift left by immediate (S=0) (no cond)",
  "LDRB -- Load and Store Word or Unsigned Byte - Immediate offset (no cond)",
  "ORR -- Data processing operands - Register (S=1) (no cond)",
  "ORR -- Data processing operands - Register (S=0) (no cond)",
  "MOV -- Data processing operands - Rotate right by immediate (S=1) (no cond)",
  "MOV -- Data processing operands - Rotate right by immediate (S=0) (no cond)",
  "LDR -- Load and Store Word or Unsigned Byte - Immediate post indexed (no cond)",
  "EOR -- Data processing operands - Rotate right by immediate (S=1) (no cond)",
  "EOR -- Data processing operands - Rotate right by immediate (S=0) (no cond)",
  "AND -- Data processing operands - Register (S=1) (no cond)",
  "AND -- Data processing operands - Register (S=0) (no cond)",
  "STR -- Load and Store Word or Unsigned Byte - Immediate pre indexed (no cond)",
  "STRB -- Load and Store Word or Unsigned Byte - Immediate offset (no cond)",
  "ORR -- Data processing operands - Logical shift left by immediate (S=1) (no cond)",
  "ORR -- Data processing operands - Logical shift left by immediate (S=0) (no cond)",
  "ADC -- Data processing operands - Register (S=1) (no cond)",
  "ADC -- Data processing operands - Register (S=0) (no cond)",
  "LDRB -- Load and Store Word or Unsigned Byte - Register offset (U=1) (no cond)",
  "LDRB -- Load and Store Word or Unsigned Byte - Register offset (U=0) (no cond)",
  "RSB -- Data processing operands - Register (S=1) (no cond)",
  "RSB -- Data processing operands - Register (S=0) (no cond)",
  "BIC -- Data processing operands - Immediate (S=1) (no cond)",
  "BIC -- Data processing operands - Immediate (S=0) (no cond)",
  "MVN -- Data processing operands - Immediate (S=1) (no cond)",
  "MVN -- Data processing operands - Immediate (S=0) (no cond)",
  "ORR -- Data processing operands - Logical shift right by immediate (S=1) (no cond)",
  "ORR -- Data processing operands - Logical shift right by immediate (S=0) (no cond)",
  "EOR -- Data processing operands - Logical shift right by immediate (S=1) (no cond)",
  "EOR -- Data processing operands - Logical shift right by immediate (S=0) (no cond)",
  "LDR -- Load and Store Word or Unsigned Byte - Register offset (U=1) (no cond)",
  "LDR -- Load and Store Word or Unsigned Byte - Register offset (U=0) (no cond)",
  "MOV -- Data processing operands - Logical shift right by register (S=1) (no cond)",
  "MOV -- Data processing operands - Logical shift right by register (S=0) (no cond)",
  "STRB -- Load and Store Word or Unsigned Byte - Register offset (U=1) (no cond)",
  "STRB -- Load and Store Word or Unsigned Byte - Register offset (U=0) (no cond)",
  "STR -- Load and Store Word or Unsigned Byte - Scaled register offset (U=1) (no cond)",
  "STR -- Load and Store Word or Unsigned Byte - Scaled register offset (U=0) (no cond)",
  "CMN -- Data processing operands - Register (no cond)",
  "STR -- Load and Store Word or Unsigned Byte - Register post indexed (U=1) (no cond)",
  "STR -- Load and Store Word or Unsigned Byte - Register post indexed (U=0) (no cond)",
  "STR -- Load and Store Word or Unsigned Byte - Register offset (U=1) (no cond)",
  "STR -- Load and Store Word or Unsigned Byte - Register offset (U=0) (no cond)",
  "EOR -- Data processing operands - Logical shift left by immediate (S=1) (no cond)",
  "EOR -- Data processing operands - Logical shift left by immediate (S=0) (no cond)",
  "RSB -- Data processing operands - Immediate (S=1) (no cond)",
  "RSB -- Data processing operands - Immediate (S=0) (no cond)",
  "MOV -- Data processing operands - Arithmetic shift right by immediate (S=1) (no cond)",
  "MOV -- Data processing operands - Arithmetic shift right by immediate (S=0) (no cond)",
  "ADD -- Data processing operands - Rotate right by immediate (S=1) (no cond)",
  "ADD -- Data processing operands - Rotate right by immediate (S=0) (no cond)",
  "RSB -- Data processing operands - Logical shift left by immediate (S=1) (no cond)",
  "RSB -- Data processing operands - Logical shift left by immediate (S=0) (no cond)",
  "STRB -- Load and Store Word or Unsigned Byte - Immediate post indexed (no cond)",
  "STM (1) -- Load and Store Multiple - Increment after (W=1) (no cond)",
  "STM (1) -- Load and Store Multiple - Increment after (W=0) (no cond)",
  "TST -- Data processing operands - Immediate (no cond)",
  "STM (1) -- Load and Store Multiple - Decrement before (W=1) (no cond)",
  "STM (1) -- Load and Store Multiple - Decrement before (W=0) (no cond)",
  "MVN -- Data processing operands - Register (S=1) (no cond)",
  "MVN -- Data processing operands - Register (S=0) (no cond)",
  "STM (1) -- Load and Store Multiple - Increment before (W=1) (no cond)",
  "STM (1) -- Load and Store Multiple - Increment before (W=0) (no cond)",
  "ADD -- Data processing operands - Logical shift right by immediate (S=1) (no cond)",
  "ADD -- Data processing operands - Logical shift right by immediate (S=0) (no cond)",
  "STR -- Load and Store Word or Unsigned Byte - Immediate post indexed (no cond)",
  "LDRB -- Load and Store Word or Unsigned Byte - Scaled register offset (U=1) (no cond)",
  "LDRB -- Load and Store Word or Unsigned Byte - Scaled register offset (U=0) (no cond)",
  "SUB -- Data processing operands - Logical shift left by immediate (S=1) (no cond)",
  "SUB -- Data processing operands - Logical shift left by immediate (S=0) (no cond)",
  "LDM (1) -- Load and Store Multiple - Increment before (W=1) (no cond)",
  "LDM (1) -- Load and Store Multiple - Increment before (W=0) (no cond)",
  "LDRH -- Miscellaneous Loads and Stores - Immediate offset (U=1) (no cond)",
  "LDRH -- Miscellaneous Loads and Stores - Immediate offset (U=0) (no cond)",
  "LDR -- Load and Store Word or Unsigned Byte - Immediate pre indexed (no cond)",
  "SMULL (S=1) (no cond)",
  "SMULL (S=0) (no cond)",
  "RSB -- Data processing operands - Arithmetic shift right by immediate (S=1) (no cond)",
  "RSB -- Data processing operands - Arithmetic shift right by immediate (S=0) (no cond)",
  "TST -- Data processing operands - Register (no cond)",
  "EOR -- Data processing operands - Immediate (S=1) (no cond)",
  "EOR -- Data processing operands - Immediate (S=0) (no cond)",
  "ORR -- Data processing operands - Arithmetic shift right by immediate (S=1) (no cond)",
  "ORR -- Data processing operands - Arithmetic shift right by immediate (S=0) (no cond)",
  "ORR -- Data processing operands - Immediate (S=1) (no cond)",
  "ORR -- Data processing operands - Immediate (S=0) (no cond)",
  "SUB -- Data processing operands - Arithmetic shift right by immediate (S=1) (no cond)",
  "SUB -- Data processing operands - Arithmetic shift right by immediate (S=0) (no cond)",
  "MOV -- Data processing operands - Logical shift left by register (S=1) (no cond)",
  "MOV -- Data processing operands - Logical shift left by register (S=0) (no cond)",
  "MUL (S=1) (no cond)",
  "MUL (S=0) (no cond)",
  "CMN -- Data processing operands - Immediate (no cond)",
  "LDR (1) (no immed)",
  "LSL (1) (no immed)",
  "Unpredictable or undefined instruction"};

const char *slv6_instruction_references[SLV6_TABLE_SIZE] = {
  "A4.1.23--A5.2.2",
  "A4.1.99--A5.2.2",
  "A4.1.5",
  "A4.1.5",
  "A4.1.106--A5.1.3",
  "A4.1.106--A5.1.3",
  "A4.1.15--A5.1.4",
  "A4.1.3--A5.1.3",
  "A4.1.3--A5.1.3",
  "A4.1.3--A5.1.4",
  "A4.1.3--A5.1.4",
  "A4.1.18--A5.1.4",
  "A4.1.18--A5.1.4",
  "A4.1.4--A5.1.3",
  "A4.1.4--A5.1.3",
  "A4.1.35--A5.1.7",
  "A4.1.35--A5.1.7",
  "A4.1.17",
  "A4.1.35--A5.1.5",
  "A4.1.35--A5.1.5",
  "A4.1.35--A5.1.3",
  "A4.1.35--A5.1.3",
  "A4.1.20--A5.4.2",
  "A4.1.20--A5.4.2",
  "A4.1.15--A5.1.3",
  "A4.1.23--A5.2.4",
  "A4.1.23--A5.2.4",
  "A4.1.10",
  "A4.1.3--A5.1.5",
  "A4.1.3--A5.1.5",
  "A4.1.24--A5.2.2",
  "A4.1.42--A5.1.4",
  "A4.1.42--A5.1.4",
  "A4.1.35--A5.1.11",
  "A4.1.35--A5.1.11",
  "A4.1.23--A5.2.8",
  "A4.1.18--A5.1.11",
  "A4.1.18--A5.1.11",
  "A4.1.4--A5.1.4",
  "A4.1.4--A5.1.4",
  "A4.1.99--A5.2.5",
  "A4.1.100--A5.2.2",
  "A4.1.42--A5.1.5",
  "A4.1.42--A5.1.5",
  "A4.1.2--A5.1.4",
  "A4.1.2--A5.1.4",
  "A4.1.24--A5.2.3",
  "A4.1.24--A5.2.3",
  "A4.1.60--A5.1.4",
  "A4.1.60--A5.1.4",
  "A4.1.6--A5.1.3",
  "A4.1.6--A5.1.3",
  "A4.1.41--A5.1.3",
  "A4.1.41--A5.1.3",
  "A4.1.42--A5.1.7",
  "A4.1.42--A5.1.7",
  "A4.1.18--A5.1.7",
  "A4.1.18--A5.1.7",
  "A4.1.23--A5.2.3",
  "A4.1.23--A5.2.3",
  "A4.1.35--A5.1.8",
  "A4.1.35--A5.1.8",
  "A4.1.100--A5.2.3",
  "A4.1.100--A5.2.3",
  "A4.1.99--A5.2.4",
  "A4.1.99--A5.2.4",
  "A4.1.14--A5.1.4",
  "A4.1.99--A5.2.9",
  "A4.1.99--A5.2.9",
  "A4.1.99--A5.2.3",
  "A4.1.99--A5.2.3",
  "A4.1.18--A5.1.5",
  "A4.1.18--A5.1.5",
  "A4.1.60--A5.1.3",
  "A4.1.60--A5.1.3",
  "A4.1.35--A5.1.9",
  "A4.1.35--A5.1.9",
  "A4.1.3--A5.1.11",
  "A4.1.3--A5.1.11",
  "A4.1.60--A5.1.5",
  "A4.1.60--A5.1.5",
  "A4.1.100--A5.2.8",
  "A4.1.97--A5.4.2",
  "A4.1.97--A5.4.2",
  "A4.1.117--A5.1.3",
  "A4.1.97--A5.4.5",
  "A4.1.97--A5.4.5",
  "A4.1.41--A5.1.4",
  "A4.1.41--A5.1.4",
  "A4.1.97--A5.4.3",
  "A4.1.97--A5.4.3",
  "A4.1.3--A5.1.7",
  "A4.1.3--A5.1.7",
  "A4.1.99--A5.2.8",
  "A4.1.24--A5.2.4",
  "A4.1.24--A5.2.4",
  "A4.1.106--A5.1.5",
  "A4.1.106--A5.1.5",
  "A4.1.20--A5.4.3",
  "A4.1.20--A5.4.3",
  "A4.1.28--A5.3.2",
  "A4.1.28--A5.3.2",
  "A4.1.23--A5.2.5",
  "A4.1.87",
  "A4.1.87",
  "A4.1.60--A5.1.9",
  "A4.1.60--A5.1.9",
  "A4.1.117--A5.1.4",
  "A4.1.18--A5.1.3",
  "A4.1.18--A5.1.3",
  "A4.1.42--A5.1.9",
  "A4.1.42--A5.1.9",
  "A4.1.42--A5.1.3",
  "A4.1.42--A5.1.3",
  "A4.1.106--A5.1.9",
  "A4.1.106--A5.1.9",
  "A4.1.35--A5.1.6",
  "A4.1.35--A5.1.6",
  "A4.1.40",
  "A4.1.40",
  "A4.1.14--A5.1.3",
  "A4.1.2--A5.1.3",
  "A4.1.2--A5.1.5",
  "A4.1.2--A5.1.6",
  "A4.1.2--A5.1.7",
  "A4.1.2--A5.1.8",
  "A4.1.2--A5.1.9",
  "A4.1.2--A5.1.10",
  "A4.1.2--A5.1.11",
  "A4.1.2--A5.1.12",
  "A4.1.2--A5.1.13",
  "A4.1.3--A5.1.6",
  "A4.1.3--A5.1.8",
  "A4.1.3--A5.1.9",
  "A4.1.3--A5.1.10",
  "A4.1.3--A5.1.12",
  "A4.1.3--A5.1.13",
  "A4.1.4--A5.1.5",
  "A4.1.4--A5.1.6",
  "A4.1.4--A5.1.7",
  "A4.1.4--A5.1.8",
  "A4.1.4--A5.1.9",
  "A4.1.4--A5.1.10",
  "A4.1.4--A5.1.11",
  "A4.1.4--A5.1.12",
  "A4.1.4--A5.1.13",
  "A4.1.6--A5.1.4",
  "A4.1.6--A5.1.5",
  "A4.1.6--A5.1.6",
  "A4.1.6--A5.1.7",
  "A4.1.6--A5.1.8",
  "A4.1.6--A5.1.9",
  "A4.1.6--A5.1.10",
  "A4.1.6--A5.1.11",
  "A4.1.6--A5.1.12",
  "A4.1.6--A5.1.13",
  "A4.1.7",
  "A4.1.8",
  "A4.1.9",
  "A4.1.11",
  "A4.1.12",
  "A4.1.13",
  "A4.1.14--A5.1.5",
  "A4.1.14--A5.1.6",
  "A4.1.14--A5.1.7",
  "A4.1.14--A5.1.8",
  "A4.1.14--A5.1.9",
  "A4.1.14--A5.1.10",
  "A4.1.14--A5.1.11",
  "A4.1.14--A5.1.12",
  "A4.1.14--A5.1.13",
  "A4.1.15--A5.1.5",
  "A4.1.15--A5.1.6",
  "A4.1.15--A5.1.7",
  "A4.1.15--A5.1.8",
  "A4.1.15--A5.1.9",
  "A4.1.15--A5.1.10",
  "A4.1.15--A5.1.11",
  "A4.1.15--A5.1.12",
  "A4.1.15--A5.1.13",
  "A4.1.16",
  "A4.1.18--A5.1.6",
  "A4.1.18--A5.1.8",
  "A4.1.18--A5.1.9",
  "A4.1.18--A5.1.10",
  "A4.1.18--A5.1.12",
  "A4.1.18--A5.1.13",
  "A4.1.19--A5.5.2",
  "A4.1.19--A5.5.3",
  "A4.1.19--A5.5.4",
  "A4.1.19--A5.5.5",
  "A4.1.20--A5.4.4",
  "A4.1.20--A5.4.5",
  "A4.1.21--A5.4.2",
  "A4.1.21--A5.4.3",
  "A4.1.21--A5.4.4",
  "A4.1.21--A5.4.5",
  "A4.1.22--A5.4.2",
  "A4.1.22--A5.4.3",
  "A4.1.22--A5.4.4",
  "A4.1.22--A5.4.5",
  "A4.1.23--A5.2.6",
  "A4.1.23--A5.2.7",
  "A4.1.23--A5.2.9",
  "A4.1.23--A5.2.10",
  "A4.1.24--A5.2.5",
  "A4.1.24--A5.2.6",
  "A4.1.24--A5.2.7",
  "A4.1.24--A5.2.8",
  "A4.1.24--A5.2.9",
  "A4.1.24--A5.2.10",
  "A4.1.25--A5.2.8",
  "A4.1.25--A5.2.9",
  "A4.1.25--A5.2.10",
  "A4.1.26--A5.3.2",
  "A4.1.26--A5.3.3",
  "A4.1.26--A5.3.4",
  "A4.1.26--A5.3.5",
  "A4.1.26--A5.3.6",
  "A4.1.26--A5.3.7",
  "A4.1.27",
  "A4.1.28--A5.3.3",
  "A4.1.28--A5.3.4",
  "A4.1.28--A5.3.5",
  "A4.1.28--A5.3.6",
  "A4.1.28--A5.3.7",
  "A4.1.29--A5.3.2",
  "A4.1.29--A5.3.3",
  "A4.1.29--A5.3.4",
  "A4.1.29--A5.3.5",
  "A4.1.29--A5.3.6",
  "A4.1.29--A5.3.7",
  "A4.1.30--A5.3.2",
  "A4.1.30--A5.3.3",
  "A4.1.30--A5.3.4",
  "A4.1.30--A5.3.5",
  "A4.1.30--A5.3.6",
  "A4.1.30--A5.3.7",
  "A4.1.31--A5.2.8",
  "A4.1.31--A5.2.9",
  "A4.1.31--A5.2.10",
  "A4.1.32",
  "A4.1.33",
  "A4.1.34",
  "A4.1.35--A5.1.4",
  "A4.1.35--A5.1.10",
  "A4.1.35--A5.1.12",
  "A4.1.35--A5.1.13",
  "A4.1.36",
  "A4.1.37",
  "A4.1.38",
  "A4.1.39",
  "A4.1.39",
  "A4.1.41--A5.1.5",
  "A4.1.41--A5.1.6",
  "A4.1.41--A5.1.7",
  "A4.1.41--A5.1.8",
  "A4.1.41--A5.1.9",
  "A4.1.41--A5.1.10",
  "A4.1.41--A5.1.11",
  "A4.1.41--A5.1.12",
  "A4.1.41--A5.1.13",
  "A4.1.42--A5.1.6",
  "A4.1.42--A5.1.8",
  "A4.1.42--A5.1.10",
  "A4.1.42--A5.1.11",
  "A4.1.42--A5.1.12",
  "A4.1.42--A5.1.13",
  "A4.1.43",
  "A4.1.44",
  "A4.1.45--A5.2.2",
  "A4.1.45--A5.2.3",
  "A4.1.45--A5.2.4",
  "A4.1.46",
  "A4.1.47",
  "A4.1.48",
  "A4.1.49",
  "A4.1.50",
  "A4.1.51",
  "A4.1.52",
  "A4.1.53",
  "A4.1.54",
  "A4.1.55",
  "A4.1.56",
  "A4.1.57",
  "A4.1.58",
  "A4.1.59--A5.4.2",
  "A4.1.59--A5.4.3",
  "A4.1.59--A5.4.4",
  "A4.1.59--A5.4.5",
  "A4.1.60--A5.1.6",
  "A4.1.60--A5.1.7",
  "A4.1.60--A5.1.8",
  "A4.1.60--A5.1.10",
  "A4.1.60--A5.1.11",
  "A4.1.60--A5.1.12",
  "A4.1.60--A5.1.13",
  "A4.1.61--A5.1.3",
  "A4.1.61--A5.1.4",
  "A4.1.61--A5.1.5",
  "A4.1.61--A5.1.6",
  "A4.1.61--A5.1.7",
  "A4.1.61--A5.1.8",
  "A4.1.61--A5.1.9",
  "A4.1.61--A5.1.10",
  "A4.1.61--A5.1.11",
  "A4.1.61--A5.1.12",
  "A4.1.61--A5.1.13",
  "A4.1.62",
  "A4.1.63",
  "A4.1.64",
  "A4.1.65--A5.1.3",
  "A4.1.65--A5.1.4",
  "A4.1.65--A5.1.5",
  "A4.1.65--A5.1.6",
  "A4.1.65--A5.1.7",
  "A4.1.65--A5.1.8",
  "A4.1.65--A5.1.9",
  "A4.1.65--A5.1.10",
  "A4.1.65--A5.1.11",
  "A4.1.65--A5.1.12",
  "A4.1.65--A5.1.13",
  "A4.1.66",
  "A4.1.67",
  "A4.1.68",
  "A4.1.69",
  "A4.1.70",
  "A4.1.71",
  "A4.1.72",
  "A4.1.73",
  "A4.1.74",
  "A4.1.75",
  "A4.1.76",
  "A4.1.77",
  "A4.1.78",
  "A4.1.79",
  "A4.1.80",
  "A4.1.81",
  "A4.1.82",
  "A4.1.83",
  "A4.1.84",
  "A4.1.85",
  "A4.1.86",
  "A4.1.88",
  "A4.1.89",
  "A4.1.90--A5.4.2",
  "A4.1.90--A5.4.3",
  "A4.1.90--A5.4.4",
  "A4.1.90--A5.4.5",
  "A4.1.91",
  "A4.1.92",
  "A4.1.93",
  "A4.1.94",
  "A4.1.95",
  "A4.1.96--A5.5.2",
  "A4.1.96--A5.5.3",
  "A4.1.96--A5.5.4",
  "A4.1.96--A5.5.5",
  "A4.1.97--A5.4.4",
  "A4.1.98--A5.4.2",
  "A4.1.98--A5.4.3",
  "A4.1.98--A5.4.4",
  "A4.1.98--A5.4.5",
  "A4.1.99--A5.2.6",
  "A4.1.99--A5.2.7",
  "A4.1.99--A5.2.10",
  "A4.1.100--A5.2.4",
  "A4.1.100--A5.2.5",
  "A4.1.100--A5.2.6",
  "A4.1.100--A5.2.7",
  "A4.1.100--A5.2.9",
  "A4.1.100--A5.2.10",
  "A4.1.101--A5.2.8",
  "A4.1.101--A5.2.9",
  "A4.1.101--A5.2.10",
  "A4.1.102--A5.3.2",
  "A4.1.102--A5.3.3",
  "A4.1.102--A5.3.4",
  "A4.1.102--A5.3.5",
  "A4.1.102--A5.3.6",
  "A4.1.102--A5.3.7",
  "A4.1.103",
  "A4.1.104--A5.3.2",
  "A4.1.104--A5.3.3",
  "A4.1.104--A5.3.4",
  "A4.1.104--A5.3.5",
  "A4.1.104--A5.3.6",
  "A4.1.104--A5.3.7",
  "A4.1.105--A5.2.8",
  "A4.1.105--A5.2.9",
  "A4.1.105--A5.2.10",
  "A4.1.106--A5.1.4",
  "A4.1.106--A5.1.6",
  "A4.1.106--A5.1.7",
  "A4.1.106--A5.1.8",
  "A4.1.106--A5.1.10",
  "A4.1.106--A5.1.11",
  "A4.1.106--A5.1.12",
  "A4.1.106--A5.1.13",
  "A4.1.107",
  "A4.1.108",
  "A4.1.109",
  "A4.1.110",
  "A4.1.111",
  "A4.1.112",
  "A4.1.113",
  "A4.1.114",
  "A4.1.115",
  "A4.1.116--A5.1.3",
  "A4.1.116--A5.1.4",
  "A4.1.116--A5.1.5",
  "A4.1.116--A5.1.6",
  "A4.1.116--A5.1.7",
  "A4.1.116--A5.1.8",
  "A4.1.116--A5.1.9",
  "A4.1.116--A5.1.10",
  "A4.1.116--A5.1.11",
  "A4.1.116--A5.1.12",
  "A4.1.116--A5.1.13",
  "A4.1.117--A5.1.5",
  "A4.1.117--A5.1.6",
  "A4.1.117--A5.1.7",
  "A4.1.117--A5.1.8",
  "A4.1.117--A5.1.9",
  "A4.1.117--A5.1.10",
  "A4.1.117--A5.1.11",
  "A4.1.117--A5.1.12",
  "A4.1.117--A5.1.13",
  "A4.1.118",
  "A4.1.119",
  "A4.1.120",
  "A4.1.121",
  "A4.1.122",
  "A4.1.123",
  "A4.1.124",
  "A4.1.125",
  "A4.1.126",
  "A4.1.127",
  "A4.1.128",
  "A4.1.129",
  "A4.1.130",
  "A4.1.131",
  "A4.1.132",
  "A4.1.133",
  "A4.1.134",
  "A4.1.135",
  "A4.1.136",
  "A4.1.137",
  "A4.1.138",
  "A4.1.139",
  "A4.1.140",
  "A4.1.141",
  "A4.1.142",
  "A4.1.143",
  "A4.1.144",
  "A4.1.145",
  "A4.1.146",
  "A4.1.147",
  "A4.1.148",
  "A7.1.28",
  "A7.1.25",
  "A7.1.58",
  "A7.1.13",
  "A7.1.38",
  "A7.1.5",
  "A7.1.42",
  "A7.1.22",
  "A7.1.30",
  "A7.1.26",
  "A7.1.66",
  "A7.1.43",
  "A7.1.4",
  "A7.1.31",
  "A7.1.10",
  "A7.1.40",
  "A7.1.29",
  "A7.1.6",
  "A7.1.21",
  "A7.1.48",
  "A7.1.60",
  "A7.1.54",
  "A7.1.17",
  "A7.1.14",
  "A7.1.47",
  "A7.1.32",
  "A7.1.50",
  "A7.1.49",
  "A7.1.23",
  "A7.1.68",
  "A7.1.9",
  "A7.1.8",
  "A7.1.19",
  "A7.1.61",
  "A7.1.33",
  "A7.1.2",
  "A7.1.67",
  "A7.1.65",
  "A7.1.41",
  "A7.1.59",
  "A7.1.62",
  "A7.1.27",
  "A7.1.57",
  "A7.1.3",
  "A7.1.45",
  "A7.1.11",
  "A7.1.46",
  "A7.1.34",
  "A7.1.72",
  "A7.1.15",
  "A7.1.39",
  "A7.1.7",
  "A7.1.12",
  "A7.1.16",
  "A7.1.18",
  "A7.1.20",
  "A7.1.24",
  "A7.1.35",
  "A7.1.36",
  "A7.1.37",
  "A7.1.51",
  "A7.1.52",
  "A7.1.53",
  "A7.1.55",
  "A7.1.56",
  "A7.1.63",
  "A7.1.64",
  "A7.1.69",
  "A7.1.70",
  "A7.1.71",
  "A7.1.73",
  "A7.1.74",
  "A4.1.23--A5.2.2--NC",
  "A4.1.99--A5.2.2--NC",
  "A4.1.5--NC",
  "A4.1.5--NC",
  "A4.1.106--A5.1.3--NC",
  "A4.1.106--A5.1.3--NC",
  "A4.1.15--A5.1.4--NC",
  "A4.1.3--A5.1.3--NC",
  "A4.1.3--A5.1.3--NC",
  "A4.1.3--A5.1.4--NC",
  "A4.1.3--A5.1.4--NC",
  "A4.1.18--A5.1.4--NC",
  "A4.1.18--A5.1.4--NC",
  "A4.1.4--A5.1.3--NC",
  "A4.1.4--A5.1.3--NC",
  "A4.1.35--A5.1.7--NC",
  "A4.1.35--A5.1.7--NC",
  "A4.1.17--NC",
  "A4.1.35--A5.1.5--NC",
  "A4.1.35--A5.1.5--NC",
  "A4.1.35--A5.1.3--NC",
  "A4.1.35--A5.1.3--NC",
  "A4.1.20--A5.4.2--NC",
  "A4.1.20--A5.4.2--NC",
  "A4.1.15--A5.1.3--NC",
  "A4.1.23--A5.2.4--NC",
  "A4.1.23--A5.2.4--NC",
  "A4.1.10--NC",
  "A4.1.3--A5.1.5--NC",
  "A4.1.3--A5.1.5--NC",
  "A4.1.24--A5.2.2--NC",
  "A4.1.42--A5.1.4--NC",
  "A4.1.42--A5.1.4--NC",
  "A4.1.35--A5.1.11--NC",
  "A4.1.35--A5.1.11--NC",
  "A4.1.23--A5.2.8--NC",
  "A4.1.18--A5.1.11--NC",
  "A4.1.18--A5.1.11--NC",
  "A4.1.4--A5.1.4--NC",
  "A4.1.4--A5.1.4--NC",
  "A4.1.99--A5.2.5--NC",
  "A4.1.100--A5.2.2--NC",
  "A4.1.42--A5.1.5--NC",
  "A4.1.42--A5.1.5--NC",
  "A4.1.2--A5.1.4--NC",
  "A4.1.2--A5.1.4--NC",
  "A4.1.24--A5.2.3--NC",
  "A4.1.24--A5.2.3--NC",
  "A4.1.60--A5.1.4--NC",
  "A4.1.60--A5.1.4--NC",
  "A4.1.6--A5.1.3--NC",
  "A4.1.6--A5.1.3--NC",
  "A4.1.41--A5.1.3--NC",
  "A4.1.41--A5.1.3--NC",
  "A4.1.42--A5.1.7--NC",
  "A4.1.42--A5.1.7--NC",
  "A4.1.18--A5.1.7--NC",
  "A4.1.18--A5.1.7--NC",
  "A4.1.23--A5.2.3--NC",
  "A4.1.23--A5.2.3--NC",
  "A4.1.35--A5.1.8--NC",
  "A4.1.35--A5.1.8--NC",
  "A4.1.100--A5.2.3--NC",
  "A4.1.100--A5.2.3--NC",
  "A4.1.99--A5.2.4--NC",
  "A4.1.99--A5.2.4--NC",
  "A4.1.14--A5.1.4--NC",
  "A4.1.99--A5.2.9--NC",
  "A4.1.99--A5.2.9--NC",
  "A4.1.99--A5.2.3--NC",
  "A4.1.99--A5.2.3--NC",
  "A4.1.18--A5.1.5--NC",
  "A4.1.18--A5.1.5--NC",
  "A4.1.60--A5.1.3--NC",
  "A4.1.60--A5.1.3--NC",
  "A4.1.35--A5.1.9--NC",
  "A4.1.35--A5.1.9--NC",
  "A4.1.3--A5.1.11--NC",
  "A4.1.3--A5.1.11--NC",
  "A4.1.60--A5.1.5--NC",
  "A4.1.60--A5.1.5--NC",
  "A4.1.100--A5.2.8--NC",
  "A4.1.97--A5.4.2--NC",
  "A4.1.97--A5.4.2--NC",
  "A4.1.117--A5.1.3--NC",
  "A4.1.97--A5.4.5--NC",
  "A4.1.97--A5.4.5--NC",
  "A4.1.41--A5.1.4--NC",
  "A4.1.41--A5.1.4--NC",
  "A4.1.97--A5.4.3--NC",
  "A4.1.97--A5.4.3--NC",
  "A4.1.3--A5.1.7--NC",
  "A4.1.3--A5.1.7--NC",
  "A4.1.99--A5.2.8--NC",
  "A4.1.24--A5.2.4--NC",
  "A4.1.24--A5.2.4--NC",
  "A4.1.106--A5.1.5--NC",
  "A4.1.106--A5.1.5--NC",
  "A4.1.20--A5.4.3--NC",
  "A4.1.20--A5.4.3--NC",
  "A4.1.28--A5.3.2--NC",
  "A4.1.28--A5.3.2--NC",
  "A4.1.23--A5.2.5--NC",
  "A4.1.87--NC",
  "A4.1.87--NC",
  "A4.1.60--A5.1.9--NC",
  "A4.1.60--A5.1.9--NC",
  "A4.1.117--A5.1.4--NC",
  "A4.1.18--A5.1.3--NC",
  "A4.1.18--A5.1.3--NC",
  "A4.1.42--A5.1.9--NC",
  "A4.1.42--A5.1.9--NC",
  "A4.1.42--A5.1.3--NC",
  "A4.1.42--A5.1.3--NC",
  "A4.1.106--A5.1.9--NC",
  "A4.1.106--A5.1.9--NC",
  "A4.1.35--A5.1.6--NC",
  "A4.1.35--A5.1.6--NC",
  "A4.1.40--NC",
  "A4.1.40--NC",
  "A4.1.14--A5.1.3--NC",
  "A7.1.28--NI",
  "A7.1.38--NI",
  "no ref."};

SemanticsFunction slv6_instruction_functions[SLV6_TABLE_SIZE] = {
  slv6_G_LDR_M2_ImmOff,
  slv6_G_STR_M2_ImmOff,
  slv6_G_B_L1,
  slv6_G_B_L0,
  slv6_G_SUB_M1_Imm_S1,
  slv6_G_SUB_M1_Imm_S0,
  slv6_G_CMP_M1_Reg,
  slv6_G_ADD_M1_Imm_S1,
  slv6_G_ADD_M1_Imm_S0,
  slv6_G_ADD_M1_Reg_S1,
  slv6_G_ADD_M1_Reg_S0,
  slv6_G_EOR_M1_Reg_S1,
  slv6_G_EOR_M1_Reg_S0,
  slv6_G_AND_M1_Imm_S1,
  slv6_G_AND_M1_Imm_S0,
  slv6_G_MOV_M1_LSRImm_S1,
  slv6_G_MOV_M1_LSRImm_S0,
  slv6_G_CPY,
  slv6_G_MOV_M1_LSLImm_S1,
  slv6_G_MOV_M1_LSLImm_S0,
  slv6_G_MOV_M1_Imm_S1,
  slv6_G_MOV_M1_Imm_S0,
  slv6_G_LDM1_M4_IA_W1,
  slv6_G_LDM1_M4_IA_W0,
  slv6_G_CMP_M1_Imm,
  slv6_G_LDR_M2_ScRegOff_U1,
  slv6_G_LDR_M2_ScRegOff_U0,
  slv6_G_BX,
  slv6_G_ADD_M1_LSLImm_S1,
  slv6_G_ADD_M1_LSLImm_S0,
  slv6_G_LDRB_M2_ImmOff,
  slv6_G_ORR_M1_Reg_S1,
  slv6_G_ORR_M1_Reg_S0,
  slv6_G_MOV_M1_RRImm_S1,
  slv6_G_MOV_M1_RRImm_S0,
  slv6_G_LDR_M2_Imm_postInd,
  slv6_G_EOR_M1_RRImm_S1,
  slv6_G_EOR_M1_RRImm_S0,
  slv6_G_AND_M1_Reg_S1,
  slv6_G_AND_M1_Reg_S0,
  slv6_G_STR_M2_Imm_preInd,
  slv6_G_STRB_M2_ImmOff,
  slv6_G_ORR_M1_LSLImm_S1,
  slv6_G_ORR_M1_LSLImm_S0,
  slv6_G_ADC_M1_Reg_S1,
  slv6_G_ADC_M1_Reg_S0,
  slv6_G_LDRB_M2_RegOff_U1,
  slv6_G_LDRB_M2_RegOff_U0,
  slv6_G_RSB_M1_Reg_S1,
  slv6_G_RSB_M1_Reg_S0,
  slv6_G_BIC_M1_Imm_S1,
  slv6_G_BIC_M1_Imm_S0,
  slv6_G_MVN_M1_Imm_S1,
  slv6_G_MVN_M1_Imm_S0,
  slv6_G_ORR_M1_LSRImm_S1,
  slv6_G_ORR_M1_LSRImm_S0,
  slv6_G_EOR_M1_LSRImm_S1,
  slv6_G_EOR_M1_LSRImm_S0,
  slv6_G_LDR_M2_RegOff_U1,
  slv6_G_LDR_M2_RegOff_U0,
  slv6_G_MOV_M1_LSRReg_S1,
  slv6_G_MOV_M1_LSRReg_S0,
  slv6_G_STRB_M2_RegOff_U1,
  slv6_G_STRB_M2_RegOff_U0,
  slv6_G_STR_M2_ScRegOff_U1,
  slv6_G_STR_M2_ScRegOff_U0,
  slv6_G_CMN_M1_Reg,
  slv6_G_STR_M2_Reg_postInd_U1,
  slv6_G_STR_M2_Reg_postInd_U0,
  slv6_G_STR_M2_RegOff_U1,
  slv6_G_STR_M2_RegOff_U0,
  slv6_G_EOR_M1_LSLImm_S1,
  slv6_G_EOR_M1_LSLImm_S0,
  slv6_G_RSB_M1_Imm_S1,
  slv6_G_RSB_M1_Imm_S0,
  slv6_G_MOV_M1_ASRImm_S1,
  slv6_G_MOV_M1_ASRImm_S0,
  slv6_G_ADD_M1_RRImm_S1,
  slv6_G_ADD_M1_RRImm_S0,
  slv6_G_RSB_M1_LSLImm_S1,
  slv6_G_RSB_M1_LSLImm_S0,
  slv6_G_STRB_M2_Imm_postInd,
  slv6_G_STM1_M4_IA_W1,
  slv6_G_STM1_M4_IA_W0,
  slv6_G_TST_M1_Imm,
  slv6_G_STM1_M4_DB_W1,
  slv6_G_STM1_M4_DB_W0,
  slv6_G_MVN_M1_Reg_S1,
  slv6_G_MVN_M1_Reg_S0,
  slv6_G_STM1_M4_IB_W1,
  slv6_G_STM1_M4_IB_W0,
  slv6_G_ADD_M1_LSRImm_S1,
  slv6_G_ADD_M1_LSRImm_S0,
  slv6_G_STR_M2_Imm_postInd,
  slv6_G_LDRB_M2_ScRegOff_U1,
  slv6_G_LDRB_M2_ScRegOff_U0,
  slv6_G_SUB_M1_LSLImm_S1,
  slv6_G_SUB_M1_LSLImm_S0,
  slv6_G_LDM1_M4_IB_W1,
  slv6_G_LDM1_M4_IB_W0,
  slv6_G_LDRH_M3_ImmOff_U1,
  slv6_G_LDRH_M3_ImmOff_U0,
  slv6_G_LDR_M2_Imm_preInd,
  slv6_G_SMULL_S1,
  slv6_G_SMULL_S0,
  slv6_G_RSB_M1_ASRImm_S1,
  slv6_G_RSB_M1_ASRImm_S0,
  slv6_G_TST_M1_Reg,
  slv6_G_EOR_M1_Imm_S1,
  slv6_G_EOR_M1_Imm_S0,
  slv6_G_ORR_M1_ASRImm_S1,
  slv6_G_ORR_M1_ASRImm_S0,
  slv6_G_ORR_M1_Imm_S1,
  slv6_G_ORR_M1_Imm_S0,
  slv6_G_SUB_M1_ASRImm_S1,
  slv6_G_SUB_M1_ASRImm_S0,
  slv6_G_MOV_M1_LSLReg_S1,
  slv6_G_MOV_M1_LSLReg_S0,
  slv6_G_MUL_S1,
  slv6_G_MUL_S0,
  slv6_G_CMN_M1_Imm,
  slv6_G_ADC_M1_Imm,
  slv6_G_ADC_M1_LSLImm,
  slv6_G_ADC_M1_LSLReg,
  slv6_G_ADC_M1_LSRImm,
  slv6_G_ADC_M1_LSRReg,
  slv6_G_ADC_M1_ASRImm,
  slv6_G_ADC_M1_ASRReg,
  slv6_G_ADC_M1_RRImm,
  slv6_G_ADC_M1_RRReg,
  slv6_G_ADC_M1_RRE,
  slv6_G_ADD_M1_LSLReg,
  slv6_G_ADD_M1_LSRReg,
  slv6_G_ADD_M1_ASRImm,
  slv6_G_ADD_M1_ASRReg,
  slv6_G_ADD_M1_RRReg,
  slv6_G_ADD_M1_RRE,
  slv6_G_AND_M1_LSLImm,
  slv6_G_AND_M1_LSLReg,
  slv6_G_AND_M1_LSRImm,
  slv6_G_AND_M1_LSRReg,
  slv6_G_AND_M1_ASRImm,
  slv6_G_AND_M1_ASRReg,
  slv6_G_AND_M1_RRImm,
  slv6_G_AND_M1_RRReg,
  slv6_G_AND_M1_RRE,
  slv6_G_BIC_M1_Reg,
  slv6_G_BIC_M1_LSLImm,
  slv6_G_BIC_M1_LSLReg,
  slv6_G_BIC_M1_LSRImm,
  slv6_G_BIC_M1_LSRReg,
  slv6_G_BIC_M1_ASRImm,
  slv6_G_BIC_M1_ASRReg,
  slv6_G_BIC_M1_RRImm,
  slv6_G_BIC_M1_RRReg,
  slv6_G_BIC_M1_RRE,
  slv6_G_BKPT,
  slv6_G_BLX1,
  slv6_G_BLX2,
  slv6_G_BXJ,
  slv6_G_CDP,
  slv6_G_CLZ,
  slv6_G_CMN_M1_LSLImm,
  slv6_G_CMN_M1_LSLReg,
  slv6_G_CMN_M1_LSRImm,
  slv6_G_CMN_M1_LSRReg,
  slv6_G_CMN_M1_ASRImm,
  slv6_G_CMN_M1_ASRReg,
  slv6_G_CMN_M1_RRImm,
  slv6_G_CMN_M1_RRReg,
  slv6_G_CMN_M1_RRE,
  slv6_G_CMP_M1_LSLImm,
  slv6_G_CMP_M1_LSLReg,
  slv6_G_CMP_M1_LSRImm,
  slv6_G_CMP_M1_LSRReg,
  slv6_G_CMP_M1_ASRImm,
  slv6_G_CMP_M1_ASRReg,
  slv6_G_CMP_M1_RRImm,
  slv6_G_CMP_M1_RRReg,
  slv6_G_CMP_M1_RRE,
  slv6_G_CPS,
  slv6_G_EOR_M1_LSLReg,
  slv6_G_EOR_M1_LSRReg,
  slv6_G_EOR_M1_ASRImm,
  slv6_G_EOR_M1_ASRReg,
  slv6_G_EOR_M1_RRReg,
  slv6_G_EOR_M1_RRE,
  slv6_G_LDC_M5_ImmOff,
  slv6_G_LDC_M5_Imm_preInd,
  slv6_G_LDC_M5_Imm_postInd,
  slv6_G_LDC_M5_U,
  slv6_G_LDM1_M4_DA,
  slv6_G_LDM1_M4_DB,
  slv6_G_LDM2_M4_IA,
  slv6_G_LDM2_M4_IB,
  slv6_G_LDM2_M4_DA,
  slv6_G_LDM2_M4_DB,
  slv6_G_LDM3_M4_IA,
  slv6_G_LDM3_M4_IB,
  slv6_G_LDM3_M4_DA,
  slv6_G_LDM3_M4_DB,
  slv6_G_LDR_M2_Reg_preInd,
  slv6_G_LDR_M2_ScReg_preInd,
  slv6_G_LDR_M2_Reg_postInd,
  slv6_G_LDR_M2_ScReg_postInd,
  slv6_G_LDRB_M2_Imm_preInd,
  slv6_G_LDRB_M2_Reg_preInd,
  slv6_G_LDRB_M2_ScReg_preInd,
  slv6_G_LDRB_M2_Imm_postInd,
  slv6_G_LDRB_M2_Reg_postInd,
  slv6_G_LDRB_M2_ScReg_postInd,
  slv6_G_LDRBT_M2_Imm_postInd,
  slv6_G_LDRBT_M2_Reg_postInd,
  slv6_G_LDRBT_M2_ScReg_postInd,
  slv6_G_LDRD_M3_ImmOff,
  slv6_G_LDRD_M3_RegOff,
  slv6_G_LDRD_M3_Imm_preInd,
  slv6_G_LDRD_M3_Reg_preInd,
  slv6_G_LDRD_M3_Imm_postInd,
  slv6_G_LDRD_M3_Reg_postInd,
  slv6_G_LDREX,
  slv6_G_LDRH_M3_RegOff,
  slv6_G_LDRH_M3_Imm_preInd,
  slv6_G_LDRH_M3_Reg_preInd,
  slv6_G_LDRH_M3_Imm_postInd,
  slv6_G_LDRH_M3_Reg_postInd,
  slv6_G_LDRSB_M3_ImmOff,
  slv6_G_LDRSB_M3_RegOff,
  slv6_G_LDRSB_M3_Imm_preInd,
  slv6_G_LDRSB_M3_Reg_preInd,
  slv6_G_LDRSB_M3_Imm_postInd,
  slv6_G_LDRSB_M3_Reg_postInd,
  slv6_G_LDRSH_M3_ImmOff,
  slv6_G_LDRSH_M3_RegOff,
  slv6_G_LDRSH_M3_Imm_preInd,
  slv6_G_LDRSH_M3_Reg_preInd,
  slv6_G_LDRSH_M3_Imm_postInd,
  slv6_G_LDRSH_M3_Reg_postInd,
  slv6_G_LDRT_M2_Imm_postInd,
  slv6_G_LDRT_M2_Reg_postInd,
  slv6_G_LDRT_M2_ScReg_postInd,
  slv6_G_MCR,
  slv6_G_MCRR,
  slv6_G_MLA,
  slv6_G_MOV_M1_Reg,
  slv6_G_MOV_M1_ASRReg,
  slv6_G_MOV_M1_RRReg,
  slv6_G_MOV_M1_RRE,
  slv6_G_MRC,
  slv6_G_MRRC,
  slv6_G_MRS,
  slv6_G_MSRimm,
  slv6_G_MSRreg,
  slv6_G_MVN_M1_LSLImm,
  slv6_G_MVN_M1_LSLReg,
  slv6_G_MVN_M1_LSRImm,
  slv6_G_MVN_M1_LSRReg,
  slv6_G_MVN_M1_ASRImm,
  slv6_G_MVN_M1_ASRReg,
  slv6_G_MVN_M1_RRImm,
  slv6_G_MVN_M1_RRReg,
  slv6_G_MVN_M1_RRE,
  slv6_G_ORR_M1_LSLReg,
  slv6_G_ORR_M1_LSRReg,
  slv6_G_ORR_M1_ASRReg,
  slv6_G_ORR_M1_RRImm,
  slv6_G_ORR_M1_RRReg,
  slv6_G_ORR_M1_RRE,
  slv6_G_PKHBT,
  slv6_G_PKHTB,
  slv6_G_PLD_M2_ImmOff,
  slv6_G_PLD_M2_RegOff,
  slv6_G_PLD_M2_ScRegOff,
  slv6_G_QADD,
  slv6_G_QADD16,
  slv6_G_QADD8,
  slv6_G_QADDSUBX,
  slv6_G_QDADD,
  slv6_G_QDSUB,
  slv6_G_QSUB,
  slv6_G_QSUB16,
  slv6_G_QSUB8,
  slv6_G_QSUBADDX,
  slv6_G_REV,
  slv6_G_REV16,
  slv6_G_REVSH,
  slv6_G_RFE_M4_IA,
  slv6_G_RFE_M4_IB,
  slv6_G_RFE_M4_DA,
  slv6_G_RFE_M4_DB,
  slv6_G_RSB_M1_LSLReg,
  slv6_G_RSB_M1_LSRImm,
  slv6_G_RSB_M1_LSRReg,
  slv6_G_RSB_M1_ASRReg,
  slv6_G_RSB_M1_RRImm,
  slv6_G_RSB_M1_RRReg,
  slv6_G_RSB_M1_RRE,
  slv6_G_RSC_M1_Imm,
  slv6_G_RSC_M1_Reg,
  slv6_G_RSC_M1_LSLImm,
  slv6_G_RSC_M1_LSLReg,
  slv6_G_RSC_M1_LSRImm,
  slv6_G_RSC_M1_LSRReg,
  slv6_G_RSC_M1_ASRImm,
  slv6_G_RSC_M1_ASRReg,
  slv6_G_RSC_M1_RRImm,
  slv6_G_RSC_M1_RRReg,
  slv6_G_RSC_M1_RRE,
  slv6_G_SADD16,
  slv6_G_SADD8,
  slv6_G_SADDSUBX,
  slv6_G_SBC_M1_Imm,
  slv6_G_SBC_M1_Reg,
  slv6_G_SBC_M1_LSLImm,
  slv6_G_SBC_M1_LSLReg,
  slv6_G_SBC_M1_LSRImm,
  slv6_G_SBC_M1_LSRReg,
  slv6_G_SBC_M1_ASRImm,
  slv6_G_SBC_M1_ASRReg,
  slv6_G_SBC_M1_RRImm,
  slv6_G_SBC_M1_RRReg,
  slv6_G_SBC_M1_RRE,
  slv6_G_SEL,
  slv6_G_SETEND,
  slv6_G_SHADD16,
  slv6_G_SHADD8,
  slv6_G_SHADDSUBX,
  slv6_G_SHSUB16,
  slv6_G_SHSUB8,
  slv6_G_SHSUBADDX,
  slv6_G_SMLAxy,
  slv6_G_SMLAD,
  slv6_G_SMLAL,
  slv6_G_SMLALxy,
  slv6_G_SMLALD,
  slv6_G_SMLAWy,
  slv6_G_SMLSD,
  slv6_G_SMLSLD,
  slv6_G_SMMLA,
  slv6_G_SMMLS,
  slv6_G_SMMUL,
  slv6_G_SMUAD,
  slv6_G_SMULxy,
  slv6_G_SMULWy,
  slv6_G_SMUSD,
  slv6_G_SRS_M4_IA,
  slv6_G_SRS_M4_IB,
  slv6_G_SRS_M4_DA,
  slv6_G_SRS_M4_DB,
  slv6_G_SSAT,
  slv6_G_SSAT16,
  slv6_G_SSUB16,
  slv6_G_SSUB8,
  slv6_G_SSUBADDX,
  slv6_G_STC_M5_ImmOff,
  slv6_G_STC_M5_Imm_preInd,
  slv6_G_STC_M5_Imm_postInd,
  slv6_G_STC_M5_U,
  slv6_G_STM1_M4_DA,
  slv6_G_STM2_M4_IA,
  slv6_G_STM2_M4_IB,
  slv6_G_STM2_M4_DA,
  slv6_G_STM2_M4_DB,
  slv6_G_STR_M2_Reg_preInd,
  slv6_G_STR_M2_ScReg_preInd,
  slv6_G_STR_M2_ScReg_postInd,
  slv6_G_STRB_M2_ScRegOff,
  slv6_G_STRB_M2_Imm_preInd,
  slv6_G_STRB_M2_Reg_preInd,
  slv6_G_STRB_M2_ScReg_preInd,
  slv6_G_STRB_M2_Reg_postInd,
  slv6_G_STRB_M2_ScReg_postInd,
  slv6_G_STRBT_M2_Imm_postInd,
  slv6_G_STRBT_M2_Reg_postInd,
  slv6_G_STRBT_M2_ScReg_postInd,
  slv6_G_STRD_M3_ImmOff,
  slv6_G_STRD_M3_RegOff,
  slv6_G_STRD_M3_Imm_preInd,
  slv6_G_STRD_M3_Reg_preInd,
  slv6_G_STRD_M3_Imm_postInd,
  slv6_G_STRD_M3_Reg_postInd,
  slv6_G_STREX,
  slv6_G_STRH_M3_ImmOff,
  slv6_G_STRH_M3_RegOff,
  slv6_G_STRH_M3_Imm_preInd,
  slv6_G_STRH_M3_Reg_preInd,
  slv6_G_STRH_M3_Imm_postInd,
  slv6_G_STRH_M3_Reg_postInd,
  slv6_G_STRT_M2_Imm_postInd,
  slv6_G_STRT_M2_Reg_postInd,
  slv6_G_STRT_M2_ScReg_postInd,
  slv6_G_SUB_M1_Reg,
  slv6_G_SUB_M1_LSLReg,
  slv6_G_SUB_M1_LSRImm,
  slv6_G_SUB_M1_LSRReg,
  slv6_G_SUB_M1_ASRReg,
  slv6_G_SUB_M1_RRImm,
  slv6_G_SUB_M1_RRReg,
  slv6_G_SUB_M1_RRE,
  slv6_G_SWI,
  slv6_G_SWP,
  slv6_G_SWPB,
  slv6_G_SXTAB,
  slv6_G_SXTAB16,
  slv6_G_SXTAH,
  slv6_G_SXTB,
  slv6_G_SXTB16,
  slv6_G_SXTH,
  slv6_G_TEQ_M1_Imm,
  slv6_G_TEQ_M1_Reg,
  slv6_G_TEQ_M1_LSLImm,
  slv6_G_TEQ_M1_LSLReg,
  slv6_G_TEQ_M1_LSRImm,
  slv6_G_TEQ_M1_LSRReg,
  slv6_G_TEQ_M1_ASRImm,
  slv6_G_TEQ_M1_ASRReg,
  slv6_G_TEQ_M1_RRImm,
  slv6_G_TEQ_M1_RRReg,
  slv6_G_TEQ_M1_RRE,
  slv6_G_TST_M1_LSLImm,
  slv6_G_TST_M1_LSLReg,
  slv6_G_TST_M1_LSRImm,
  slv6_G_TST_M1_LSRReg,
  slv6_G_TST_M1_ASRImm,
  slv6_G_TST_M1_ASRReg,
  slv6_G_TST_M1_RRImm,
  slv6_G_TST_M1_RRReg,
  slv6_G_TST_M1_RRE,
  slv6_G_UADD16,
  slv6_G_UADD8,
  slv6_G_UADDSUBX,
  slv6_G_UHADD16,
  slv6_G_UHADD8,
  slv6_G_UHADDSUBX,
  slv6_G_UHSUB16,
  slv6_G_UHSUB8,
  slv6_G_UHSUBADDX,
  slv6_G_UMAAL,
  slv6_G_UMLAL,
  slv6_G_UMULL,
  slv6_G_UQADD16,
  slv6_G_UQADD8,
  slv6_G_UQADDSUBX,
  slv6_G_UQSUB16,
  slv6_G_UQSUB8,
  slv6_G_UQSUBADDX,
  slv6_G_USAD8,
  slv6_G_USADA8,
  slv6_G_USAT,
  slv6_G_USAT16,
  slv6_G_USUB16,
  slv6_G_USUB8,
  slv6_G_USUBADDX,
  slv6_G_UXTAB,
  slv6_G_UXTAB16,
  slv6_G_UXTAH,
  slv6_G_UXTB,
  slv6_G_UXTB16,
  slv6_G_UXTH,
  slv6_G_Tb_LDR1,
  slv6_G_Tb_CPY,
  slv6_G_Tb_STR1,
  slv6_G_Tb_B1,
  slv6_G_Tb_LSL1,
  slv6_G_Tb_ADD3,
  slv6_G_Tb_MOV1,
  slv6_G_Tb_CMP2,
  slv6_G_Tb_LDR3,
  slv6_G_Tb_EOR,
  slv6_G_Tb_SUB2,
  slv6_G_Tb_MOV2,
  slv6_G_Tb_ADD2,
  slv6_G_Tb_LDR4,
  slv6_G_Tb_AND,
  slv6_G_Tb_LSR1,
  slv6_G_Tb_LDR2,
  slv6_G_Tb_ADD4,
  slv6_G_Tb_CMP1,
  slv6_G_Tb_ORR,
  slv6_G_Tb_STR3,
  slv6_G_Tb_ROR,
  slv6_G_Tb_BL,
  slv6_G_Tb_B2,
  slv6_G_Tb_NEG,
  slv6_G_Tb_LDRB1,
  slv6_G_Tb_PUSH,
  slv6_G_Tb_POP,
  slv6_G_Tb_CMP3,
  slv6_G_Tb_SUB4,
  slv6_G_Tb_ADD7,
  slv6_G_Tb_ADD6,
  slv6_G_Tb_BX,
  slv6_G_Tb_STRB1,
  slv6_G_Tb_LDRB2,
  slv6_G_Tb_ADC,
  slv6_G_Tb_SUB3,
  slv6_G_Tb_SUB1,
  slv6_G_Tb_LSR2,
  slv6_G_Tb_STR2,
  slv6_G_Tb_STRB2,
  slv6_G_Tb_LDMIA,
  slv6_G_Tb_STMIA,
  slv6_G_Tb_ADD1,
  slv6_G_Tb_MUL,
  slv6_G_Tb_ASR1,
  slv6_G_Tb_MVN,
  slv6_G_Tb_LDRH1,
  slv6_G_Tb_TST,
  slv6_G_Tb_BIC,
  slv6_G_Tb_LSL2,
  slv6_G_Tb_ADD5,
  slv6_G_Tb_ASR2,
  slv6_G_Tb_BKPT,
  slv6_G_Tb_BLX2,
  slv6_G_Tb_CMN,
  slv6_G_Tb_CPS,
  slv6_G_Tb_LDRH2,
  slv6_G_Tb_LDRSB,
  slv6_G_Tb_LDRSH,
  slv6_G_Tb_REV,
  slv6_G_Tb_REV16,
  slv6_G_Tb_REVSH,
  slv6_G_Tb_SBC,
  slv6_G_Tb_SETEND,
  slv6_G_Tb_STRH1,
  slv6_G_Tb_STRH2,
  slv6_G_Tb_SWI,
  slv6_G_Tb_SXTB,
  slv6_G_Tb_SXTH,
  slv6_G_Tb_UXTB,
  slv6_G_Tb_UXTH,
  slv6_G_LDR_M2_ImmOff_NC,
  slv6_G_STR_M2_ImmOff_NC,
  slv6_G_B_L1_NC,
  slv6_G_B_L0_NC,
  slv6_G_SUB_M1_Imm_S1_NC,
  slv6_G_SUB_M1_Imm_S0_NC,
  slv6_G_CMP_M1_Reg_NC,
  slv6_G_ADD_M1_Imm_S1_NC,
  slv6_G_ADD_M1_Imm_S0_NC,
  slv6_G_ADD_M1_Reg_S1_NC,
  slv6_G_ADD_M1_Reg_S0_NC,
  slv6_G_EOR_M1_Reg_S1_NC,
  slv6_G_EOR_M1_Reg_S0_NC,
  slv6_G_AND_M1_Imm_S1_NC,
  slv6_G_AND_M1_Imm_S0_NC,
  slv6_G_MOV_M1_LSRImm_S1_NC,
  slv6_G_MOV_M1_LSRImm_S0_NC,
  slv6_G_CPY_NC,
  slv6_G_MOV_M1_LSLImm_S1_NC,
  slv6_G_MOV_M1_LSLImm_S0_NC,
  slv6_G_MOV_M1_Imm_S1_NC,
  slv6_G_MOV_M1_Imm_S0_NC,
  slv6_G_LDM1_M4_IA_W1_NC,
  slv6_G_LDM1_M4_IA_W0_NC,
  slv6_G_CMP_M1_Imm_NC,
  slv6_G_LDR_M2_ScRegOff_U1_NC,
  slv6_G_LDR_M2_ScRegOff_U0_NC,
  slv6_G_BX_NC,
  slv6_G_ADD_M1_LSLImm_S1_NC,
  slv6_G_ADD_M1_LSLImm_S0_NC,
  slv6_G_LDRB_M2_ImmOff_NC,
  slv6_G_ORR_M1_Reg_S1_NC,
  slv6_G_ORR_M1_Reg_S0_NC,
  slv6_G_MOV_M1_RRImm_S1_NC,
  slv6_G_MOV_M1_RRImm_S0_NC,
  slv6_G_LDR_M2_Imm_postInd_NC,
  slv6_G_EOR_M1_RRImm_S1_NC,
  slv6_G_EOR_M1_RRImm_S0_NC,
  slv6_G_AND_M1_Reg_S1_NC,
  slv6_G_AND_M1_Reg_S0_NC,
  slv6_G_STR_M2_Imm_preInd_NC,
  slv6_G_STRB_M2_ImmOff_NC,
  slv6_G_ORR_M1_LSLImm_S1_NC,
  slv6_G_ORR_M1_LSLImm_S0_NC,
  slv6_G_ADC_M1_Reg_S1_NC,
  slv6_G_ADC_M1_Reg_S0_NC,
  slv6_G_LDRB_M2_RegOff_U1_NC,
  slv6_G_LDRB_M2_RegOff_U0_NC,
  slv6_G_RSB_M1_Reg_S1_NC,
  slv6_G_RSB_M1_Reg_S0_NC,
  slv6_G_BIC_M1_Imm_S1_NC,
  slv6_G_BIC_M1_Imm_S0_NC,
  slv6_G_MVN_M1_Imm_S1_NC,
  slv6_G_MVN_M1_Imm_S0_NC,
  slv6_G_ORR_M1_LSRImm_S1_NC,
  slv6_G_ORR_M1_LSRImm_S0_NC,
  slv6_G_EOR_M1_LSRImm_S1_NC,
  slv6_G_EOR_M1_LSRImm_S0_NC,
  slv6_G_LDR_M2_RegOff_U1_NC,
  slv6_G_LDR_M2_RegOff_U0_NC,
  slv6_G_MOV_M1_LSRReg_S1_NC,
  slv6_G_MOV_M1_LSRReg_S0_NC,
  slv6_G_STRB_M2_RegOff_U1_NC,
  slv6_G_STRB_M2_RegOff_U0_NC,
  slv6_G_STR_M2_ScRegOff_U1_NC,
  slv6_G_STR_M2_ScRegOff_U0_NC,
  slv6_G_CMN_M1_Reg_NC,
  slv6_G_STR_M2_Reg_postInd_U1_NC,
  slv6_G_STR_M2_Reg_postInd_U0_NC,
  slv6_G_STR_M2_RegOff_U1_NC,
  slv6_G_STR_M2_RegOff_U0_NC,
  slv6_G_EOR_M1_LSLImm_S1_NC,
  slv6_G_EOR_M1_LSLImm_S0_NC,
  slv6_G_RSB_M1_Imm_S1_NC,
  slv6_G_RSB_M1_Imm_S0_NC,
  slv6_G_MOV_M1_ASRImm_S1_NC,
  slv6_G_MOV_M1_ASRImm_S0_NC,
  slv6_G_ADD_M1_RRImm_S1_NC,
  slv6_G_ADD_M1_RRImm_S0_NC,
  slv6_G_RSB_M1_LSLImm_S1_NC,
  slv6_G_RSB_M1_LSLImm_S0_NC,
  slv6_G_STRB_M2_Imm_postInd_NC,
  slv6_G_STM1_M4_IA_W1_NC,
  slv6_G_STM1_M4_IA_W0_NC,
  slv6_G_TST_M1_Imm_NC,
  slv6_G_STM1_M4_DB_W1_NC,
  slv6_G_STM1_M4_DB_W0_NC,
  slv6_G_MVN_M1_Reg_S1_NC,
  slv6_G_MVN_M1_Reg_S0_NC,
  slv6_G_STM1_M4_IB_W1_NC,
  slv6_G_STM1_M4_IB_W0_NC,
  slv6_G_ADD_M1_LSRImm_S1_NC,
  slv6_G_ADD_M1_LSRImm_S0_NC,
  slv6_G_STR_M2_Imm_postInd_NC,
  slv6_G_LDRB_M2_ScRegOff_U1_NC,
  slv6_G_LDRB_M2_ScRegOff_U0_NC,
  slv6_G_SUB_M1_LSLImm_S1_NC,
  slv6_G_SUB_M1_LSLImm_S0_NC,
  slv6_G_LDM1_M4_IB_W1_NC,
  slv6_G_LDM1_M4_IB_W0_NC,
  slv6_G_LDRH_M3_ImmOff_U1_NC,
  slv6_G_LDRH_M3_ImmOff_U0_NC,
  slv6_G_LDR_M2_Imm_preInd_NC,
  slv6_G_SMULL_S1_NC,
  slv6_G_SMULL_S0_NC,
  slv6_G_RSB_M1_ASRImm_S1_NC,
  slv6_G_RSB_M1_ASRImm_S0_NC,
  slv6_G_TST_M1_Reg_NC,
  slv6_G_EOR_M1_Imm_S1_NC,
  slv6_G_EOR_M1_Imm_S0_NC,
  slv6_G_ORR_M1_ASRImm_S1_NC,
  slv6_G_ORR_M1_ASRImm_S0_NC,
  slv6_G_ORR_M1_Imm_S1_NC,
  slv6_G_ORR_M1_Imm_S0_NC,
  slv6_G_SUB_M1_ASRImm_S1_NC,
  slv6_G_SUB_M1_ASRImm_S0_NC,
  slv6_G_MOV_M1_LSLReg_S1_NC,
  slv6_G_MOV_M1_LSLReg_S0_NC,
  slv6_G_MUL_S1_NC,
  slv6_G_MUL_S0_NC,
  slv6_G_CMN_M1_Imm_NC,
  slv6_G_Tb_LDR1_NI,
  slv6_G_Tb_LSL1_NI,
  NULL};

bool may_branch(const struct SLv6_Instruction *instr) {
  switch (instr->args.g0.id) {
  case SLV6_LDR_M2_ImmOff_ID:
    return instr->args.g1.d==15;
  case SLV6_B_L1_ID: return true;
  case SLV6_B_L0_ID: return true;
  case SLV6_SUB_M1_Imm_S1_ID:
    return instr->args.g3.d==15;
  case SLV6_SUB_M1_Imm_S0_ID:
    return instr->args.g3.d==15;
  case SLV6_ADD_M1_Imm_S1_ID:
    return instr->args.g3.d==15;
  case SLV6_ADD_M1_Imm_S0_ID:
    return instr->args.g3.d==15;
  case SLV6_ADD_M1_Reg_S1_ID:
    return instr->args.g5.d==15;
  case SLV6_ADD_M1_Reg_S0_ID:
    return instr->args.g5.d==15;
  case SLV6_EOR_M1_Reg_S1_ID:
    return instr->args.g5.d==15;
  case SLV6_EOR_M1_Reg_S0_ID:
    return instr->args.g5.d==15;
  case SLV6_AND_M1_Imm_S1_ID:
    return instr->args.g3.d==15;
  case SLV6_AND_M1_Imm_S0_ID:
    return instr->args.g3.d==15;
  case SLV6_MOV_M1_LSRImm_S1_ID:
    return instr->args.g6.d==15;
  case SLV6_MOV_M1_LSRImm_S0_ID:
    return instr->args.g6.d==15;
  case SLV6_CPY_ID:
    return instr->args.g7.d==15;
  case SLV6_MOV_M1_LSLImm_S1_ID:
    return instr->args.g6.d==15;
  case SLV6_MOV_M1_LSLImm_S0_ID:
    return instr->args.g6.d==15;
  case SLV6_MOV_M1_Imm_S1_ID:
    return instr->args.g8.d==15;
  case SLV6_MOV_M1_Imm_S0_ID:
    return instr->args.g8.d==15;
  case SLV6_LDM1_M4_IA_W1_ID: return instr->args.g9.register_list>>15;
  case SLV6_LDM1_M4_IA_W0_ID: return instr->args.g9.register_list>>15;
  case SLV6_LDR_M2_ScRegOff_U1_ID:
    return instr->args.g11.d==15;
  case SLV6_LDR_M2_ScRegOff_U0_ID:
    return instr->args.g11.d==15;
  case SLV6_BX_ID: return true;
  case SLV6_ADD_M1_LSLImm_S1_ID:
    return instr->args.g13.d==15;
  case SLV6_ADD_M1_LSLImm_S0_ID:
    return instr->args.g13.d==15;
  case SLV6_ORR_M1_Reg_S1_ID:
    return instr->args.g5.d==15;
  case SLV6_ORR_M1_Reg_S0_ID:
    return instr->args.g5.d==15;
  case SLV6_MOV_M1_RRImm_S1_ID:
    return instr->args.g6.d==15;
  case SLV6_MOV_M1_RRImm_S0_ID:
    return instr->args.g6.d==15;
  case SLV6_LDR_M2_Imm_postInd_ID:
    return instr->args.g1.d==15;
  case SLV6_EOR_M1_RRImm_S1_ID:
    return instr->args.g13.d==15;
  case SLV6_EOR_M1_RRImm_S0_ID:
    return instr->args.g13.d==15;
  case SLV6_AND_M1_Reg_S1_ID:
    return instr->args.g5.d==15;
  case SLV6_AND_M1_Reg_S0_ID:
    return instr->args.g5.d==15;
  case SLV6_ORR_M1_LSLImm_S1_ID:
    return instr->args.g13.d==15;
  case SLV6_ORR_M1_LSLImm_S0_ID:
    return instr->args.g13.d==15;
  case SLV6_ADC_M1_Reg_S1_ID:
    return instr->args.g5.d==15;
  case SLV6_ADC_M1_Reg_S0_ID:
    return instr->args.g5.d==15;
  case SLV6_RSB_M1_Reg_S1_ID:
    return instr->args.g5.d==15;
  case SLV6_RSB_M1_Reg_S0_ID:
    return instr->args.g5.d==15;
  case SLV6_BIC_M1_Imm_S1_ID:
    return instr->args.g3.d==15;
  case SLV6_BIC_M1_Imm_S0_ID:
    return instr->args.g3.d==15;
  case SLV6_MVN_M1_Imm_S1_ID:
    return instr->args.g8.d==15;
  case SLV6_MVN_M1_Imm_S0_ID:
    return instr->args.g8.d==15;
  case SLV6_ORR_M1_LSRImm_S1_ID:
    return instr->args.g13.d==15;
  case SLV6_ORR_M1_LSRImm_S0_ID:
    return instr->args.g13.d==15;
  case SLV6_EOR_M1_LSRImm_S1_ID:
    return instr->args.g13.d==15;
  case SLV6_EOR_M1_LSRImm_S0_ID:
    return instr->args.g13.d==15;
  case SLV6_LDR_M2_RegOff_U1_ID:
    return instr->args.g5.d==15;
  case SLV6_LDR_M2_RegOff_U0_ID:
    return instr->args.g5.d==15;
  case SLV6_EOR_M1_LSLImm_S1_ID:
    return instr->args.g13.d==15;
  case SLV6_EOR_M1_LSLImm_S0_ID:
    return instr->args.g13.d==15;
  case SLV6_RSB_M1_Imm_S1_ID:
    return instr->args.g3.d==15;
  case SLV6_RSB_M1_Imm_S0_ID:
    return instr->args.g3.d==15;
  case SLV6_MOV_M1_ASRImm_S1_ID:
    return instr->args.g6.d==15;
  case SLV6_MOV_M1_ASRImm_S0_ID:
    return instr->args.g6.d==15;
  case SLV6_ADD_M1_RRImm_S1_ID:
    return instr->args.g13.d==15;
  case SLV6_ADD_M1_RRImm_S0_ID:
    return instr->args.g13.d==15;
  case SLV6_RSB_M1_LSLImm_S1_ID:
    return instr->args.g13.d==15;
  case SLV6_RSB_M1_LSLImm_S0_ID:
    return instr->args.g13.d==15;
  case SLV6_MVN_M1_Reg_S1_ID:
    return instr->args.g7.d==15;
  case SLV6_MVN_M1_Reg_S0_ID:
    return instr->args.g7.d==15;
  case SLV6_ADD_M1_LSRImm_S1_ID:
    return instr->args.g13.d==15;
  case SLV6_ADD_M1_LSRImm_S0_ID:
    return instr->args.g13.d==15;
  case SLV6_SUB_M1_LSLImm_S1_ID:
    return instr->args.g13.d==15;
  case SLV6_SUB_M1_LSLImm_S0_ID:
    return instr->args.g13.d==15;
  case SLV6_LDM1_M4_IB_W1_ID: return instr->args.g9.register_list>>15;
  case SLV6_LDM1_M4_IB_W0_ID: return instr->args.g9.register_list>>15;
  case SLV6_LDR_M2_Imm_preInd_ID:
    return instr->args.g1.d==15;
  case SLV6_RSB_M1_ASRImm_S1_ID:
    return instr->args.g13.d==15;
  case SLV6_RSB_M1_ASRImm_S0_ID:
    return instr->args.g13.d==15;
  case SLV6_EOR_M1_Imm_S1_ID:
    return instr->args.g3.d==15;
  case SLV6_EOR_M1_Imm_S0_ID:
    return instr->args.g3.d==15;
  case SLV6_ORR_M1_ASRImm_S1_ID:
    return instr->args.g13.d==15;
  case SLV6_ORR_M1_ASRImm_S0_ID:
    return instr->args.g13.d==15;
  case SLV6_ORR_M1_Imm_S1_ID:
    return instr->args.g3.d==15;
  case SLV6_ORR_M1_Imm_S0_ID:
    return instr->args.g3.d==15;
  case SLV6_SUB_M1_ASRImm_S1_ID:
    return instr->args.g13.d==15;
  case SLV6_SUB_M1_ASRImm_S0_ID:
    return instr->args.g13.d==15;
  case SLV6_ADC_M1_Imm_ID:
    return instr->args.g17.d==15;
  case SLV6_ADC_M1_LSLImm_ID:
    return instr->args.g18.d==15;
  case SLV6_ADC_M1_LSRImm_ID:
    return instr->args.g18.d==15;
  case SLV6_ADC_M1_ASRImm_ID:
    return instr->args.g18.d==15;
  case SLV6_ADC_M1_RRImm_ID:
    return instr->args.g18.d==15;
  case SLV6_ADC_M1_RRE_ID:
    return instr->args.g20.d==15;
  case SLV6_ADD_M1_ASRImm_ID:
    return instr->args.g18.d==15;
  case SLV6_ADD_M1_RRE_ID:
    return instr->args.g20.d==15;
  case SLV6_AND_M1_LSLImm_ID:
    return instr->args.g18.d==15;
  case SLV6_AND_M1_LSRImm_ID:
    return instr->args.g18.d==15;
  case SLV6_AND_M1_ASRImm_ID:
    return instr->args.g18.d==15;
  case SLV6_AND_M1_RRImm_ID:
    return instr->args.g18.d==15;
  case SLV6_AND_M1_RRE_ID:
    return instr->args.g20.d==15;
  case SLV6_BIC_M1_Reg_ID:
    return instr->args.g20.d==15;
  case SLV6_BIC_M1_LSLImm_ID:
    return instr->args.g18.d==15;
  case SLV6_BIC_M1_LSRImm_ID:
    return instr->args.g18.d==15;
  case SLV6_BIC_M1_ASRImm_ID:
    return instr->args.g18.d==15;
  case SLV6_BIC_M1_RRImm_ID:
    return instr->args.g18.d==15;
  case SLV6_BIC_M1_RRE_ID:
    return instr->args.g20.d==15;
  case SLV6_BKPT_ID: return true;
  case SLV6_BLX1_ID: return true;
  case SLV6_BLX2_ID: return true;
  case SLV6_BXJ_ID: return true;
  case SLV6_CPS_ID:
    return (instr->args.g25.F || instr->args.g25.I) && instr->args.g25.imod==2;
  case SLV6_EOR_M1_ASRImm_ID:
    return instr->args.g18.d==15;
  case SLV6_EOR_M1_RRE_ID:
    return instr->args.g20.d==15;
  case SLV6_LDM1_M4_DA_ID: return instr->args.g26.register_list>>15;
  case SLV6_LDM1_M4_DB_ID: return instr->args.g26.register_list>>15;
  case SLV6_LDM3_M4_IA_ID: return true;
  case SLV6_LDM3_M4_IB_ID: return true;
  case SLV6_LDM3_M4_DA_ID: return true;
  case SLV6_LDM3_M4_DB_ID: return true;
  case SLV6_LDR_M2_Reg_preInd_ID:
    return instr->args.g27.d==15;
  case SLV6_LDR_M2_ScReg_preInd_ID:
    return instr->args.g28.d==15;
  case SLV6_LDR_M2_Reg_postInd_ID:
    return instr->args.g27.d==15;
  case SLV6_LDR_M2_ScReg_postInd_ID:
    return instr->args.g28.d==15;
  case SLV6_LDRD_M3_Imm_postInd_ID:
    return instr->args.g29.n==15;
  case SLV6_LDRD_M3_Reg_postInd_ID:
    return instr->args.g27.n==15;
  case SLV6_LDRH_M3_Imm_postInd_ID:
    return instr->args.g29.n==15;
  case SLV6_LDRH_M3_Reg_postInd_ID:
    return instr->args.g27.n==15;
  case SLV6_LDRSB_M3_Imm_postInd_ID:
    return instr->args.g29.n==15;
  case SLV6_LDRSB_M3_Reg_postInd_ID:
    return instr->args.g27.n==15;
  case SLV6_LDRSH_M3_Imm_postInd_ID:
    return instr->args.g29.n==15;
  case SLV6_LDRSH_M3_Reg_postInd_ID:
    return instr->args.g27.n==15;
  case SLV6_MCR_ID: return instr->args.g31.cp_num==15;
  case SLV6_MCRR_ID: return instr->args.g32.cp_num==15;
  case SLV6_MOV_M1_Reg_ID:
    return instr->args.g33.d==15;
  case SLV6_MOV_M1_RRE_ID:
    return instr->args.g33.d==15;
  case SLV6_MSRimm_ID: return instr->args.g36.field_mask&1;
  case SLV6_MSRreg_ID: return instr->args.g37.field_mask&1;
  case SLV6_MVN_M1_LSLImm_ID:
    return instr->args.g38.d==15;
  case SLV6_MVN_M1_LSRImm_ID:
    return instr->args.g38.d==15;
  case SLV6_MVN_M1_ASRImm_ID:
    return instr->args.g38.d==15;
  case SLV6_MVN_M1_RRImm_ID:
    return instr->args.g38.d==15;
  case SLV6_MVN_M1_RRE_ID:
    return instr->args.g33.d==15;
  case SLV6_ORR_M1_RRImm_ID:
    return instr->args.g18.d==15;
  case SLV6_ORR_M1_RRE_ID:
    return instr->args.g20.d==15;
  case SLV6_RFE_M4_IA_ID: return true;
  case SLV6_RFE_M4_IB_ID: return true;
  case SLV6_RFE_M4_DA_ID: return true;
  case SLV6_RFE_M4_DB_ID: return true;
  case SLV6_RSB_M1_LSRImm_ID:
    return instr->args.g18.d==15;
  case SLV6_RSB_M1_RRImm_ID:
    return instr->args.g18.d==15;
  case SLV6_RSB_M1_RRE_ID:
    return instr->args.g20.d==15;
  case SLV6_RSC_M1_Imm_ID:
    return instr->args.g17.d==15;
  case SLV6_RSC_M1_Reg_ID:
    return instr->args.g20.d==15;
  case SLV6_RSC_M1_LSLImm_ID:
    return instr->args.g18.d==15;
  case SLV6_RSC_M1_LSRImm_ID:
    return instr->args.g18.d==15;
  case SLV6_RSC_M1_ASRImm_ID:
    return instr->args.g18.d==15;
  case SLV6_RSC_M1_RRImm_ID:
    return instr->args.g18.d==15;
  case SLV6_RSC_M1_RRE_ID:
    return instr->args.g20.d==15;
  case SLV6_SBC_M1_Imm_ID:
    return instr->args.g17.d==15;
  case SLV6_SBC_M1_Reg_ID:
    return instr->args.g20.d==15;
  case SLV6_SBC_M1_LSLImm_ID:
    return instr->args.g18.d==15;
  case SLV6_SBC_M1_LSRImm_ID:
    return instr->args.g18.d==15;
  case SLV6_SBC_M1_ASRImm_ID:
    return instr->args.g18.d==15;
  case SLV6_SBC_M1_RRImm_ID:
    return instr->args.g18.d==15;
  case SLV6_SBC_M1_RRE_ID:
    return instr->args.g20.d==15;
  case SLV6_STRD_M3_Imm_postInd_ID:
    return instr->args.g29.n==15;
  case SLV6_STRD_M3_Reg_postInd_ID:
    return instr->args.g27.n==15;
  case SLV6_STRH_M3_Imm_postInd_ID:
    return instr->args.g29.n==15;
  case SLV6_STRH_M3_Reg_postInd_ID:
    return instr->args.g27.n==15;
  case SLV6_SUB_M1_Reg_ID:
    return instr->args.g20.d==15;
  case SLV6_SUB_M1_LSRImm_ID:
    return instr->args.g18.d==15;
  case SLV6_SUB_M1_RRImm_ID:
    return instr->args.g18.d==15;
  case SLV6_SUB_M1_RRE_ID:
    return instr->args.g20.d==15;
  case SLV6_SWI_ID: return true;
  case SLV6_Tb_LDR1_ID:
    return instr->args.g62.d==15;
  case SLV6_Tb_CPY_ID:
    return instr->args.g63.d==15;
  case SLV6_Tb_B1_ID: return true;
  case SLV6_Tb_LSL1_ID:
    return instr->args.g65.d==15;
  case SLV6_Tb_ADD3_ID:
    return instr->args.g66.d==15;
  case SLV6_Tb_MOV1_ID:
    return instr->args.g67.d==15;
  case SLV6_Tb_LDR3_ID:
    return instr->args.g67.d==15;
  case SLV6_Tb_EOR_ID:
    return instr->args.g63.d==15;
  case SLV6_Tb_SUB2_ID:
    return instr->args.g67.d==15;
  case SLV6_Tb_MOV2_ID:
    return instr->args.g69.d==15;
  case SLV6_Tb_ADD2_ID:
    return instr->args.g67.d==15;
  case SLV6_Tb_LDR4_ID:
    return instr->args.g67.d==15;
  case SLV6_Tb_AND_ID:
    return instr->args.g63.d==15;
  case SLV6_Tb_LSR1_ID:
    return instr->args.g65.d==15;
  case SLV6_Tb_LDR2_ID:
    return instr->args.g66.d==15;
  case SLV6_Tb_ADD4_ID:
    return instr->args.g63.d==15;
  case SLV6_Tb_ORR_ID:
    return instr->args.g63.d==15;
  case SLV6_Tb_ROR_ID:
    return instr->args.g71.d==15;
  case SLV6_Tb_BL_ID: return instr->args.g72.H!=2;
  case SLV6_Tb_B2_ID: return true;
  case SLV6_Tb_NEG_ID:
    return instr->args.g63.d==15;
  case SLV6_Tb_LDRB1_ID:
    return instr->args.g62.d==15;
  case SLV6_Tb_POP_ID: return instr->args.g74.R==1;
  case SLV6_Tb_ADD6_ID:
    return instr->args.g67.d==15;
  case SLV6_Tb_BX_ID: return true;
  case SLV6_Tb_LDRB2_ID:
    return instr->args.g66.d==15;
  case SLV6_Tb_ADC_ID:
    return instr->args.g63.d==15;
  case SLV6_Tb_SUB3_ID:
    return instr->args.g66.d==15;
  case SLV6_Tb_SUB1_ID:
    return instr->args.g77.d==15;
  case SLV6_Tb_LSR2_ID:
    return instr->args.g71.d==15;
  case SLV6_Tb_LDMIA_ID:
    return instr->args.g78.n==15;
  case SLV6_Tb_STMIA_ID:
    return instr->args.g78.n==15;
  case SLV6_Tb_ADD1_ID:
    return instr->args.g77.d==15;
  case SLV6_Tb_MUL_ID:
    return instr->args.g63.d==15;
  case SLV6_Tb_ASR1_ID:
    return instr->args.g65.d==15;
  case SLV6_Tb_MVN_ID:
    return instr->args.g63.d==15;
  case SLV6_Tb_LDRH1_ID:
    return instr->args.g62.d==15;
  case SLV6_Tb_BIC_ID:
    return instr->args.g63.d==15;
  case SLV6_Tb_LSL2_ID:
    return instr->args.g71.d==15;
  case SLV6_Tb_ADD5_ID:
    return instr->args.g67.d==15;
  case SLV6_Tb_ASR2_ID:
    return instr->args.g71.d==15;
  case SLV6_Tb_BKPT_ID: return true;
  case SLV6_Tb_BLX2_ID: return true;
  case SLV6_Tb_LDRH2_ID:
    return instr->args.g66.d==15;
  case SLV6_Tb_LDRSB_ID:
    return instr->args.g66.d==15;
  case SLV6_Tb_LDRSH_ID:
    return instr->args.g66.d==15;
  case SLV6_Tb_SBC_ID:
    return instr->args.g63.d==15;
  case SLV6_Tb_SWI_ID: return true;
  case SLV6_Tb_SXTB_ID:
    return instr->args.g63.d==15;
  case SLV6_Tb_SXTH_ID:
    return instr->args.g63.d==15;
  case SLV6_Tb_UXTB_ID:
    return instr->args.g63.d==15;
  case SLV6_Tb_UXTH_ID:
    return instr->args.g63.d==15;
  case SLV6_LDR_M2_ImmOff_NC_ID:
    return instr->args.g1.d==15;
  case SLV6_B_L1_NC_ID: return true;
  case SLV6_B_L0_NC_ID: return true;
  case SLV6_SUB_M1_Imm_S1_NC_ID:
    return instr->args.g3.d==15;
  case SLV6_SUB_M1_Imm_S0_NC_ID:
    return instr->args.g3.d==15;
  case SLV6_ADD_M1_Imm_S1_NC_ID:
    return instr->args.g3.d==15;
  case SLV6_ADD_M1_Imm_S0_NC_ID:
    return instr->args.g3.d==15;
  case SLV6_ADD_M1_Reg_S1_NC_ID:
    return instr->args.g5.d==15;
  case SLV6_ADD_M1_Reg_S0_NC_ID:
    return instr->args.g5.d==15;
  case SLV6_EOR_M1_Reg_S1_NC_ID:
    return instr->args.g5.d==15;
  case SLV6_EOR_M1_Reg_S0_NC_ID:
    return instr->args.g5.d==15;
  case SLV6_AND_M1_Imm_S1_NC_ID:
    return instr->args.g3.d==15;
  case SLV6_AND_M1_Imm_S0_NC_ID:
    return instr->args.g3.d==15;
  case SLV6_MOV_M1_LSRImm_S1_NC_ID:
    return instr->args.g6.d==15;
  case SLV6_MOV_M1_LSRImm_S0_NC_ID:
    return instr->args.g6.d==15;
  case SLV6_CPY_NC_ID:
    return instr->args.g7.d==15;
  case SLV6_MOV_M1_LSLImm_S1_NC_ID:
    return instr->args.g6.d==15;
  case SLV6_MOV_M1_LSLImm_S0_NC_ID:
    return instr->args.g6.d==15;
  case SLV6_MOV_M1_Imm_S1_NC_ID:
    return instr->args.g8.d==15;
  case SLV6_MOV_M1_Imm_S0_NC_ID:
    return instr->args.g8.d==15;
  case SLV6_LDM1_M4_IA_W1_NC_ID: return instr->args.g9.register_list>>15;
  case SLV6_LDM1_M4_IA_W0_NC_ID: return instr->args.g9.register_list>>15;
  case SLV6_LDR_M2_ScRegOff_U1_NC_ID:
    return instr->args.g11.d==15;
  case SLV6_LDR_M2_ScRegOff_U0_NC_ID:
    return instr->args.g11.d==15;
  case SLV6_BX_NC_ID: return true;
  case SLV6_ADD_M1_LSLImm_S1_NC_ID:
    return instr->args.g13.d==15;
  case SLV6_ADD_M1_LSLImm_S0_NC_ID:
    return instr->args.g13.d==15;
  case SLV6_ORR_M1_Reg_S1_NC_ID:
    return instr->args.g5.d==15;
  case SLV6_ORR_M1_Reg_S0_NC_ID:
    return instr->args.g5.d==15;
  case SLV6_MOV_M1_RRImm_S1_NC_ID:
    return instr->args.g6.d==15;
  case SLV6_MOV_M1_RRImm_S0_NC_ID:
    return instr->args.g6.d==15;
  case SLV6_LDR_M2_Imm_postInd_NC_ID:
    return instr->args.g1.d==15;
  case SLV6_EOR_M1_RRImm_S1_NC_ID:
    return instr->args.g13.d==15;
  case SLV6_EOR_M1_RRImm_S0_NC_ID:
    return instr->args.g13.d==15;
  case SLV6_AND_M1_Reg_S1_NC_ID:
    return instr->args.g5.d==15;
  case SLV6_AND_M1_Reg_S0_NC_ID:
    return instr->args.g5.d==15;
  case SLV6_ORR_M1_LSLImm_S1_NC_ID:
    return instr->args.g13.d==15;
  case SLV6_ORR_M1_LSLImm_S0_NC_ID:
    return instr->args.g13.d==15;
  case SLV6_ADC_M1_Reg_S1_NC_ID:
    return instr->args.g5.d==15;
  case SLV6_ADC_M1_Reg_S0_NC_ID:
    return instr->args.g5.d==15;
  case SLV6_RSB_M1_Reg_S1_NC_ID:
    return instr->args.g5.d==15;
  case SLV6_RSB_M1_Reg_S0_NC_ID:
    return instr->args.g5.d==15;
  case SLV6_BIC_M1_Imm_S1_NC_ID:
    return instr->args.g3.d==15;
  case SLV6_BIC_M1_Imm_S0_NC_ID:
    return instr->args.g3.d==15;
  case SLV6_MVN_M1_Imm_S1_NC_ID:
    return instr->args.g8.d==15;
  case SLV6_MVN_M1_Imm_S0_NC_ID:
    return instr->args.g8.d==15;
  case SLV6_ORR_M1_LSRImm_S1_NC_ID:
    return instr->args.g13.d==15;
  case SLV6_ORR_M1_LSRImm_S0_NC_ID:
    return instr->args.g13.d==15;
  case SLV6_EOR_M1_LSRImm_S1_NC_ID:
    return instr->args.g13.d==15;
  case SLV6_EOR_M1_LSRImm_S0_NC_ID:
    return instr->args.g13.d==15;
  case SLV6_LDR_M2_RegOff_U1_NC_ID:
    return instr->args.g5.d==15;
  case SLV6_LDR_M2_RegOff_U0_NC_ID:
    return instr->args.g5.d==15;
  case SLV6_EOR_M1_LSLImm_S1_NC_ID:
    return instr->args.g13.d==15;
  case SLV6_EOR_M1_LSLImm_S0_NC_ID:
    return instr->args.g13.d==15;
  case SLV6_RSB_M1_Imm_S1_NC_ID:
    return instr->args.g3.d==15;
  case SLV6_RSB_M1_Imm_S0_NC_ID:
    return instr->args.g3.d==15;
  case SLV6_MOV_M1_ASRImm_S1_NC_ID:
    return instr->args.g6.d==15;
  case SLV6_MOV_M1_ASRImm_S0_NC_ID:
    return instr->args.g6.d==15;
  case SLV6_ADD_M1_RRImm_S1_NC_ID:
    return instr->args.g13.d==15;
  case SLV6_ADD_M1_RRImm_S0_NC_ID:
    return instr->args.g13.d==15;
  case SLV6_RSB_M1_LSLImm_S1_NC_ID:
    return instr->args.g13.d==15;
  case SLV6_RSB_M1_LSLImm_S0_NC_ID:
    return instr->args.g13.d==15;
  case SLV6_MVN_M1_Reg_S1_NC_ID:
    return instr->args.g7.d==15;
  case SLV6_MVN_M1_Reg_S0_NC_ID:
    return instr->args.g7.d==15;
  case SLV6_ADD_M1_LSRImm_S1_NC_ID:
    return instr->args.g13.d==15;
  case SLV6_ADD_M1_LSRImm_S0_NC_ID:
    return instr->args.g13.d==15;
  case SLV6_SUB_M1_LSLImm_S1_NC_ID:
    return instr->args.g13.d==15;
  case SLV6_SUB_M1_LSLImm_S0_NC_ID:
    return instr->args.g13.d==15;
  case SLV6_LDM1_M4_IB_W1_NC_ID: return instr->args.g9.register_list>>15;
  case SLV6_LDM1_M4_IB_W0_NC_ID: return instr->args.g9.register_list>>15;
  case SLV6_LDR_M2_Imm_preInd_NC_ID:
    return instr->args.g1.d==15;
  case SLV6_RSB_M1_ASRImm_S1_NC_ID:
    return instr->args.g13.d==15;
  case SLV6_RSB_M1_ASRImm_S0_NC_ID:
    return instr->args.g13.d==15;
  case SLV6_EOR_M1_Imm_S1_NC_ID:
    return instr->args.g3.d==15;
  case SLV6_EOR_M1_Imm_S0_NC_ID:
    return instr->args.g3.d==15;
  case SLV6_ORR_M1_ASRImm_S1_NC_ID:
    return instr->args.g13.d==15;
  case SLV6_ORR_M1_ASRImm_S0_NC_ID:
    return instr->args.g13.d==15;
  case SLV6_ORR_M1_Imm_S1_NC_ID:
    return instr->args.g3.d==15;
  case SLV6_ORR_M1_Imm_S0_NC_ID:
    return instr->args.g3.d==15;
  case SLV6_SUB_M1_ASRImm_S1_NC_ID:
    return instr->args.g13.d==15;
  case SLV6_SUB_M1_ASRImm_S0_NC_ID:
    return instr->args.g13.d==15;
  case SLV6_Tb_LDR1_NI_ID:
    return instr->args.g62.d==15;
  case SLV6_Tb_LSL1_NI_ID:
    return instr->args.g65.d==15;
  case SLV6_UNPRED_OR_UNDEF_ID: return true;
  default: return false;
  }
}

END_SIMSOC_NAMESPACE
