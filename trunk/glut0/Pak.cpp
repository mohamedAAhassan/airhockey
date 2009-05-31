#include "Pak.h"
#include <stdio.h>
#include <cmath>

Pak::Pak() {}

Pak::Pak(Point2 start, Point2 gibanje1, double radij, double frik, bool glavni, char* ime1){
	pozicija=start;
	gibanje=gibanje1;
	r=radij;
	trenje=frik;
	jeglavni=glavni;
	ime=ime1;
}
Pak::~Pak() {}

void Pak::UpdatePos(double gol) {
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

char* Pak::getIme() {
	return ime;
}
