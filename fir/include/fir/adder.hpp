#ifndef _FIR_ADDER_H_
#define _FIR_ADDER_H_

#include <type_traits>

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

namespace fir {

namespace detail {

template <unsigned _N>
struct pipeline_adder_basis
{
  sc_signal<int> partial_sum[_N];
  pipeline_adder<_N> sub_level;

  static constexpr unsigned get_level_number(void)
  { return 1 + pipeline_adder<_N>::get_level_number(); }

  static constexpr unsigned get_level_size(unsigned lvl)
  { return (lvl == 0) ? _N : pipeline_adder<_N>::get_level_size(lvl-1); }

  inline sc_signal<int>* get_level(unsigned lvl)
  { return (lvl == 0) ? partial_sum : sub_level.get_level(lvl-1); }

  inline sc_signal<int> const* get_level(unsigned lvl) const
  { return (lvl == 0) ? partial_sum : sub_level.get_level(lvl-1); }

  inline void compute(sc_signal<int>* operand, unsigned limit)
  {
    this->sub_level.compute(this->partial_sum);
    for (unsigned i = 0; i < limit; ++i)
      this->partial_sum[i].write(
            operand[4*i  ].read()
          + operand[4*i+1].read()
          + operand[4*i+2].read()
          + operand[4*i+3].read());
  }
};

struct pipeline_adder_basis_le_4
{
  sc_signal<int> sum;

  static constexpr unsigned get_level_number(void) { return 1; }

  static constexpr unsigned get_level_size(unsigned lvl)
  { return (lvl == 0) ? 1 : 0; }

  sc_signal<int>* get_level(unsigned lvl)
  { return (lvl == 0) ? &sum : nullptr; }

