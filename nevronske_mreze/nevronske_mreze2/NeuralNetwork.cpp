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

bool NeuralNetwork::saveNeuralNetwork(char* filename)
{
	fstream file(filename, fstream::out);

	if ( !file.is_open() )
	{
		cout<<"Error: file not open."<<endl;
		return false;
	}

	/*
	prve 3 vrstice:
	st. notranjih plasti
	st. vhodnih neuronov
	...
	st. neuronov za vsako skrito plast
	...
	st. izhodnih neuronov
	st. vhodov neurona
	aktivacija
	...
	utezi vhodne plasti
	...
	utezi izhodnih plasti
	...
	utezi izhodnih plasti
	...
	*/
	file << this->m_layers << endl; // st. skritih plasti
	file << this->m_inputs << endl; // st. vhodnih neuronov
	for ( int i=1; i<=this->m_layers; i++ )   // za vsako skrito plat izpisi st. neuronov
		file << this->layerAt(i)->numNeurons() << endl;

	file << this->m_outputs << endl; // st. izhodnih neuronov

	// sharni utezi neuronov za vhodno plast
	for ( int i=0; i< this->m_inputs; i++ )
	{
		// za vsak neuron shrani: st. vhodov, aktivacijo in utezi
		file << this->layerAt(0)->neuronAt(i)->numberOfInputs() << endl;
		file << this->layerAt(0)->neuronAt(i)->activationValue() << endl; // altivacija

		for ( int j=0; j<this->layerAt(0)->neuronAt(i)->numberOfInputs(); j++ )
			file << this->layerAt(0)->neuronAt(i)->weightAt(j) << endl;
	}

	// shrani utezi neuronov za vsako notranjo plast
	for ( int k=1; k< this->m_nlayers.size()-1; k++) // od plasti na indeksu 1 do izhodne, z zadnjim indeksom
	{
		for ( int i=0; i< this->m_nlayers[k]->numNeurons(); i++ ) // 
		{
			//int ouput_layer_index = this->m_nlayers.size()-1;
			// za vsak neuron shrani: st. vhodov, aktivacijo in utezi
			file << this->layerAt(k)->neuronAt(i)->numberOfInputs() << endl;
			file << this->layerAt(k)->neuronAt(i)->activationValue() << endl; // aktivacija

			for ( int j=0; j<this->layerAt(k)->neuronAt(i)->numberOfInputs(); j++ )
				file << this->layerAt(k)->neuronAt(i)->weightAt(j) << endl;
		}
	}

	// shrani utezi neuronov za izhodno plast
	for ( int i=0; i< this->m_outputs; i++ )
	{
		int ouput_layer_index = this->m_nlayers.size()-1;
		// za vsak neuron shrani: st. vhodov, aktivacijo in utezi
		file << this->layerAt(ouput_layer_index)->neuronAt(i)->numberOfInputs() << endl;
		file << this->layerAt(ouput_layer_index)->neuronAt(i)->activationValue() << endl; // altivacija

		for ( int j=0; j<this->layerAt(ouput_layer_index)->neuronAt(i)->numberOfInputs(); j++ )
			file << this->layerAt(ouput_layer_index)->neuronAt(i)->weightAt(j) << endl;
	}
	//file << this->layerAt(0)->

	file.close();
	return true;
}

