//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "dce_driver.hpp"

using namespace std;

namespace simsoc {

  DCE_Driver::DCE_Driver(sc_core::sc_module_name name):
    Module(name),
    dte(NULL), ok(false), rts(true), dtr(true), acc(),
    line_pending(false), delayed_chars()
  {
    SC_THREAD(compute);
  }

  void DCE_Driver::end_of_elaboration() {
    if (!dte) {
      error() <<"the DTE interface is not connected" <<endl;
      exit(3);
    }
  }

  bool DCE_Driver::did_success() const {return ok;}
  
  void DCE_Driver::wait_line(const char *line) {
    info() <<"waiting line : \"" <<line <<"\"\n";
    bool same;
    do {
      if (!line_pending) wait(line_event);
      same = strcmp(line,acc.c_str())==0;
      ack_line();
    } while (!same);
    info() <<"expected line received\n";
  }

  void DCE_Driver::wait_prompt(const char *prompt) {
    info() <<"waiting prompt : \"" <<prompt <<"\"\n";
    bool found = false;
    size_t len = strlen(prompt);
    while (!found) {
      while (acc.size()<len && !line_pending) wait(char_event);
      if (!line_pending) {
        // wait a little to check whether other characters are coming.
        sc_core::wait(888,sc_core::SC_MS,char_event);
        found = strcmp(prompt,acc.c_str())==0;
        if (!found && !line_pending) wait(line_event);
      }
      ack_line();
    }
    info() <<"expected prompt received\n";
  }

  void DCE_Driver::expect_line(const char *line) {
    info() <<"expecting line : \"" <<line <<"\"\n";
    if (!line_pending) wait(line_event);
    if (strcmp(line,acc.c_str())!=0) {
      error() <<"received \"" <<acc <<"\" instead of \"" <<line <<"\"\n";
      exit(1);
    }
    ack_line();
    info() <<"expected line received\n";
  }

  void DCE_Driver::expect_prompt(const char *prompt) {
    info() <<"expecting prompt : \"" <<prompt <<"\"\n";
    size_t len = strlen(prompt);
    while (acc.size()<len && !line_pending) wait(char_event);
    if (line_pending) {
      error() <<"received an unexpected new line character\n";
      exit(1);
    }
    // wait a little to check whether other characters are coming.
    sc_core::wait(888,sc_core::SC_MS,char_event);
    if (strcmp(prompt,acc.c_str())!=0) {
      error() <<"received \"" <<acc <<"\" instead of \"" <<prompt <<"\"\n";
      exit(1);
    }
    ack_line();
    info() <<"expected prompt received\n";
  }

  void DCE_Driver::reply(char c) {
    sc_core::wait(10,sc_core::SC_MS); // Send the characters slowly, i.e., at 100 Hz
    // FIXME: check the RTS/DTR signal vlaue
    dte->receive(c);
  }

  void DCE_Driver::reply(const char *s) {
    info() <<"sending string: \"" <<s <<"\"\n";
    while (*s) {reply(*s); ++s;}
    reply('\n');
    info() <<"string sent\n";
  }

  void DCE_Driver::end_of_test() {
    info() <<"End of test\n";
    ok = true;
    sc_core::sc_stop();
    wait(/*forever*/);
  }

  void DCE_Driver::bind(AbstractRS232_DTE *dte_) {
    assert(!dte);
    dte = dte_;
    assert(dte);
  }

  void DCE_Driver::ack_line() {
    acc = ""; line_pending = false;
    while (!delayed_chars.empty() && !line_pending) {
      this->send(delayed_chars.front());
      delayed_chars.pop();
    }
  }

  void DCE_Driver::send(uint8_t c) {
    if (c=='\r') return; // ignore "carriage return"
    if (line_pending) {
      debug() <<"Overrun in DCE test driver, likely because the UART does not wait\n"
        "\t\t\t\t\t before sending the next character\n";
      delayed_chars.push(c);
      return;
    }
    char_event.notify();
    if (c=='\n') {
      info() <<"line received: \"" <<acc <<"\"\n";
      line_event.notify();
      line_pending = true;
    // } else if (c<32) {
    //   TODO("handle special characters");
    } else {
      acc += c;
      debug() <<"character received, current line is: \"" <<acc <<"\"\n";
    }
  }

  void DCE_Driver::set_rts(bool value) {rts = value;}

  void DCE_Driver::set_dtr(bool value) {dtr = value;}

} // namespace simsoc
