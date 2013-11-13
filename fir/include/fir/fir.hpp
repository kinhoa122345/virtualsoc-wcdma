#ifndef _FIR_FIR_H_
#define _FIR_FIR_H_

#include <systemc.h>

#include <fir/adder.hpp>


namespace fir {

template <unsigned _Size>
SC_MODULE(fir)
{
  static constexpr unsigned size = _Size;

  /// Filter coefficients.
  sc_in<int> coeff[size];
  /// Input.
  sc_in<int> x;
  /// Output.
  sc_out<int> y;

  /// Input shift register. More recent is 0.
  sc_signal<int> shift_register[size];
  /// Products between shift_register and coeff elements.
  sc_signal<int> prod[size];

  pipeline_adder<size> adder;

  SC_CTOR(fir)
  {
    SC_METHOD(compute_fir);
    sensitive << x;
  }

  void compute_fir(void)
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
        prod[i].write(shift_register[i].read() * coeff[i].read());
    }

    // Compute addition.
    adder.compute(prod);

    // Write result in y.
    y.write(adder.get_level(
              pipeline_adder<size>::get_level_number()-1)
            ->read());
  }
};

} // fir

#endif // _FIR_FIR_H_
