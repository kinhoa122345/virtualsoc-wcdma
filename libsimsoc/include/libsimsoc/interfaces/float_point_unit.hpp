#ifndef FLOAT_POINT_UNIT_HPP
#define FLOAT_POINT_UNIT_HPP

#include "libsimsoc/module.hpp"

#include <iostream>
#include <inttypes.h>
#include <mpfr.h>
#include <cassert>

namespace simsoc{

  static const uint8_t FP_EXCP_NUM = 13;

  typedef enum fp_exception_type{
    INXCT=0,//inexact due to roundoff or over/underflow
    UNFLO=1,//underflow, gradual or not
    DIVBZ=2,//finite nonzero number divide zero; e.g. 1/0
    OVFLO=3,//overflow
    INTXR=4,//conversion to integer when overflow,infinity or NaN precludes a faithful representation in that format
    ZOVRZ=5,//0.0/0.0
    IOVRI=6,//Infinity/Infinity
    IMINI=7,//Infinity-Infinify
    ZTMSI=8,//0.0 * Infinity
    FODOM=9,//function computed outside its domain; e.g. sqrt(-1)
    IVREM=10,//Remainder. x REM y where y is zero or x is infinite
    UNDTA=11,//uninitialized datum or variable, or SNAN
    IVCOM=12 //comparison when the operands are unordered
  }fp_excp_t;

  typedef enum FP_EXCP_STATUS{
    NOEXCP=0,
    DISABLED_EXCP=1,
    ENABLED_EXCP=2
  }fp_excp_status;

  typedef enum fp_operation_type{
    FADD = 0,
    FSUB = 1,
    FMUL = 2,
    FDIV = 3,
    FSQRT = 4,
    //FRES = 5,
    //FRSQRT = 6,
    FMADD = 7,
    FMSUB = 8,
    FRND = 9,
    FCOV32S = 10,
    FCOV32U = 11,
    FCOV64S = 12,
    FCOV64U = 13,
    FCOMPO = 14,
    FCOMPU = 15
  }fp_op_t;

  //important range value for mpfr
  typedef struct FloatPoint_Env{
    mp_prec_t prec;
    mp_prec_t Bias;
    mp_exp_t emin;
    mp_exp_t emax;
    mp_exp_t normal_emin;
    mp_exp_t normal_emax;
    mp_exp_t denormal_emin;
    mp_exp_t denormal_emax;
    uint32_t exp_adjust;
    uint64_t max_infinity;
    uint64_t min_infinity;
  }fp_range_t;

  typedef enum Precsion_Type{
    Double = 0,
    Single = 1
  }fp_prec_t;

  static const uint64_t QNAN_VALUE = 0x7ff8000000000000ULL;

