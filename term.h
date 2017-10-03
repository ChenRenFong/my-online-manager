#ifndef TERM_H
#define TERM_H

#include <iostream>
#include <string>
#include <sstream>

using std::string;
using std::stringstream;

class Term {
public:
  int _number;
  stringstream ss;

  Term (string s):_symbol(s) {}
  Term (string sa, string sb):_symbol(sa), _value(sb) {}
  Term (int sNumber):_number(sNumber) { ss<<_number; ss>>_symbol; _value=_symbol; }

  string _type;
  string _symbol;
  string _value;
  bool _assignable;
  
  string type() { return _type; } 
  string symbol() { return _symbol; }
  string value() { return _value; }
  bool assignable() { return _assignable; }
  
  void setType(string s) { _type = s; }
  void setValue(string s) { _value = s; }
  void setValue(int sNumber) { ss<<sNumber; ss>>_value; }
  void setAssignable() { _assignable = true; }
  void setNotAssignable() { _assignable = false; }
};

#endif
