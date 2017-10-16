#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "term.h"

using std::string;

class Variable : public Term{
public:
  Variable(string s):_symbol(s){}
  
  string type() const{ return _type; }
  string symbol() const{ return _symbol; }
  string value() { return _value; }
  
  bool match( Term & term ){
	bool ret = _assignable;
	
    if(_assignable){
      _value = term.symbol();
      _assignable = false;
    }
	else {
      if (_value == term.value()) {return true;}
      else {return false;}
	}
    
	return ret;
  }
  /*
  bool match( Term & term ){
	bool ret = _assignable;
	
    if(_assignable){
      _value = term.symbol();
      _assignable = false;
    }
	else {
      if (_value == term.value()) {return true;}
      else {return false;}
	}
    
	return ret;
  }
  */
  string _type="Variable";
  string _symbol;
  string _value;
  bool _assignable = true;
};

#endif
