#include "Pak.h"
#include <cmath>

Pak::Pak() {}

Pak::Pak(Point2 start, Point2 gibanje1, double radij, double frik, double s, double v){
	pozicija=start;
	gibanje=gibanje1;
	r=radij;
	trenje=frik;
	sirina=s;
	visina=v;
}
Pak::~Pak() {}

void Pak::UpdatePos() {

	if (abs((pozicija+gibanje).getX())>=sirina-r) {
		gibanje.setX(gibanje.getX()*-1);
			}
	if (abs((pozicija+gibanje).getY())>=visina-r) {
		gibanje.setY(gibanje.getY()*-1);
			}

	pozicija=pozicija+gibanje;
	gibanje=gibanje*trenje;
}
Point2 Pak::getPos() {
	return pozicija;
}
Point2 Pak::getDir() {
	return gibanje;
}
void Pak::setDir(double a, double b) {
	gibanje.setX(a);
	gibanje.setY(b);
}
void Pak::setPos(double a, double b){
	pozicija.setX(a);
	pozicija.setY(b);
}
void Pak::setPos(Point2 a){
	pozicija.setX(a.getX());
	pozicija.setY(a.getY());
}
double Pak::getFri(){return trenje;}
double Pak::getRad(){return r;}
void Pak::setRad(double ra){r=ra;}
void Pak::setFri(double fri){trenje=fri;}
void Pak::setLastPos(double a, double b) {
	lastpos.setX(a);
	lastpos.setY(b);
}
Point2 Pak::getLastPos(){
					   
	return lastpos;
}
