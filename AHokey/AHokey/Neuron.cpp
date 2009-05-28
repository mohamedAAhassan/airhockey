#include "StdAfx.h"
#include "Neuron.h"
#include <cmath>
#include <iostream>

Neuron::Neuron(int numberOfInputs) : m_numberOfInputs(numberOfInputs) {
    for(int i=0; i<m_numberOfInputs; i++) {
        m_wights.push_back(1.0);
    }
}

double Neuron::calculate(vector<double> inputs) {
	for(int i=0; i<m_numberOfInputs; i++) {
		std::cout << inputs[i] << "  ";
	}
	std::cout << std::endl;
    double result = 0.0;
    for(int i=0; i<m_numberOfInputs; i++) {
        result += (inputs[i] * m_wights[i]);
    }
    return activationFunction(result);
}

double Neuron::activationFunction(double input) {
	//return input;
	return (1.0 / (1.0 + exp((-input)/1)));
}
