//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "libsimsoc/display.hpp"
#include "isc_parse.hpp"

using namespace std;
using namespace simsoc;

Isc * isc_parse(istream& is, ostream& os, const char * filename) {
  string line;
  unsigned line_number = 0;
  unsigned tmp_line_number;
  do {
    ++line_number;
    getline(is,line);
    if (!!is && !(line.size()>=2 && line[0]=='%' && line[1]=='%'))
      os <<line <<endl;
  } while (!!is && !(line.size()>=2 && line[0]=='%' && line[1]=='%'));
  if (!is) {
    error() <<"[ISC parsing] %% not found" <<endl;
    exit(8);
  }
  if (line.size()>2)
    warning() <<"[ISC parsing] " <<dec <<line.size()-2 <<" ignored characters after first %%" <<endl;
  string word;
  while (!!is && is.peek()=='\n') {
    ++line_number;
    getline(is,line);
  }
  tmp_line_number = ++line_number;
  is >>word;
  getline(is,line);
  Isc * I = new Isc(word.size(),filename);
  while (!!is && !(word.size()>=2 && word[0]=='%' && word[1]=='%')) {
    while (!!is && (is.peek()==' '||is.peek()=='\t')) {
      string contline;
      ++line_number;
      getline(is,contline);
      line = line + "\n" + contline;
    }
    I->add(word,line,tmp_line_number);
    while (!!is && is.peek()=='\n') {
      ++line_number;
      getline(is,line);
    }
    tmp_line_number = ++line_number;
    is >>word;
    getline(is,line);
  }
  if (!is)
    warning() <<"[ISC parsing] ending %% not found" <<endl;
  else if (word.size()>2)
    warning() <<"[ISC parsing] " <<word.size()-2 <<" ignored characters after ending %%" <<endl;
  os <<endl;
  return I;
}

void isc_epilogue(istream& is, ostream& os) {
  string line;
  while (!!is) {
    getline(is,line);
    os <<line <<endl;
  }
}
