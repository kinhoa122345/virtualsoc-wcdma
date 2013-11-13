//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "uart_16550.hpp"
#include "libsimsoc/display.hpp"
#ifndef PARALLEL
#include "libsimsoc/interfaces/yield.hpp"
#endif

using namespace std;
using namespace sc_core;

namespace simsoc {

// static function
uint32_t Uart16550::speed(uint16_t divisor) {
  return MAX_SPEED/divisor;
}

  Uart16550::Uart16550(sc_module_name name, bool be):
  Module(name),
  rbr(0), ier(IER_ERROR), iir(IIR_FIFO_ENABLED),
  fifo_enabled(false), dma_mode(false), trigger_level(1),
  lcr(3), dlab(false), // 8 data bits, one stop bit, no parity, break signal disabled, dlab is false
  mcr(0),
  lsr(LSR_THR_EMPTY|LSR_LINE_IDLE),
  msr(0), // initial value?
  scratch(0),
  divisor(0x000c), // = 9600 bps
  dce(NULL),
  receive_fifo(),
  big_endian(be)
{
  rw_port(*this);
//   SC_METHOD(timeout_process);
//   dont_initialize();
//   sensitive <<timeout_event;
}

Uart16550::~Uart16550() {}

void Uart16550::end_of_elaboration() {
  if (!dce) {
    error() <<"the DCE interface is not connected" <<endl;
    exit(3);
  }
}

uint8_t Uart16550::read_byte(uint32_t addr) {
  switch (addr) {
  case RBR:
    if (dlab) { // not RBR, but DLL
      return (uint8_t) divisor;
    } else {
      uint8_t data = rbr;
      if (fifo_enabled) {
        if (receive_fifo.size()==0) {
#ifndef PARALLEL
          warning() <<"read access to register RBR but no new character inside" <<endl;
          assert(!(lsr&LSR_DATA_AVAILABLE));
#endif
        } else if (receive_fifo.size()==1) {
          receive_fifo.pop_front();
          lsr &= ~LSR_DATA_AVAILABLE;
        } else {
          receive_fifo.pop_front();
          rbr = receive_fifo.front();
        }
      } else {
        if (!(lsr&LSR_DATA_AVAILABLE))
          warning() <<"read access to register RBR but no new character inside" <<endl;
        lsr &= ~LSR_DATA_AVAILABLE;
      }
      update_iir();
      return data;
    }
  case IER:
    if (dlab) { // not IER, but DLM
      return divisor>>8;
    } else {
      debug() <<"read ier: " <<hex <<(unsigned) ier <<'\n';
      return ier;
    }
  case IIR:
    debug() <<"read iir: " <<hex <<(unsigned) iir <<'\n';
    return iir;
  case LCR:
    debug() <<"read lcr: " <<hex <<(unsigned) lcr <<'\n';
    return lcr;
  case MCR:
    debug() <<"read mcr: " <<hex <<(unsigned) mcr <<'\n';
    return mcr;
  case LSR:
    lsr &= ~(LSR_OVERRUN_ERROR|LSR_PARITY_ERROR|    // It is not clear in the specification
             LSR_FRAMING_ERROR|LSR_BREAK_RECEIVED);// when to clear these bits
    update_iir();
    debug() <<"read lsr: " <<hex <<(unsigned) lsr <<'\n';
    return lsr;
  case MSR: {
    uint8_t data = msr;
    msr &= ~(MSR_CHANGE_CLEAR_TO_SEND|
             MSR_CHANGE_DATA_SET_READY|
             MSR_CHANGE_RING_INDICATOR|
             MSR_CHANGE_CARRIER_DETECT);
    update_iir();
    debug() <<"read msr: " <<hex <<(unsigned) msr <<'\n';
    return data;
  }
  case SCR:
    debug() <<"read scr: " <<hex <<(unsigned) scratch <<'\n';
    return scratch;
  default:
    error() <<"invalid read outside range (offset = " <<hex <<addr <<")" <<endl;
    exit(3);
    return 0;
  }
}

void Uart16550::write_byte(uint32_t addr, uint8_t data) {
  debug() <<"write byte " <<hex <<(unsigned) data <<" at address " <<addr <<'\n';
  switch (addr) {
  case THR:
    if (dlab) { // not THR, but DLL
      divisor = (divisor&0xff00)|data;
      return;
    } else {
      dce->send(data);
      //       if (mcr&MCR_LOOPBACK_MODE)
      //         receive(data);
#ifndef PARALLEL
      YIELD();
#endif
      return;
    }
  case IER:
    if (dlab) { // not THR, but DLM
      divisor = (divisor&0xff)|((uint16_t)data<<8);
      return;
    } else {
      ier = data;
      update_iir();
      return;
    }
  case FCR:
    fifo_enabled = data&FCR_ENABLE_FIFO;
    if (data&FCR_CLEAR_RECEIVE_FIFO)
      receive_fifo.clear();
    dma_mode = data&FCR_DMA_MODE;
    switch (data&FCR_TRIGGER_LEVEL_BITS) {
    case FCR_TRIGGER_LEVEL_1: trigger_level = 1; break;
    case FCR_TRIGGER_LEVEL_4: trigger_level = 4; break;
    case FCR_TRIGGER_LEVEL_8: trigger_level = 8; break;
    case FCR_TRIGGER_LEVEL_14: trigger_level = 14; break;
    default: UNREACHABLE;
    }
    update_iir();
    return;
  case LCR:
    lcr = data;
    dlab = lcr&LCR_DLAB;
    return;
  case MCR:
    if ((data&MCR_TERMINAL_READY)!=(mcr&MCR_TERMINAL_READY))
      dce->set_dtr(data&MCR_TERMINAL_READY);
    if (data&(MCR_AUX_1|MCR_AUX_2)) {
      data &=~ (MCR_AUX_1|MCR_AUX_2);
      debug() <<"auxiliary output signals not implemented" <<endl;
    }
    if (data&MCR_LOOPBACK_MODE) {
      data &=~ MCR_LOOPBACK_MODE;
      warning() <<"loopback mode not implemented" <<endl;
    }
    if (data&MCR_OTHERS)
      warning() <<"bits 5:7 of MCR register should be zero" <<endl;
    if ((data&MCR_REQUEST_TO_SEND)!=(mcr&MCR_REQUEST_TO_SEND))
      dce->set_rts(data&MCR_REQUEST_TO_SEND);
    mcr = data;
    return;
  case LSR:
    error() <<"invalid write access to LSR register" <<endl;
    exit(3);
  case MSR:
    error() <<"invalid write access to MSR register" <<endl;
    exit(3);
  case SCR:
    scratch = data;
    return;
  default:
    error() <<"invalid write access outside range (offset = " <<hex <<addr <<")" <<endl;
    exit(3);
    return;
  }
}

void Uart16550::receive(uint8_t c) {
//   timeout_event.cancel();
//   timeout_event.notify(8*YIELD_DURATION);
  if (fifo_enabled) {
    if (receive_fifo.size()==FIFO_SIZE) {
      assert(lsr&LSR_DATA_AVAILABLE);
      warning() <<"overrun detected (fifo enabled); new character discarded" <<endl;
      lsr |= LSR_OVERRUN_ERROR;
    } else if (receive_fifo.size()==0) {
      receive_fifo.push_back(c);
      rbr = c;
      lsr |= LSR_DATA_AVAILABLE;
    } else {
      receive_fifo.push_back(c);
#ifndef PARALLEL
      assert(lsr&LSR_DATA_AVAILABLE);
#else
      lsr |= LSR_DATA_AVAILABLE;
#endif
    }
  } else {
    if (lsr&LSR_DATA_AVAILABLE) {
      warning() <<"overrun detected (fifo disabled); new character discarded" <<endl;
      lsr |= LSR_OVERRUN_ERROR;
    } else {
      rbr = c;
      lsr |= LSR_DATA_AVAILABLE;
    }
  }
  update_iir();
}

void Uart16550::set_cts(bool new_val) {
  bool old_val = msr&MSR_CLEAR_TO_SEND;
  if (old_val!=new_val)
    msr |= MSR_CHANGE_CLEAR_TO_SEND;
  if (new_val)
    msr |= MSR_CLEAR_TO_SEND;
  else
    msr &= ~MSR_CLEAR_TO_SEND;
  update_iir();
}

void Uart16550::set_dsr(bool new_val) {
  bool old_val = msr&MSR_DATA_SET_READY;
  if (old_val!=new_val)
    msr |= MSR_CHANGE_DATA_SET_READY;
  if (new_val)
    msr |= MSR_DATA_SET_READY;
  else
    msr &= ~MSR_DATA_SET_READY;
  update_iir();
}

// void Uart16550::timeout_process() {
//   DEBUG <<*this <<"timeout" <<endl;
//   if ((!ier&IER_DATA_AVAILABLE)||(lsr&LSR_DATA_AVAILABLE))
//     return;
//   bool it_pending = iir&IIR_IT_PENDING;
//   iir |= IIR_TIMEOUT;
//   if (!it_pending) {
//     iir |= IIR_IT_PENDING;
//     it_port->interrupt(true);
//   }
// }

void Uart16550::update_iir() {
  iir &= ~IIR_ID_BITS;
  if ((ier&IER_ERROR) &&
      (lsr&(LSR_OVERRUN_ERROR|LSR_PARITY_ERROR|LSR_FRAMING_ERROR|LSR_BREAK_RECEIVED))) {
    // not the same in all spec
    iir |= IIR_ERROR;
  } else if ((ier&IER_DATA_AVAILABLE) &&
             (lsr&LSR_DATA_AVAILABLE) &&
             (!fifo_enabled||receive_fifo.size()>=trigger_level)) {
    debug() <<"data available" <<endl;
    iir |= IIR_DATA_AVAILABLE;
  } else if ((ier&IER_THR_EMPTY) &&
             (lsr&LSR_THR_EMPTY)) {
    iir |= IIR_THR_EMPTY;
  } else if ((ier&IER_MSR_CHANGE) &&
             (msr&(MSR_CHANGE_CLEAR_TO_SEND|MSR_CHANGE_DATA_SET_READY|
                   MSR_CHANGE_RING_INDICATOR|MSR_CHANGE_CARRIER_DETECT))) {
    iir |= IIR_MSR_CHANGE;
  } else {
    iir &= ~IIR_IT_PENDING;
    it_signal = false;
    return;
  }
  iir |= IIR_IT_PENDING;
  it_signal = true;
}

} // namespace simsoc
