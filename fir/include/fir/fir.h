#ifndef _FIR_FIR_H_
#define _FIR_FIR_H_

#include <cstring>

#include <systemc>

#include <fir/adder.h>


namespace fir {

enum fir_mode_t
{
  STATIC,
  DYNAMIC
};

namespace detail {

template <unsigned _Size, fir_mode_t mode = STATIC>
class fir_coefficient
{
public:

  int val[_Size];

  inline int read(unsigned pos)
  {
    return val[pos];
  }

  void set_values(int values[_Size])
  { std::memcpy(val, values, sizeof(values)); }
};

template <unsigned _Size>
class fir_coefficient<_Size, DYNAMIC>
{
public:

  sc_in<int> val[_Size];

  inline int read(unsigned pos)
  {
    return val[pos].read();
  }

  void set_values(int values[_Size])
  {
    for (unsigned i = 0; i < _Size; ++i)
      val[i].write(values[i]);
  }
};

} // detail
} // fir

namespace fir {

template <unsigned _Size, fir_mode_t _Mode = STATIC>
SC_MODULE(fir)
{
  static constexpr unsigned size = _Size;

  /// Filter coefficients.
  detail::fir_coefficient<size, _Mode> coeff;
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

  void compute_fir(void);

  inline void init_coefficient(int values[size])
  { coeff.set_values(values); }
};

} // fir

#endif // _FIR_FIR_H_
