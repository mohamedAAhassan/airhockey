#include "Point2.h"
#include <cmath>

Point2::Point2() {x=0;y=0;}

Point2::Point2(double a, double b){
	x=a;
	y=b;
}

Point2::~Point2() {}

double Point2::getX() {
	return x;
}

double Point2::getY() {
	return y;
}

void Point2::setX(double a){
	x=a;
}

void Point2::setY(double a){
	y=a;
}
double Point2::Lenght() {
	return sqrt(pow(x,2)+pow(y,2));
}
Point2 Point2::operator* (double a){
	x*=a;
	y*=a;
	return *this;
}
Point2 Point2::operator+ (Point2 a) {
	x+=a.getX();
	y+=a.getY();
	return *this;
}
Point2 Point2::operator- (Point2 a) {
	x-=a.getX();
	y-=a.getY();
	return *this;
}
double Point2::dot(Point2 a){
	return x*a.getX()+y*a.getY();
}