#ifndef TERM_H
#define TERM_H

#include <vector>
#include <string>

using std::string;
using std::vector;

template<class T>
class Iterator;

class Term {
public:
//=====basic.===================================
  virtual string type() const= 0;
  virtual string symbol() const { return _symbol; }
  virtual string value() { return symbol(); }
//=====match.===================================
  virtual bool match(Term & term) { return symbol() == term.symbol(); }
  virtual bool matchWithVariable(Term & term) {}
//=====size.===================================
  virtual int arity() {}
//=====createIterator.===================================
  virtual Iterator<Term*> * createIterator();
//=====args.===================================
  virtual Term * args(int i) {}
//=====parameter.===================================
  string _symbol;
};

#endif
