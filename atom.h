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

  string _type="Atom";
  string _symbol;
};


#endif
