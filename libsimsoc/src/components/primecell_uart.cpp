//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "primecell_uart.hpp"
#include "libsimsoc/display.hpp"
#include "libsimsoc/interfaces/yield.hpp"
using namespace std;
using namespace sc_core;

namespace simsoc {

// static function
uint32_t PrimeCellUart::speed(uint32_t divisor) {
  return MAX_SPEED/divisor;
}

PrimeCellUart::PrimeCellUart(sc_module_name name):
  Module(name),
  dr(0),rsr(0),fr(FR_TXFE|FR_RXFE),
  ibrd(0), fbrd(0),
  lcr_h(LCR_H_WLEN),fifo_enabled(false),// 8 data bits, one stop bit, no parity, break signal disabled, FIFOs disabled
  cr(0),ifls(0x12),transmit_trigger_level(8),
  receive_trigger_level(8),imsc(0),ris(0),dmacr(0),
  dce(NULL),
  transmit_fifo(),
  receive_fifo(),
  timeout_duration(1,SC_MS)
{
  rw_port(*this); // bind target port

  SC_METHOD(compute);
  sensitive <<cts_event;

  SC_METHOD(compute_timeout);
  dont_initialize();
  sensitive <<timeout_event;

  debug() <<"constructor finished\n";
}

PrimeCellUart::~PrimeCellUart() {
  debug() <<"destructor called\n";
}

void PrimeCellUart::end_of_elaboration() {
  if (!dce) {
    error() <<"the DCE interface is not connected" <<endl;
    exit(3);
  }
}

uint16_t PrimeCellUart::mis() const {
  return ris&imsc;
}

bool PrimeCellUart::rts_signal() const {
  return cr&CR_RTS;
}

bool PrimeCellUart::cts_signal() const {
  return fr&FR_CTS;
}



uint16_t PrimeCellUart::read_half(uint32_t addr) {
  uint16_t data;
  switch (addr) {
  case DR:
    rsr = dr>>8;
    if (fifo_enabled) {
      if (receive_fifo.size()==0) {
        if (!(fr&FR_RXFE)) UNREACHABLE;
        error() <<"read access to register DR but no new character inside" <<endl;
        exit(1);
      }
      data = dr|receive_fifo.front();
      receive_fifo.pop();

      if (receive_fifo.size()+1==receive_trigger_level)
        ris &= ~RIS_RXRIS;

      // update FR and DR register
      if (receive_fifo.size()==0) {
        fr |= FR_RXFE;
        ris &=~ RIS_RTRIS;
      }
      else if (receive_fifo.size()==FIFO_SIZE-1) {
        fr &= ~FR_RXFF;
        dr &= ~DR_OE;
        ris &= ~RIS_OERIS;
      }

      if (cr&CR_RTSEn) { // hardware flow control
        if ((receive_fifo.size()<receive_trigger_level) != rts_signal()) {
          if (rts_signal()) UNREACHABLE;
          cr |= CR_RTS;
          info() <<"RTS signal asserted" <<endl;
          dce->set_rts(rts_signal());
          YIELD();
        }
      }
    } else { // fifo disabled
      if (receive_fifo.size()==0) {
        if (!(fr&FR_RXFE)) UNREACHABLE;
        error() <<"read access to register DR but no new character inside" <<endl;
        exit(1);
      }
      data = dr|receive_fifo.front();
      receive_fifo.pop();
      if (receive_fifo.size()!=0) UNREACHABLE;
      dr &= ~DR_OE;
      ris &= ~RIS_RXRIS;
      ris &= ~RIS_RTRIS;
      ris &= ~RIS_OERIS;
      fr |= FR_RXFE;
      fr &= ~FR_RXFF;
    }
    update_it_signal();
    return data;

  case RSR:
    return rsr;

  case FR: // may be used for polling
    YIELD();
    return fr;

  case IBRD:
    return ibrd;

  case FBRD:
    return fbrd;

  case LCR_H:
    return lcr_h;

  case CR:
    return cr;

  case IFLS:
    return ifls;

  case IMSC:
    return imsc;

  case RIS:
    return ris;

  case MIS:
    return mis();

  case ICR:
    warning() <<"invalid read access of write-only register ICR" <<endl;
//    exit(1);
	return icr;

  case DMACR:
    return dmacr;

  default:
    error() <<"invalid read outside range (offset = " <<hex <<addr <<")" <<endl;
    exit(3);
    return 0;
  }
}

void PrimeCellUart::write_half(uint32_t addr, uint16_t data) {
  switch (addr) {
  case DR:
    if (!uart_transmit_enabled()) {
      error() <<"write access to DR register but the transmission is not enabled " <<endl;
      exit(1);
    }

    if (transmit_fifo.size()>0) {
      if (fr&FR_TXFE) UNREACHABLE;
      if (!fifo_enabled) {
        if (!(fr&FR_TXFF)) UNREACHABLE;
        warning()<<"transmit overrun detected (fifo disabled); new character discarded" <<endl;
      } else  if (transmit_fifo.size()==FIFO_SIZE) {
        if (!(fr&FR_TXFF)) UNREACHABLE;
        warning()<<"transmit overrun detected (fifo enabled); new character discarded" <<endl;
      } else {
        transmit_fifo.push(data); // the process "compute" will send the data
        if (transmit_fifo.size()==FIFO_SIZE)
          fr |= FR_TXFF;
        if (transmit_fifo.size()>transmit_trigger_level)
          ris &= ~RIS_TXRIS;
      }
    } else { // transmit fifo is empty
      if (!(fr&FR_TXFE)) UNREACHABLE;
      if (fr&FR_TXFF) UNREACHABLE;

      if ((cr&CR_CTSEn) && !cts_signal()) { // harware flow control and dce is not ready
        transmit_fifo.push(data); // the process "compute" will send the data
        fr &= ~FR_TXFE;
        if (!fifo_enabled) {
          fr |= FR_TXFF;
          ris &= ~RIS_TXRIS;
        }
      } else { // dce should be ready
        debug() <<"character sent: " <<((32<=data&&data<127)? (char) data: '.')
             <<" (" <<hex <<(uint16_t) data <<")" <<endl;
        dce->send(data);
        if (!fifo_enabled)
          ris |= RIS_TXRIS;
        YIELD();
      }
    }
    update_it_signal();
    return;
  case ECR:
    rsr = 0;
    dr = 0;
    ris &= ~RIS_ERRORS;
    update_it_signal();
    return;
  case FR:
    error() <<"invalid write access to register FR" <<endl;
    exit(1);
  case IBRD:
    ibrd = data;
    return;
  case FBRD:
    fbrd = data&FBRD_MSK;
    return;
  case LCR_H:
    lcr_h = data;
    fifo_enabled = lcr_h&LCR_H_FEN;
    info() <<"fifo " <<(fifo_enabled? "enabled": "disabled") <<endl;
    if (lcr_h&LCR_H_BRK)
      TODO("Send break signal");
    return;
  case CR:
    if ((data&CR_RTS)!=(cr&CR_RTS))
      if (data&CR_RTSEn)
        warning()<<"write access to CR register tries to change to value of RTS,"
                <<" but the hardware flow control is enabled." <<endl;
      else
        dce->set_rts(data&CR_RTS);
    if ((data&CR_RTSEn)&&!(cr&CR_RTSEn)) { // enable hardware flow control
      if (receive_fifo.size()<receive_trigger_level) {
        data |= CR_RTS;
        dce->set_rts(true);
      } else {
        data &= ~CR_RTS;
        dce->set_rts(false);
      }
    }
    cr = data;
    return;
  case IFLS:
    ifls = data;
    switch (data&IFLS_RXIFLSEL) {
    case IFLS_RXIFLSEL_TRIGGER_LEVEL_2: receive_trigger_level = 2; break;
    case IFLS_RXIFLSEL_TRIGGER_LEVEL_4: receive_trigger_level = 4; break;
    case IFLS_RXIFLSEL_TRIGGER_LEVEL_8: receive_trigger_level = 8; break;
    case IFLS_RXIFLSEL_TRIGGER_LEVEL_12: receive_trigger_level = 12; break;
    case IFLS_RXIFLSEL_TRIGGER_LEVEL_14: receive_trigger_level = 14; break;
    default: UNREACHABLE;
    }
    switch (data&IFLS_TXIFLSEL) {
    case IFLS_TXIFLSEL_TRIGGER_LEVEL_2: transmit_trigger_level = 2; break;
    case IFLS_TXIFLSEL_TRIGGER_LEVEL_4: transmit_trigger_level = 4; break;
    case IFLS_TXIFLSEL_TRIGGER_LEVEL_8: transmit_trigger_level = 8; break;
    case IFLS_TXIFLSEL_TRIGGER_LEVEL_12: transmit_trigger_level = 12; break;
    case IFLS_TXIFLSEL_TRIGGER_LEVEL_14: transmit_trigger_level = 14; break;
    default: UNREACHABLE;
    }
    info() <<"trigger levels: receive=" <<receive_trigger_level
         <<"; transmit=" <<transmit_trigger_level <<'.' <<endl;
    return;
  case IMSC:
    imsc = data;
    update_it_signal();
    return;
  case RIS:
    error() <<"invalid write access to RIS register" <<endl;
    exit(3);
  case MIS:
    error() <<"invalid write access to MIS register" <<endl;
    exit(3);
  case ICR:
    if (data&ICR_RIMIC)
      ris &= ~RIS_RIRMIS;
    if (data&ICR_CTSMIC)
      ris &= ~RIS_CTSRMIS;
    if (data&ICR_DCDMIC)
      ris &= ~RIS_DCDRMIS;
    if (data&ICR_DSRMIC)
      ris &= ~RIS_DSRRMIS;
    if (data&ICR_RXIC)
      ris &= ~RIS_RXRIS;
    if (data&ICR_TXIC)
      ris &= ~RIS_TXRIS;
    if (data&ICR_RTIC)
      ris &= ~RIS_RTRIS;
    if (data&ICR_FEIC)
      ris &= ~RIS_FERIS;
    if (data&ICR_PEIC)
      ris &= ~RIS_PERIS;
    if (data&ICR_BEIC)
      ris &= ~RIS_BERIS;
    if (data&ICR_OEIC)
      ris &= ~RIS_OERIS;
    update_it_signal();
    return;
  case DMACR:
    dmacr = data;
    return;
  default:
    error() <<"invalid write access outside range (offset = " <<hex <<addr <<")" <<endl;
    exit(3);
    return;
  }
}

bool PrimeCellUart::uart_receive_enabled() const {
  return (cr&CR_UARTEN) && (cr&CR_RXE);
}

bool PrimeCellUart::uart_transmit_enabled() const {
  return (cr&CR_UARTEN) && (cr&CR_TXE);
}

void PrimeCellUart::receive(uint8_t c) {
  if (!uart_receive_enabled()) {
    warning() <<"receive disabled" <<endl;
    return;
  }
  timeout_event.cancel();
  if (fifo_enabled) {
    if (receive_fifo.size()==FIFO_SIZE) {
      warning() <<"overrun detected (fifo enabled); new character discarded" <<endl;
      if (!(fr&FR_RXFF)) UNREACHABLE;
      dr |= DR_OE;
      ris |= RIS_OERIS;
    } else { // fifo is not full
      debug() <<"character received: " <<((32<=c&&c<127)? (char)c: '.') <<" (" <<(uint16_t) c <<")" <<endl;
      receive_fifo.push(c);

      if (receive_fifo.size()==receive_trigger_level)
        ris |= RIS_RXRIS;
      timeout_event.notify(timeout_duration);

      // update FR register
      if (receive_fifo.size()==FIFO_SIZE)
        fr |= FR_RXFF;
      else if (receive_fifo.size()==1)
        fr &= ~FR_RXFE;

      if (cr&CR_RTSEn) { // hardware flow control
        if ((receive_fifo.size()<receive_trigger_level) != rts_signal()) {
          if (!rts_signal()) UNREACHABLE;
          cr &= ~CR_RTS;
          info() <<"RTS signal cleared" <<endl;
          dce->set_rts(rts_signal());
          YIELD();
        }
      }
    }
  } else { // fifo disabled
    if (receive_fifo.size()==1) {
      warning() <<"overrun detected (fifo enabled); new character discarded" <<endl;
      if (!(fr&FR_RXFF)) UNREACHABLE;
      if (fr&FR_RXFE) UNREACHABLE;
      dr |= DR_OE;
      ris |= RIS_OERIS;
    } else {
      debug() <<"character received: " <<c <<" (" <<hex <<(uint16_t) c <<")" <<endl;
      if (!(fr&FR_RXFE)) UNREACHABLE;
      if (fr&FR_RXFF) UNREACHABLE;
      receive_fifo.push(c);
      if (receive_fifo.size()!=1) UNREACHABLE;
      ris |= RIS_RXRIS;
      fr |= FR_RXFF;
      fr &= ~FR_RXFE;
    }
  }
  update_it_signal();
}

void PrimeCellUart::compute() {
  if (transmit_fifo.size()==0) {
    if ((fr&FR_TXFF)||!(fr&FR_TXFE)) UNREACHABLE;
    return; // wait cts_event
  }
  if (!cts_signal())
    return; // wait cts_event
  uint8_t data = transmit_fifo.front();
  transmit_fifo.pop();
  if (fifo_enabled) {
    if (transmit_fifo.size()==transmit_trigger_level)
      ris |= RIS_TXRIS;
    if (transmit_fifo.size()==FIFO_SIZE-1)
      fr &= ~FR_TXFF;
    else if (transmit_fifo.size()==0)
      fr |= FR_TXFE;
  } else { // fifo disabled
    if ((fr&FR_TXFE)||!(fr&FR_TXFF)) UNREACHABLE;
    fr |= FR_TXFE;
    fr &= ~FR_TXFF;
    ris |= RIS_TXRIS;
  }
  debug() <<"character sent: " <<((32<=data&&data<127)? (char) data: '.')
       <<" (" <<hex <<(uint16_t) data <<")" <<endl;
  dce->send(data);
  METHOD_YIELD();
}

void PrimeCellUart::compute_timeout() {
  if (fifo_enabled && receive_fifo.size() &&
      !(ris&(RIS_RTRIS|RIS_RXRIS))) { // no receive interruption already raised
    ris |= RIS_RTRIS;
    update_it_signal();
  }
}

void PrimeCellUart::set_cts(bool value) {
  if (value) {
    ris |= RIS_CTSRMIS;
    fr |= FR_CTS;
  } else {
    ris &= ~RIS_CTSRMIS;
    fr &= ~FR_CTS;
  }

  // harware flow control
  if (cr&CR_CTSEn)
    if (cts_signal())
      cts_event.notify();

  update_it_signal();
}

void PrimeCellUart::set_dsr(bool new_val) {
  // ignore it
}

void PrimeCellUart::update_it_signal() {

  // Important:
  // Actually, the errors below never happen (transmission is always correct in the model)
  //  - break error
  //  - parity error
  //  - framing error

  if (it_signal!=(bool)mis()) {
    it_signal = mis();
    if (it_signal)
      info() <<"interrupt asserted (mis = " <<hex <<mis() <<")" <<endl;
    else
      info() <<"interrupt cleared" <<endl;
  }
}

} // namespace simsoc
