#ifndef NEURON_NETWORK_H_
#define NEURON_NETWORK_H_

#include <vector>
#include <fstream>
#include <cstdlib>
#include "NeuronLayer.h"
using namespace std;

class NeuralNetwork {
public:
    NeuralNetwork(int, int, int, int);
	NeuralNetwork();
    vector<double> calculate(vector<double>);
	vector<NeuronLayer*> layers();
	NeuronLayer* layerAt(int);

	bool save(char*);
	bool load(char*);

private:
    int m_inputs;
    int m_layers;
    int m_outputs;
    int m_neuronsPerLayer;
    vector<NeuronLayer*> m_nlayers;
};

#endif
