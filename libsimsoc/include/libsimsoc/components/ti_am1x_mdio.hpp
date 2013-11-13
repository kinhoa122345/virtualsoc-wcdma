//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#if !defined (LIBSIMSOC_TI_AM1X_MDIO_HPP__)
# define LIBSIMSOC_TI_AM1X_MDIO_HPP__

# include "libsimsoc/module.hpp"
# include "libsimsoc/interfaces/tlm.hpp"
# include "libsimsoc/interfaces/tlm_signal.hpp"
# include "libsimsoc/components/ti_am1x_core.hpp"

# include <inttypes.h>

namespace simsoc  {
namespace TI_AM1x {

  // ------------------------------------------------------------------
  class MDIO: public TI_AM1x_core<MDIO> {
  public:
    MDIO(sc_core::sc_module_name name);
    virtual ~MDIO();

  protected:
    virtual uint32_t read_word (uint32_t address);
    virtual void     write_word(uint32_t address, uint32_t value);
  };

} // namespace TI_AM1x
} // namespace simsoc

#endif // !LIBSIMSOC_TI_AM1X_MDIO_HPP__
