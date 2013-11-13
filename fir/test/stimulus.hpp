#include "systemc.h"

template <unsigned _Size>
SC_MODULE(stimulus)
{
protected :

  bool _is_init;
  int _x_val;
  int _x_val_p;

public :

  static constexpr unsigned size = _Size;

  sc_out<int> x;
  sc_out<int> coeff[size];
  sc_in_clk clock;

  SC_CTOR(stimulus)
    : _is_init(false)
    , _x_val(1)
    , _x_val_p(1)
  {
    SC_METHOD(process);
    dont_initialize();

    sensitive << clock.pos();
  }

  void process(void)
  {
    if (!_is_init)
    {
      int val = 23;
      for (sc_out<int>& c : coeff)
      {
        c.write((val%2) ? val : -val);
        val = (val%2)
            ? 3*val-1
            : val/2;
        val %= 1000;
      }

      _is_init = true;
    }

    x.write(_x_val);
    _x_val = _x_val_p + (_x_val_p = _x_val);
    _x_val %= 1000;
  }
};
