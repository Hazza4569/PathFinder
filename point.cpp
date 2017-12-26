#include <iostream>

#include "point.h"


Point::Point()
    : fX(0), fY(0) {}

Point::Point(int x, int y)
    : fX(x), fY(y) {}

Point::Point(const int* a)
    : fX(a[0]), fY(a[1]) {}

Point::Point(const Point& p)
    : fX(p.fX), fY(p.fY) {}

Point::~Point() {}

void Point::Print()const
{
   //print vector parameters
   std::cout << "X: " << X() << ", Y: " << Y() << std::endl;
}

bool operator == (const Point&a, const Point&b)
{
    return ((a.X() == b.X()) && (a.Y() == b.Y())) ? true : false;
}
