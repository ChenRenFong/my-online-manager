#ifndef UTITERATOR_H
#define UTITERATOR_H

#include "struct.h"
#include "variable.h"
#include "atom.h"
#include "number.h"
#include "list.h"
#include "iterator.h"

// s(1, t(X, 2), Y)
TEST(iterator, struct_iterator) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &two });
    Struct s(Atom("s"), { &one, &t, &Y });
    Iterator<Term*> *itStruct = s.createIterator();
    itStruct->first();
    ASSERT_EQ("1", itStruct->currentItem()->symbol());
    ASSERT_FALSE(itStruct->isDone());
    itStruct->next();
    ASSERT_EQ("t(X, 2)", itStruct->currentItem()->symbol());
    ASSERT_FALSE(itStruct->isDone());
    itStruct->next();
    ASSERT_EQ("Y", itStruct->currentItem()->symbol());
    itStruct->next();
	ASSERT_TRUE(itStruct->isDone());
}

// s(1, t(X, 2), Y)
TEST(iterator, nested_iterator) {
	Number one(1);
	Variable X("X");
	Variable Y("Y");
	Number two(2);
	Struct t(Atom("t"), { &X, &two });
	Struct s(Atom("s"), { &one, &t, &Y });
	Iterator<Term*> *itStruct = s.createIterator();
	itStruct->first();
	itStruct->next();
	Struct *s2 = dynamic_cast<Struct *>(itStruct->currentItem());
	Iterator<Term*> *itStruct2 = s2->createIterator();
	itStruct2->first();
	ASSERT_EQ("X", itStruct2->currentItem()->symbol());
	ASSERT_FALSE(itStruct2->isDone());
	itStruct2->next();
	ASSERT_EQ("2", itStruct2->currentItem()->symbol());
	ASSERT_FALSE(itStruct2->isDone());
	itStruct2->next();
	ASSERT_TRUE(itStruct2->isDone());
}

// [1, t(X, 2), Y]
TEST(iterator, list_iterator) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &two });
    List l({ &one, &t, &Y });
	Iterator<Term*> *itList = l.createIterator();
    itList->first();
    ASSERT_EQ("1", itList->currentItem()->symbol());
    ASSERT_FALSE(itList->isDone());
    itList->next();
    ASSERT_EQ("t(X, 2)", itList->currentItem()->symbol());
    ASSERT_FALSE(itList->isDone());
    itList->next();
    ASSERT_EQ("Y", itList->currentItem()->symbol());
    itList->next();
    ASSERT_TRUE(itList->isDone());
}

TEST(iterator, null_iterator){
	Number one(1);
	NullIterator<Term*> nullIterator(&one);
	nullIterator.first();
	ASSERT_TRUE(nullIterator.isDone());
	Iterator<Term*> * it = one.createIterator();
	it->first();
	ASSERT_TRUE(it->isDone());
}

// s(1, t(X, 2), Y)
TEST(iterator, struct_iterator_BFS1){
	Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &two });
    Struct s(Atom("s"), { &one, &t, &Y });
    Iterator<Term*> *itStruct = s.createBFSIterator();
    itStruct->first();
    ASSERT_EQ("1", itStruct->currentItem()->symbol());
    ASSERT_FALSE(itStruct->isDone());
    itStruct->next();
	ASSERT_EQ("t(X, 2)", itStruct->currentItem()->symbol());
    ASSERT_FALSE(itStruct->isDone());
    itStruct->next();
    ASSERT_EQ("Y", itStruct->currentItem()->symbol());
    ASSERT_FALSE(itStruct->isDone());
    itStruct->next();
    ASSERT_EQ("X", itStruct->currentItem()->symbol());
    itStruct->next();
	ASSERT_EQ("2", itStruct->currentItem()->symbol());
    itStruct->next();
	ASSERT_TRUE(itStruct->isDone());
}

// s(1, t(z(X), 2), Y)
TEST(iterator, struct_iterator_BFS2){
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
	Struct z(Atom("z"), { &X });
    Struct t(Atom("t"), { &z, &two });
    Struct s(Atom("s"), { &one, &t, &Y });
    Iterator<Term*> *itStruct = s.createBFSIterator();
    itStruct->first();
    ASSERT_EQ("1", itStruct->currentItem()->symbol());
    ASSERT_FALSE(itStruct->isDone());
    itStruct->next();
	ASSERT_EQ("t(z(X), 2)", itStruct->currentItem()->symbol());
    ASSERT_FALSE(itStruct->isDone());
    itStruct->next();
    ASSERT_EQ("Y", itStruct->currentItem()->symbol());
    ASSERT_FALSE(itStruct->isDone());
    itStruct->next();
	ASSERT_EQ("z(X)", itStruct->currentItem()->symbol());
    ASSERT_FALSE(itStruct->isDone());
    itStruct->next();
    ASSERT_EQ("2", itStruct->currentItem()->symbol());
    itStruct->next();
	ASSERT_EQ("X", itStruct->currentItem()->symbol());
    itStruct->next();
	ASSERT_TRUE(itStruct->isDone());
}

// [1, t(X, 2), Y]
TEST(iterator, list_iterator_BFS1){
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &two });
    List l({ &one, &t, &Y });
    Iterator<Term*> *itList = l.createBFSIterator();
    itList->first();
    ASSERT_EQ("1", itList->currentItem()->symbol());
    ASSERT_FALSE(itList->isDone());
    itList->next();
	ASSERT_EQ("t(X, 2)", itList->currentItem()->symbol());
    ASSERT_FALSE(itList->isDone());
    itList->next();
    ASSERT_EQ("Y", itList->currentItem()->symbol());
    ASSERT_FALSE(itList->isDone());
    itList->next();
    ASSERT_EQ("X", itList->currentItem()->symbol());
    itList->next();
	ASSERT_EQ("2", itList->currentItem()->symbol());
    itList->next();
	ASSERT_TRUE(itList->isDone());
}

