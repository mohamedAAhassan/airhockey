#ifndef __POINT_3
#define __POINT_3

#include <iostream>
#include <cmath>

using namespace std;

class Point3
{
public:
    double x;
    double y;
    double z;

    double angle, r;

    Point3(); //: x(0.0), y(0.0), z(0.0) {};
    Point3(const Point3 &p);
    Point3(double x, double y, double z);
    double Length();
    Point3 Normalize();

    double operator*(Point3 &p); // skalarni produkt vektorjev

    Point3 &operator=(const Point3 &a);
    Point3 operator*(double t); // produkt vektorja s skalarjem
    Point3 operator+(Point3 &p);
    Point3 operator-(Point3 &p);
    Point3 operator^(Point3 &p); // vektorski produkt
    bool operator ==(const Point3& p) const;
    bool operator !=(const Point3 &a) const;

    void dumpInfo();
    void calcPolarCoords();
    void calcPolarCoords(const Point3 &p);
};

////
Point3 crossProduct(const Point3 &a, const Point3 &b);

#endif
