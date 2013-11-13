//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef TLM_SIGNAL_HPP
#error "tlm_signal.tpp cannot be used directly; include tlm_signal.hpp instead"
#endif

namespace simsoc {

// Target Port

template<typename T>
SignalTargetPort<T>::SignalTargetPort(T defval):
  sc_core::sc_export<SignalTarget<T> >(),
  initiator(NULL), default_value(defval) {}

template<typename T>
void SignalTargetPort<T>::bind_to_initiator(SignalInitiatorPort<T> *i) {
  initiator = i;
}

template<typename T>
T SignalTargetPort<T>::get() const {return initiator? initiator->get(): default_value;}


// Multi Target Port

template<typename T>
SignalMultiTargetPort<T>::SignalMultiTargetPort(SignalMultiTarget<T> *h, unsigned int n, T defval):
  initiator(NULL), default_value(defval), host(h), id(n) {}

template<typename T>
SignalMultiTargetPort<T>::SignalMultiTargetPort(SignalMultiTarget<T> *h, T defval):
  initiator(NULL), default_value(defval), host(h), id(0) {num=0;}

template<typename T>
SignalMultiTargetPort<T>::SignalMultiTargetPort(const SignalMultiTargetPort<T> &mtp):
  initiator(NULL), default_value(mtp.default_value), host(mtp.host), id(num++) {}

template<typename T>
void SignalMultiTargetPort<T>::bind_to_initiator(SignalInitiatorPort<T> *i) {
  initiator = i;
}

template<typename T>
T SignalMultiTargetPort<T>::get() const {
  return initiator? initiator->get(): default_value;
}

template<typename T>
void SignalMultiTargetPort<T>::signal(T value) {
  host->signal(value,id);
}


// Initiator Port

template<typename T>
SignalInitiatorPort<T>::SignalInitiatorPort(): value(false) {}

template<typename T>
void SignalInitiatorPort<T>::operator()(SignalTargetPort<T> &t) {
  port(t);
  t.bind_to_initiator(this);
}

template<typename T>
void SignalInitiatorPort<T>::operator()(SignalMultiTargetPort<T> &t) {
  port(t);
  t.bind_to_initiator(this);
}

template<typename T>
void SignalInitiatorPort<T>::set(T b) {
  if (b==value)
    return;
  value = b;
  for (size_t i = 0, ei = port.size(); i!=ei; ++i)
    port[i]->signal(b);
}

template<typename T>
T SignalInitiatorPort<T>::get() const {return value;}

} // namespace simsoc
