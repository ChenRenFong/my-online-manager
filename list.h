#ifndef LIST_H
#define LIST_H

#include "term.h"

#include <vector>
using std::vector;

class List : public Term {
public:
  List (): _elements() {}
  List (vector<Term *> const & elements):_elements(elements){}
//=====myself basic.===================================
  Term * head() const{ 
    if(_elements.size()==0) { throw string("Accessing head in an empty list"); }
	return _elements[0]; 
  }
  List * tail() const{
	if(_elements.size()==0) { throw string("Accessing tail in an empty list"); }
	List * listPtr = new List();
	// get all contain term except first term
	for(int i=1; i < _elements.size(); i++) { listPtr->_elements.push_back(_elements[i]); }
	return listPtr;
  }
//=====basic.===================================
  string type() const{ return _type; }
  string symbol() const{ 
    if(_elements.size()==0) { return "[]"; } 
	else { 
	  // get all contain term's symbol 
	  string ret = "[";
      for(int i=0; i < (_elements.size()-1); i++){ ret += _elements[i]->symbol() + ", "; }
	  ret += _elements[_elements.size()-1]->symbol() + "]";  
	  return ret;
	}
  }
  string value() const{ 
    if(_elements.size()==0) { return "[]"; } 
	else { 
	  // get all contain term's value 
	  string ret = "[";
      for(int i=0; i < (_elements.size()-1); i++) { ret += _elements[i]->value() + ", "; }
	  ret += _elements[_elements.size()-1]->value() + "]";
	  return ret;
	}
  }
//=====match.===================================
  bool match(Term & term) {
	// different type different method
	if(term.type()=="List") {
	  List * tempPtr = dynamic_cast<List *>(&term);
	  // compare each size
	  if(_elements.size() != tempPtr->_elements.size()) { return false; }
	  // match each all contain term if each one term match false then return false
	  for(int i=0; i<_elements.size(); i++) { if(_elements[i]->match(*tempPtr->_elements[i])==false) { return false; } }
	  return true;
	}
	else if(term.type()=="Variable") { return term.matchWithVariable(*this); }
	else { return symbol() == term.symbol(); }
  }
//=====parameter.===================================
  string _type = "List";
  vector<Term *> _elements;
  string _value;
};

#endif
