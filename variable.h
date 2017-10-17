#ifndef VARIABLE_H
#define VARIABLE_H

#include <iostream>
#include <vector>
#include <string>
#include "term.h"
#include "atom.h"
#include "number.h"
#include "struct.h"
#include "variable.h"

using std::string;
using std::vector;

class Variable : public Term{
public:
  Variable(string s):_symbol(s) {}
  
  string type() const{ return _type; }
  string symbol() const{ return _symbol; }
  string value() {
    if(_value!=NULL) {
	  
	  if(_struct!=NULL) {
		// recheck value
	    string * str = new string();
	    *str = _struct->value();
	    _value = str;
	  }
	  
	  return *_value;
	}
    else {return _symbol;}	
  }
  
  bool match( Term & term ){
	bool ret = _assignable;
	
	if(term.type()=="Atom") {
	  Atom * tempPtr = dynamic_cast<Atom *>(&term);
	  
	  if(_assignable) {
		// point to target
	    _value = &tempPtr->_symbol;
	    _assignable = false;
		
		// my connector point to my point's target 
		for(int i=0; i<_connect.size(); i++) {
		  _connect[i]->_value = _value;
	    }
	  }
	  else {
        if (_value == &tempPtr->_symbol) {return true;}
        else {return false;}
	  }
	}
	else if(term.type()=="Number") {
	  Number * tempPtr = dynamic_cast<Number *>(&term);
	  
	  if(_assignable) {
		// point to target
	    _value = &tempPtr->_symbol;
	    _assignable = false;
		
		// my connector point to my point's target 
		for(int i=0; i<_connect.size(); i++) {
		  _connect[i]->_value = _value;
	    }
	  }
	  else {
        if (_value == &tempPtr->_symbol) {return true;}
        else {return false;}
	  }
	}
	else if(term.type()=="Variable") {
	  Variable * tempPtr = dynamic_cast<Variable *>(&term);
	  vector<Variable *> myConnect = _connect;
	  vector<Variable *> youConnect = tempPtr->_connect;
	  
	  // get your connector
	  for(int i=0; i<youConnect.size(); i++) {
		_connect.push_back(youConnect[i]);
	  }
	  // give you my connector
	  for(int i=0; i<myConnect.size(); i++) {
		tempPtr->_connect.push_back(myConnect[i]);
	  }
	  
	  // set each other is connector
	  _connect.push_back(tempPtr);
	  tempPtr->_connect.push_back(this);
	  
	  // set same target
	  _value = tempPtr->_value;
	  
	  // set my connector point to same target
	  for(int i=0; i<_connect.size(); i++) {
		_connect[i]->_value = tempPtr->_value;
	  }
	}
	else if(term.type()=="Struct") {
	  Struct * tempPtr = dynamic_cast<Struct *>(&term);
	  _struct = tempPtr;
	  
	  if(_assignable) {
		// point to target
		string * str = new string();
		*str = tempPtr->symbol();
		_value = str;
		// Atom * temp = &tempPtr->_name;
	    // _value = &temp->_symbol;
	    _assignable = false;
		
		// my connector point to my point's target 
		for(int i=0; i<_connect.size(); i++) {
		  _connect[i]->_value = _value;
	    }
	  }
	  else {
        // if (_value == &tempPtr->_symbol) {return true;}
        // else {return false;}
	  }
	}

	return ret;
  }
	
  string _type = "Variable";
  string _symbol;
  string * _value = NULL;
  bool _assignable = true;
  vector<Variable *> _connect;
  Struct * _struct = NULL;
};

#endif
