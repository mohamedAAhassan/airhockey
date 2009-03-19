#include "neuron.h"


// ctor
Neuron::Neuron()
{
	this->x.push_back(-1);  // na prvi indeks gre -1
}


double Neuron::Y()
{
	double a = 0.0; // aktivacija
	//double y = 0.0; // izhod

	for(int i=0; i<this->x.size(); i++)
		a += w[i] * x[i]; // aktivacija je vsota (utezi*vhodi) = SUM(Wi * Xi)

	return  1/(1 + pow(2.7182, -a)); // sigmoida; 1 / 1 + e^(-a)

	//return y;
		
}
