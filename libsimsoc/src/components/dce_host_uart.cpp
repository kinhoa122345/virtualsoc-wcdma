//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "dce_host_uart.hpp"
#include "libsimsoc/interfaces/yield.hpp"
#include "libsimsoc/display.hpp"
#include <termios.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <fcntl.h>
using namespace std;
using namespace sc_core;

namespace simsoc {

DCE_HostUART::DCE_HostUART(sc_module_name name):
  Module(name), fd(0)
{
  SC_METHOD(compute);

  fd = open("/dev/ttyS0",O_RDWR|O_NOCTTY);
  if (fd==-1) {
    error() <<"failed to open /dev/ttyS0" <<endl;
    close(fd);
    exit(1);
  }

  tcgetattr(fd, &hostuart_tios);

  hostuart_tios.c_lflag &= ~ICANON;
  hostuart_tios.c_cc[VTIME] = 0;
  hostuart_tios.c_cc[VMIN] = 1;
  hostuart_tios.c_lflag &= ~ECHO;
  hostuart_tios.c_iflag &= ~ICRNL;

  cfsetispeed(&hostuart_tios, B9600);
  cfsetospeed(&hostuart_tios, B9600);

  hostuart_tios.c_cflag &= ~CSIZE;
  hostuart_tios.c_cflag |= ~CS5;

  hostuart_tios.c_cflag &= ~PARENB;
  //hostuart_tios.c_cflag &= ~PARODD;

  hostuart_tios.c_cflag &= ~CRTSCTS;

  tcsetattr(fd, TCSANOW, &hostuart_tios);
}

DCE_HostUART::~DCE_HostUART() {
  close(fd);
}

void DCE_HostUART::end_of_elaboration() {
  if (!dte) {
    error() <<"the DTE interface is not connected" <<endl;
    exit(3);
  }
}

void DCE_HostUART::send(uint8_t ch)
{
  if(write(fd, &ch, 1)<0){
    error()<<"write operation failed!"<<endl;
    exit(1);
  }
}

void DCE_HostUART::set_rts(bool rts_signal) {
  bool cts_signal = false;
  if (rts_signal==true)
    dte->set_cts(cts_signal);
}

void DCE_HostUART::set_dtr(bool dtr_signal) {
}

void DCE_HostUART::compute() {

  fd_set fds;
  FD_ZERO(&fds);
  FD_SET(fd, &fds);

  struct timeval tv;
  tv.tv_sec = 0;
  tv.tv_usec = 0;

  if (select(fd+1, &fds, NULL, NULL, &tv)) {
    uint8_t c;
    size_t len = read(fd, &c, 1);
    assert(len<=1);
    if (len) {
      info() <<"receive character" <<c <<endl;
      dte->receive(c);
    }
  }
  METHOD_YIELD();
}

} // namespace simsoc
