#ifndef UTLIST_H
#define UTLIST_H

#include <vector>
#include <string>

using std::vector;
using std::string;

#include "list.h"
#include "struct.h"
#include "atom.h"
#include "number.h"
#include "variable.h"

// When create a new list without any item
// Then #symbol() of the list should return "[]"
TEST (List, constructor) {
  List list;
  EXPECT_EQ("[]", list.symbol());
}

// Given there are two perfect Numbers: 8128, 496
// When create a new list with the perfect Number
// Then #symbol() of the list should return "[496, 8128]"
TEST(List, Numbers) {
  Number num_496(496);
  Number num_8128(8128);
  vector<Term *> v = {&num_496, &num_8128};
  List list(v);
  EXPECT_EQ("[496, 8128]", list.symbol());
}

// Given there are two atoms: "terence_tao", "alan_mathison_turing"
// When create a new list with the Atoms
// Then #symbol() of the list should return "[terence_tao, alan_mathison_turing]"
TEST(List, Atoms) {
  Atom terence_tao("terence_tao");
  Atom alan_mathison_turing("alan_mathison_turing");
  vector<Term *> v = {&terence_tao, &alan_mathison_turing};
  List list(v);
  EXPECT_EQ("[terence_tao, alan_mathison_turing]", list.symbol());
}

// Given there are two variables: X, Y
// When create a new list with the variables
// Then #symbol() of the list should return "[X, Y]"
TEST(List, Vars) {
  Variable X("X");
  Variable Y("Y");
  vector<Term *> v = {&X, &Y};
  List list(v);
  EXPECT_EQ("[X, Y]", list.symbol());
}

// ?- tom = [496, X, terence_tao].
// false.
TEST(List, matchToAtomShouldFail) {
  Atom tom("tom");
  Number num_496(496);
  Variable X("X");
  Atom terence_tao("terence_tao");
  vector<Term *> v = {&num_496, &X, &terence_tao};
  List list(v);
  EXPECT_FALSE(tom.match(list));
}

// ?- 8128 = [496, X, terence_tao].
// false.
TEST(List, matchToNumberShouldFail) {
  Number num_8128(8128);
  Number num_496(496);
  Variable X("X");
  Atom terence_tao("terence_tao");
  vector<Term *> v = {&num_496, &X, &terence_tao};
  List list(v);
  EXPECT_FALSE(num_8128.match(list));
}

// ?- s(X) = [496, X, terence_tao].
// false.
TEST(List, matchToStructShouldFail) {
  Variable X("X");
  vector<Term *> v1 = {&X};
  Struct s(Atom("s"), v1);
  Number num_496(496);
  Atom terence_tao("terence_tao");
  vector<Term *> v2 = {&num_496, &X, &terence_tao};
  List list(v2);
  EXPECT_FALSE(s.match(list));
}

// ?- Y = [496, X, terence_tao].
// Y = [496, X, terence_tao].
TEST(List, matchToVarShouldSucceed) {
  Variable Y("Y");
  Number num_496(496);
  Variable X("X");
  Atom terence_tao("terence_tao");
  vector<Term *> v = {&num_496, &X, &terence_tao};
  List list(v);
  EXPECT_TRUE(Y.match(list));
  EXPECT_EQ("[496, X, terence_tao]", Y.value());
}

// ?- X = [496, X, terence_tao].
// false.
TEST(List, matchToVarOccuredInListShouldFail) {
  Number num_496(496);
  Variable X("X");
  Atom terence_tao("terence_tao");
  vector<Term *> v = {&num_496, &X, &terence_tao};
  List list(v);
  EXPECT_FALSE(X.match(list));
  //EXPECT_TRUE(X.match(list));
  //EXPECT_EQ("[496, X, terence_tao]", X.value());
}

// ?- [496, X, terence_tao] = [496, X, terence_tao].
// true.
TEST(List, matchToSameListShouldSucceed) {
  Number num_496(496);
  Variable X("X");
  Atom terence_tao("terence_tao");
  vector<Term *> v = {&num_496, &X, &terence_tao};
  List list1(v);
  EXPECT_TRUE(list1.match(list1));
}

