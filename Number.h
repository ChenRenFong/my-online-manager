#ifndef NUMBER_H
#define NUMBER_H

#include <string>
#include "term.h"

using std::string;

class Number : public Term {
public:
  Number (string s):Term(s) { setType("Number"); setValue(s); setNotAssignable(); }
  Number (int sNumber):Term(sNumber) { setType("Number"); setNotAssignable(); }
  
  bool match( Term &term ){
	if ( term.type() == _type || term.type() == "Atom" ) {
	  if (_symbol == term.symbol()) {return true;}
      else {return false;}
	}
	else {
	  bool ret = term.assignable();
      if (term.assignable() == true) {
        term.setValue(_symbol);
        term.setNotAssignable();
      }
	  else {
        if (_value == term.value()) {return true;}
        else {return false;}
	  }
      return ret;
	}
  }
};

#endif
