#ifndef _FIR_ADDER_H_
#define _FIR_ADDER_H_

#include <systemc.h>


namespace fir {

/** @brief Optimal pipeline adder of _Size elements.
 **
 ** @param _Size The number of elements to add.
 **/
template <unsigned _Size, typename = void>
struct pipeline_adder
{
  /// Return the pipeline level used for this adder type.
  static constexpr unsigned get_level_number(void);

  /// Return the number of 2-adders used for the given level.
  static constexpr unsigned get_level_size(unsigned lvl);

  /// Return the signal table entry of the given level.
  sc_signal<int>* get_level(unsigned lvl);

  /// Return the signal table const entry of the given level.
  sc_signal<int> const* get_level(unsigned lvl) const;

  /// Add the input signals.
  void compute(sc_signal<int> operand[_Size]);
};

} // fir

#endif // _FIR_ADDER_H_