// ?- [496, X, terence_tao] = [496, Y, terence_tao].
// true.
TEST(List, matchToSameListWithDiffVarNameShouldSucceed) {
  Number num_496(496);
  Variable X("X");
  Variable Y("Y");
  Atom terence_tao("terence_tao");
  vector<Term *> v1 = {&num_496, &X, &terence_tao};
  vector<Term *> v2 = {&num_496, &Y, &terence_tao};
  List list1(v1);
  List list2(v2);
  EXPECT_TRUE(list1.match(list2));
}

// ?- [496, X, terence_tao] = [496, 8128, terence_tao].
// X = 8128.
TEST(List, matchToVarToAtominListShouldSucceed) {
  Number num_496(496);
  Number num_8128(8128);
  Variable X("X");
  Atom terence_tao("terence_tao");
  vector<Term *> v1 = {&num_496, &X, &terence_tao};
  vector<Term *> v2 = {&num_496, &num_8128, &terence_tao};
  List list1(v1);
  List list2(v2);
  EXPECT_TRUE(list1.match(list2));
  EXPECT_EQ("8128", X.value());
}

// ?- Y = [496, X, terence_tao], X = alan_mathison_turing.
// Y = [496, alan_mathison_turing, terence_tao],
// X = alan_mathison_turing.
TEST(List, matchVarinListToAtomShouldSucceed) {
  Variable Y("Y");
  Variable X("X");
  Number num_496(496);
  Atom alan_mathison_turing("alan_mathison_turing");
  Atom terence_tao("terence_tao");
  vector<Term *> v = {&num_496, &alan_mathison_turing, &terence_tao};
  List list(v);
  EXPECT_TRUE(Y.match(list));
  EXPECT_TRUE(X.match(alan_mathison_turing));
  EXPECT_EQ("[496, alan_mathison_turing, terence_tao]", Y.value());
  EXPECT_EQ("alan_mathison_turing", X.value());
}

// Example: 
// ?- [first, second, third] = [H|T].
// H = first, T = [second, third].
TEST(List, headAndTailMatching1) {
  Atom f("first"), s("second"), t("third");
  vector<Term *> args = {&f, &s, &t};
  List l(args);

  EXPECT_EQ(string("first"), l.head()->symbol());
  EXPECT_EQ(string("[second, third]"), l.tail()->value());
}

// Example:
// ?- [first, second, third] = [first, H|T].
// H = second, T = [third].
TEST(List, headAndTailMatching2) {
  Atom f("first"), s("second"), t("third");
  vector<Term *> args = {&f, &s, &t};
  List l(args);

  EXPECT_EQ(string("second"), l.tail()->head()->value());
  EXPECT_EQ(string("[third]"), l.tail()->tail()->value());
}

// ?- [[first], second, third] = [H|T].
// H = [first], T = [second, third].
TEST(List, headAndTailMatching3) {
  Atom f("first"), s("second"), t("third");
  vector<Term *> args1 = {&f};
  List l1(args1);
  vector<Term *> args2 = {&l1, &s, &t};
  List l2(args2);

  EXPECT_EQ(string("[first]"), l2.head()->value());
  EXPECT_EQ(string("[second, third]"), l2.tail()->value());
}

// ?- [first, second, third] = [first, second, H|T].
// H = third, T = [].
TEST(List, headAndTailMatching4) {
  Atom f("first"), s("second"), t("third");
  vector<Term *> args = {&f, &s, &t};
  List l(args);

  EXPECT_EQ(string("third"), l.tail()->tail()->head()->value());
  EXPECT_EQ(string("[]"), l.tail()->tail()->tail()->value());
}

// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing head in an empty list" as an exception.
TEST (List, emptyExecptionOfHead) {
  try { List list; list.head()->value(); }
  catch(string e1) { EXPECT_EQ(string("Accessing head in an empty list"), e1); }
}

// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing tail in an empty list" as an exception.
TEST (List, emptyExecptionOfTail) {
  try { List list; list.tail()->value(); }
  catch(string e1) { EXPECT_EQ(string("Accessing tail in an empty list"), e1); }
}

#endif
