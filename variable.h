#ifndef VARIABLE_H
#define VARIABLE_H

#include <iostream>
#include <vector>
#include <string>
#include "term.h"
#include "atom.h"
#include "number.h"
#include "struct.h"
#include "list.h"

using std::string;
using std::vector;

class Variable : public Term{
public:
  Variable(string s):_symbol(s) {}
//=====basic.===================================
  string type() const{ return _type; }
  string symbol() const{ return _symbol; }
  string value() {
    if(_value!=&_symbol) {
	  if(_struct!=NULL) {
		// let value newest
	    string * str = new string();
	    *str = _struct->value();
	    _value = str;
	  }
	  else if(_list!=NULL) {
		  // let value newest
	    string * str = new string();
	    *str = _list->value();
	    _value = str;
	  }
	  return *_value;
	}
    else {return _symbol;}	
  }
//=====match.===================================
  bool match( Term & term ){
	bool ret = _assignable;
    // different type different method
	if(term.type()=="Atom") {
	  Atom * tempPtr = dynamic_cast<Atom *>(&term);
	  if(_assignable) {
		// point to target
	    _value = &tempPtr->_symbol;
	    _assignable = false;
		// my connector point to my point's target 
		for(int i=0; i<_connect.size(); i++) { _connect[i]->_value = _value; }
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
		for(int i=0; i<_connect.size(); i++) { _connect[i]->_value = _value; }
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
	  for(int i=0; i<youConnect.size(); i++) { _connect.push_back(youConnect[i]); }
	  // give you my connector
	  for(int i=0; i<myConnect.size(); i++) { tempPtr->_connect.push_back(myConnect[i]); }
	  // set each other is connector
	  _connect.push_back(tempPtr);
	  tempPtr->_connect.push_back(this);
	  // set same target
	  tempPtr->_value = _value;
	  // set my connector point to same target
	  for(int i=0; i<_connect.size(); i++) { _connect[i]->_value = tempPtr->_value; }
	  
	  return true;
	}
	else if(term.type()=="Struct") {
	  Struct * tempPtr = dynamic_cast<Struct *>(&term);
	  // set connect with struct
	  _struct = tempPtr;
	  if(_assignable) {
		// point to target
		string * str = new string();
		*str = tempPtr->symbol();
		_value = str;
	    _assignable = false;
		// my connector point to my point's target 
		for(int i=0; i<_connect.size(); i++) { _connect[i]->_value = _value; }
	  }
	  else {
        if (*_value == tempPtr->symbol()) {return true;}
        else {return false;}
	  }
	}
	else if(term.type()=="List") {
	  List * tempPtr = dynamic_cast<List *>(&term);
	  // set connect with list
	  _list = tempPtr;
	  // check is list contain myself
	  for(int i=0 ; i<tempPtr->_elements.size() ;i++) {
		if(_symbol == tempPtr->_elements[i]->symbol()) {
		  // disable connect with list
		  _list = NULL;
		  return false;
		}
	  }
	  if(_assignable) {
		// point to target
		string * str = new string();
		*str = tempPtr->symbol();
		_value = str;
	    _assignable = false;
		// my connector point to my point's target 
		for(int i=0; i<_connect.size(); i++) { _connect[i]->_value = _value; }
	  }
	  else {
        if (*_value == tempPtr->symbol()) {return true;}
        else {return false;}
	  }
	}
	return ret;
  }
  bool matchWithVariable(Term & term) { return match(term); }
//=====parameter.===================================
  string _type = "Variable";
  string _symbol;
  string * _value = &_symbol;
  bool _assignable = true;
  vector<Variable *> _connect;
  Struct * _struct = NULL;
  List * _list = NULL;
};

#endif
