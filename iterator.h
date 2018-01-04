#ifndef ITERATOR_H
#define ITERATOR_H

#include "struct.h"
#include "list.h"

template<class T>
class Iterator {
public:
  virtual void first() = 0;
  virtual void next() = 0;
  virtual T currentItem() const = 0;
  virtual bool isDone() const = 0;
};

template<class T>
class NullIterator :public Iterator<T>{
public:
  NullIterator(T n){}
  void first(){}
  void next(){}
  T currentItem() const{
      return nullptr;
  }
  bool isDone() const{
    return true;
  }
};

template<class T>
class StructIterator :public Iterator<T> {
public:
  friend class Struct;
  void first() {
    _index = 0;
  }

  T currentItem() const {
    return _s->args(_index);
  }

  bool isDone() const {
    return _index >= _s->arity();
  }

  void next() {
    _index++;
  }
  
private:
  StructIterator(Struct *s): _index(0), _s(s) {}
  int _index;
  Struct* _s;
};

template<class T>
class ListIterator :public Iterator<T> {
public:
  friend class List;
  void first() {
    _index = 0;
  }

  T currentItem() const {
    return _list->args(_index);
  }

  bool isDone() const {
    return _index >= _list->arity();
  }

  void next() {
    _index++;
  }
  
private:
  ListIterator(List *l): _index(0), _list(l) {}
  int _index;
  List* _list;
};

template<class T>
class createStructBFSIterator :public Iterator<T> {
public:
  friend class Struct;
  void first() {
    _index = 0;

	int i, j;
	vector<Term *> temp;
	vector<Term *> temp2;
	
	for(i=0; i<_s->arity(); i++) {
	  
	  if(_s->args(i)->type()!="Struct" && _s->args(i)->type()!="List") {
		_tree.push_back(_s->args(i));
	  }
	  else {
		_tree.push_back(_s->args(i));
		temp.push_back(_s->args(i));
	  }
	  
	}
	
	while(temp.size()!=0) {
	  temp2.clear();
	  temp2.assign(temp.begin(), temp.end());
	  temp.clear();
	  
	  for(i=0; i<temp2.size(); i++) {
	    for(j=0; j<temp2[i]->arity(); j++) {
		  
		  if(temp2[i]->args(j)->type()!="Struct" && temp2[i]->args(j)->type()!="List") {
			_tree.push_back(temp2[i]->args(j));  
		  }
		  else {
			_tree.push_back(temp2[i]->args(j));
			temp.push_back(temp2[i]->args(j));  
		  }
		  
		}
	  }
	}
  }

  T currentItem() const {
    return _tree[_index];
  }

  bool isDone() const {
    return _index >= _tree.size();
  }

  void next() {
    _index++;
  }
  
private:
  createStructBFSIterator(Struct *s): _index(0), _s(s) {}
  int _index;
  Struct * _s;
  vector<T> _tree;
};

template<class T>
class createListBFSIterator :public Iterator<T> {
public:
  friend class List;
  void first() {
    _index = 0;

	int i, j;
	vector<Term *> temp;
	vector<Term *> temp2;
	
	for(i=0; i<_l->arity(); i++) {
	  
	  if(_l->args(i)->type()!="Struct" && _l->args(i)->type()!="List") {
	    _tree.push_back(_l->args(i));
	  }
	  else {
		_tree.push_back(_l->args(i));
		temp.push_back(_l->args(i));
	  }
	  
	}
	
	while(temp.size()!=0) {
	  temp2.clear();
	  temp2.assign(temp.begin(), temp.end());
	  temp.clear();
	  
	  for(i=0; i<temp2.size(); i++) {
	    for(j=0; j<temp2[i]->arity(); j++) {
		  
		  if(temp2[i]->args(j)->type()!="Struct" && temp2[i]->args(j)->type()!="List") {
			_tree.push_back(temp2[i]->args(j));  
		  }
		  else {
			_tree.push_back(temp2[i]->args(j));
			temp.push_back(temp2[i]->args(j));  
		  }
		  
		}
	  }
	}
  }

  T currentItem() const {
    return _tree[_index];
  }

  bool isDone() const {
    return _index >= _tree.size();
  }

  void next() {
    _index++;
  }
  
private:
  createListBFSIterator(List *l): _index(0), _l(l) {}
  int _index;
  List* _l;
  vector<T> _tree;
};

template<class T>
class createStructDFSIterator :public Iterator<T> {
public:
  friend class Struct;
  void first() {
    _index = 0;
    
	int i;
	
	for(i=0; i<_s->arity(); i++) {
	  
	  if(_s->args(i)->type()!="Struct" && _s->args(i)->type()!="List") {
	    _tree.push_back(_s->args(i));
	  }
	  else {
		_tree.push_back(_s->args(i));
		checkSubTerm(_s->args(i));
	  }
	  
	}
  }

  T currentItem() const {
    return _tree[_index];
  }

  bool isDone() const {
    return _index >= _tree.size();
  }

  void next() {
    _index++;
  }
  
private:
  void checkSubTerm(Term* termPtr) {
	for(int i=0; i<termPtr->arity(); i++) {
	  if(termPtr->args(i)->type() == "Struct" || termPtr->args(i)->type() == "List") {
		_tree.push_back(termPtr->args(i));
		checkSubTerm(termPtr->args(i));
	  }
	  else {
		_tree.push_back(termPtr->args(i));
	  }
	}
  }

  createStructDFSIterator(Struct *s): _index(0), _s(s) {}
  int _index;
  Struct * _s;
  vector<T> _tree;
};

template<class T>
class createListDFSIterator :public Iterator<T> {
public:
  friend class List;
  void first() {
    _index = 0;
    
	int i;
	
	for(i=0; i<_l->arity(); i++) {
	  
	  if(_l->args(i)->type()!="Struct" && _l->args(i)->type()!="List") {
	    _tree.push_back(_l->args(i));
	  }
	  else {
		_tree.push_back(_l->args(i));
		checkSubTerm(_l->args(i));
	  }
	  
	}
  }

  T currentItem() const {
    return _tree[_index];
  }

  bool isDone() const {
    return _index >= _tree.size();
  }

  void next() {
    _index++;
  }
  
private:
  void checkSubTerm(Term* termPtr) {
	for(int i=0; i<termPtr->arity(); i++) {
	  if(termPtr->args(i)->type() == "Struct" || termPtr->args(i)->type() == "List") {
		_tree.push_back(termPtr->args(i));
		checkSubTerm(termPtr->args(i));
	  }
	  else {
		_tree.push_back(termPtr->args(i));
	  }
	}
  }

  createListDFSIterator(List *l): _index(0), _l(l) {}
  int _index;
  List* _l;
  vector<T> _tree;
};

#endif
