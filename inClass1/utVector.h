#ifndef UTVECTOR_H_INCLUDED
#define UTVECTOR_H_INCLUDED
#include <string>
#include "Vector.h"
#include <vector>

TEST (Vector, create)
{
    double a[2]={1,2};
    Vector v(a, 2);

    ASSERT_EQ(2,v.dim());
    ASSERT_EQ(1,v.component(1));
    ASSERT_EQ(2,v.component(2));
}

TEST (Vector, innerProduct){
    double a[2]={1,2}, b[2]={3,4};
    Vector v(a, 2),w(b, 2);

    ASSERT_EQ(11 ,innerProduct(v,w));
    // testing if a correct copy constructor is provided
    EXPECT_EQ(1,v.component(1));
    EXPECT_EQ(2,v.component(2));
}

TEST (Vector, minus){
    double a[2]={1,2}, b[2]={3,4};
    Vector v(a, 2),w(b, 2);
    Vector x=v-w;
    EXPECT_EQ(-2,x[1]);
    EXPECT_EQ(-2,x[2]);
    EXPECT_NEAR(2*sqrt(2),x.length(),0.00001);
}

TEST (Vector, innerProductEx){
    double a[2]={1,2}, b[3]={3,4,5};
    Vector v(a, 2),w(b, 3);
    ASSERT_ANY_THROW(innerProduct(v,w));
}

TEST (Vector, innerProductExString){
    double a[2]={1,2}, b[3]={3,4,5};
    Vector v(a, 2),w(b, 3);
    try {
        innerProduct(v,w);
        FAIL() << "should not be here!";
    } catch(std::string s) {
        ASSERT_EQ(std::string("wrong dim"), s);
    }
}
TEST (Vector, multiply) {
    double a[3]={0,2,2}, b[3]={2,2,6};
    Vector v(a, 3),w(b, 3);
    multiply(0.5,v);
    ASSERT_EQ(0,v.component(1));
    ASSERT_EQ(1,v.component(2));
    ASSERT_EQ(1,v.component(3));
}
TEST (Vector, linearTransform){
    double a[3]={1,1,3}, b[3]={0,1,1};
    Vector v(a, 3),w(b, 3);
    linearTransform(-1,w,v);
    ASSERT_EQ(1,v.component(1));
    ASSERT_EQ(0,v.component(2));
    ASSERT_EQ(2,v.component(3));
}


TEST (Matrix, First){
    double a[3]={0,2,2}, b[3]={2,2,6};
    Vector v(a, 3),w(b, 3);
    std::vector <Vector*> m;
    m.push_back(0);
    m.push_back(&v);
    m.push_back(&w);
    ASSERT_EQ(0,m[1]->component(1));
    ASSERT_EQ(2,m[2]->component(2));
    swapVector(m,1,2);
    ASSERT_EQ(2,m[1]->component(2));
    ASSERT_EQ(0,m[2]->component(1));
}

TEST (vector, intArray) {
    int a[5] = {1,2,3,4,5};
    std::vector<int> v(a,a+5);
    ASSERT_EQ(a[3],v[3]);
    v.push_back(6);
    ASSERT_EQ(6,v[5]);
    ASSERT_EQ(6,v.size());

}

TEST (pivot, first) {
    double a[3]={0,2,2}, b[3]={2,2,6};
    Vector v(a, 3),w(b, 3);
    std::vector <Vector*> m;
    m.push_back(0);
    m.push_back(&v);
    m.push_back(&w);

    pivot(1, m);
    ASSERT_EQ(2,m[1]->component(1));
    ASSERT_EQ(2,m[1]->component(2));
    ASSERT_EQ(6,m[1]->component(3));


}

TEST (pivot, noSwap) {
    double a[3]={2,2,6}, b[3]={0,2,2};
    Vector v(a, 3),w(b, 3);
    std::vector <Vector*> m;
    m.push_back(0);
    m.push_back(&v);
    m.push_back(&w);

    pivot(1, m);
    ASSERT_EQ(2,m[1]->component(1));
    ASSERT_EQ(2,m[1]->component(2));
    ASSERT_EQ(6,m[1]->component(3));
}

