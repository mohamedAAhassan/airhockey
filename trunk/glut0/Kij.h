#include "Pak.h"
#ifndef KIJ_H
#define KIJ_H

class Kij: public Pak {
protected:
	int stevec;
public:
	Kij(Point2 start, Point2 gibanje1, double radij, double frik, bool glavni, char* ime1);
};
#endif