#ifndef NEURON_LAYER_H_
#define NEURON_LAYER_H_

#include "Neuron.h"
#include <vector>
using namespace std;

class NeuronLayer {
public:
        NeuronLayer(int, int);
        vector<double> calculate(vector<double>);
		vector<Neuron*> neurons();
		Neuron* neuronAt(int);

private:
        int m_inputsPerNeuron;
        int m_numberOfNeurons;
        vector<Neuron*> m_neurons;
};

#endif
