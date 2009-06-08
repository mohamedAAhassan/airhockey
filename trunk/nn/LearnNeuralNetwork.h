#ifndef LEARN_NEURAL_NETWORK_
#define LEARN_NEURAL_NETWORK_

#include "NeuralNetwork.h"
#include "Error.h"

class LearnNeuralNetwork
{
public:
	LearnNeuralNetwork(NeuralNetwork*);
	~LearnNeuralNetwork();

	void learn(vector< vector<double> >, vector< vector<double> >, double, Error*);

private:
	NeuralNetwork* m_neuralNetwork;
	double m_learningSpeed;
	vector<NeuronLayer*> m_layers;
	vector< vector<double> > m_layerOutputs;
	vector< vector< vector<double> > > m_newWeights;

	void calculateLayerOutputs(vector<double>&);
	void updateOutputLayer(vector<double>&, vector<double>&);
	void updateHiddenLayers(vector<double>&);
	double calculateLocalError(vector<double>&, vector<double>&);
	void updateWeights();
	double devirative(double);
};

#endif
