#ifndef UTMATRIX_H_INCLUDED
#define UTMATRIX_H_INCLUDED

#include "Matrix.h"

TEST (Matrix, Constructor){
    double a[3]={0,2,2}, b[3]={2,2,6};
    Vector v(a, 3),w(b, 3);
    Vector * vec[2] = {&v, &w};
    Matrix m(vec,2);

    ASSERT_EQ(0,m[1][1]);
    ASSERT_EQ(2,m[2][2]);
    m[1][1] = 100;
    ASSERT_EQ(100, m[1][1]);
    //swapVector(m,1,2);
    //ASSERT_EQ(2,m[1]->component(2));
    //ASSERT_EQ(0,m[2]->component(1));
}

TEST (Matrix, Assignment){
    double a[3]={0,2,2}, b[3]={2,2,6};
    Vector v(a, 3),w(b, 3);
    Vector * vec[2] = {&v, &w};
    Matrix m(vec, 2);
    Matrix n(vec, 2);

    ASSERT_EQ(0,m[1][1]);
    ASSERT_EQ(2,m[2][2]);
    m[1][1] = 100;
    ASSERT_EQ(100, m[1][1]);
    n = m;
    ASSERT_EQ(100, n[1][1]);
    n = n;
    ASSERT_EQ(100, n[1][1]);
}

TEST (Matrix, Swap){
    double a[3]={0,2,2}, b[3]={2,2,6};
    Vector v(a, 3),w(b, 3);
    Vector * vec[2] = {&v, &w};
    Matrix m(vec,2);
    m.swap(1, 2);

    ASSERT_EQ(2, m[1][1]);
    ASSERT_EQ(2, m[2][2]);
}

TEST (Matrix, pivot){
    double a[3]={0,2,2}, b[3]={2,2,6};
    Vector v(a, 3),w(b, 3);
    Vector * vec[2] = {&v, &w};
    Matrix m(vec,2);
    m.pivot(1);

    ASSERT_EQ(2, m[1][1]);
    ASSERT_EQ(2, m[2][2]);
}

TEST (Matrix, forward) {
    double a[3]={0,2,2}, b[3]={2,2,6};
    Vector v(a, 3),w(b, 3);
    Vector * vec[2] = {&v, &w};
    Matrix m(vec,2);

    m.forward();
    ASSERT_EQ(1,m[1][1]);
    ASSERT_EQ(1,m[1][2]);
    ASSERT_EQ(3,m[1][3]);
    ASSERT_EQ(0,m[2][1]);
    ASSERT_EQ(1,m[2][2]);
    ASSERT_EQ(1,m[2][3]);

}

/*
TEST (Matrix, MatrixFromString) {
    std::string s("[0 2 2] \n [2 2 6] \n");
    Matrix m = MatrixFromString(s);

    EXPECT_EQ(0, m[1][1]);
    EXPECT_EQ(2, m[1][2]);
    EXPECT_EQ(2, m[1][3]);

    EXPECT_EQ(2, m[2][1]);
    EXPECT_EQ(2, m[2][2]);
    EXPECT_EQ(6, m[2][3]);

    EXPECT_EQ(2, m[2][1]);
    EXPECT_EQ(2, m[2][2]);
    EXPECT_EQ(6, m[2][3]);

    EXPECT_EQ(2, m(2,1));
    EXPECT_EQ(2, m(2,2));
    EXPECT_EQ(6, m(2,3));
}
*/
#endif // UTMATRIX_H_INCLUDED