TEST (forward, first) {
    double a[3]={0,2,2}, b[3]={2,2,6};
    Vector v(a, 3),w(b, 3);
    std::vector <Vector*> m;
    m.push_back(0);
    m.push_back(&v);
    m.push_back(&w);

    forward(m);
    ASSERT_EQ(1,m[1]->component(1));
    ASSERT_EQ(1,m[1]->component(2));
    ASSERT_EQ(3,m[1]->component(3));
    ASSERT_EQ(0,m[2]->component(1));
    ASSERT_EQ(1,m[2]->component(2));
    ASSERT_EQ(1,m[2]->component(3));

}
TEST (backward, first) {
    double a[3]={1,1,3}, b[3]={0,1,1};
    Vector v(a, 3),w(b, 3);
    std::vector <Vector*> m;
    m.push_back(0);
    m.push_back(&v);
    m.push_back(&w);

    backward(m);
    ASSERT_EQ(1,m[1]->component(1));
    ASSERT_EQ(0,m[1]->component(2));
    ASSERT_EQ(2,m[1]->component(3));
    ASSERT_EQ(0,m[2]->component(1));
    ASSERT_EQ(1,m[2]->component(2));
    ASSERT_EQ(1,m[2]->component(3));
}

TEST (GaussJordan, first) {
    double a[3]={0,2,2}, b[3]={2,2,6};
    Vector v(a, 3),w(b, 3);
    std::vector <Vector*> m;
    m.push_back(0);
    m.push_back(&v);
    m.push_back(&w);

    GuassJordan(m);
    ASSERT_EQ(1,m[1]->component(1));
    ASSERT_EQ(0,m[1]->component(2));
    ASSERT_EQ(2,m[1]->component(3));
    ASSERT_EQ(0,m[2]->component(1));
    ASSERT_EQ(1,m[2]->component(2));
    ASSERT_EQ(1,m[2]->component(3));
}

TEST(Vector, compnent) {
    double a[3]={0,2,2}, b[3]={2,2,6};
    Vector v(a, 3),w(b, 3);
    ASSERT_EQ(0, v.component(1));
    v.component(1) = 100;
    ASSERT_EQ(100, v.component(1));

    Vector z(v);
    ASSERT_EQ(100, z.component(1));

}
 TEST(Vector, multiply1) {
    double a[3]={0,2,2}, b[3]={2,2,6};
    Vector v(a, 3),w(b, 3);
    v.multiply(3);
    ASSERT_EQ(6,v.component(2));
}

TEST(Vector, saxpy) {
    double a[3]={0,2,2}, b[3]={2,2,6};
    Vector v(a, 3),w(b, 3);
    v.saxpy(3, w);
    ASSERT_EQ(6,v.component(1));
}

TEST(Vector,outPut){
    double a[3]={0,2,2}, b[3]={2,2,6};
    Vector v(a, 3),w(b, 3);
    std::string ans("[ 0 2 2 ]");
    ASSERT_EQ(ans,v.toString());

}

TEST(Vector,inPut){

    std::string ans("[ 0 2 2 ]");
    Vector v=stringToVector(ans);
    EXPECT_EQ(3,v.dim());
    EXPECT_EQ(0,v[1]);
    EXPECT_EQ(2,v[2]);
    EXPECT_EQ(2,v[3]);

}

TEST(Vector,inPut2){

    std::string ans("   [      0 2 2 3]");
    Vector v=stringToVector(ans);
    EXPECT_EQ(4,v.dim());
    EXPECT_EQ(0,v[1]);
    EXPECT_EQ(2,v[2]);
    EXPECT_EQ(2,v[3]);
    EXPECT_EQ(3,v[4]);
}

TEST(VectorArea,triangle){
    double a[2] = {1,0}, b[2] = {1,1}, c[2] = {0, 0};
    Vector u(a, 2), v(b, 2), w(c, 2);
    EXPECT_NEAR(0.5,VectorArea(u,v,w),0.00001);
}

TEST(Vector, centroid){
    double a[2] = {1, 1}, b[2] = {0, 2}, c[2] = {0, 0},d[2] = {1, 0};
    Vector u(b, 2), v(a, 2), w(c, 2), x(d, 2);
    Vector *p[4] = { &u, &v, &w, &x};
    Vector cent =centroid(p, 4);

    EXPECT_NEAR(0.5, cent[1], 0.0001);
    EXPECT_NEAR(0.75, cent[2], 0.0001);
}

TEST(Vector, angle){
    double a[2] = {1, 0},b[2] ={1,1}, c[2] = {1, -1};
    Vector u(a,2), v(b,2), w(c,2);
    EXPECT_NEAR(45.0,angle(u, v),0.0001);
    EXPECT_NEAR(315.0,angle(u, w),0.0001);
}
#endif // UTVECTOR_H_INCLUDED
