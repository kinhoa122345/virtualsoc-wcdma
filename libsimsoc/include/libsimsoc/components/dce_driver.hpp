//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef DCE_DRIVER_HPP
#define DCE_DRIVER_HPP

#include <libsimsoc/module.hpp>
#include <libsimsoc/interfaces/RS232.hpp>
#include <queue>

namespace simsoc {

  struct DCE_Driver: Module, AbstractRS232_DCE {

    SC_HAS_PROCESS(DCE_Driver);
    DCE_Driver(sc_core::sc_module_name);
    void end_of_elaboration();

    bool did_success() const;

    // implementaion of the AbstractRS232_DCE interface
    void bind(AbstractRS232_DTE*);
    void send(uint8_t c);
    void set_rts(bool value);
    void set_dtr(bool value);

  protected:
    virtual void compute() = 0;

    void wait_line(const char *);
    void wait_prompt(const char *);
    void expect_line(const char *);
    void expect_prompt(const char *);
    void reply(char);
    void reply(const char *);
    void end_of_test();

  private:
    void ack_line();

    AbstractRS232_DTE *dte;
    bool ok;
    bool rts, dtr;
    std::string acc;
    bool line_pending;
    sc_core::sc_event char_event;
    sc_core::sc_event line_event;
    std::queue<char> delayed_chars;
  };

} // namespace simsoc

#endif // DCE_DRIVER_HPP
