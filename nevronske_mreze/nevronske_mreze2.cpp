#include <iostream>
#include <vector>
#include <cstdlib>
#include <stdarg.h>
#include <sstream>
using namespace std;

#include "NeuralNetwork.h"
#include "LearnNeuralNetwork.h"
#include "NNParser.h"
#include "DeltaError.h"

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

void print_weights2(NeuralNetwork* network) {
	vector<NeuronLayer*> layers = network->layers();
	for(int i=0; i<layers.size(); i++) {
		vector<Neuron*> neurons = layers[i]->neurons();
		for(int j=0; j<neurons.size(); j++) {
			vector<double> weights = neurons[j]->weights();
			for(int k=0; k<weights.size(); k++) {
				std::cout << "w" << (j+1) << "." << (k+1) << "(" << (i+1) << "):" << weights[k] <<std::endl;
			}
			std::cout << " O" << (j+1) << "(" << (i+1) << "):" << neurons[j]->activationValue() <<std::endl;
		}
	}
	std::cout << std::endl;
}

void testPrimer1() {

}

int main(int argc, char** argv) {
	NeuralNetwork network(6, 1, 30, 2);
	
	vector< vector<double> > x;
	vector< vector<double> > d;

	CNNParser parser("vzorci.txt");
	parser.parse();

	int num = 0;
	for(int i=0; i<parser.getPatterns().getM(); i++) {
		if(i%5 == 0) {
			num++;
			vector<double> temp;
			int size = parser.getPatterns().returnVector(i).size()-1;
			temp.push_back(parser.getPatterns().returnVector(i)[6]);
			temp.push_back(parser.getPatterns().returnVector(i)[7]);
			d.push_back(temp);
			
			vector<double> temp2 = parser.getPatterns().returnVector(i);
			temp2.pop_back();
			temp2.pop_back();
			temp2.pop_back();
			temp2.pop_back();
			temp2.pop_back();
			temp2.pop_back();
			temp2.pop_back();
			temp2.pop_back();

			x.push_back(temp2);
		}
	}
	
	cout << "Stevilo vzorcev: " << num << endl;

	LearnNeuralNetwork networkLearn(&network);
	//networkLearn.learn(x, d, 0.5, new Error(0.00145, x.size()));
	networkLearn.learn(x, d, 0.5, new DeltaError(0.0007, x.size()));
	//networkLearn.learn(x, d, 0.5, new Error(0.1, x.size()));

	char filename[50];
	sprintf(filename, "utezi_%d_%dx%d.txt", num, network.layers().size()-1, network.layerAt(0)->neurons().size());
	cout << filename <<endl;

	network.save(filename);
	
    cin.get();
    return 0;
}

