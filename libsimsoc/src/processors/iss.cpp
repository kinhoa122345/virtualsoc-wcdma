//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "iss.tpp"

#include "arm/arm_processor.hpp"
#include "arm/armis.hpp"
//#include "mips/mips_processor.hpp"
//#include "mips/mipspi.hpp"
//#include "ppc/ppc_processor.hpp"
//#include "ppc/ppcis.hpp"
//#include "ppc/ppc_pi.hpp"

namespace simsoc {

  template class ISS<ARM_Processor>;

  //template class ISS<MIPS_Processor<BUS32> >;

  //template class ISS<MIPS_Processor<BUS64> >;

  //template class ISS<PPC_Processor>;

} // namespace simsoc
