#include <sstream>

#include <systemc.h>

#include <fir/fir.hpp>

#include "stimulus.hpp"
#include "display.hpp"

#ifndef FIR_SIZE
# define FIR_SIZE 13
#endif // FIR_SIZE


int sc_main(int argc, char** argv)
{
  std::string filename;
  {
    std::stringstream ss;
    ss << "./wave/waveform" << FIR_SIZE;
    filename = ss.str();
  }

  // Trace file.
  vcd_trace_file* const output_debug =
      (vcd_trace_file*)
      sc_create_vcd_trace_file(
        filename.c_str());

  // FIR signals.
  sc_signal<int> x;
  sc_signal<int> y;
  sc_signal<int> coeff[FIR_SIZE];
  sc_clock clock;

  // Binding.
  stimulus<FIR_SIZE> stim("stimulus");
  fir::fir<FIR_SIZE> fir_module("fir_module");
  display <FIR_SIZE> displ("display", output_debug, fir_module.adder);
  {
    // stimulus.
    for (unsigned i = 0; i < FIR_SIZE; ++i)
      stim.coeff[i](coeff[i]);
    stim.x(x);
    stim.clock(clock);

    // fir.
    for (unsigned i = 0; i < FIR_SIZE; ++i)
      fir_module.coeff[i](coeff[i]);
    fir_module.x(x);
    fir_module.y(y);

    // display.
    displ.x(x);
    displ.y(y);
    for (unsigned i = 0; i < FIR_SIZE; ++i)
      displ.coeff[i](coeff[i]);
    displ.clock(clock);
  }

  //Simulation
  sc_start(100, SC_NS);

  sc_close_vcd_trace_file(output_debug);

  return 0;
}

