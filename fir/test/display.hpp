#include <string>
#include <iostream>
#include <sstream>
#include <cstdio>

#include <systemc.h>

#include <fir/adder.hpp>


template <unsigned _Size>
SC_MODULE(display)
{
  static constexpr unsigned size = _Size;

  fir::pipeline_adder<size> const& adder;
  sc_in<int> coeff[size];
  sc_in<int> x;
  sc_in<int> y;
  sc_in_clk clock;

  SC_HAS_PROCESS(display);
  display(sc_module_name name_,
          sc_trace_file *F,
          fir::pipeline_adder<size> const& add)
    : sc_module(name_)
    , adder(add)
  {
    SC_METHOD(entry);
    dont_initialize();
    sensitive << clock.pos();

    sc_trace(F, x, "x");
    sc_trace(F, y, "y");
    for (unsigned i = 0; i < size; ++i)
    {
      std::stringstream ss;
      ss << "coeff(" << i << ")";
      sc_trace(F, coeff[i], ss.str());
    }
    for (unsigned i = 0; i < adder.get_level_number(); ++i)
    {
      auto const* lvl = adder.get_level(i);

      for (unsigned j = 0; j < adder.get_level_size(i); ++j)
      {
        std::stringstream ss;
        ss << "adder(" << i << "," << j << ")";
        sc_trace(F, lvl[j], ss.str());
      }
    }
    sc_trace(F, clock,"clock");
  }

  void entry(void)
  {
    std::stringstream sscoeff;
    sscoeff << "["<< coeff[0].read();
    for (unsigned i = 1; i < size; ++i)
      sscoeff << "," << coeff[i].read();
    sscoeff << "]" << std::endl;

    std::printf("x=%-10d | y=%-10d | coeff=%s",
                x.read(),
                y.read(),
                sscoeff.str().c_str());
  }
};

