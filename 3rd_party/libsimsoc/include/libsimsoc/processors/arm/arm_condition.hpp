//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef ARM_CONDITION_HPP
#define ARM_CONDITION_HPP

#include "libsimsoc/processors/arm/arm_status_register.hpp"

namespace simsoc {

typedef enum{EQ, NE, CS_HS, CC_LO, MI, PL, VS, VC,
             HI, LS, GE, LT, GT, LE, AL, ARM_CONDITION_END} ARM_Condition;
extern const char * ARM_CONDITION_NAMES[15];
const ARM_Condition ARM_CONDITION_FIRST = EQ;

std::ostream& operator<<(std::ostream& os, const ARM_Condition& c);
ARM_Condition& operator++(ARM_Condition& c);

bool conditionPassed(const ARM_StatusRegister& sr, ARM_Condition c);

bool EQ_Passed(const ARM_StatusRegister& sr);
bool NE_Passed(const ARM_StatusRegister& sr);
bool CS_HS_Passed(const ARM_StatusRegister& sr);
bool CC_LO_Passed(const ARM_StatusRegister& sr);
bool MI_Passed(const ARM_StatusRegister& sr);
bool PL_Passed(const ARM_StatusRegister& sr);
bool VS_Passed(const ARM_StatusRegister& sr);
bool VC_Passed(const ARM_StatusRegister& sr);
bool HI_Passed(const ARM_StatusRegister& sr);
bool LS_Passed(const ARM_StatusRegister& sr);
bool GE_Passed(const ARM_StatusRegister& sr);
bool LT_Passed(const ARM_StatusRegister& sr);
bool GT_Passed(const ARM_StatusRegister& sr);
bool LE_Passed(const ARM_StatusRegister& sr);
bool AL_Passed(const ARM_StatusRegister& sr);

extern const bool not_arm_cond[15][2][2][2][2];

} // namespace simsoc

#endif //ARM_CONDITION_HPP
