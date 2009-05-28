#ifndef NEURON_H_
#define NEURON_H_

#include "Neuron.h"
#include <vector>
using namespace std;

class Neuron {
public:
    Neuron(int);
    double calculate(vector<double>);

private:
    int m_numberOfInputs;
    vector<double> m_wights;

    double activationFunction(double);
};

#endif
