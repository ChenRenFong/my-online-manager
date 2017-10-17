#ifndef TERM_H
#define TERM_H

#include <vector>
#include <string>

using std::string;
using std::vector;

class Term {
public:
  virtual string type() const= 0;
  virtual string symbol() const= 0;
  virtual string value() { return symbol(); }
  virtual bool assignable() { return false; }
  virtual void setNotAssignable() {}
  virtual void setValue(string &s) {}
  virtual bool match(Term & term) { return symbol() == term.symbol(); }
  
};

#endif
