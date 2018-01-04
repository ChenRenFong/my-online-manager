#ifndef STRUCT_H
#define STRUCT_H

#include <iostream>
#include <vector>
#include <string>
#include "term.h"
#include "atom.h"

using std::string;
using std::vector;

class Struct: public Term {
public:
  Struct(Atom const & name, vector<Term *> args):_name(name), _args(args) {}
  Struct(Atom const & name):_name(name) {}
//=====args.===================================
  Term * args(int i) { return _args[i]; }
//=====myself basic.===================================
  Term const & name() { return _name; }
//=====basic.===================================
  string type() const{ return _type; }
  string symbol() const{
	// get all contain term's symbol 
    string ret = _name.symbol() + "(";
    for(int i=0; ( i<(_args.size()-1) ) && ( _args.size()!=0 ) ; i++) { ret += _args[i]->symbol() + ", "; }
	
	if(_args.size()!=0) { ret += _args[_args.size()-1]->symbol() + ")"; }
	else { ret += ")"; }
	
	return ret;
  }
  string value() { 
    // get all contain term's value 
    string ret = _name.symbol() + "(";
    for(int i=0; ( i<(_args.size()-1) ) && ( _args.size()!=0 ) ; i++) { ret += _args[i]->value() + ", "; }
	
	if(_args.size()!=0) { ret += _args[_args.size()-1]->value() + ")"; }
	else { ret += ")"; } 
	
	return ret;
  }  
//=====match.===================================  
  bool match(Term & term) {
    Struct * ps = dynamic_cast<Struct *>(&term);
    if (ps){
	  // compare each name
      if (!_name.match(ps->_name)) {return false;}
	  // compare each size
      if(_args.size() != ps->_args.size()) {return false;}
	  // compare each all contain term
      for(int i=0;i<_args.size();i++){ if(_args[i]->symbol() != ps->_args[i]->symbol()) {return false;} }
      return true;
    }
    return false;
  }
//=====size.===================================
  int arity() { return _args.size(); }
//=====createIterator.===================================
  Iterator<Term*> * createIterator();
  Iterator<Term*> * createBFSIterator();
  Iterator<Term*> * createDFSIterator();
//=====parameter.===================================
  string _type = "Struct";
  Atom _name;
  vector<Term *> _args;
};

#endif
