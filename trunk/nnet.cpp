#include "nnet.h"

// ctor
NeuralNet::NeuralNet(int input, int hidden, int output) : input(input), hidden(hidden), output(output)
{
	// todo
}

void NeuralNet::init() // inicializacija nevronske mreze
{
	srand(time(NULL)); // "random" seed
	
	// inicializacija skrite plasti
	for(int i=0; i<this->hidden; i++) // naredi i skritih nevronov
	{
		Neuron current;
		for(int j=0; j<input; j++) // utezi imajo toliko, kot vhodni nevroni; utezi so inicializirane na neko majhno vrednost
			current.w.push_back(LITTLE_RAND); // malo nakljucno st. med -0.2 in 0.2 ;)
						
		this->hiddenNeurons.push_back(current); // nevron, napolnjen z nakljucnimi utezmi, gre na notranjo plast vektorjev
	}

	// inicializacija izhodne plasti
	for(int i=0; i<this->output; i++) // naredi i skritih nevronov
	{
		Neuron current;
		for(int j=0; j<hidden; j++) // utezi imajo toliko, kot vhodni nevroni; utezi so inicializirane na neko majhno vrednost
			current.w.push_back(LITTLE_RAND); // malo nakljucno st. med -0.2 in 0.2 ;)
									
		this->outputNeurons.push_back(current); // nevron, napolnjen z nakljucnimi utezmi, gre na notranjo plast vektorjev
	}
}

void train( /* todo */ ) // ucenje nevronske mreze
{
	// todo
}
