//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include <assert.h>
#include "libsimsoc/display.hpp"
#include "isc.hpp"

using namespace std;
using namespace simsoc;

static bool is_letter(char c) {
  return ('a'<=c && c<='z') || ('A'<=c && c<='Z');
}

const char ICoding::unused[] = "__attribute__ ((unused)) ";

ICoding::ICoding(const string b, const string c, unsigned ln):
  line_number(ln), bits(b), c_code(c), pattern(b.size(), UNDEF)
{
  unsigned last = b.size()-1;
  for (unsigned i = 0; i<b.size(); ++i) {
    if (bits[last-i]=='0')
      pattern[i] = ZERO;
    else if (bits[last-i]=='1')
      pattern[i] = ONE;
  }
}

ICoding::ICoding(const ICoding& i, unsigned num):
  line_number(i.line_number),
  bits(i.bits), c_code(i.c_code), pattern(i.pattern.size()-1)
{
  unsigned m = 0;
  unsigned n;
  for (n = 0; n<i.pattern.size(); ++n)
    if (n!=num) {
      pattern[m] = i.pattern[n];
      ++m;
    }
  assert(m+1==n);
}

unsigned ICoding::nb_bits() const {
  return pattern.size();
}

unsigned ICoding::total_nb_bits() const {
  return bits.size();
}

ICoding::bit_value ICoding::get(unsigned n) const {
  assert(n<pattern.size());
  return pattern[n];
}

void ICoding::gencode(const char * filename, ostream &os) const {
  unsigned last = bits.size()-1;
  char c = 0;
  unsigned start = 0;
  for (unsigned i = 0; i<bits.size(); ++i) {
    if (c && c!=bits[last-i]) {
      if (is_letter(c))
        gencode_param(os, c, start, i-start);
      c = 0;
    }
    if (!c && bits[last-i]!='0' && bits[last-i]!='1') {
      c = bits[last-i];
      start = i;
    }
  }
  if (c && is_letter(c))
    gencode_param(os, c, start, bits.size()-start);
  os <<"#line " <<line_number <<" \"" <<filename <<'"' <<endl
     <<c_code <<endl;
}

ostream& ICoding::display(ostream &os) const {
  return os <<bits <<c_code <<endl;
}

bool ICoding::is_undef() const {
  for (unsigned i = 0; i<pattern.size(); ++i)
    if (pattern[i]!=UNDEF)
      return false;
  return true;
}

void ICoding::gencode_param(ostream &os,
                            char name, unsigned start, unsigned length) const {
  assert(length);
  if (length==1)
    os <<"bool " <<unused <<name <<" = bincode&(1<<" <<start <<");" <<endl;
  else if (length<=8)
    os <<"uint8_t " <<unused <<name <<" = (bincode>>" <<start <<")&" <<((1<<length)-1) <<';' <<endl;
  else if (length<=16)
    os <<"uint16_t " <<unused <<name <<" = (bincode>>" <<start <<")&" <<((1<<length)-1) <<';' <<endl;
  else if (length<=32)
    os <<"uint32_t " <<unused <<name <<" = (bincode>>" <<start <<")&" <<((1LLU<<length)-1) <<';' <<endl;
  else if (length<=64)
    os <<"uint64_t " <<unused <<name <<" = (bincode>>" <<start <<")&" <<((1LLU<<length)-1) <<';' <<endl;
  else {
    error() <<HERE <<"too long parameter (> 64 bits)";
    exit(4);
  }
}

bool ICoding::operator<(const ICoding& b) const {
  for (int i=nb_bits()-1; i>=0; --i)
    if (get(i)==UNDEF && b.get(i)!=UNDEF)
      return false;
  return true;
}

ostream& operator<<(ostream &os, const ICoding& i) {
  return i.display(os);
}

/******************************************************************************/

Isc::Isc(unsigned nb_bits, const char * filename):
  isc_file(filename), nbits(nb_bits), icodings(),
  undefs(nb_bits,0), zeros(nb_bits,0), ones(nb_bits,0),
  real_nums(nb_bits),
  seen_mask(0), seen_value(0)
{
  for (unsigned i = 0; i<nbits; ++i)
    real_nums[i] = i;
  assert(nbits<=64);
}

Isc::Isc(const Isc& parent, unsigned num, ICoding::bit_value is_not):
  isc_file(parent.isc_file),
  nbits(parent.nbits-1), icodings(),
  undefs(nbits,0), zeros(nbits,0), ones(nbits,0),
  real_nums(nbits),
  seen_mask(parent.seen_mask|(1LLU<<parent.real_nums[num])),
  seen_value(parent.seen_value|((is_not==ICoding::ZERO)?(1LLU<<parent.real_nums[num]):0))
{
  for (unsigned i = 0; i<parent.icodings.size(); ++i)
    if (parent.icodings[i].get(num)!=is_not) {
      icodings.push_back(ICoding(parent.icodings[i],num));
      update_uzo();
    }
  assert(icodings.size());
  for (unsigned i = 0; i<nbits; ++i)
    real_nums[i] = (i<num)? parent.real_nums[i]: parent.real_nums[i+1];
}

