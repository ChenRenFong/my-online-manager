#ifndef UTATOM_H
#define UTATOM_H

#include "number.h"

TEST(Number, hello) 
{
  ASSERT_TRUE(true);
}

TEST(Number, num_25) 
{
  Number num_25(25);
  ASSERT_EQ("25", num_25.symbol());
  EXPECT_EQ("25", num_25.value());
}

TEST(Number, matchNum_25AndNum_30) 
{
  Number num_25(25);
  Number num_30(30);
  EXPECT_FALSE(num_25.match(num_30));
  EXPECT_TRUE(num_25.match(num_25));
}

TEST(Number, virtualAtom)
{
  Term * t = new Number(25);
  EXPECT_EQ("25", t->symbol());
  EXPECT_EQ("25", t->value());
}

#endif
