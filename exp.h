#ifndef EXP_H
#define EXP_H

#include "term.h"

class Exp {
public:
  virtual bool evaluate() = 0;
  virtual string getExpressionResult() = 0;
  virtual bool checkIsVariableMatchItsalf() {};
  virtual string checkLeftType() {};
  virtual string checkRightType() {};
  
static std::vector<string> _sameList;
};


class MatchExp : public Exp {
public:
  MatchExp(Term* left, Term* right): _left(left), _right(right){}

  string getExpressionResult() {
    if(evaluate()) {
      if( _left->symbol() == _right->symbol() ) {
        return "true";
      }
      return _left->symbol() + " = " + _right->value();
    }
    else {
      return "false";
    }
  }
  
  bool checkIsVariableMatchItsalf() {
	if(_left->type() == "Variable" && _right->type() == "Variable") {
	  if(_left->symbol() == _right->symbol()) {
		return true;
	  }
	}
	return false;
  }
  
  string checkType() {
	return _left->type();
  }
  
  string checkRightType() {
	return _right->type();
  }
  
  bool evaluate(){
    return _left->match(*_right);
  }

private:
  Term* _left;
  Term* _right;
};

class ConjExp : public Exp {
public:
  ConjExp(Exp *left, Exp *right) : _left(left), _right(right) {}

  string getExpressionResult() {
    if(evaluate()) {
      if( _left->getExpressionResult() == _right->getExpressionResult()) {
		return _right->getExpressionResult();
      }
	  if( _left->getExpressionResult() != _right->getExpressionResult()) {
		if(_left->checkIsVariableMatchItsalf()) {
		  return _right->getExpressionResult();
		}
		MatchExp* pm = dynamic_cast<MatchExp*>(_right);
		if(pm) {
		  if(_right->checkIsVariableMatchItsalf()) {
			return _left->getExpressionResult();
		  }
		}
      }
      return _left->getExpressionResult() + ", " + _right->getExpressionResult();
    }
    else {
      return "false";
    }
  }
  
  bool evaluate() {
    return (_left->evaluate() && _right->evaluate());
  }

private:
  Exp * _left;
  Exp * _right;
};

class DisjExp : public Exp {
public:
  DisjExp(Exp *left, Exp *right) : _left(left), _right(right) {}
  
  string getExpressionResult() {

    if(evaluate()) {
      if( _left->getExpressionResult() == _right->getExpressionResult()) {
        return "true";
      }
      return _left->getExpressionResult() + "; " + _right->getExpressionResult();
    }
    else {
      return "false";
    }
  }
  
  bool evaluate() {
    return (_left->evaluate() || _right->evaluate());
  }

private:
  Exp * _left;
  Exp * _right;
};
#endif
