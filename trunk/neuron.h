#ifndef __NEURON_H
#define __NEURON_H

#include <vector>
#include <cmath>

using namespace std;

class Neuron
{
private:
	Neuron(); 
	vector<double> x; // vektor vhodov
	vector<double> w; // vektor utezi

public:
	double Y(); // izhod
};

#endif
