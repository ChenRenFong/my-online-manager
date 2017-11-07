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
  Number(double value) { stringstream ss; ss<<value; ss>>_symbol; _value=_symbol; }
//=====basic.===================================
  string type() const{ return _type; }
  string symbol() const{ return _symbol; };
  string value() const{ return _value; };
//=====match.===================================
  bool match( Term &term ){
	if ( term.type() == "Variable" ) { return term.matchWithVariable(*this); }
	else {
	  if (_symbol == term.symbol()) {return true;}
      else {return false;}
	}
  }
//=====parameter.===================================
  string _type = "Number";
  string _symbol;
  string _value;
};

#endif
