//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef ARM_STATUS_REGISTER_HPP
#define ARM_STATUS_REGISTER_HPP

#include <inttypes.h>
#include <libsimsoc/display.hpp>

namespace simsoc {

  typedef enum{ARM_FIQ, ARM_IRQ, ARM_ABT, ARM_UND, ARM_SVC, ARM_SYSTEM, ARM_USER,
               ARM_MODE_END, ARM_WRONG} ARM_Mode;
  extern const char * ARM_MODE_NAMES[7];

  ARM_Mode arm_mode(uint8_t binary);

  class ARM_StatusRegister: public Printable
  {
  public:
    static const uint8_t MODE_BITS[7];

    ARM_StatusRegister();

    bool n; // Negative
    bool z; // Zero
    bool c; // Carry
    bool v; // oVerflow
    bool q; // sticky overflow (E-DSP)

    bool i; // Disables IRQ
    bool f; // Disables FIQ

    bool t; // Thumb mode

    ARM_Mode mode;

    uint32_t binary_encoding() const;

    std::ostream& display(std::ostream& os) const;
  };

  std::ostream& operator<<(std::ostream& os, const simsoc::ARM_Mode& m);

} // namespace simsoc

#endif //ARM_STATUS_REGISTER_HPP