  typedef class FloatPoint_Type{
  public:

    FloatPoint_Type(const FloatPoint_Type& op){
      prec_type = op.prec_type;
      range = &prec_range[prec_type];
      isQnan = op.isQnan;
      mpfr_init2(fp_value,range->prec);
      int inext=mpfr_set(fp_value,op.fp_value,GMP_RNDZ);
      assert(inext==0);
    }

    /*
     * Getter Setter Interface with fpr register
     */
     FloatPoint_Type(fp_prec_t _prec_type=Double)
      :range(NULL),prec_type(_prec_type),isQnan(false){
       range = &prec_range[prec_type];
       mpfr_init2(fp_value,range->prec);
     }

     FloatPoint_Type(uint64_t dformat)
      :range(NULL),prec_type(Double),isQnan(false){
       range = &prec_range[prec_type];
       double dvalue = *reinterpret_cast<double*>(&dformat);
       debug()<<"set: "<<dvalue<<"[ "<<std::hex<<dformat<<"] \n";
       mpfr_init2(fp_value,range->prec);
       int inext=mpfr_set_d(fp_value,dvalue,GMP_RNDZ);
       assert(inext==0);
       if(mpfr_nan_p(fp_value) && ((dformat>>51) & 0x1)){
         isQnan=true;
       }
    }

    void set_prec(fp_prec_t prec_type_){
      prec_type=prec_type_;
      range = &prec_range[prec_type];
      int inext=mpfr_prec_round(fp_value,range->prec,GMP_RNDZ);
      assert(inext==0);
    }

    ~FloatPoint_Type(){
      mpfr_clear(fp_value);
    }

    uint64_t get_value() const{
      if(isQnan)
        return QNAN_VALUE;

      double value=mpfr_get_d(fp_value,GMP_RNDZ);
      return *reinterpret_cast<uint64_t*>(&value);
    };

    /*
     * Interface with mpfr function
     */
    mpfr_ptr operator*(){
      return fp_value;
    };

    /*
     * Interface between mpfr and IEEE
     */
    int prec_round(mp_rnd_t rnd){
      assert(range);
      int inext=mpfr_prec_round(fp_value,range->prec,rnd);
      return inext;
    }

    void adjust_exp_for_ovflo_trap(){
      assert(range);
      mp_exp_t exp=mpfr_get_exp(fp_value);
      exp -= range->exp_adjust;
      mpfr_set_exp(fp_value,exp);
    }

    void adjust_exp_for_udflo_trap(){
      assert(range);
      mp_exp_t exp=mpfr_get_exp(fp_value);
      exp += range->exp_adjust;
      mpfr_set_exp(fp_value,exp);
    }

    /*
     * Wrapper of mpfr_t object attribute
     */
    bool is_snan(){ return mpfr_nan_p(fp_value) && (!isQnan);}
    bool is_qnan(){return mpfr_nan_p(fp_value) && isQnan;}
    bool is_nan(){return mpfr_nan_p(fp_value) || isQnan;}
    bool is_inf(){return mpfr_inf_p(fp_value);}
    bool is_zero(){return mpfr_zero_p(fp_value);}

    //return -1 if sign bit is 1; return 1 if sign bit is 0
    mpfr_sign_t sign(){return fp_value[0]._mpfr_sign;}

    bool is_tiny(){
      assert(range);
      mp_exp_t exp=mpfr_get_exp(fp_value);
      return exp<range->normal_emin;
    }

    bool is_normalized(){
      assert(range);
      mp_exp_t exp=mpfr_get_exp(fp_value);
      return exp>=range->normal_emin && exp<=range->normal_emax;
    }

    bool is_denormalized(){
      assert(range);
      mp_exp_t exp=mpfr_get_exp(fp_value);
      return exp>=range->denormal_emin && exp<=range->denormal_emax;
    }

    bool is_overflow(){
      assert(range);
      if(is_snan() || is_inf() || is_zero()){//not zero,inf or nan
        return 0;
      }else{
        mp_exp_t exp= mpfr_get_exp(fp_value);
        return exp>range->normal_emax;
      }
    }

    int overflow(int inext,mp_rnd_t rnd_mode){
      assert(range);
      mpfr_set_emin(range->emin);
      mpfr_set_emax(range->emax);
      inext= mpfr_check_range(fp_value,inext,rnd_mode);
      return inext;
    }

    bool is_underflow(){
      assert(range);
      if(is_snan() || is_inf() || is_zero()){//not zero,inf or nan
        return false;
      }else{
        mp_exp_t exp= mpfr_get_exp(fp_value);
        return exp<range->denormal_emin;
      }
    }

      int underflow(int inext,mp_rnd_t rnd_mode){
      assert(range);
      mpfr_set_emin(range->emin);
      mpfr_set_emax(range->emax);

      if(is_underflow()){
        inext= mpfr_check_range(fp_value,inext,rnd_mode);
      }else{
        inext = mpfr_subnormalize(fp_value,inext,rnd_mode);
      }
      return inext;
    }

    typedef union{
      struct{
        uint32_t frac:23;
        uint32_t exp:8;
        uint32_t sign:1;
      }s;
      uint32_t value;
    }ieee_sformat;

    typedef union{
      struct{
        uint64_t frac:52;
        uint64_t exp:11;
        uint64_t sign:1;
      }d;
      uint64_t value;
    }ieee_dformat;


    /*
     * Convert functions for Load/Store single precision oprand
     */
    static uint64_t double_format(uint32_t sformat){
      ieee_sformat svalue;
      svalue.value = sformat;
      ieee_dformat dvalue;
      dvalue.value = 0;

      if(svalue.s.exp>0 && svalue.s.exp<255){//normalized operand
        dvalue.d.exp = svalue.s.exp - 127 + 1023;
        dvalue.d.frac = static_cast<uint64_t>(svalue.s.frac)<<29;
        dvalue.d.sign = svalue.s.sign;
      }else if(svalue.s.exp==0 && svalue.s.frac!=0){//denormalized operand, normalize it
        int64_t exp = -126;
        uint64_t frac = static_cast<uint64_t>(svalue.s.frac)<<29;
        const uint64_t leadingbit_mask = (uint64_t)1<<52;
        while(!(frac & leadingbit_mask)){
          frac = frac <<1;
          exp--;
        }
        dvalue.d.sign=svalue.s.sign;
        dvalue.d.exp = exp + 1023;
        const uint64_t dfrac_mask = ((uint64_t)1<<53) -1;
        dvalue.d.frac = frac & dfrac_mask;
      }else if(svalue.s.exp==255 || (svalue.s.exp==0 && svalue.s.frac==0)){//Infinity/QNaN/SNaN/Zero
        dvalue.d.sign = svalue.s.sign;
        const uint32_t sexp_mask = ((uint32_t)1<<8) -1;
        const uint32_t dexp_mask = ((uint64_t)1<<11) -1;
        dvalue.d.exp = static_cast<int16_t>(static_cast<int8_t>(svalue.s.exp)) & dexp_mask;
        dvalue.d.frac = static_cast<uint64_t>(svalue.s.frac)<<29;
      }
      return dvalue.value;
    };

    static uint32_t single_format(uint64_t dformat){
      ieee_dformat dvalue;
      dvalue.value = dformat;
      ieee_sformat svalue;
      svalue.value = 0;
      if(dvalue.d.exp>896 || (dvalue.d.exp==0 && dvalue.d.frac==0)){//No denormalization required
        svalue.s.sign = dvalue.d.sign;
        svalue.s.exp = dvalue.d.exp==0?0:dvalue.d.exp-1023>128?255:dvalue.d.exp -1023 +127;
        svalue.s.frac = dvalue.d.frac >>29;
      }else if(dvalue.d.exp>=874 && dvalue.d.exp<=896){//denormalize operand
        int64_t exp = dvalue.d.exp - 1023;
        const uint64_t dfrac_leadingbit = (uint64_t)1<<52;
        uint64_t frac = dvalue.d.frac | dfrac_leadingbit ;
        while(exp<-126){
          frac = frac>>1;
          exp++;
        }
        svalue.s.sign = dvalue.d.sign;
        svalue.s.exp = 0;
        const uint64_t sfrac_mask = ((uint64_t)1<<23)-1;
        svalue.s.frac = frac>>29 & sfrac_mask;
      }else{
        error()<<"undefined value"<<std::endl;
        exit(1);
      }
      return svalue.value;
    };

    bool fit_single_format(){
      if(is_nan() || is_inf() || is_zero())
        return true;
      mp_exp_t exp= mpfr_get_exp(fp_value);
      if(exp>=prec_range[Single].emin && exp<=prec_range[Single].emax)
        return true;
      return false;
    }
  private:
    static const fp_range_t prec_range[2];
    const fp_range_t *range;
    fp_prec_t prec_type;
    mpfr_t fp_value;
    bool isQnan;
  }fp_t;

