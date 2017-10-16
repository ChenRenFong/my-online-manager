#ifndef UTATOM_H
#define UTATOM_H

#include "atom.h"

TEST(Atom, hello) 
{
  ASSERT_TRUE(true);
}

TEST(Atom, tom) 
{
  Atom tom("tom");
  ASSERT_EQ("tom", tom.symbol());
  EXPECT_EQ("tom", tom.value());
}

TEST(Atom, matchTomAndJerry) 
{
  Atom tom("tom");
  Atom jerry("jerry");
  EXPECT_FALSE(tom.match(jerry));
  EXPECT_TRUE(tom.match(tom));
}

TEST(Atom, virtualAtom)
{
  Term * t = new Atom("tom");
  EXPECT_EQ("tom", t->symbol());
  EXPECT_EQ("tom", t->value());
}

#endif
