#include "float_point_unit.hpp"

namespace simsoc{
  static const fp_range_t double_prec =
    { 53/*prec*/,1023/*bias*/,-1073/*emin*/,1024/*emax*/
      ,-1021/*normal emin*/,1024/*normal emax*/,-1073/*denormal emin*/,-1022/*denormal emax*/,1536/*exp_adjust*/,0x7fefffffffffffffULL/*max infinity*/,0x1ULL/*min infinity*/};

  static const fp_range_t single_prec =
    { 24/*prec*/,127/*bias*/,-148/*emin*/,128/*emax*/
      ,-125/*normal emin*/,128/*normal emax*/,-148/*denormal emin*/,-126/*denormal emax*/,192/*exp_adjust*/,0x47efffffe0000000ULL/*max infinity*/,0x36a0000000000000ULL/*min infinity*/};

  const fp_range_t FloatPoint_Type::prec_range[2]={
    double_prec,
    single_prec
  };
}//namespace simsoc
