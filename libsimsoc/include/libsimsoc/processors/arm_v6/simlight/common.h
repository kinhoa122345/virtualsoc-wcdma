// Stub for the simlight code
// NB: compiled as C++ code.

#ifndef SLV6_COMMON_H
#define SLV6_COMMON_H

#include <libsimsoc/display.hpp>
#include <libsimsoc/simsoc-config.h>
#include <inttypes.h>
#include <cassert>
#include <string>

#define BEGIN_SIMSOC_NAMESPACE namespace simsoc {
#define END_SIMSOC_NAMESPACE }

#ifdef SIMSOC_HAVE_HOT_COLD_ATTR
#define SLV6_HOT /* __attribute__ ((hot)) */
#define SLV6_COLD __attribute__ ((cold))
#else
#define SLV6_HOT
#define SLV6_COLD
#endif

#define EXTERN_C extern "C"

#define DEBUG(X) ((void) 0)

namespace simsoc {

  static void ERROR(const char *msg) {simsoc::error() <<msg <<std::endl; abort();}

  static void unpredictable(const char *msg) {
    std::string s("simulating something unpredictable, inside: ");
    s += msg;
    ERROR(s.c_str());
  }

  // implemented in arm_v6_processor.cpp
  struct SLv6_Status_Register;
  struct SLv6_Processor;
  std::ostream& operator<<(std::ostream&, const SLv6_Status_Register&);
  std::ostream& operator<<(std::ostream&, const SLv6_Processor&);

} // namespace simsoc

#endif // SLV6_COMMON_H
