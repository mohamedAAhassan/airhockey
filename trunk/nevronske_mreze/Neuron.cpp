#include "Neuron.h"
#include <cmath>
#include <iostream>

Neuron::Neuron(int numberOfInputs) : m_numberOfInputs(numberOfInputs) {
    for(int i=0; i<m_numberOfInputs; i++) {
        m_wights.push_back((rand()%10)/10.0-0.5);
		//m_wights.push_back(0.5);
    }
	m_activationValue = 0.0;
}

double Neuron::calculate(vector<double> inputs) {
	/*for(int i=0; i<m_numberOfInputs; i++) {
		std::cout << inputs[i] << "  ";
	}
	std::cout << std::endl;*/
    double result = 0.0;
    for(int i=0; i<m_numberOfInputs; i++) {
        result += (inputs[i] * m_wights[i]);
    }
	result -= m_activationValue;
    return activationFunction(result);
}

vector<double> Neuron::weights() {
	return m_wights;
}

double Neuron::weightAt(int index) {
	return m_wights[index];
}

void Neuron::setWeight(int weightIndex, double newValue) {
	m_wights[weightIndex] = newValue;	
}

void Neuron::addWeight(double newValue) {
	m_wights.push_back(newValue);	
}

double Neuron::activationValue() {
	return m_activationValue;
}

void Neuron::setActivationValue(double value) {
	m_activationValue = value;
}

double Neuron::activationFunction(double input) {
	//return input;
	return (1.0 / (1.0 + exp((-input)/1)));
}

int Neuron::numberOfInputs() const {
	return this->m_numberOfInputs;
}

void Neuron::setNumberOfInputs(int num)
{
	this->m_numberOfInputs = num;
}