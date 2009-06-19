#include "NeuralNetwork.h"
#include <iostream>
#include "stdafx.h"

NeuralNetwork::NeuralNetwork(int inputs, int layers, int neuronsPerLayer, int outputs)
    : m_inputs(inputs), m_layers(layers), m_neuronsPerLayer(neuronsPerLayer), m_outputs(outputs) {

    m_nlayers.push_back(new NeuronLayer(m_inputs, neuronsPerLayer));

    for(int i=0; i<m_layers-1; i++) {
        m_nlayers.push_back(new NeuronLayer(neuronsPerLayer, neuronsPerLayer));
    }

    m_nlayers.push_back(new NeuronLayer(neuronsPerLayer, m_outputs));
}

NeuralNetwork::NeuralNetwork() { }

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

bool NeuralNetwork::load(char *filename)
{
	char current[30];
//	int st_utezi = 0;

	fstream file(filename, fstream::in);

	if ( !file.is_open() )
	{
		cout<<"Error: file not found."<<endl;
		return false;
	}

	// 1. st. notranjih plasti
	file >> current;
	this->m_layers = atoi(current);

	// 2. st. vhod. neuronov
	file >> current;
	this->m_inputs = atoi(current);

	// 3. st. vhod. neuronov za vsako notranjo plast
	file >> current;
	this->m_neuronsPerLayer = atoi(current);

	// 3. st. vhod. neuronov za zunanjo plast
	file >> current;
	this->m_outputs = atoi(current);

	// zgradimo mrezo
    m_nlayers.push_back(new NeuronLayer(this->m_inputs, this->m_neuronsPerLayer));

    for(int i=0; i<m_layers-1; i++) {
        m_nlayers.push_back(new NeuronLayer(this->m_neuronsPerLayer, this->m_neuronsPerLayer));
    }

    m_nlayers.push_back(new NeuronLayer(this->m_neuronsPerLayer, this->m_outputs));

	// utezi in prag za vhodno plast
	// za vsak neuron:
	for ( int i=0; i< this->m_neuronsPerLayer; i++ )
	{
		// aktivacija
		file >> current;
		this->layerAt(0)->neuronAt(i)->setActivationValue(atof(current));
		
		// utezi // 	void setWeight(int, double);
		for ( int j=0; j<this->layerAt(0)->neuronAt(i)->numberOfInputs(); j++ )
		{
			file >> current;
			this->layerAt(0)->neuronAt(i)->setWeight(j, atof(current));
		}
	}

	// utezi in prag za notranje plasti
	// za vsako plast:
	for ( int k=1; k< this->m_nlayers.size()-1; k++) // od plasti na indeksu 1 do izhodne, z zadnjim indeksom
	{
		for ( int i=0; i< this->m_neuronsPerLayer; i++ )
		{
			// aktivacija
			file >> current;
			this->layerAt(k)->neuronAt(i)->setActivationValue(atof(current));
			
			for ( int j=0; j<this->layerAt(k)->neuronAt(i)->numberOfInputs(); j++ )
			{
				file >> current;
				this->layerAt(k)->neuronAt(i)->setWeight(j, atof(current));
			}
		}
	}
	
	// utezi in prag za izhodno plast
	// za vsak neuron:
	for ( int i=0; i< this->m_outputs; i++ )
	{
		int ouput_layer_index = this->m_nlayers.size()-1;
		// aktivacija
		file >> current;
		this->layerAt(ouput_layer_index)->neuronAt(i)->setActivationValue(atof(current));
		
		// utezi // 	void setWeight(int, double);
		for ( int j=0; j<this->layerAt(ouput_layer_index)->neuronAt(i)->numberOfInputs(); j++ )
		{
			file >> current;
			this->layerAt(ouput_layer_index)->neuronAt(i)->setWeight(j, atof(current));
		}
	}

	return true;
}

bool NeuralNetwork::save(char* filename)
{
	fstream file(filename, fstream::out);

	if ( !file.is_open() )
	{
		cout<<"Error: file not open."<<endl;
		return false;
	}

	/*
	st. notranjih plasti
	st. vhodnih neuronov
	st. neuronov za vsako skrito plast
	st. izhodnih neuronov
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
	file << this->m_neuronsPerLayer << endl;
	file << this->m_outputs << endl; // st. izhodnih neuronov

	// sharni utezi neuronov za vhodno plast
	//for ( int i=0; i< this->m_inputs; i++ )
	for ( int i=0; i< this->layerAt(0)->neurons().size(); i++ )
	{
		// za vsak neuron shran aktivacijo in utezi
		file << this->layerAt(0)->neuronAt(i)->activationValue() << endl; // altivacija

		for ( int j=0; j<this->layerAt(0)->neuronAt(i)->numberOfInputs(); j++ )
			file << this->layerAt(0)->neuronAt(i)->weightAt(j) << endl;
	}

	// shrani utezi neuronov za vsako notranjo plast
	for ( int k=1; k< this->m_nlayers.size()-1; k++) // od plasti na indeksu 1 do izhodne, z zadnjim indeksom
	{
		for ( int i=0; i< this->m_neuronsPerLayer; i++ ) // 
		{
			//int ouput_layer_index = this->m_nlayers.size()-1;
			// za vsak neuron shrani aktivacijo in utezi
			file << this->layerAt(k)->neuronAt(i)->activationValue() << endl; // aktivacija

			for ( int j=0; j<this->layerAt(k)->neuronAt(i)->numberOfInputs(); j++ )
				file << this->layerAt(k)->neuronAt(i)->weightAt(j) << endl;
		}
	}

	// shrani utezi neuronov za izhodno plast
	for ( int i=0; i< this->m_outputs; i++ )
	{
		int ouput_layer_index = this->m_nlayers.size()-1;
		file << this->layerAt(ouput_layer_index)->neuronAt(i)->activationValue() << endl; // aktivacija

		for ( int j=0; j<this->layerAt(ouput_layer_index)->neuronAt(i)->numberOfInputs(); j++ )
			file << this->layerAt(ouput_layer_index)->neuronAt(i)->weightAt(j) << endl;
	}

	file.close();
	return true;
}