Isc::Isc(const Isc& parent):
  isc_file(parent.isc_file),
  nbits(parent.nbits), icodings(),
  undefs(nbits,0), zeros(nbits,0), ones(nbits,0),
  real_nums(parent.real_nums),
  seen_mask(parent.seen_mask),
  seen_value(parent.seen_value)
{
  for (unsigned i = 1; i<parent.icodings.size(); ++i) {
    icodings.push_back(ICoding(parent.icodings[i]));
    update_uzo();
  }
}

unsigned Isc::nb_bits() const {
  return nbits;
}

unsigned Isc::total_nb_bits() const {
  assert(icodings.size());
  return icodings[0].total_nb_bits();
}

void Isc::add(const string& bits, const string& c_code, unsigned line_number) {
  if (nb_bits()!=bits.size()) {
    error() <<"[ISC parsing] wrong pattern size on line " <<line_number <<endl;
    exit(8);
  }
  icodings.push_back(ICoding(bits,c_code,line_number));
  update_uzo();
}

void Isc::add(const ICoding& i, unsigned num) {
  icodings.push_back(ICoding(i,num));
  update_uzo();
}

void Isc::gencode(ostream &os) {
  assert(icodings.size());
  if (icodings[0].is_undef()) {
    gencode_first(os);
    return;
  }
  unsigned i = 0;
  for (unsigned b = 1; b<nbits; ++b)
    if (undefs[b]<=undefs[i])
      i = b;
  if (!zeros[i] && !undefs[i]) {
    ostream &os = error();
    os <<"[Code generation] no valid choices (bit[" <<real_nums[i] <<"]==0)" <<endl;
    print_pattern(seen_mask|(1LLU<<real_nums[i]),
                  seen_value,
                  os);
    os <<endl;
    exit(2);
  }
  if (!ones[i] && !undefs[i]) {
    ostream &os = error();
    os <<"[Code generation] no valid choices (bit[" <<real_nums[i] <<"]==1)" <<endl;
    print_pattern(seen_mask|(1LLU<<real_nums[i]),
                  seen_value|(1LLU<<real_nums[i]),
                  os);
    os <<endl;
    for (unsigned i = 0; i<icodings.size(); ++i)
      os <<icodings[i];
    os <<endl;
    exit(3);
  }
  gencode_split(os,i);
}

void Isc::gencode_split(ostream &os, unsigned i) {
  assert(zeros[i]+undefs[i]);
  assert(ones[i]+undefs[i]);
  info() <<HERE <<"bit " <<real_nums[i] <<", " <<undefs[i] <<" undefs." <<endl;
  if (real_nums[i]<32)
    os <<"if (bincode&(1<<" <<real_nums[i] <<")) {" <<endl;
  else
    os <<"if (bincode&(1LLU<<" <<real_nums[i] <<")) {" <<endl;
  Isc(*this,i,ICoding::ZERO).gencode(os);
  os <<"} else {" <<endl;
  Isc(*this,i,ICoding::ONE).gencode(os);
  os <<'}' <<endl;
}

void Isc::gencode_first(ostream &os) {
  assert(icodings.size());
  assert(icodings[0].is_undef());
  os <<"{\n";
  icodings[0].gencode(isc_file,os);
  os <<'}' <<endl;
  if (icodings.size()>1) {
    info() <<HERE <<"many valid choices:\n";
    for (unsigned i = 0; i<icodings.size(); ++i)
      info() <<icodings[i];
    info() <<endl;
    Isc(*this).gencode(os); // remove icodings[0]
  }
}

void Isc::update_uzo() {
  unsigned i = icodings.size()-1;
  assert(nb_bits()==icodings[i].nb_bits());
  for (unsigned b=0; b<nbits; ++b)
    switch (icodings[i].get(b)) {
    case ICoding::UNDEF: ++undefs[b]; break;
    case ICoding::ZERO: ++zeros[b]; break;
    case ICoding::ONE: ++ones[b]; break;
    }
}

void Isc::print_uzo(ostream &os) {
  os <<"undef:\t";
  for (int b=nbits-1; b>=0; --b)
    os <<' ' <<undefs[b];
  os <<endl;
  os <<"zero:\t";
  for (int b=nbits-1; b>=0; --b)
    os <<' ' <<zeros[b];
  os <<endl;
  os <<"one:\t";
  for (int b=nbits-1; b>=0; --b)
    os <<' ' <<ones[b];
  os <<endl;
}

void Isc::print_pattern(uint64_t mask, uint64_t value, ostream& os) {
  for (int b = total_nb_bits()-1; b>=0; --b)
    if (mask&(1LLU<<b))
      os <<((value&(1LLU<<b))?'1':'0');
    else
      os <<'-';
}
