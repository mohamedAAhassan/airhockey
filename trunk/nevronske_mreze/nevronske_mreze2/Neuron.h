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
	void addWeight(double newValue);
	double activationValue();
	void setActivationValue(double);

	void setNumberOfInputs(int num);
	int numberOfInputs() const;

private:
    int m_numberOfInputs;
	double m_activationValue;
    vector<double> m_wights;

    double activationFunction(double);
};

#endif