  class FloatPoint_Unit:public Module{
  public:
    FloatPoint_Unit(sc_core::sc_module_name name)
      :Module(name){
    };

    ~FloatPoint_Unit(){};

    virtual fp_excp_status set_invalid_excp(fp_op_t op,fp_excp_t excp)=0;
    virtual fp_excp_status set_divzero_excp(int sign)=0;

    /*
     * mp_rnd_t {GMP_RNDN,GMP_RNDZ,GMP_RNDU,GMP_RNDD}
     */
    fp_excp_status check_invalid_operand(fp_op_t op_type,fp_t& op,mp_rnd_t rnd=GMP_RNDZ){
      switch(op_type){
      case FSQRT:
        {
          if(op.is_snan())
            return set_invalid_excp(FSQRT,UNDTA);

          if(op.sign() == -1 && !op.is_zero())// negative number, -inf, except -0
            return set_invalid_excp(FSQRT,FODOM);//mpfr_sqrt set NAN
        }
        break;
      case FRND:
        {
          if(op.is_snan())
            return set_invalid_excp(FRND,UNDTA);//mpfr_prec_round return nan
        }
        break;
      case FCOV32U:
        {
          fp_excp_status ret=NOEXCP;
          if(op.is_snan()){
            ret=set_invalid_excp(FCOV32U,UNDTA);
            //SNaN can be set with VXCVI,so don't return here
          }

          //nan; inf; <0; exp too big; frac too big
          mpfr_clear_flags();
          uint64_t value = mpfr_get_ui(*op,rnd);
          if(mpfr_erangeflag_p()
             || value > static_cast<uint64_t>((uint32_t)0xffffffff)){
            ret=set_invalid_excp(FCOV32U,INTXR);
          }
          return ret;
        }
        break;
      case FCOV32S:
        {
          fp_excp_status ret=NOEXCP;
          if(op.is_snan()){
            ret=set_invalid_excp(FCOV32S,UNDTA);
            //SNaN can be set with VXCVI,so don't return here
          }

          //nan; inf; exp too big; frac too big
          mpfr_clear_flags();
          int64_t value = mpfr_get_si(*op,rnd);
          if(mpfr_erangeflag_p()
             || value > static_cast<int64_t>((int32_t)0x7fffffff)
             || value < static_cast<int64_t>((int32_t)0x80000000)){
            ret=set_invalid_excp(FCOV32S,INTXR);
            }
          return ret;
        }
        break;
      case FCOV64U:
        {
          fp_excp_status ret=NOEXCP;
          if(op.is_snan()){
            ret=set_invalid_excp(FCOV64U,UNDTA);
            //SNaN can be set with VXCVI,so don't return here
          }

          if(!mpfr_fits_ulong_p(*op,rnd)){
            ret=set_invalid_excp(FCOV64U,INTXR);
            }
          return ret;
        }
        break;
      case FCOV64S:
        {
          fp_excp_status ret=NOEXCP;
          if(op.is_snan()){
            ret=set_invalid_excp(FCOV64S,UNDTA);
            //SNaN can be set with VXCVI,so don't return here
          }

          if(!mpfr_fits_slong_p(*op,rnd)){
            ret=set_invalid_excp(FCOV64S,INTXR);
           }
          return ret;
        }
        break;
      default:
        break;
      }
      return NOEXCP;
    }

