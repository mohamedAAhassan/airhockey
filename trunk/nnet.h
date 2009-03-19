#ifndef __NNET_H
#define __NNET_H

#include <ctime>
#include <cstdlib>
#include "neuron.h"

#define LITTLE_RAND (rand()%2-rand()%2)/10 // tole bi naj generiralo stevila med -0.2 in 0.2 ;)

class NeuralNet
{
private:
	int input, hidden, output; // stevilo: vhodnih, skritih in izhodnih neuronov
	double alfa; // hitrost ucenja
	double min_err; // najmanjsa dovoljena napaka

public:
	// ctor
	NeuralNet(int input, int hidden, int output);
	
	void init(); // inicializacija nevronske mreze
	void train( /* todo */ ); // ucenje nevronske mreze

	vector<Neuron> hiddenNeurons; // notranji(skriti) nevroni
	vector<Neuron> outputNeurons; // izhodni nevroni
};

#endif
