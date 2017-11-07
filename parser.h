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
	// get now token
    int token = _scanner.nextToken();
	// do different way with different case
    if(token == VAR){
	  // create variable term
      return new Variable(symtable[_scanner.tokenValue()].first);
    }else if(token == NUMBER){
      // create number term
      return new Number(_scanner.tokenValue());
    }else if(token == ATOM || token == ATOMSC){
	  // create atom term, it can be normal atom term, or can be struct's name
      Atom* atom = new Atom(symtable[_scanner.tokenValue()].first);
      // check next that is struct or not
	  if(_scanner.currentChar() == '(' ) {
		// yes then get the token '('
        _scanner.nextToken();
		// check next that is struct empty or not
		if(_scanner.currentChar() == ')' ) {
		  // yes then get the token ')' and creat empty struct term
		  _scanner.nextToken();
		  return new Struct(*atom);
		}
		else {
		  // get struct's all args
          vector<Term*> terms = getArgs();
          // check now that is struct over or not
		  if(_currentToken == ')')
			// creat struct term with args
            return new Struct(*atom, terms);
		}
      }
      else {
		// return normal atom term
		return atom;
	  }
    }else if(token == '['){
	  // check next that is list empty or not
	  if(_scanner.currentChar() == ']' ) {
		// yes then get the token ']' and creat empty list term
		_scanner.nextToken() ;
		return new List;
	  }
	  else {
		// get list's all elements and creat list term with args
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
	// get term successfully then mark this is args
    if(term) {args.push_back(term);}
	// not get the term then redo get token until input over
    while((_currentToken = _scanner.nextToken()) == ',') {
      // encounter ',' then mean get the term so mark this is args
	  args.push_back(createTerm());
    }
	
	// exception case
	if(_currentToken!=' ') {}
	else if(_currentToken!=')') { throw string("unexpected token"); }
	
    return args;
  }
//=====get elements.===================================
  vector<Term*> getElements()
  {
    Term* term = createTerm();
    vector<Term*> elements;
	// get term successfully then mark this is elements
    if(term) {elements.push_back(term);}
	// not get the term then redo get token until input over
    while((_currentToken = _scanner.nextToken()) == ',') {
	  // encounter ',' then mean get the term so mark this is elements
	  elements.push_back(createTerm());
    }
	
	// exception case
	if(_currentToken!=' ') {}
	else if(_currentToken!=']') { throw string("unexpected token"); }
	
	return elements;
  }
//=====parameter.===================================
  Scanner _scanner;
  int _currentToken;
};
#endif
