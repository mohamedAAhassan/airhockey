#ifndef __NEURON_H
#define __NEURON_H

#include <vector>
#include <cmath>

using namespace std;

class Neuron
{
private:


public:
	Neuron(); 

	vector<double> x; // vektor vhodov
	vector<double> w; // vektor utezi

	double Y(); // izhod
};

#endif
