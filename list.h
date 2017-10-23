#ifndef LIST_H
#define LIST_H

#include "term.h"

#include <vector>
using std::vector;

class List : public Term {
public:
  List (): _elements() {}
  
  List (vector<Term *> const & elements):_elements(elements){}
  
  Term * head() const{ 
    if(_elements.size()==0) { throw "Accessing head in an empty list"; }
	return _elements[0]; 
  }
  
  List * tail() const{
	if(_elements.size()==0) { throw "Accessing tail in an empty list"; }
	  
	List * listPtr = new List();
	
	for(int i=1; i < _elements.size(); i++){		
	  listPtr->_elements.push_back(_elements[i]);  
    }
	
	return listPtr;
  }

  string type() const{ return _type; }

  string symbol() const{ 
    if(_elements.size()==0) { return "[]"; } 
	else { 
	  string ret = "[";
	
      for(int i=0; i < (_elements.size()-1); i++){		
	    ret += _elements[i]->symbol() + ", ";  
      }
	  ret += _elements[_elements.size()-1]->symbol() + "]";  

	  return ret;
	}
  }
  
  string value() const{ 
    if(_elements.size()==0) { return "[]"; } 
	else { 
	  string ret = "[";
	
      for(int i=0; i < (_elements.size()-1); i++){		
	    ret += _elements[i]->value() + ", ";  
      }
	  ret += _elements[_elements.size()-1]->value() + "]";  

	  return ret;
	}
  }
  
  bool match(Term & term) {
	if(term.type()=="List") {
	  List * tempPtr = dynamic_cast<List *>(&term);
	  
	  if(_elements.size() != tempPtr->_elements.size()) { return false; }
	  for(int i=0; i<_elements.size(); i++) {
		if(_elements[i]->match(*tempPtr->_elements[i])==false) { return false; }
	  }
	  return true;
	}
	else if(term.type()=="Variable") {
	  bool ret = term.assignable();
      if (term.assignable() == true) {
		string str = value();
        term.setValue(str);
        term.setNotAssignable();
      }
	  else {
        if (value() == term.value()) {return true;}
        else {return false;}
	  }
      return ret;
	}
	else {
	  return symbol() == term.symbol();
	}
  };

  string _type = "List";
  vector<Term *> _elements;
};

#endif
