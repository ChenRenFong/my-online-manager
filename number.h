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
  string symbol() { return _value; };
  
  string _type="Number";
  string _symbol;
  string _value;
};

#endif
