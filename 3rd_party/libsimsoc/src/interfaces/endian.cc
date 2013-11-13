#include "endian.hh"
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string.h>


using namespace std;

namespace simsoc{

#if 0
  ParameterBase void_param;


//=============================================================================
//=                             ParameterBase                                 =
//=============================================================================

  ParameterBase::ParameterBase(const char *_name) :
    name(_name)
  {
  }

  ParameterBase::ParameterBase() :
    name()
  {
  }

  ParameterBase::~ParameterBase()
  {
  }

  const char *ParameterBase::GetName() const
  {
    return name.c_str();
  }

  ParameterBase::operator bool () const { return false; }
  ParameterBase::operator char () const { return (long long) *this; }
  ParameterBase::operator short () const { return (long long) *this; }
  ParameterBase::operator int () const { return (long long) *this; }
  ParameterBase::operator long () const { return (long long) *this; }
  ParameterBase::operator long long () const { return 0LL; }
  ParameterBase::operator unsigned char () const { return (unsigned long long) *this; }
  ParameterBase::operator unsigned short () const { return (unsigned long long) *this; }
  ParameterBase::operator unsigned int () const { return (unsigned long long) *this; }
  ParameterBase::operator unsigned long () const { return (unsigned long long) *this; }
  ParameterBase::operator unsigned long long () const { return 0ULL; }
  ParameterBase::operator float () const { return (double) *this; }
  ParameterBase::operator double () const { return 0.0; }
  ParameterBase::operator string () const { return string(); }

  ParameterBase& ParameterBase::operator = (bool value) { return *this; }
  ParameterBase& ParameterBase::operator = (char value) { *this = (long long) value; return *this; }
  ParameterBase& ParameterBase::operator = (short value) { *this = (long long) value; return *this; }
  ParameterBase& ParameterBase::operator = (int value) { *this = (long long) value; return *this; }
  ParameterBase& ParameterBase::operator = (long value) { *this = (long long) value; return *this; }
  ParameterBase& ParameterBase::operator = (long long value) { return *this; }
  ParameterBase& ParameterBase::operator = (unsigned char value) { *this = (unsigned long long) value; return *this; }
  ParameterBase& ParameterBase::operator = (unsigned short value) { *this = (unsigned long long) value; return *this; }
  ParameterBase& ParameterBase::operator = (unsigned int value) { *this = (unsigned long long) value; return *this; }
  ParameterBase& ParameterBase::operator = (unsigned long value) { *this = (unsigned long long) value; return *this; }
  ParameterBase& ParameterBase::operator = (unsigned long long value) { return *this; }
  ParameterBase& ParameterBase::operator = (float value) { *this = (double) value; return *this; }
  ParameterBase& ParameterBase::operator = (double value) { return *this; }
  ParameterBase& ParameterBase::operator = (const char *value) { return *this; }

  ParameterBase& ParameterBase::operator [] (unsigned int index)
  {
    if(index >= 0)
      {
        cout << "Subscript out of range" << endl;
        return void_param;
      }
	return *this;
}

//=============================================================================
//=                            Parameter<TYPE>                                =
//=============================================================================

