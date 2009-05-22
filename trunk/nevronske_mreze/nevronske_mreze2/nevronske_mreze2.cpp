// nevronske_mreze2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <stdarg.h>
using namespace std;

#include "NeuralNetwork.h"
#include "LearnNeuralNetwork.h"
#include "NNPArser.h"

void setWeight(NeuralNetwork* network, int layer, int neuron, int weight, double value) {
	network->layerAt(layer)->neuronAt(neuron)->setWeight(weight, value);
}

void setActivationValue(NeuralNetwork* network, int layer, int neuron, double value) {
	network->layerAt(layer)->neuronAt(neuron)->setActivationValue(value);
}

void addValues(vector< vector<double> > &x, int n, ...) {
	vector<double> temp;
	va_list arg;
	double value;
	va_start(arg, n); 
	for (int i=0; i<n; i++) {
		value = va_arg(arg, double);
		temp.push_back(value);
	}
	va_end(arg);
	x.push_back(temp);
}

void testNeuralNetwork(NeuralNetwork* network,  int n, ...) {
	vector<double> data;
	va_list arg;
	double value;
	va_start(arg, n); 
	for (int i=0; i<n; i++) {
		value = va_arg(arg, double);
		data.push_back(value);
	}
	va_end(arg);
	vector<double> output = network->calculate(data);
	for(int i=0; i<output.size(); i++) {
		cout << "o" << (i+1) << ": " << output[i];
		if(i+1 != output.size()) {
			cout << ", ";
		}
	}
	cout <<endl;
}

void print_input_values2(vector< vector<double> > x, vector< vector<double> > p) {
	for(int i=0; i<x.size(); i++) {
		for(int j=0; j<x[i].size(); j++) {
			std::cout << "x" << (j+1) << " = " << x[i][j] << ", ";
		}
		for(int j=0; j<p[i].size(); j++) {
			std::cout << "p" << (j+1) << " = " << p[i][j] << ", ";
		}
		std::cout << std::endl;
	}
}

void testPrimer1() {
	NeuralNetwork network(6, 1, 5, 2);
	
	vector< vector<double> > x;
	vector< vector<double> > d;

	CNNParser parser("vzorci.txt");
	parser.parse();

	for(int i=0; i<parser.getPatterns().getM(); i++) {
		vector<double> temp;
		int size = parser.getPatterns().returnVector(i).size()-1;
		temp.push_back(parser.getPatterns().returnVector(i)[size-1]);
		temp.push_back(parser.getPatterns().returnVector(i)[size]);
		d.push_back(temp);
		
		vector<double> temp2 = parser.getPatterns().returnVector(i);
		temp2.pop_back();
		temp2.pop_back();

		x.push_back(temp2);
	}

	//print_input_values2(x, d);

	LearnNeuralNetwork networkLearn(&network);
	networkLearn.learn(x, d, 0.5, 0.001);

	network.save("test2.txt");
}

void testPrimer2() {
	NeuralNetwork network(2, 2, 3, 2);

	setWeight(&network, 0, 0, 0, 0.5);
	setWeight(&network, 0, 0, 1, 0.2);
	setWeight(&network, 0, 1, 0, 0.4);
	setWeight(&network, 0, 1, 1, 0.6);
	setWeight(&network, 0, 2, 0, 0.1);
	setWeight(&network, 0, 2, 1, 0.2);
	setWeight(&network, 1, 0, 0, 0.10);
	setWeight(&network, 1, 0, 1, 0.20);
	setWeight(&network, 1, 0, 2, 0.25);
	setWeight(&network, 1, 1, 0, 0.55);
	setWeight(&network, 1, 1, 1, 0.45);
	setWeight(&network, 1, 1, 2, 0.15);
	setWeight(&network, 1, 2, 0, 0.35);
	setWeight(&network, 1, 2, 1, 0.35);
	setWeight(&network, 1, 2, 2, 0.60);
	setWeight(&network, 2, 0, 0, 0.30);
	setWeight(&network, 2, 0, 1, 0.35);
	setWeight(&network, 2, 0, 2, 0.45);
	setWeight(&network, 2, 1, 0, 0.35);
	setWeight(&network, 2, 1, 1, 0.25);
	setWeight(&network, 2, 1, 2, 0.30);

	setActivationValue(&network, 0, 0, 0.0);
	setActivationValue(&network, 0, 1, 0.0);
	setActivationValue(&network, 0, 2, 0.0);
	setActivationValue(&network, 1, 0, 0.0);
	setActivationValue(&network, 1, 1, 0.0);
	setActivationValue(&network, 1, 2, 0.0);
	setActivationValue(&network, 2, 0, 0.0);
	setActivationValue(&network, 2, 1, 0.0);

	vector< vector<double> > x;
	vector< vector<double> > d;
	
	addValues(x, 2, 0.05, 0.02);
	addValues(d, 2, 1.0, 0.0);
	addValues(x, 2, 0.09, 0.11);
	addValues(d, 2, 1.0, 0.0);
	addValues(x, 2, 0.12, 0.20);
	addValues(d, 2, 1.0, 0.0);
	addValues(x, 2, 0.15, 0.22);
	addValues(d, 2, 1.0, 0.0);
	addValues(x, 2, 0.20, 0.25);
	addValues(d, 2, 1.0, 0.0);
	addValues(x, 2, 0.75, 0.75);
	addValues(d, 2, 0.0, 0.0);
	addValues(x, 2, 0.80, 0.83);
	addValues(d, 2, 0.0, 0.0);
	addValues(x, 2, 0.82, 0.80);
	addValues(d, 2, 0.0, 0.0);
	LearnNeuralNetwork networkLearn(&network);
	networkLearn.learn(x, d, 0.3, 0.001);

	cout << "test: " <<endl;
	testNeuralNetwork(&network, 2, 0.90, 0.92);
	testNeuralNetwork(&network, 2, 0.40, 0.45);
	testNeuralNetwork(&network, 2, 0.10, 0.20);
	testNeuralNetwork(&network, 2, 0.15, 0.25);
	testNeuralNetwork(&network, 2, 0.70, 0.80);
	testNeuralNetwork(&network, 2, 0.50, 0.54);
	testNeuralNetwork(&network, 2, 0.60, 0.64);
}


int main(int argc, char** argv) {
    testPrimer1();
	//testPrimer2();
    cin.get();
    return 0;
}

