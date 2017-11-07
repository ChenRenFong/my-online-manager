#ifndef ATOM_H
#define ATOM_H

#include <string>
#include "term.h"

using std::string;

class Atom : public Term{
public:
  Atom(string s):_symbol(s) {}
//=====basic.===================================
  string type() const{ return _type; }
  string symbol() const{ return _symbol; }
  string value() const{ return symbol(); }
//=====match.===================================
  bool match( Term &term ){
	if ( term.type() == "Variable" ) { return term.matchWithVariable(*this); }
	else {
	  if (_symbol == term.symbol()) {return true;}
      else {return false;}
	}
  }
//=====parameter.===================================
  string _type = "Atom";
  string _symbol;
};


#endif
