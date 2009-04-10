#include "StdAfx.h"
#include "NeuralNetwork.h"
#include <iostream>

NeuralNetwork::NeuralNetwork(int inputs, int layers, int neuronsPerLayer, int outputs)
    : m_inputs(inputs), m_layers(layers), m_neuronsPerLayer(neuronsPerLayer), m_outputs(outputs) {
    m_nlayers.push_back(new NeuronLayer(m_inputs, neuronsPerLayer));
    for(int i=0; i<m_layers-1; i++) {
        m_nlayers.push_back(new NeuronLayer(neuronsPerLayer, neuronsPerLayer));
    }
    m_nlayers.push_back(new NeuronLayer(neuronsPerLayer, m_outputs));
}

vector<double> NeuralNetwork::calculate(vector<double> inputs) {
    vector<double> result = inputs;
    for(int i=0; i<m_layers+1; i++) {
		//std::cout << "layer " << i <<std::endl;
        result = m_nlayers[i]->calculate(result);
    }
    return result;
}

vector<NeuronLayer*> NeuralNetwork::layers() {
	return m_nlayers;
}

NeuronLayer* NeuralNetwork::layerAt(int index) {
	return m_nlayers[index];
}

