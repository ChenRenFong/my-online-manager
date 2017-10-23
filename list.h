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
    
  }
  
  List * tail() const{
	
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
	else {
	  return symbol() == term.symbol();
	}
  };

  string _type = "List";
  vector<Term *> _elements;
};

#endif
