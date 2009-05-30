#include "Point2.h"
#ifndef PAK_H
#define PAK_H

class Pak {
protected:
	Point2 pozicija;
	Point2 lastpos;
	Point2 gibanje;
	double r;
	double trenje;
	double sirina;
	double visina;
public:
	Pak();
	Pak(Point2 start, Point2 gibanje1, double radij, double frik,double s, double v);
	~Pak();
	void UpdatePos();
	Point2 getPos();
	Point2 getDir();
	void setLastPos(double a, double b);
	Point2 getLastPos();
	void setDir(double a, double b);
	void setPos(double a, double b);
	void setPos(Point2 a);
	double getFri();
	double getRad();
	void setRad(double ra);
	void setFri(double fri);
};
#endif