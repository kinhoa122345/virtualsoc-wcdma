//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "dce_host_uart_pthread.hpp"
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

DCE_HostUART_PTHREAD::DCE_HostUART_PTHREAD(sc_module_name name):
  Module(name),
  fd(0)
{
  SC_METHOD(compute);
  simulation_started = false;

  fd = open("/dev/ttyS0",O_RDWR|O_NOCTTY);
  if (fd==-1) {
    error() <<"failed to open /dev/ttyS0" <<endl;
    exit(1);
    close(fd);
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

DCE_HostUART_PTHREAD::~DCE_HostUART_PTHREAD() {
  close(fd);
  pthread_join(uart_thread,NULL);
}

void DCE_HostUART_PTHREAD::end_of_elaboration() {
  if (!dte) {
    error() <<"the DTE interface is not connected" <<endl;
    exit(3);
  }
  pthread_mutex_init(&input_mutex,NULL);
  pthread_cond_init(&input_cond,NULL);
  int cs;
  cs=pthread_create(&uart_thread,NULL,compute_pthread,static_cast<DCE_HostUART_PTHREAD*>(this));
  if (cs!=0) {
    error() <<"Create   pthread   error!\n"<<endl;
    exit(1);
  }
}

void DCE_HostUART_PTHREAD::send(uint8_t ch)
{
  if(write(fd, &ch, 1)<0){
    error()<<"write operation failed!"<<endl;
    exit(1);
  }
}

void DCE_HostUART_PTHREAD::set_rts(bool rts_signal) {
  bool cts_signal = false;
  if (rts_signal==true)
    dte->set_cts(cts_signal);
}

void DCE_HostUART_PTHREAD::set_dtr(bool dtr_signal) {
}

void DCE_HostUART_PTHREAD::compute() {
  pthread_mutex_lock(&input_mutex);
  pthread_cond_signal(&input_cond);
  simulation_started = true;
  pthread_mutex_unlock(&input_mutex);
}

void* DCE_HostUART_PTHREAD::compute_pthread(void* t) {
DCE_HostUART_PTHREAD *this_ = static_cast<DCE_HostUART_PTHREAD*>(t);

  ssize_t len;
  uint8_t c;

  pthread_mutex_lock(&this_->input_mutex);
  if (!this_->simulation_started)
    pthread_cond_wait(&this_->input_cond,&this_->input_mutex);
  pthread_mutex_unlock(&this_->input_mutex);

  while(1)
  {
    len = read(this_->fd, &c, 1);
    if (len==1) {
      this_->info() <<"receive character" <<c <<endl;
      this_->dte->receive(c);
    } else if (len==-1) {
      this_->error() <<"read returned an error (error number: " <<errno <<')' <<endl;
    } else if (len==0) {
      break;
    } else {
      UNREACHABLE;
    }
  }
  this_->info() <<"end of pthread" <<endl;
  return NULL;
}

} // namespace simsoc
