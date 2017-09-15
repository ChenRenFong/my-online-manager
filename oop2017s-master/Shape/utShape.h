#ifndef UTSHAPE_H_INCLUDED
#define UTSHAPE_H_INCLUDED
#include "../Polygon/Polygon.h"
#include "Shape.h"
#include "printShape.h"
TEST(shape, printPolygon)
{
    double a[2] = {1, 1}, b[2] = {0, 1}, c[2] = {0, 0},d[2] = {1, 0};
    Vector u(a, 2), v(b, 2), w(c, 2), x(d, 2);
    Vector *p[4] = { &u, &v, &w, &x};
    Polygon square = createConvexPolygon(p, 4);
    ASSERT_EQ("name:polygon, area= 1, perimeter= 4", printShape(square));
    ASSERT_EQ("name:polygon, area= 1, perimeter= 4", printShape(&square));
}

TEST(shape, printCircle)
{
    double a[2]={0,0};
    Vector c(a,2);
    Circle cir(c, 1);
    ASSERT_EQ("name:circle, area= 3.14159, perimeter= 6.28318", printShape(cir));
    ASSERT_EQ("name:circle, area= 3.14159, perimeter= 6.28318", printShape(&cir));
}

/*
Problem: Given a vector of pointers to Shape objects, sort the shapes
         by areas in decreasing order.

*/

TEST(Shape, sorting){
    double a[2] = {1, 1}, b[2] = {0, 1}, c[2] = {0, 0},d[2] = {1, 0};
    Vector u(a, 2), v(b, 2), w(c, 2), x(d, 2);
    Vector *p[4] = {&u, &v, &w, &x};
    Polygon square = createConvexPolygon(p, 4);

    double a0[2]={0,0};
    Vector c0(a0,2);
    Circle cir0(c0, 1);

    double a1[2]={0,0};
    Vector c1(a1,2);
    Circle cir1(c1,2);

    std::vector<Shape * > Shapes ;
    Shapes.push_back (&cir0);
    Shapes.push_back (&square);
    Shapes.push_back (&cir1);
    std::sort (Shapes.begin(),Shapes.end(),areaGreater);
    ASSERT_EQ(&cir1, Shapes[0]);  // compare the address
    ASSERT_EQ(&cir0, Shapes[1]);
    ASSERT_EQ(&square, Shapes[2]);

}
#endif // UTSHAPE_H_INCLUDED
