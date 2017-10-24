#ifndef NUMBER_H
#define NUMBER_H

#include <iostream>
#include <string>
#include <sstream>
#include "term.h"

using std::string;
using std::stringstream;

class Number : public Term {
public:
  Number(double value) {stringstream ss; ss<<value; ss>>_symbol; _value=_symbol;}
  
  string type() const{ return _type; }
  string symbol() const{ return _symbol; };
  string value() const{ return _value; };
  
  bool match( Term &term ){
	if ( term.type() == _type || term.type() == "Atom" || term.type() == "Struct" || term.type() == "List" ) {
	  if (_symbol == term.symbol()) {return true;}
      else {return false;}
	}
	else {
		
	  return term.matchWithVariable(*this);
	  
	  /*
	  bool ret = term.assignable();
      if (term.assignable() == true) {
        term.setValue(_symbol);
        term.setNotAssignable();
		term.setConnecter();
      }
	  else {
        if (_symbol == term.value()) {return true;}
        else {return false;}
	  }
      return ret;
	  */
	}
  }
  
  string _type = "Number";
  string _symbol;
  string _value;
};

#endif
