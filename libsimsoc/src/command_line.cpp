//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "libsimsoc/command_line.hpp"
#include "libsimsoc/context.hpp"

#include <string>
#include <sstream>

using namespace std;

namespace simsoc {

  ParameterAbstract::ParameterAbstract(const char *k, const char *nm, const char *msg):
    kind(k), name(nm), message(msg)
  {
    main_context().register_parameter(this);
  }

  bool ParameterAbstract::operator<(const ParameterAbstract &pa) const {
    return strcmp(kind,pa.kind)<0;
  }

/////////////////////////////////////////////////////////////////////////////

  ParameterStrQueue::ParameterStrQueue(const char *k, const char *nm, const char *msg):
    ParameterAbstract(k,nm,msg), values()
  {}

  void ParameterStrQueue::set(const char *arg) {
    values.push_back(arg);
  }

  ostream &ParameterStrQueue::display(ostream &os) const {
    if (values.empty())
      return os <<"none";
    os <<values.front();
    deque<const char *>::const_iterator i = values.begin();
    const deque<const char *>::const_iterator ei = values.end();
    for(++i;i!=ei;++i)
      os <<", " <<*i;
    return os;
  }

  void ParameterStrQueue::print_usage(ostream &os) const {
    os <<"=<string> (repeat the option for next " <<kind <<")\n";
  }

  const char *ParameterStrQueue::front() const {
    return values.empty()? "": values.front();
  }

  void ParameterStrQueue::pop_front() {
    if (!values.empty())
      values.pop_front();
  }

/////////////////////////////////////////////////////////////////////////////

  ParameterUintQueue::ParameterUintQueue(const char *k, const char *nm,
                                         const char *msg, uint64_t df):
    ParameterAbstract(k,nm,msg), values(), default_(df)
  {}

  void ParameterUintQueue::set(const char *arg) {
    values.push_back(strtoull(arg,NULL,0));
  }

  ostream &ParameterUintQueue::display(ostream &os) const {
    if (values.empty())
      return os <<"none";
    os <<values.front();
    deque<uint64_t>::const_iterator i = values.begin();
    const deque<uint64_t>::const_iterator ei = values.end();
    for(++i;i!=ei;++i)
      os <<", " <<*i;
    return os;
  }

  void ParameterUintQueue::print_usage(ostream &os) const {
    os <<"=<number> (repeat the option for next " <<kind <<")\n";
  }

  uint64_t ParameterUintQueue::front() const {
    return values.empty()? default_: values.front();
  }

  void ParameterUintQueue::pop_front() {
    if (!values.empty())
      values.pop_front();
  }

/////////////////////////////////////////////////////////////////////////////

  ParameterInt::ParameterInt(const char *k, const char *nm, const char *msg, int d):
    ParameterAbstract(k,nm,msg), value(d)
  {}

  void ParameterInt::set(const char *arg) {
    value = strtol(arg,NULL,0);
  }

  std::ostream &ParameterInt::display(std::ostream &os) const {
    return os <<dec <<value;
  }

  void ParameterInt::print_usage(ostream &os) const {
    os <<"=<number>\n";
  }

/////////////////////////////////////////////////////////////////////////////

  ParameterBool::ParameterBool(const char *k, const char *nm, const char *msg):
    ParameterAbstract(k,nm,msg), value(false)
  {}

  void ParameterBool::set(const char *arg) {
    value = true;
  }

  std::ostream &ParameterBool::display(std::ostream &os) const {
    return os <<(value? "set": "not set");
  }

  void ParameterBool::print_usage(ostream &os) const {}

/////////////////////////////////////////////////////////////////////////////

  ParameterEnum::ParameterEnum(const char *k, const char *nm, const char *msg,
                               const char **c, size_t cc, size_t d):
    ParameterAbstract(k,nm,msg),
    choices(c), choice_count(cc), value(d)
  {
    assert(d<cc);
  }

  void ParameterEnum::set(const char *arg) {
    size_t i;
    for (i=0; i!=choice_count; ++i)
      if (!strcmp(arg,choices[i])) {
        value = i;
        break;
      }
    if (i==choice_count) {
      error() <<'"' <<arg <<"\" should be one of: " <<choices[0];
      for (size_t i=1; i!=choice_count; ++i)
        error() <<", " <<choices[i];
      error() <<".\n";
      exit(1);
    }
  }

  std::ostream &ParameterEnum::display(std::ostream &os) const {
    return os <<choices[value];
  }

  void ParameterEnum::print_usage(ostream &os) const {
    os <<"=<" <<choices[0];
    for (size_t i=1; i<choice_count; ++i)
      os <<'|' <<choices[i];
    os <<">\n";
  }

/////////////////////////////////////////////////////////////////////////////

  ParameterEnumQueue::ParameterEnumQueue(const char *k, const char *nm, const char *msg,
                                         const char **c, size_t cc, size_t d):
    ParameterAbstract(k,nm,msg),
    choices(c), choice_count(cc), values(), default_(d)
  {
    assert(d<cc);
  }

  void ParameterEnumQueue::set(const char *arg) {
    for (size_t i=0; i!=choice_count; ++i)
      if (!strcmp(arg,choices[i])) {
        values.push_back(i);
        return;
      }
    if (!strcmp(arg,"default")) {
      values.push_back(default_);
      return;
    }
    ostream &os = error();
    os <<'"' <<arg <<"\" should be one of: default";
    for (size_t i=0; i!=choice_count; ++i)
      os <<", " <<choices[i];
    os <<".\n";
    exit(1);
  }

  std::ostream &ParameterEnumQueue::display(std::ostream &os) const {
    if (values.empty())
      return os <<"none";
    os <<choices[values.front()];
    deque<size_t>::const_iterator i = values.begin();
    const deque<size_t>::const_iterator ei = values.end();
    for(++i;i!=ei;++i)
      os <<", " <<choices[*i];
    return os;
  }

  void ParameterEnumQueue::print_usage(ostream &os) const {
    os <<"=<default";
    for (size_t i=0; i<choice_count; ++i)
      os <<'|' <<choices[i];
    os <<">\n" <<"\t(repeat this parameter for next " <<kind <<")\n";
  }

  size_t ParameterEnumQueue::front() const {
    return values.empty()? default_: values.front();
  }

  void ParameterEnumQueue::pop_front() {
    if (!values.empty())
      values.pop_front();
  }

/////////////////////////////////////////////////////////////////////////////
  bool eX_line::parse(const std::string &input, struct eX_line &output) {
    output.name = "";
    output.arguments.clear();

    stringstream ss(input);
    string item;

    while (std::getline(ss, item, ' ')) {
      if (!item.length())
        continue ;

      if (!output.name.length())
        output.name = item;
      else {
        string::size_type eqpos = item.find('=');
        string value;

        if (eqpos != string::npos) {
          value = item.substr(eqpos+1);
          item  = item.substr(0, eqpos);
        }

        if (item.length() == 0)
          return false;
        if (output.arguments.find(item) != output.arguments.end())
          return false;
        output.arguments[item] = value;
      }
    }

    return true;
  }

} // namespace simsoc
