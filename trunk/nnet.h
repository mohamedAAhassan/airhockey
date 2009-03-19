#ifndef __NNET_H
#define __NNET_H

#include "neuron.h"

class NeuralNet
{
private:
	int input, hidden, output; // stevilo: vhodnih, skritih in izhodnih neuronov
	double alfa; // hitrost ucenja
	double min_err; // najmanjsa dovoljena napaka

	vector<Neuron> hiddenNeurons; // notranji(skriti) nevroni
	vector<Neuron> outputNeurons; // izhodni nevroni
	
public:
	// ctor
	NeuralNet(int input, int hidden, int output);
	
	void init( /* todo */ ); // inicializacija nevronske mreze
	void train( /* todo */ ); // ucenje nevronske mreze
};

#endif
