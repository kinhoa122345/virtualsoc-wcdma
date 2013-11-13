//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "irqc.hpp"
#ifndef PARALLEL
#include "libsimsoc/interfaces/yield.hpp"
#endif

using namespace sc_core;

namespace simsoc {

Irqc::Irqc(sc_module_name name):
  Module(name),
  status(0x0), enabled(~0x0),
  in_signals(32,SignalMultiTargetPort<bool>(this,false))
{
  rw_port(*this);
}

Irqc::~Irqc() {}

void Irqc::signal(bool b, size_t n) {
  if (b)
    status |= 1<<n;
  else
    status &= ~(1<<n);
  debug() <<"write " <<std::dec <<((bool)(status&enabled)) <<" to the out signal\n";
  out_signal = status&enabled;
}

uint32_t Irqc::read_word(uint32_t a) {
  switch (a) {
  case IRQ:
#ifndef PARALLEL
    YIELD();
#endif
    return status;
  default:
    assert(false);
  }
  return 0;
}

void Irqc::write_word(uint32_t a, uint32_t d) {
  switch (a) {
  case MASK: {
    enabled |= 1<<d;
    out_signal = status&enabled;
    return; }
  case UNMASK: {
    enabled &= ~(1<<d);
    out_signal = status&enabled;
#ifndef PARALLEL
    YIELD();
#endif
    return; }
  default:
    assert(false);
  }
}

} // namespace simsoc
