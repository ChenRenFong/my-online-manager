#ifndef UTEXP_H_INCLUDED
#define UTEXP_H_INCLUDED
int X(int num1, int num2);
int X(int num1, int num2)
{
    return num1 * num2;
}

TEST (testX,first) {
    ASSERT_TRUE(X(2, 3) ==6);
}

TEST (testX, second) {
    ASSERT_EQ(20, X(4,5));
}

#endif // UTEXP_H_INCLUDED
