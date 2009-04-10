#ifndef NEURON_H_
#define NEURON_H_

#include "Neuron.h"
#include <vector>
using namespace std;

class Neuron {
public:
    Neuron(int);
    double calculate(vector<double>);
	vector<double> weights();
	double weightAt(int);
	void setWeight(int, double);
	double activationValue();
	void setActivationValue(double);

private:
    int m_numberOfInputs;
	double m_activationValue;
    vector<double> m_wights;

    double activationFunction(double);
};

#endif
