#ifndef NODE_H
#define NODE_H

#include "term.h"

//             {0          1      2             }
//             {;          ,      =             }
enum Operators {SEMICOLON, COMMA, EQUALITY, TERM};

class Node {
public:
  Node(Operators op):payload(op), term(0), left(0), right(0) {}
  Node(Operators op, Term *t, Node *l, Node *r):payload(op), term(t), left(l), right(r) {}
//=====evaluate.===================================
  bool evaluate() {   
	return preOrder(this); 
  }
//=====preOrder.===================================  
  bool preOrder(Node* nowNode) {
	
	if(nowNode->left->payload == TERM) {
	  bool fin = nowNode->left->term->match(*nowNode->right->term);
	  return fin;
	}
    
	bool ans;
	
	ans = preOrder(nowNode->left);
	ans = preOrder(nowNode->right);
	
	return ans;
  }
//=====parameter.===================================
  Operators payload;
  Term * term;
  Node * left;
  Node * right;
};

#endif
