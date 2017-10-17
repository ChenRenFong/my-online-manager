#ifndef ATOM_H
#define ATOM_H

#include <string>
#include "term.h"

using std::string;

class Atom : public Term{
public:
  Atom(string s):_symbol(s) {}

  string type() const{ return _type; }
  string symbol() const{ return _symbol; }
  string value() const{ return symbol(); }
  
  bool match( Term &term ){
	if ( term.type() == _type || term.type() == "Number" ) {
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

  string _type = "Atom";
  string _symbol;
};


#endif
