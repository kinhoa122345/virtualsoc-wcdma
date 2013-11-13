//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "arm_condition.hpp"
#include <cassert>
#include "libsimsoc/display.hpp"

using namespace std;

namespace simsoc {

const char * ARM_CONDITION_NAMES[15] =
  {"EQ", "NE", "CS", "CC", "MI", "PL", "VS", "VC", "HI", "LS", "GE", "LT", "GT", "LE", ""};

ostream& operator<<(ostream& os, const ARM_Condition& c) {
  return os <<ARM_CONDITION_NAMES[c];
}

ARM_Condition& operator++(ARM_Condition& c) {
  return (ARM_Condition&) ++((uint8_t&) c);
}

bool conditionPassed(const ARM_StatusRegister& sr, ARM_Condition c) {
  switch (c) {
  case EQ: return EQ_Passed(sr);
  case NE: return NE_Passed(sr);
  case CS_HS: return CS_HS_Passed(sr);
  case CC_LO: return CC_LO_Passed(sr);
  case MI: return MI_Passed(sr);
  case PL: return PL_Passed(sr);
  case VS: return VS_Passed(sr);
  case VC: return VC_Passed(sr);
  case HI: return HI_Passed(sr);
  case LS: return LS_Passed(sr);
  case GE: return GE_Passed(sr);
  case LT: return LT_Passed(sr);
  case GT: return GT_Passed(sr);
  case LE: return LE_Passed(sr);
  case AL: return AL_Passed(sr);
  default: break;
  }
  assert(false); //unreachable
  return false;
}

bool EQ_Passed(const ARM_StatusRegister& sr) {
  return sr.z;
}

bool NE_Passed(const ARM_StatusRegister& sr) {
  return !(sr.z);
}

bool CS_HS_Passed(const ARM_StatusRegister& sr) {
  return sr.c;
}

bool CC_LO_Passed(const ARM_StatusRegister& sr) {
  return !(sr.c);
}

bool MI_Passed(const ARM_StatusRegister& sr) {
  return sr.n;
}

bool PL_Passed(const ARM_StatusRegister& sr) {
  return !(sr.n);
}

bool VS_Passed(const ARM_StatusRegister& sr) {
  return sr.v;
}

bool VC_Passed(const ARM_StatusRegister& sr) {
  return !(sr.v);
}

bool HI_Passed(const ARM_StatusRegister& sr) {
  return sr.c && !(sr.z);
}

bool LS_Passed(const ARM_StatusRegister& sr) {
  return !(sr.c) || sr.z;
}

bool GE_Passed(const ARM_StatusRegister& sr) {
  return sr.n==sr.v;
}

bool LT_Passed(const ARM_StatusRegister& sr) {
  return sr.n!=sr.v;
}

bool GT_Passed(const ARM_StatusRegister& sr) {
  return !(sr.z) && sr.n==sr.v;
}

bool LE_Passed(const ARM_StatusRegister& sr) {
  return sr.z || sr.n!=sr.v;
}

bool AL_Passed(const ARM_StatusRegister& sr) {
  return true;
}

/***********************************************************************************/
//cond, n, z, c, v
const bool not_arm_cond[15][2][2][2][2] = {
  {{{{true,true},{true,true}},{{false,false},{false,false}}},
   {{{true,true},{true,true}},{{false,false},{false,false}}}},//EQ

  {{{{false,false},{false,false}},{{true,true},{true,true}}},
   {{{false,false},{false,false}},{{true,true},{true,true}}}},//NE

  {{{{true,true},{false,false}},{{true,true},{false,false}}},
   {{{true,true},{false,false}},{{true,true},{false,false}}}},//CS

  {{{{false,false},{true,true}},{{false,false},{true,true}}},
   {{{false,false},{true,true}},{{false,false},{true,true}}}},//CC

  {{{{true,true},{true,true}},{{true,true},{true,true}}},
   {{{false,false},{false,false}},{{false,false},{false,false}}}},//MI

  {{{{false,false},{false,false}},{{false,false},{false,false}}},
   {{{true,true},{true,true}},{{true,true},{true,true}}}},//PL

  {{{{true,false},{true,false}},{{true,false},{true,false}}},
   {{{true,false},{true,false}},{{true,false},{true,false}}}},//VS

  {{{{false,true},{false,true}},{{false,true},{false,true}}},
   {{{false,true},{false,true}},{{false,true},{false,true}}}},//VC

  {{{{true,true},{false,false}},{{true,true},{true,true}}},
   {{{true,true},{false,false}},{{true,true},{true,true}}}},//HI

  {{{{false,false},{true,true}},{{false,false},{false,false}}},
   {{{false,false},{true,true}},{{false,false},{false,false}}}},//LS

  {{{{false,true},{false,true}},{{false,true},{false,true}}},
   {{{true,false},{true,false}},{{true,false},{true,false}}}},//GE

  {{{{true,false},{true,false}},{{true,false},{true,false}}},
   {{{false,true},{false,true}},{{false,true},{false,true}}}},//LT

  {{{{false,true},{false,true}},{{true,true},{true,true}}},
   {{{true,false},{true,false}},{{true,true},{true,true}}}},//GT

  {{{{true,false},{true,false}},{{false,false},{false,false}}},
   {{{false,true},{false,true}},{{false,false},{false,false}}}},//LE

  {{{{false,false},{false,false}},{{false,false},{false,false}}},
   {{{false,false},{false,false}},{{false,false},{false,false}}}},//AL

};

/***********************************************************************************/

} // namespace simsoc
