#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <vector>
#include <stack>
using std::string;
using std::stack;

#include "atom.h"
#include "variable.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"
#include "list.h"
#include "node.h"
#include "exp.h"

//#include "utParser.h"

class Parser{
//=====public.===================================
public:
  Parser(Scanner scanner) : _scanner(scanner), _terms(){}
//=====create term.===================================
  Term* createTerm(){
    int token = _scanner.nextToken();
    _currentToken = token;
    if(token == VAR){
		
	  Variable * tempTerm = new Variable(symtable[_scanner.tokenValue()].first);
	  Node * node3 = new Node(TERM, tempTerm, nullptr, nullptr);
	  _tree.push_back(node3);
      return tempTerm;
	  
    }else if(token == NUMBER){

	  Number * tempTerm = new Number(_scanner.tokenValue());
	  Node * node3 = new Node(TERM, tempTerm, nullptr, nullptr);
	  _tree.push_back(node3);
      return tempTerm; 
	  
    }else if(token == ATOM || token == ATOMSC){
		
      Atom* atom = new Atom(symtable[_scanner.tokenValue()].first);	  
      if(_scanner.currentChar() == '(' ) {
		Term* tempTerm = structure();
        return tempTerm;
      }
      else { 
		Node * node3 = new Node(TERM, atom, nullptr, nullptr);
	    _tree.push_back(node3);
        return atom;
	  }
	  
    }
    else if(token == '['){
		
	  Term* tempTerm = list(); 
      return tempTerm;
	  
    }
    return nullptr;
  }
//=====case:structure.===================================
  Term * structure() {
    Atom structName = Atom(symtable[_scanner.tokenValue()].first);
    int startIndexOfStructArgs = _terms.size();
    _scanner.nextToken();
    createTerms();	
    if(_currentToken == ')')
    {
      vector<Term *> args(_terms.begin() + startIndexOfStructArgs, _terms.end());	  
	  
	  int i, start=0, end=0;
	  
	  for(i=0; i<_tree.size(); i++) {
		if(_tree[i]->term == _terms[startIndexOfStructArgs]) {
		  start = i;
		}
		if(_tree[i]->term == _terms[_terms.size()-1]) {
		  end = i;
		}
	  }
	  
      _terms.erase(_terms.begin() + startIndexOfStructArgs, _terms.end());	  
	  _tree.erase(_tree.begin()+start, _tree.end());	
	  
	  Term* tempTerm = new Struct(structName, args);
	  Node * node3 = new Node(TERM, tempTerm, nullptr, nullptr);
	  _tree.push_back(node3); 

      return tempTerm;
    }
	else {	
      throw string("unexpected token");
    }
  }
//=====case:list.===================================
  Term * list() {
    int startIndexOfListArgs = _terms.size();
    createTerms();
    if(_currentToken == ']')
    {
      vector<Term *> args(_terms.begin() + startIndexOfListArgs, _terms.end());
	  
	  int i, start=0, end=0;
	  
	  for(i=0; i<_tree.size(); i++) {
		if(_tree[i]->term == _terms[startIndexOfListArgs]) {
		  start = i;
		}
		if(_tree[i]->term == _terms[_terms.size()-1]) {
		  end = i;
		}
	  }
	  
      _terms.erase(_terms.begin() + startIndexOfListArgs, _terms.end());
	  _tree.erase(_tree.begin()+start, _tree.end());
	  
	  Term* tempTerm = new List(args);
	  Node * node3 = new Node(TERM, tempTerm, nullptr, nullptr);
	  _tree.push_back(node3); 
	  
      return tempTerm;
    }
	else {
      throw string("unexpected token");
    }
  }
//=====getTerms.===================================
  vector<Term *> & getTerms() {
    return _terms;
  }
//=====matchings.===================================  
  void matchings() {
	createTerms();	
    getTree();
	checkSameTerm(_root);
  }
//=====expressionTree.===================================
  Node * expressionTree() {
    return _root;
  }
//=====buildExpression.===================================
  void buildExpression(){
    disjunctionMatch();
    restDisjunctionMatch();
    if (createTerm() != nullptr || _currentToken != '.') {
	  throw string("Missing token '.'");
	}
  }
//=====restDisjunctionMatch.===================================  
  void restDisjunctionMatch() {	  
    if (_scanner.currentChar() == ';') {
      createTerm();
	  
	  if(_scanner.currentChar() == '.') {
		throw string("Unexpected ';' before '.'");  
	  }
	  
      disjunctionMatch();
      Exp *right = _expStack.top();
      _expStack.pop();
      Exp *left = _expStack.top();
      _expStack.pop();
      _expStack.push(new DisjExp(left, right));
      restDisjunctionMatch();
    }
  }
//=====disjunctionMatch.===================================
  void disjunctionMatch() {
    conjunctionMatch();
    restConjunctionMatch();
  }
//=====restConjunctionMatch.===================================
  void restConjunctionMatch() {  
    
  
    if (_scanner.currentChar() == ',') {
      createTerm();
	  
	  if(_scanner.currentChar() == '.') {
		throw string("Unexpected ',' before '.'");  
	  }
	  
      conjunctionMatch();
      Exp *right = _expStack.top();
      _expStack.pop();
      Exp *left = _expStack.top();
      _expStack.pop();
      _expStack.push(new ConjExp(left, right));
      restConjunctionMatch();
    }
  }
//=====conjunctionMatch.===================================
  void conjunctionMatch() {
	Term * left = createTerm();
	if (createTerm() == nullptr && _currentToken == '=') {
      Term * right = createTerm();
      _expStack.push(new MatchExp(left, right));
    }
	else if(_currentToken == ';' && _scanner.currentChar() == '.') {
	  throw string("Unexpected ';' before '.'");
	}
	else if(_currentToken == ',' && _scanner.currentChar() == '.') {
	  throw string("Unexpected ',' before '.'");
	}
	else if(_currentToken == '.') {
	  string msg = left->symbol() + " does never get assignment";
	  throw string(msg);
	}
  }
//=====getExpressionTree.===================================  
  Exp* getExpressionTree(){
    return _expStack.top();
  }
//=====getExpressionResult.=================================== 
  string getExpressionResult(){
    return _expStack.top()->getExpressionResult() + ".";
  }
//=====public.===================================
public:
  //FRIEND_TEST(ParserTest, createArgs);
  //FRIEND_TEST(ParserTest,ListOfTermsEmpty);
  //FRIEND_TEST(ParserTest,listofTermsTwoNumber);
  //FRIEND_TEST(ParserTest, createTerm_nestedStruct3);
//=====createTerms.===================================
  void createTerms() {
    Term* term = createTerm();
    if(term!=nullptr)
    {
      _terms.push_back(term);
	  
      while((_currentToken = _scanner.nextToken()) == ',' || _currentToken == '=' || _currentToken == ';') {
		int operatorNum = _currentToken;
		
		if(operatorNum==';' && _scanner.currentChar() == ')') {
		  throw string("Unbalanced operator");
		}
		else if(operatorNum==';' && _scanner.currentChar() == ']') {
		  throw string("Unbalanced operator");
		}
		
		if(operatorNum==';') {
		  Node * node2 = new Node(SEMICOLON, nullptr, nullptr, nullptr);
		  _tree.push_back(node2);
		}
		else if(operatorNum==',') {
		  Node * node2 = new Node(COMMA, nullptr, nullptr, nullptr);
		  _tree.push_back(node2);
		}
		else if(operatorNum=='=') {		
		  Node * node2 = new Node(EQUALITY, nullptr, nullptr, nullptr);
		  _tree.push_back(node2);
		}	

		Term * tempTerm = createTerm();
        _terms.push_back(tempTerm);
      }
    }
  }
//=====getTree.===================================
  void getTree() {
    int i, term = 0;
	vector<Node *> tempNode;
	vector<Node *> tempTerm;
	vector<Node *> tempOpera;
	
	for(i=0; i<_tree.size(); i++) {
	  
	  if(_tree[i]->payload==TERM) {
	    tempTerm.push_back(_tree[i]);
	    term++;
		
		if(term==2) {
		  tempOpera[tempOpera.size()-1]->left = tempTerm[0];
		  tempOpera[tempOpera.size()-1]->right = tempTerm[1];
		  tempNode.push_back(tempOpera[tempOpera.size()-1]);
		  tempOpera.pop_back();
		  tempTerm.pop_back();
		  tempTerm.pop_back();
		  term=0;
		}
	  }
	  else {
		tempOpera.push_back(_tree[i]);
	  }
	  
	}
	
	for(i=0; i<tempOpera.size(); i++) {
	  if(i!=tempOpera.size()-1) {
		tempOpera[i]->left = tempNode[i];
		tempOpera[i]->right = tempOpera[i+1];
	  }
	  else {
		tempOpera[i]->left = tempNode[i];
		tempOpera[i]->right = tempNode[i+1];
	  }
	}
	
	_root = tempOpera[0];
  }
//=====checkSameTerm.===================================  
  void checkSameTerm(Node * subRoot) {
	if(subRoot->payload==EQUALITY) {
	  checkSame(subRoot->left->term);
	  checkSame(subRoot->right->term);
	}
	else {
	  
	  if(subRoot->payload==SEMICOLON) {
		checkSame(subRoot->left->left->term);
		checkSame(subRoot->left->right->term);
		sameList.clear();
		checkSameTerm(subRoot->right);
	  }
	  else if(subRoot->payload==COMMA) {
		checkSame(subRoot->left->left->term);
		checkSame(subRoot->left->right->term);
		checkSameTerm(subRoot->right);
	  }
	  
	}
  }
//=====checkSame.===================================
  void checkSame(Term * nodeTerm) {
    if(nodeTerm->type() == "Variable") {
	  if(sameList.size()==0) {
		sameList.push_back(nodeTerm);
	  }
	  else {
		if(!setSame(nodeTerm)) {
		  sameList.push_back(nodeTerm);
		}
	  }
	}
	else if(nodeTerm->type() == "Struct") {
	  Struct * tempPtr = dynamic_cast<Struct *>(nodeTerm);
	  checkSubTerm(tempPtr);
	}
  }
//=====setSame.===================================
  bool setSame(Term * term) {
    for(int i=0; i<sameList.size(); i++) {
      if(sameList[i]->symbol() == term->symbol()) {
		for(int j=0; j<_terms.size(); j++) {
		  if(_terms[j] == term) {
			for(int k=0; k<_tree.size(); k++) {
              if(_tree[k]->term == term) {
				term = sameList[i]; 
			    _terms[j] = sameList[i];
				_tree[k]->term = sameList[i];
			    return true;
			  }
			}
		  }
		}
	  }
    }
	return false;
  }
//=====checkSubTerm.===================================  
  void checkSubTerm(Struct* structPtr) {	
	for(int i=0; i<structPtr->arity(); i++) {
	  if(structPtr->args(i)->type() == "Struct") {
		Struct * tempPtr = dynamic_cast<Struct *>(structPtr->_args[i]);
		checkSubTerm(tempPtr);
	  }
	  else if(structPtr->args(i)->type() == "Variable") {
		for(int j=0; j<sameList.size(); j++) {
		  bool set = false;
		  if(structPtr->args(i)->symbol() == sameList[j]->symbol()) {
			Struct * tempPtr = dynamic_cast<Struct *>(structPtr);
			tempPtr->_args[i] = sameList[j];
			set = true;
		  }
		  if(!set) {
			Struct * tempPtr = dynamic_cast<Struct *>(structPtr);
			sameList.push_back(structPtr->_args[i]);
		  }
		}
	  }
	}
  }
//=====parameter.===================================
  vector<Term *> _terms;
  Scanner _scanner;
  int _currentToken;
  vector<Node *> _tree;
  Node * _root;
  vector<Term *> sameList;	 
  stack<Exp*> _expStack;
};
#endif
