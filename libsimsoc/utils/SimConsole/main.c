/*
 * SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
 * LGPL license version 3
 */

#include <termios.h>
#include <errno.h>
#include <signal.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

struct termios console_slave_tios;
int inputd;
int outputd;

void sigint_handler(int n)
{
  char c = 3;
  if(write(outputd, &c, 1)<0){
    exit(1);
  }
  signal(SIGINT, sigint_handler);
}

void sigcont_handler(int n)
{
  tcsetattr(STDIN_FILENO, TCSANOW, &console_slave_tios);
  signal(SIGCONT, sigcont_handler);
}

int descriptor_avail(int d)
{
  fd_set rfds;
  struct timeval tv;

  FD_ZERO(&rfds);
  FD_SET(d, &rfds);
  tv.tv_sec = 0;
  tv.tv_usec = 0;
  return select(d+1, &rfds, NULL, NULL, &tv);
}

int main(int argc, const char *argv[])
{
  int len;
  char buf[16384];

  assert(argc==3);
  inputd = atoi(argv[1]);
  outputd = atoi(argv[2]);

  tcgetattr(STDIN_FILENO, &console_slave_tios);

  console_slave_tios.c_lflag &= ~ICANON;
  console_slave_tios.c_cc[VTIME] = 0;
  console_slave_tios.c_cc[VMIN] = 1;
  console_slave_tios.c_lflag &= ~ECHO;
  console_slave_tios.c_iflag &= ~ICRNL;
  tcsetattr(STDIN_FILENO, TCSANOW, &console_slave_tios);

  signal(SIGINT, sigint_handler);
  signal(SIGCONT, sigcont_handler);

  puts("simconsole is ready");

  while (1) {

    if (descriptor_avail(inputd)) {
      len = read(inputd, buf, sizeof(buf));
      if (len < 1)
        exit(0);
      if(write(STDOUT_FILENO, buf, len)<0){
        exit(1);
      }
      fflush(stdout);
    }

    if (descriptor_avail(STDIN_FILENO)) {
      len = read(STDIN_FILENO, buf, sizeof(buf));
      if (len < 1)
        exit(0);
      if(write(outputd, buf, len)<0){
        exit(1);
      }
    }

    usleep(10000);
  }
}
