#ifndef TERM_H
#define TERM_H

#include <string>

using std::string;

class Term {
public:
  Term (string s):_symbol(s) {}

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
  void setAssignable() { _assignable = true; }
  void setNotAssignable() { _assignable = false; }
};

#endif