  template <class TYPE>
  Parameter<TYPE>::Parameter(const char *_name, TYPE& _storage) :
    ParameterBase(_name), storage(&_storage)
{
}

template <class TYPE> Parameter<TYPE>::operator bool () const { return (*storage) ? true : false; }
template <class TYPE> Parameter<TYPE>::operator long long () const { return (long long) *storage; }
template <class TYPE> Parameter<TYPE>::operator unsigned long long () const { return (unsigned long long) *storage; }
template <class TYPE> Parameter<TYPE>::operator double () const { return (double) *storage; }
template <class TYPE> Parameter<TYPE>::operator string () const { stringstream sstr; sstr << "0x" << hex << *storage; return sstr.str(); }

template <class TYPE> ParameterBase& Parameter<TYPE>::operator = (bool value) { *storage = value ? 1 : 0; return *this; }
template <class TYPE> ParameterBase& Parameter<TYPE>::operator = (long long value) { *storage = value;	return *this; }
template <class TYPE> ParameterBase& Parameter<TYPE>::operator = (unsigned long long value) { *storage = value;	return *this; }
template <class TYPE> ParameterBase& Parameter<TYPE>::operator = (double value) { *storage = (TYPE) value; return *this; }

//=============================================================================
//=                           ParameterArray<TYPE>                            =
//=============================================================================

template <class TYPE>
ParameterArray<TYPE>::ParameterArray(const char *_name, TYPE *_params, unsigned int dim) :
	ParameterBase(_name),
	params()
{
	unsigned int i;
	for(i = 0; i < dim; i++)
	{
		stringstream sstr;

		sstr << _name << "[" << i << "]";
		params.push_back(new Parameter<TYPE>(sstr.str().c_str(),*(_params + i)));
	}
}


template <class TYPE>
ParameterArray<TYPE>::~ParameterArray()
{
	typename vector<ParameterBase *>::iterator param_iter;

	for(param_iter = params.begin(); param_iter != params.end(); param_iter++)
	{
		delete *param_iter;
	}
}

template <class TYPE>
ParameterBase& ParameterArray<TYPE>::operator [] (unsigned int index)
{
	if(index >= params.size())
	{
		cerr << "Subscript out of range" << endl;
		return void_param;
	}
	return *params[index];
}

//=============================================================================
//=                         specialized Parameter<>                           =
//=============================================================================

template <> ParameterBase& Parameter<bool>::operator = (const char *value) { *storage = strcmp(value, "true") == 0; return *this; }
template <> ParameterBase& Parameter<char>::operator = (const char *value) { *storage = strtoll(value, 0, 0); return *this; }
template <> ParameterBase& Parameter<short>::operator = (const char *value) { *storage = strtoll(value, 0, 0); return *this; }
template <> ParameterBase& Parameter<int>::operator = (const char *value) {	*storage = strtoll(value, 0, 0); return *this; }
template <> ParameterBase& Parameter<long>::operator = (const char *value) { *storage = strtoll(value, 0, 0); return *this; }
template <> ParameterBase& Parameter<long long>::operator = (const char *value) { *storage = strtoll(value, 0, 0); return *this; }
template <> ParameterBase& Parameter<unsigned char>::operator = (const char *value) { *storage = strtoull(value, 0, 0); return *this; }
template <> ParameterBase& Parameter<unsigned short>::operator = (const char *value) { *storage = strtoull(value, 0, 0); return *this; }
template <> ParameterBase& Parameter<unsigned int>::operator = (const char *value) { *storage = strtoull(value, 0, 0); return *this; }
template <> ParameterBase& Parameter<unsigned long>::operator = (const char *value) { *storage = strtoull(value, 0, 0); return *this; }
template <> ParameterBase& Parameter<unsigned long long>::operator = (const char *value) { *storage = strtoull(value, 0, 0); return *this; }
template <> ParameterBase& Parameter<float>::operator = (const char *value) { *storage = strtod(value, 0); return *this; }
template <> ParameterBase& Parameter<double>::operator = (const char *value) { *storage = strtod(value, 0); return *this; }

template <> Parameter<string>::Parameter(const char *_name, string& _storage) :
	ParameterBase(_name), storage(&_storage)
{
}

template <> Parameter<string>::operator bool () const { return *storage == string("true"); }
template <> Parameter<string>::operator long long () const { return strtoll(storage->c_str(), 0, 0); }
template <> Parameter<string>::operator unsigned long long () const { return strtoull(storage->c_str(), 0, 0); }
template <> Parameter<string>::operator double () const { return strtod(storage->c_str(), 0); }
template <> Parameter<string>::operator string () const { return *storage; }

template <> ParameterBase& Parameter<string>::operator = (bool value) { *storage = value ? "true" : "false"; return *this; }
template <> ParameterBase& Parameter<string>::operator = (long long value) { stringstream sstr; sstr << "0x" << hex << value; *storage = sstr.str(); return *this; }
template <> ParameterBase& Parameter<string>::operator = (unsigned long long value) { stringstream sstr; sstr << "0x" << hex << value; *storage = sstr.str(); return *this; }
template <> ParameterBase& Parameter<string>::operator = (double value) { stringstream sstr; sstr << value; *storage = sstr.str(); return *this; }
template <> ParameterBase& Parameter<string>::operator = (const char *value) { *storage = value; return *this; }

//=============================================================================
//=                       template instanciations                             =
//=============================================================================

template class Parameter<bool>;
template class Parameter<char>;
template class Parameter<short>;
template class Parameter<int>;
template class Parameter<long>;
template class Parameter<long long>;
template class Parameter<unsigned char>;
template class Parameter<unsigned short>;
template class Parameter<unsigned int>;
template class Parameter<unsigned long>;
template class Parameter<unsigned long long>;
template class Parameter<float>;
template class Parameter<double>;
template class Parameter<string>;

template class ParameterArray<bool>;
template class ParameterArray<char>;
template class ParameterArray<short>;
template class ParameterArray<int>;
template class ParameterArray<long>;
template class ParameterArray<long long>;
template class ParameterArray<unsigned char>;
template class ParameterArray<unsigned short>;
template class ParameterArray<unsigned int>;
template class ParameterArray<unsigned long>;
template class ParameterArray<unsigned long long>;
template class ParameterArray<float>;
template class ParameterArray<double>;
template class ParameterArray<string>;
#endif
}//end of namespace simsoc