// [1, t(z(X), 2), Y]
TEST(iterator, list_iterator_BFS2){
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct z(Atom("z"), { &X });
    Struct t(Atom("t"), { &z, &two });
    List l({ &one, &t, &Y });
    Iterator<Term*> *itList = l.createBFSIterator();
    itList->first();
    ASSERT_EQ("1", itList->currentItem()->symbol());
    ASSERT_FALSE(itList->isDone());
    itList->next();
	ASSERT_EQ("t(z(X), 2)", itList->currentItem()->symbol());
    ASSERT_FALSE(itList->isDone());
    itList->next();
    ASSERT_EQ("Y", itList->currentItem()->symbol());
    ASSERT_FALSE(itList->isDone());
    itList->next();
	ASSERT_EQ("z(X)", itList->currentItem()->symbol());
    ASSERT_FALSE(itList->isDone());
    itList->next();
    ASSERT_EQ("2", itList->currentItem()->symbol());
    itList->next();
	ASSERT_EQ("X", itList->currentItem()->symbol());
    itList->next();
	ASSERT_TRUE(itList->isDone());
}

// s(1, t(X, 2), Y)
TEST(iterator, struct_iterator_DFS1){
	Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &two });
    Struct s(Atom("s"), { &one, &t, &Y });
    Iterator<Term*> *itStruct = s.createDFSIterator();
    itStruct->first();
    ASSERT_EQ("1", itStruct->currentItem()->symbol());
    ASSERT_FALSE(itStruct->isDone());
    itStruct->next();
	ASSERT_EQ("t(X, 2)", itStruct->currentItem()->symbol());
    ASSERT_FALSE(itStruct->isDone());
    itStruct->next();
    ASSERT_EQ("X", itStruct->currentItem()->symbol());
    ASSERT_FALSE(itStruct->isDone());
    itStruct->next();
    ASSERT_EQ("2", itStruct->currentItem()->symbol());
    itStruct->next();
	ASSERT_EQ("Y", itStruct->currentItem()->symbol());
    itStruct->next();
	ASSERT_TRUE(itStruct->isDone());
}

// s(1, t(2, z(X, Y)), 3)
TEST(iterator, struct_iterator_DFS2){
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
	Number three(3);
	Struct z(Atom("z"), { &X, &Y });
    Struct t(Atom("t"), { &two, &z });
    Struct s(Atom("s"), { &one, &t, &three });
    Iterator<Term*> *itStruct = s.createDFSIterator();
    itStruct->first();
    ASSERT_EQ("1", itStruct->currentItem()->symbol());
    ASSERT_FALSE(itStruct->isDone());
    itStruct->next();
	ASSERT_EQ("t(2, z(X, Y))", itStruct->currentItem()->symbol());
    ASSERT_FALSE(itStruct->isDone());
    itStruct->next();
    ASSERT_EQ("2", itStruct->currentItem()->symbol());
    ASSERT_FALSE(itStruct->isDone());
    itStruct->next();
	ASSERT_EQ("z(X, Y)", itStruct->currentItem()->symbol());
    ASSERT_FALSE(itStruct->isDone());
    itStruct->next();
    ASSERT_EQ("X", itStruct->currentItem()->symbol());
    itStruct->next();
	ASSERT_EQ("Y", itStruct->currentItem()->symbol());
    itStruct->next();
	ASSERT_EQ("3", itStruct->currentItem()->symbol());
    itStruct->next();
	ASSERT_TRUE(itStruct->isDone());
}

// [1, t(X, 2), Y]
TEST(iterator, list_iterator_DFS1){
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &two });
    List l({ &one, &t, &Y });
    Iterator<Term*> *itList = l.createDFSIterator();
    itList->first();
    ASSERT_EQ("1", itList->currentItem()->symbol());
    ASSERT_FALSE(itList->isDone());
    itList->next();
	ASSERT_EQ("t(X, 2)", itList->currentItem()->symbol());
    ASSERT_FALSE(itList->isDone());
    itList->next();
    ASSERT_EQ("X", itList->currentItem()->symbol());
    ASSERT_FALSE(itList->isDone());
    itList->next();
    ASSERT_EQ("2", itList->currentItem()->symbol());
    itList->next();
	ASSERT_EQ("Y", itList->currentItem()->symbol());
    itList->next();
	ASSERT_TRUE(itList->isDone());
}

// [1, t(2, z(X, Y), 3]
TEST(iterator, list_iterator_DFS2){
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
	Number three(3);
	Struct z(Atom("z"), { &X, &Y });
    Struct t(Atom("t"), { &two, &z });
    List l({ &one, &t, &three });
	Iterator<Term*> *itList = l.createDFSIterator();
    itList->first();
    ASSERT_EQ("1", itList->currentItem()->symbol());
    ASSERT_FALSE(itList->isDone());
    itList->next();
	ASSERT_EQ("t(2, z(X, Y))", itList->currentItem()->symbol());
    ASSERT_FALSE(itList->isDone());
    itList->next();
    ASSERT_EQ("2", itList->currentItem()->symbol());
    ASSERT_FALSE(itList->isDone());
    itList->next();
	ASSERT_EQ("z(X, Y)", itList->currentItem()->symbol());
    ASSERT_FALSE(itList->isDone());
    itList->next();
    ASSERT_EQ("X", itList->currentItem()->symbol());
    itList->next();
	ASSERT_EQ("Y", itList->currentItem()->symbol());
    itList->next();
	ASSERT_EQ("3", itList->currentItem()->symbol());
    itList->next();
	ASSERT_TRUE(itList->isDone());
}

#endif
