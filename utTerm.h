#ifndef UTTERM_H
#define UTTERM_H

#include "Number.h"
#include "atom.h"
#include "variable.h"

//test Number.value()
TEST (Number,ctor) {
  Number _1(1);
  ASSERT_EQ("1", _1.value());
}
//test Number.symbol()
TEST (Number, symbol) {
  Number _1(1);
  ASSERT_EQ("1", _1.symbol());
}
//?- 25=25.
//true.
TEST (Number, matchSuccess) {
  Number _25(25);
  ASSERT_TRUE(_25.match(_25));
}
//?- 25=0.
//false.
TEST (Number, matchFailureDiffValue) {
  Number _25(25);
  Number _0(0);
  ASSERT_FALSE(_25.match(_0));
}
//?- 25=tom.
//false.
TEST (Number, matchFailureDiffConstant) {
  Number _25(25);
  Atom tom("tom");
  ASSERT_FALSE(_25.match(tom));
}
//?- 25=X.
//true.
TEST (Number, matchSuccessToVar) {
  Number _25(25);
  Var X("X");
  ASSERT_TRUE(_25.match(X));
  ASSERT_EQ("25", X.value());
}
//?- tom=25.
//false.
TEST (Atom, matchFailureDiffConstant) {
  Number _25(25);
  Atom tom("tom");
  ASSERT_FALSE(tom.match(_25));
}
// ?- tom = X.
// X = tom.
TEST (Atom, matchSuccessToVar) {
  Atom tom("tom");
  Var X("X");
  ASSERT_TRUE(tom.match(X));
  ASSERT_EQ("tom", X.value());
}
// ?- X=tom, tom=X.
// X = tom.
TEST (Atom, matchSuccessToVarInstantedToDiffConstant) {
  Atom tom("tom");
  Var X("X");
  ASSERT_TRUE(X.match(tom));
  ASSERT_TRUE(tom.match(X));
  ASSERT_EQ("tom", X.value());
}
// ?- X=jerry, tom=X.
// false.
TEST (Atom, matchFailureToVarInstantedToDiffConstant) {
  Atom tom("tom");
  Atom jerry("jerry");
  Var X("X");
  ASSERT_TRUE(X.match(jerry));
  ASSERT_FALSE(tom.match(X));
}
// ?- X = 5.
// X = 5.
TEST (Var, matchSuccessToNumber) {
  Number _5(5);
  Var X("X");
  ASSERT_TRUE(X.match(_5));
  ASSERT_EQ("5", X.value());
}
// ?- X=25, X= 100.
// false.
TEST (Var, matchFailureToTwoDiffNumbers) {
  Number _25(25);
  Number _100(100);
  Var X("X");
  ASSERT_TRUE(X.match(_25));
  ASSERT_FALSE(X.match(_100));
}
// ?- X=tom, X= 25.
// false.
TEST (Var, matchSuccessToAtomThenFailureToNumber) {
  Number _25(25);
  Atom tom("tom");
  Var X("X");
  ASSERT_TRUE(X.match(tom));
  ASSERT_FALSE(X.match(_25));
}
//?- tom=X, 25=X.
//false.
TEST (Var, matchSuccessToAtomThenFailureToNumber2) {
  Number _25(25);
  Atom tom("tom");
  Var X("X");
  ASSERT_TRUE(tom.match(X));
  ASSERT_FALSE(_25.match(X));
}
//?- X=tom, X=tom.
//true.
TEST(Var, reAssignTheSameAtom){
  Atom tom("tom");
  Var X("X");
  ASSERT_TRUE(X.match(tom));
  ASSERT_TRUE(X.match(tom));
}

#endif
