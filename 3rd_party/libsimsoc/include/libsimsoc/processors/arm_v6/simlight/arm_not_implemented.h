// Stub for the simlight code
// NB: compiled as C++ code.

// These functions are not implemented in simlight, but some ARE in SimSoC

#ifndef ARM_NOT_IMPLEMENTED_H
#define ARM_NOT_IMPLEMENTED_H

namespace simsoc {

  // these one are implemented in arm_v6_processor.cpp
  extern void update_pending_flags(struct SLv6_Processor *proc);
  extern void exec_undefined_instruction(struct SLv6_Processor *proc,
                                         struct SLv6_Instruction *instr);
  extern void debug_hook(struct SLv6_Processor *proc);

  static inline uint32_t slv6_TLB(uint32_t virtual_address) {return virtual_address;}

  // Shared memory is not implemented */
  static inline size_t ExecutingProcessor() {return 0;}
  static inline bool Shared(uint32_t a) {return false;}
  static inline void MarkExclusiveGlobal(uint32_t a, size_t b, uint32_t c) {}
  static inline void MarkExclusiveLocal(uint32_t a, size_t b, uint32_t c) {}
  static inline void ClearExclusiveByAddress2(uint32_t a, uint32_t c) {}
  static inline void ClearExclusiveByAddress3(uint32_t a, size_t b, uint32_t c) {}
  static inline void ClearExclusiveLocal(size_t a) {}
  static inline bool IsExclusiveLocal(uint32_t a, size_t b, uint32_t c) {return true;}
  static inline bool IsExclusiveGlobal(uint32_t a, size_t b, uint32_t c) {return true;}

  // Jazelle is not implemented */
  static inline bool JE_bit_of_Main_Configuration_register() {return false;}
  static inline uint32_t jpc_SUB_ARCHITECTURE_DEFINED_value() {return 0;}
  static inline uint32_t invalidhandler_SUB_ARCHITECTURE_DEFINED_value() {return 0;}
  static inline bool Jazelle_Extension_accepts_opcode_at(uint32_t a) {return false;}
  static inline bool CV_bit_of_Jazelle_OS_Control_register() {return false;}
  static inline void Start_opcode_execution_at(uint32_t a) {}
  static inline bool IMPLEMENTATION_DEFINED_CONDITION() {return false;}

  // for BKPT */
  static inline bool not_overridden_by_debug_hardware() {return true;}


  static inline bool slv6_CDP_dependent_operation(struct SLv6_Processor *proc,
                                                  uint8_t n) {
    TODO("CDP_dependent_operation");
  }

  // Coprocessor instructions (partly implemented in arm_v6_coproc.cpp)
  extern bool slv6_MCR_send(struct SLv6_Processor *proc, uint8_t n,
                            uint8_t opcode_1, uint8_t opcode_2,
                            uint8_t CRn, uint8_t CRm, uint32_t Rd);

  extern bool slv6_MCRR_send(struct SLv6_Processor *proc,
                             uint8_t n, uint32_t x);

  extern bool slv6_MRRC_first_value(struct SLv6_Processor *proc,
                                    uint32_t *result, uint8_t n);

  extern bool slv6_MRRC_second_value(struct SLv6_Processor *proc,
                                     uint32_t *result, uint8_t n);

  extern bool slv6_MRC_value(struct SLv6_Processor *proc,
                             uint32_t *result, uint8_t n,
                             uint8_t opcode_1, uint8_t opcode_2,
                             uint8_t CRn, uint8_t CRm);

} // namespace simsoc

#endif // ARM_NOT_IMPLEMENTED_H
