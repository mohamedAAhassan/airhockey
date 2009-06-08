#include "NeuronLayer.h"

NeuronLayer::NeuronLayer(int inputsPerNeuron, int numberOfNeurons)
    : m_inputsPerNeuron(inputsPerNeuron), m_numberOfNeurons(numberOfNeurons) {
    for(int i=0; i<m_numberOfNeurons; i++) {
        m_neurons.push_back(new Neuron(m_inputsPerNeuron));
    }
}

vector<double> NeuronLayer::calculate(vector<double> inputs) {
    vector<double> result;
    for(int i=0; i<m_numberOfNeurons; i++) {
        result.push_back(m_neurons[i]->calculate(inputs));
    }
    return result;
}

Neuron* NeuronLayer::neuronAt(int index) {
	return m_neurons[index];
}

vector<Neuron*> NeuronLayer::neurons() {
	return m_neurons;
}

/*int NeuronLayer::numNeurons() const
{
	return this->m_numberOfNeurons;
}

void NeuronLayer::setNumNeurons(int num)
{
	this->m_numberOfNeurons = num;
}*/