  sc_signal<int> const* get_level(unsigned lvl) const
  { return (lvl == 0) ? &sum : nullptr; }
};

} // detail


template<>
struct pipeline_adder<2>
    : public detail::pipeline_adder_basis_le_4
{
  void compute(sc_signal<int> operand[2])
  {
    sum.write(
          operand[0].read()
        + operand[1].read());
  }

  void compute(sc_signal<int> operand[1],
               sc_signal<int>& last0)
  {
    sum.write(
          operand[0].read()
        + last0.read());
  }
};

template<>
struct pipeline_adder<3>
    : public detail::pipeline_adder_basis_le_4
{
  void compute(sc_signal<int> operand[3])
  {
    sum.write(
          operand[0].read()
        + operand[1].read()
        + operand[2].read());
  }

  void compute(sc_signal<int> operand[2],
               sc_signal<int>& last0)
  {
    sum.write(
          operand[0].read()
        + operand[1].read()
        + last0.read());
  }

  void compute(sc_signal<int> operand[1],
               sc_signal<int>& last0,
               sc_signal<int>& last1)
  {
    sum.write(
          operand[0].read()
        + last0.read()
        + last1.read());
  }
};

template<>
struct pipeline_adder<4>
    : public detail::pipeline_adder_basis_le_4
{
  void compute(sc_signal<int> operand[4])
  {
    sum.write(
          operand[0].read()
        + operand[1].read()
        + operand[2].read()
        + operand[3].read());
  }

  void compute(sc_signal<int> operand[3],
               sc_signal<int>& last0)
  {
    sum.write(
          operand[0].read()
        + operand[1].read()
        + operand[2].read()
        + last0.read());
  }

  void compute(sc_signal<int> operand[2],
               sc_signal<int>& last0,
               sc_signal<int>& last1)
  {
    sum.write(
          operand[0].read()
        + operand[1].read()
        + last0.read()
        + last1.read());
  }

  void compute(sc_signal<int> operand[1],
               sc_signal<int>& last0,
               sc_signal<int>& last1,
               sc_signal<int>& last2)
  {
    sum.write(
          operand[0].read()
        + last0.read()
        + last1.read()
        + last2.read());
  }
};

template <unsigned _M>
struct pipeline_adder<_M, typename std::enable_if<_M%4==0>::type>
    : public detail::pipeline_adder_basis<_M/4>
{
  typedef detail::pipeline_adder_basis<_M/4> basis;

  static constexpr unsigned _N = _M/4;

  void compute(sc_signal<int> operand[4*_N])
  { basis::compute(operand, _N); }

  void compute(sc_signal<int> operand[4*_N-1],
               sc_signal<int>& last0)
  {
    basis::compute(operand, _N-1);

    this->partial_sum[_N].write(
          operand[4*_N-4].read()
        + operand[4*_N-3].read()
        + operand[4*_N-2].read()
        + last0.read());
  }

  void compute(sc_signal<int> operand[4*_N-1],
               sc_signal<int>& last0,
               sc_signal<int>& last1)
  {
    basis::compute(operand, _N-1);

    this->partial_sum[_N].write(
          operand[4*_N-4].read()
        + operand[4*_N-3].read()
        + last0.read()
        + last1.read());
  }

  void compute(sc_signal<int> operand[4*_N-1],
               sc_signal<int>& last0,
               sc_signal<int>& last1,
               sc_signal<int>& last2)
  {
    basis::compute(operand, _N-1);

    this->partial_sum[_N].write(
          operand[4*_N-4].read()
        + last0.read()
        + last1.read()
        + last2.read());
  }
};

template <unsigned _M>
struct pipeline_adder<_M, typename std::enable_if<_M%4==1>::type>
    : public detail::pipeline_adder_basis<_M/4+1>
{
  typedef detail::pipeline_adder_basis<_M/4+1> basis;

  static constexpr unsigned _N = _M/4;

  void compute(sc_signal<int> operand[4*_N+1])
  {
    basis::compute(operand, _N);
    this->partial_sum[_N].write(operand[4*_N].read());
  }

  void compute(sc_signal<int> operand[4*_N],
               sc_signal<int>& last0)
  {
    basis::compute(operand, _N);
    this->partial_sum[_N].write(last0.read());
  }

  void compute(sc_signal<int> operand[4*_N-1],
               sc_signal<int>& last0,
               sc_signal<int>& last1)
  {
    basis::compute(operand, _N-1);

    this->partial_sum[_N-1].write(
          operand[4*_N-4].read()
        + operand[4*_N-3].read()
        + operand[4*_N-2].read()
        + last0.read());
    this->partial_sum[_N].write(last1.read());
  }

  void compute(sc_signal<int> operand[4*_N-2],
               sc_signal<int>& last0,
               sc_signal<int>& last1,
               sc_signal<int>& last2)
  {
    basis::compute(operand, _N-1);

    this->partial_sum[_N-1].write(
          operand[4*_N-3].read()
        + operand[4*_N-2].read()
        + last0.read()
        + last1.read());
    this->partial_sum[_N].write(last2.read());
  }
};

template <unsigned _M>
struct pipeline_adder<_M, typename std::enable_if<_M%4==2>::type>
    : public detail::pipeline_adder_basis<_M/4+1>
{
  typedef detail::pipeline_adder_basis<_M/4+1> basis;

  static constexpr unsigned _N = _M/4;

  void compute(sc_signal<int> operand[4*_N+2])
  {
    basis::compute(operand, _N);

    this->partial_sum[_N].write(
          operand[4*_N  ].read()
        + operand[4*_N+1].read());
  }

  void compute(sc_signal<int> operand[4*_N+1],
               sc_signal<int>& last0)
  {
    basis::compute(operand, _N);

    this->partial_sum[_N].write(
          operand[4*_N].read()
        + last0.read());
  }

  void compute(sc_signal<int> operand[4*_N],
               sc_signal<int>& last0,
               sc_signal<int>& last1)
  {
    basis::compute(operand, _N);

    this->partial_sum[_N].write(
          last0.read() + last1.read());
  }

  void compute(sc_signal<int> operand[4*_N-1],
               sc_signal<int>& last0,
               sc_signal<int>& last1,
               sc_signal<int>& last2)
  {
    basis::compute(operand, _N-1);

    this->partial_sum[_N-1].write(
          operand[4*_N-4].read()
        + operand[4*_N-3].read()
        + operand[4*_N-2].read()
        + last0.read());
    this->partial_sum[_N  ].write(
          last1.read() + last2.read());
  }
};

template <unsigned _M>
struct pipeline_adder<_M, typename std::enable_if<_M%4==3>::type>
    : public detail::pipeline_adder_basis<_M/4+1>
{
  typedef detail::pipeline_adder_basis<_M/4+1> basis;

  static constexpr unsigned _N = _M/4;

  void compute(sc_signal<int> operand[4*_N+3])
  {
    basis::compute(operand, _N);

    this->partial_sum[_N].write(
          operand[4*_N  ].read()
        + operand[4*_N+1].read()
        + operand[4*_N+2].read());
  }

  void compute(sc_signal<int> operand[4*_N+2],
               sc_signal<int>& last0)
  {
    basis::compute(operand, _N);

    this->partial_sum[_N].write(
          operand[4*_N  ].read()
        + operand[4*_N+1].read()
        + last0.read());
  }

  void compute(sc_signal<int> operand[4*_N+1],
               sc_signal<int>& last0,
               sc_signal<int>& last1)
  {
    basis::compute(operand, _N);

    this->partial_sum[_N].write(
          operand[4*_N].read()
        + last0.read()
        + last1.read());
  }

  void compute(sc_signal<int> operand[4*_N],
               sc_signal<int>& last0,
               sc_signal<int>& last1,
               sc_signal<int>& last2)
  {
    basis::compute(operand, _N);
    this->partial_sum[_N].write(
          last0.read() + last1.read() + last2.read());
  }
};

} // fir

#endif // _FIR_ADDER_H_
