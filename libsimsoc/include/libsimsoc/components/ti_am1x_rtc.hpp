//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#if !defined (LIBSIMSOC_TI_AM1X_RTC_HPP__)
# define LIBSIMSOC_TI_AM1X_RTC_HPP__

# include "libsimsoc/module.hpp"
# include "libsimsoc/interfaces/tlm.hpp"
# include "libsimsoc/interfaces/tlm_signal.hpp"
# include "libsimsoc/components/ti_am1x_core.hpp"

namespace simsoc  {
namespace TI_AM1x {

  class RTC: public TI_AM1x_core<RTC> {
  public:
    RTC(sc_core::sc_module_name name);
    virtual ~RTC();

  protected:
    virtual uint32_t read_word (uint32_t address);
    virtual void     write_word(uint32_t address, uint32_t value);

  public:
    typedef signals::SignalInitiatorPort_Level signal_t;

    signal_t it_signal;
  };

} // namespace TI_AM1x
} // namespace simsoc

#endif // !LIBSIMSOC_TI_AM1X_RTC_HPP__
