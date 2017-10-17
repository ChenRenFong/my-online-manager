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
  virtual string value() { return symbol(); };
  virtual bool match(Term & term) { return symbol() == term.symbol(); }
};

#endif
