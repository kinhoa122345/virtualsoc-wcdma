//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "dce_xterm_pthread.hpp"
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
#include <sys/stat.h>
using namespace std;
using namespace sc_core;

#ifndef ABS_TOP_BUILDDIR
#error "ABS_TOP_BUILDDIR not defined"
#endif

#ifndef BINDIR
#error "BINDIR not defined"
#endif

namespace simsoc {

bool DCE_Xterm_PTHREAD::wait_before_close = true;

static bool is_executable_file(const char *filename) {
  struct stat file_info;
  debug() <<"trying " <<filename <<'\n';
  if (stat(filename,&file_info)) {
    debug() <<strerror(errno) <<'\n';
    return false;
  }
  debug() <<"file_info.st_mode: " <<file_info.st_mode <<endl;
  if (!S_ISREG(file_info.st_mode)) {
    debug() <<"not reg\n";
    return false;
  }
  if (!(file_info.st_mode&(1<<6))) {
    debug() <<"not executable\n";
    return false;
  }
  return true;
}

DCE_Xterm_PTHREAD::DCE_Xterm_PTHREAD(sc_module_name name, const char *path):
  Module(name),
  r_descriptor(0), w_descriptor(0)
{
  simulation_started = false;
  SC_METHOD(compute);

  int res;
  res = pipe(filedesA);
  if (res) {
    error() <<"start_xterm(): pipe():" <<errno <<endl;
    exit(1);
  }
  res = pipe(filedesB);
  if (res) {
    error() <<"start_xterm(): pipe():" <<errno <<endl;
    exit(1);
  }

  const char **a = new const char*[20];
  string * title = new string(string("SimSoc:")+this->name());
  // TODO: free a and title somewhere

  // searching simconsole
  string simconsole = string(ABS_TOP_BUILDDIR) + "/utils/SimConsole/simconsole";
  if (!is_executable_file(simconsole.c_str())) {
    simconsole = string(BINDIR) + "/simconsole";
    if (!is_executable_file(simconsole.c_str())) {
      if (path&&*path) {
        simconsole = string(path)+"/simconsole";
        if (!is_executable_file(simconsole.c_str()))
          simconsole = string("simconsole"); // maybe in PATH
      } else
        simconsole = string("simconsole"); // maybe in PATH
    }
  }

  a[0] = getenv("XTERM");
  if (a[0] == NULL)
    a[0] = "xterm";
  a[1] = "-geometry";
  a[2] = "80x25";
  a[3] = "-title";
  a[4] = title->c_str();
  a[5] = "-e";
  a[6] = simconsole.c_str();
  char * s1 = new char [80];
  snprintf(s1, 80, "%i", filedesA[0]);
  a[7] = (const char *) s1;
  char * s2 = new char [80];
  snprintf(s2, 80, "%i", filedesB[1]);
  a[8] = (const char *) s2;
  a[9] = NULL;

  pid_t p = fork();
  if (p == -1) {
    error() <<"error while trying to fork()" <<errno <<endl;
    exit(1);
  } else if (p == 0) {
    close(filedesA[1]);
    close(filedesB[0]);

    p = setsid();
    if (p < 0)
      error() <<"error while trying to do a setsid()" <<errno <<endl;

    {
      std::ostringstream oss(std::ostringstream::out);
      for (size_t i = 0; a[i]; ++i) {
        oss <<a[i];
        if (a[i+1] != NULL)
          oss <<' ';
      }
      info() <<"executing: " <<oss.str() <<endl;
    }

    res = execvp(a[0], (char* const*) a);

    {
      std::ostringstream oss(std::ostringstream::out);
      for (size_t i = 0; a[i]; ++i) {
        oss <<a[i];
        if (a[i+1] != NULL)
          oss <<' ';
      }
      error() <<"error while trying to execvp \"" <<oss.str() <<"\":\n\t" <<strerror(errno) <<'\n';
      if (errno == ENOENT)
        error() <<"Most probably you don't have xterm in your PATH. Try again." <<endl;
      exit(1);
    }
  }

  close(filedesA[0]);
  close(filedesB[1]);

  w_descriptor = filedesA[1];
  r_descriptor = filedesB[0];
}

DCE_Xterm_PTHREAD::~DCE_Xterm_PTHREAD() {

  if (wait_before_close) {
    cout <<"Press Enter to close the xterms" <<endl;
    cin.get();
    wait_before_close = false;
  }
  close(filedesA[1]);
  close(filedesB[0]);

  pthread_join(uart_thread,NULL);
}

void DCE_Xterm_PTHREAD::end_of_elaboration() {
  if (!dte) {
    error() <<"the DTE interface is not connected" <<endl;
    exit(3);
  }
  pthread_mutex_init(&input_mutex,NULL);
  pthread_cond_init(&input_cond,NULL);
  int cs;
  cs=pthread_create(&uart_thread,NULL,compute_pthread,static_cast<DCE_Xterm_PTHREAD*>(this));
  if (cs!=0) {
    error() <<"Create   pthread   error!\n"<<endl;
    exit(1);
  }
}


void DCE_Xterm_PTHREAD::send(uint8_t ch)
{
  if(write(w_descriptor, &ch, 1)<0){
    error()<<"write operation failed!"<<endl;
    exit(1);
  }
}

void DCE_Xterm_PTHREAD::set_rts(bool rts_signal) {
  bool cts_signal = false;
  if (rts_signal==true)
    dte->set_cts(cts_signal);
}

void DCE_Xterm_PTHREAD::set_dtr(bool dtr_signal) {
}

void DCE_Xterm_PTHREAD::compute() {
  pthread_mutex_lock(&input_mutex);
  pthread_cond_signal(&input_cond);
  simulation_started = true;
  pthread_mutex_unlock(&input_mutex);
}

void* DCE_Xterm_PTHREAD::compute_pthread(void* t) {
  DCE_Xterm_PTHREAD *this_ = static_cast<DCE_Xterm_PTHREAD*>(t);

  ssize_t len;
  uint8_t c;

  pthread_mutex_lock(&this_->input_mutex);
  if (!this_->simulation_started)
    pthread_cond_wait(&this_->input_cond,&this_->input_mutex);
  pthread_mutex_unlock(&this_->input_mutex);

  while(1)
  {
    len = read(this_->r_descriptor, &c, 1);
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
