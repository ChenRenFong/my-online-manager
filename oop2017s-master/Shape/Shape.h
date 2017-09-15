#ifndef SHAPE_H_INCLUDED
#define SHAPE_H_INCLUDED
#include <string>
#include <sstream>
#include "../inClass1/Vector.h"
const double PI=3.14159;
class Shape
{
public:
    virtual std::string name() const = 0;
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
};
class Circle: public Shape
{
public:
    Circle(Vector const &center, double radius):c(center),r(radius){}
    std::string name() const {
        return std::string("circle");
    }
    double area() const{
        return PI*r*r;
    }
    double perimeter() const{
        return 2.0*PI*r;
    }
private:
    Vector c;
    double r;
};

bool areaGreater (Shape * a, Shape *b) {return a->area() > b->area(); }

#endif // SHAPE_H_INCLUDED
