#ifndef POINT2_H
#define POINT2_H

#include "polyscript/polygon.h"

class Point2 {
private:
	double x;
	double y;
public:
	Point2();
	Point2(double a, double b);
    Point2(Vertex &v);
	~Point2();
	double getX();
	double getY();
	void setX(double a);
	void setY(double a);
        void set(double x, double y);

	double Lenght();
	Point2 operator* (double a);
	Point2 operator+ (Point2 a);
	Point2 operator- (Point2 a);
	double dot(Point2 a);

};
#endif