    fp_excp_status check_invalid_operand(const fp_op_t op_type,fp_t& op1,fp_t& op2){
      switch(op_type){
      case FADD:
        {
          if(op1.is_snan() || op2.is_snan())
              return set_invalid_excp(FADD,UNDTA);//mpfr_add return NAN

          if(op1.is_inf() && op2.is_inf() && (op1.sign() != op2.sign()))
              return set_invalid_excp(FADD,IMINI);//mpfr_add return NAN
        }
        break;
      case FSUB:
        {
          if(op1.is_snan() || op2.is_snan())
            return set_invalid_excp(FSUB,UNDTA);//mpfr_sub return NAN

          if(op1.is_inf() && op2.is_inf() && (op1.sign()== op2.sign()))
            return set_invalid_excp(FSUB,IMINI);//mpfr_sub return NAN
        }
        break;
      case FDIV:
        {
          if(op1.is_snan() || op2.is_snan())
            return set_invalid_excp(FDIV,UNDTA);//mpfr_div return NAN

          if(op1.is_inf() && op2.is_inf())
            return set_invalid_excp(FDIV,IOVRI);//mpfr_div return NAN

          if(op1.is_zero() && op2.is_zero())
            return set_invalid_excp(FDIV,ZOVRZ);//mpfr_div return NAN
        }
        break;
      case FMUL:
        {
          if(op1.is_snan() || op2.is_snan())
            return set_invalid_excp(FMUL,UNDTA);//mpfr_mul return NAN

          if( (op1.is_zero() && op2.is_inf()) || (op1.is_inf() && op2.is_zero()))
            return set_invalid_excp(FMUL,ZTMSI);//mpfr_mul return NAN
          }
        break;
      case FCOMPO:
        {
          if(op1.is_qnan() || op2.is_qnan())//mpfr_cmp return 0 and set erange flag
            return set_invalid_excp(FCOMPO,IVCOM);

          if(op1.is_snan() || op2.is_snan())//mpfr_cmp return 0 and set erange flag
            return set_invalid_excp(FCOMPO,UNDTA);
        }
        break;
      case FCOMPU:
        {
          if(op1.is_snan() || op2.is_snan())//mpfr_cmp return 0 and set erange flag
            return set_invalid_excp(FCOMPU,UNDTA);
        }
        break;
      default:
        break;
      }
      return NOEXCP;
    }

