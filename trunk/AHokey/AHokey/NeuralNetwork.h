#ifndef NEURON_NETWORK_H_
#define NEURON_NETWORK_H_

#include <vector>
#include "NeuronLayer.h"
using namespace std;

class NeuralNetwork {
public:
	NeuralNetwork();
    NeuralNetwork(int, int, int, int);
    vector<double> calculate(vector<double>);

private:
    int m_inputs;
    int m_layers;
    int m_outputs;
    int m_neuronsPerLayer;
    vector<NeuronLayer*> m_nlayers;
};

#endif
