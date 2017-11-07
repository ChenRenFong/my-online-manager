#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <iostream>
using std::string;

#include "atom.h"
#include "number.h"
#include "variable.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"
#include "list.h"

class Parser{
public:
  Parser(Scanner scanner) : _scanner(scanner){}
//=====create term.===================================
  Term* createTerm(){
    int token = _scanner.nextToken();
    if(token == VAR){
      return new Variable(symtable[_scanner.tokenValue()].first);
    }else if(token == NUMBER){
      return new Number(_scanner.tokenValue());
    }else if(token == ATOM || token == ATOMSC){
      Atom* atom = new Atom(symtable[_scanner.tokenValue()].first);
      if(_scanner.currentChar() == '(' ) {
        _scanner.nextToken() ;
		if(_scanner.currentChar() == ')' ) {
		  _scanner.nextToken();
		  return new Struct(*atom);
		}
		else {
          vector<Term*> terms = getArgs();
          if(_currentToken == ')')
            return new Struct(*atom, terms);
		}
      }
      else {return atom;}
    }else if(token == '['){
	  if(_scanner.currentChar() == ']' ) {
		_scanner.nextToken() ;
		return new List;
	  }
	  else {
		vector<Term*> terms = getElements();
		return new List(terms);
	  }
    }
    return nullptr;
  }
//=====get args.===================================
  vector<Term*> getArgs()
  {
	Term* term = createTerm();
    vector<Term*> args;
    if(term) {args.push_back(term);}
    while((_currentToken = _scanner.nextToken()) == ',') {
      args.push_back(createTerm());
    }
    return args;
  }
//=====get elements.===================================
  vector<Term*> getElements()
  {
    Term* term = createTerm();
    vector<Term*> elements;
    if(term) {elements.push_back(term);}
    while((_currentToken = _scanner.nextToken()) == ',') {
	  elements.push_back(createTerm());
    }
	
	if(_currentToken!=' ') {}
	else if(_currentToken!=']') { throw string("unexpected token"); }
	
	return elements;
  }
//=====parameter.===================================
  Scanner _scanner;
  int _currentToken;
};
#endif
