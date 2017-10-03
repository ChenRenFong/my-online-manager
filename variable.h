#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "term.h"

using std::string;

class Var : public Term {
public:
  Var (string s):Term(s) { setType("Variable"); setAssignable(); }
  
  bool match( Term &term ){
	bool ret = assignable();
    if(assignable()){
      setValue(term.symbol());
      setNotAssignable();
    }
	else {
      if (_value == term.value()) {return true;}
      else {return false;}
	}
    return ret;
  }
};

#endif
