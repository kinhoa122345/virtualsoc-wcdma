//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

// FIXME: this file describes the cp15 of the ARM architecture version 5
// it should be replaced by a description of the cp15 corresponding to version 6

#ifndef ARM_V5_SYSTEMCONTROL_COPROC_HPP
#define ARM_V5_SYSTEMCONTROL_COPROC_HPP

#include "arm_v6_coproc.hpp"
#include <libsimsoc/bitwise_operator.hpp>

namespace simsoc {

  class ARMv6_MMU;

  class ARMv6_SystemCoproc: public ARMv6_Coprocessor {
  public:

    //ID register, ReadOnly
    static const uint32_t ID=0x0;
    static const uint32_t MAIN_ID_OP=0x0;
    static const uint32_t CACHE_TYPE_OP=0x1;
    static const uint32_t V6_TLB_TYPE_OP=0x3;
    //mask
    static const uint32_t TLB_S = 0x1;
    //value
    const uint32_t main_id;
    const uint32_t cache_type;
    const uint32_t v6_tlb_type;


    // Control register, ReadWrite
    static const uint32_t CONTROL=0x1;
    // mask:
    //mmu endabled
    static const uint32_t CONTROL_M = 1<<0;
    //Alignment fault checking enabled
    static const uint32_t CONTROL_A = 1<<1;
    //Write buffer enabled
    static const uint32_t CONTROL_W = 1<<3;
    //Configured for big-endian memory system
    static const uint32_t CONTROL_B = 1<<7;
    //System protection bit
    static const uint32_t CONTROL_S = 1<<8;
    //Rom protection bit
    static const uint32_t CONTROL_R = 1<<9;
    //High exception vectors selected
    static const uint32_t CONTROL_V = 1<<13;
    // New in ARMv6
    static const uint32_t CONTROL_VE = 1<<24;
    static const uint32_t CONTROL_EE = 1<<25;
    static const uint32_t CONTROL_U = 1<<22;
    //value:
    uint32_t control;

    // Translation table base, RW register
    static const uint32_t TTB = 0x2;
    //mask
    static const uint32_t TTB_BASE = 0xffffc000;
    //value
    uint32_t ttb;

    //Domain access control, RW register
    static const uint32_t CP15_DOMAIN = 0x3;
    //mask
    //value:
    uint32_t domain;


    //Fault status, RW register
    static const uint32_t FSR = 0x5;
    //mask
    static const uint32_t FSR_DOMAIN =0xf0;
    static const uint32_t FSR_STATUS =0xf;
    //value
    uint32_t fsr;

    //Fault Address
    static const uint32_t FAR = 0x6;
    //value
    uint32_t far;

    //CAHCE WRITE CONTROL
    static const uint32_t CACHE_WRITE_CONTROL=0x7;

    //TLB functions, Write Only register
    static const uint32_t TLBFUN = 0x8;
    //mask
    static const uint32_t TLBFUN_OP2_ENTIRE = 0x0;
    static const uint32_t TLBFUN_OP2_SINGLE = 0x1;
    static const uint32_t TLBFUN_CRM_UNIFIED=0x7;
    static const uint32_t TLBFUN_CRM_ITLB=0x5;
    static const uint32_t TLBFUN_CRM_DTLB=0x6;

    //TLB Locak Down
    static const uint32_t TLBLOCK=0x10;
    //mask

    //value
    uint32_t lock;

    //Process ID, ReadWrite register
    static const uint32_t PID = 0x13;
    //mask
    static const uint32_t PID_ID = 0xfe;
    //value
    uint32_t pid;

  public:
    ARMv6_SystemCoproc(sc_core::sc_module_name name,
                       ARMv6_Processor *proc,
                       ARMv6_MMU *mmu);

    bool mcr(uint8_t opcode1, uint8_t opcode2,
             uint32_t Rd_value, uint8_t CRn, uint8_t CRm);

    bool mrc(uint32_t &result, uint8_t opcode1, uint8_t opcode2,
             uint8_t CRn, uint8_t CRm);

    void tlb_fun(uint32_t Rd_value, uint8_t CRm, uint8_t opcode2);

    inline uint32_t get_arch() const {return bits<uint32_t>(main_id,19,16);}
    inline bool is_seperate_TLB() const {return v6_tlb_type&TLB_S;}
    inline uint32_t get_DTLB_size() const {return bits<uint32_t>(v6_tlb_type,15,8);}
    inline uint32_t get_ITLB_size() const {return bits<uint32_t>(v6_tlb_type,23,16);}

    inline bool is_mmu_enabled() const {return control & CONTROL_M;}
    inline bool check_align() const {return control & CONTROL_A;}
    inline uint32_t get_R() const {return control & CONTROL_R;}
    inline uint32_t get_S() const {return control & CONTROL_S;}

    inline bool get_exception_vector() const {return control & CONTROL_V;}
    inline void set_exception_vector(bool x = true) {
      if (x) control |= CONTROL_V;
      else control &=~ CONTROL_V;
    }
    inline bool is_big_endian() const {return control & CONTROL_B;}
    inline void set_big_endian(bool be = true) {
      if (be)
        control |= CONTROL_B;
      else
        control &=~ CONTROL_B;
    }

    inline uint32_t get_ttb() const {return ttb & TTB_BASE;}

    inline uint32_t get_domain(uint32_t id) const {return (domain>>(id*2))&3;}

    inline void set_fsr(uint32_t status,uint32_t domain) {
      fsr = (domain<<4) | status;
    }
    inline void set_far(uint32_t va) {far=va;}
    inline uint32_t get_pid() const {return pid & PID_ID;}

    inline bool get_VE() const {return control & CONTROL_VE;}
    inline bool get_EE() const {return control & CONTROL_EE;}
    inline bool get_U() const {return control & CONTROL_U;}

  protected:
    ARMv6_MMU *mmu;
  };
  
} // namespace simsoc

#endif // ARM_V5_SYSTEMCONTROL_COPROC_HPP