    fp_excp_status check_invalid_operand(const fp_op_t op_type,fp_t& op1,fp_t& op2,fp_t& op3){
      switch(op_type){
      case FMADD:
        {
          fp_excp_status ret=NOEXCP;
          if(op1.is_snan() || op2.is_snan() || op3.is_snan()){//mpfr_fma return NAN
            ret=set_invalid_excp(FMADD,UNDTA);
            //may be set with VXIMZ,so don't return here
          }

          if(op1.is_inf() || op2.is_inf()){
            if( op1.is_zero() ||
                op2.is_zero()){
              ret=set_invalid_excp(FMADD,ZTMSI);//mpfr return NAN
            }
            if(op3.is_inf() &&
               (op1.sign() * op2.sign() != op3.sign())){
              ret=set_invalid_excp(FMADD,IMINI);//mpfr return NAN
            }
          }
          return ret;
        }
      break;
      case FMSUB:
        {
          fp_excp_status ret = NOEXCP;
          if(op1.is_snan() || op2.is_snan() || op3.is_snan()){
            ret= set_invalid_excp(FMSUB,UNDTA);//mpfr_fms return NAN
            //may be set with VXIMZ,so don't return here
          }
          if(op1.is_inf() || op2.is_inf()){
            if( op1.is_zero() || op2.is_zero() ){
              ret=set_invalid_excp(FMSUB,ZTMSI);//mpfr_fms return NAN
            }
            if(op3.is_inf() &&
               (op1.sign() * op2.sign() == op3.sign())){
              ret=set_invalid_excp(FMSUB,IMINI);//mpfr_fms return NAN
            }
          }
          return ret;
        }
        break;
      default:
        break;
      }//swtich
      return NOEXCP;
    }

    fp_excp_status check_zero_divide(fp_t& op1,fp_t& op2){
      // the case of 0/0 is excluded here
      if(!op1.is_zero() && !op1.is_inf() && op2.is_zero())
        return set_divzero_excp(op1.sign()/op2.sign());//mpfr_div return inf
      return NOEXCP;
    }
  };

}//namespace simsoc
#endif
