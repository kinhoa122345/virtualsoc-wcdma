//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef TLM_SIGNAL_HPP
#define TLM_SIGNAL_HPP

#include <systemc>

namespace simsoc {

template<typename T>
class SignalTarget: public sc_core::sc_interface
{
public:
  virtual void signal(T)=0;
};

template<typename T>
class SignalInitiatorPort;

template<typename T>
class SignalTargetPort: public sc_core::sc_export<SignalTarget<T> > {
public:
  SignalTargetPort(T default_value);
  T get() const;
  operator T () const {return get();}
protected:
  friend class SignalInitiatorPort<T>;
  SignalInitiatorPort<T> *initiator;
  T default_value; // value used if not bound to an initiator port
  void bind_to_initiator(SignalInitiatorPort<T> *);
};

template<typename T>
class SignalMultiTarget {
public:
  virtual ~SignalMultiTarget() {}
  virtual void signal(T,size_t)=0;
};

template<typename T>
class SignalMultiTargetPort: public SignalTarget<T> {
public:
  SignalMultiTargetPort(SignalMultiTarget<T> *h, unsigned int n, T default_value);
  // for vector initialization:
  SignalMultiTargetPort(SignalMultiTarget<T> *h, T default_value);
  SignalMultiTargetPort(const SignalMultiTargetPort<T> &mtp);
  T get() const;
  operator T () const {return get();}

protected:
  friend class SignalInitiatorPort<T>;
  void signal(T value);
  SignalInitiatorPort<T> *initiator;
  T default_value; // value used if not bound to an initiator port
  void bind_to_initiator(SignalInitiatorPort<T> *);
  static unsigned int num;
  SignalMultiTarget<T> *host;
  unsigned int id;
};

template<typename T>
unsigned int SignalMultiTargetPort<T>::num = 0;

template<typename T>
class SignalInitiatorPort {
public:
  SignalInitiatorPort();
  void operator()(SignalTargetPort<T> &t);
  void operator()(SignalMultiTargetPort<T> &t);
  void set(T b);
  T get() const;
  operator T () const {return get();}
  SignalInitiatorPort& operator = (T b) {set(b); return *this;}
protected:
  T value;
  sc_core::sc_port<SignalTarget<T>,0,sc_core::SC_ZERO_OR_MORE_BOUND> port;
};

} // namespace simsoc

#include "tlm_signal.tpp"

#endif //TLM_SIGNAL_HPP
