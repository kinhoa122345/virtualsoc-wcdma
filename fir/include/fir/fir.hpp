#ifndef _FIR_FIR_HPP_
#define _FIR_FIR_HPP_

#include <cstring>

#include <systemc.h>

#include <fir/fir.h>
#include <fir/adder.hpp>


namespace fir {


template <unsigned _Size, fir_mode_t _Mode>
void fir<_Size, _Mode>::compute_fir(void)
{
  // Shifting.
  {
    for (unsigned i = 0; i < size-1; ++i)
      shift_register[i+1].write(shift_register[i].read());

    shift_register[0].write(x.read());
  }

  // Product.
  {
    for (unsigned i = 0; i < size; ++i)
      prod[i].write(shift_register[i].read() * coeff.read(i));
  }

  // Compute addition.
  adder.compute(prod);

  // Write result in y.
  y.write(adder.get_level(
            pipeline_adder<size>::get_level_number()-1)
          ->read());
}


} // fir

#endif // _FIR_FIR_HPP_
