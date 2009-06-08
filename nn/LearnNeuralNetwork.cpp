#include <iostream>
#include <cmath>
#include "LearnNeuralNetwork.h"

void print_weights(NeuralNetwork* network) {
	vector<NeuronLayer*> layers = network->layers();
	for(int i=0; i<layers.size(); i++) {
		vector<Neuron*> neurons = layers[i]->neurons();
		for(int j=0; j<neurons.size(); j++) {
			vector<double> weights = neurons[j]->weights();
			for(int k=0; k<weights.size(); k++) {
				std::cout << "w" << (j+1) << "." << (k+1) << "(" << (i+1) << "):" << weights[k] <<std::endl;
			}
			std::cout << " O" << (j+1) << "(" << (i+1) << "):" << neurons[j]->activationValue() <<std::endl;
		}
	}
	std::cout << std::endl;
}

void print_input_values(vector< vector<double> > x, vector< vector<double> > p) {
	for(int i=0; i<x.size(); i++) {
		for(int j=0; j<x[i].size(); j++) {
			std::cout << "x" << (j+1) << " = " << x[i][j] << ", ";
		}
		for(int j=0; j<p[i].size(); j++) {
			std::cout << "p" << (j+1) << " = " << p[i][j] << ", ";
		}
		std::cout << std::endl;
	}
}

LearnNeuralNetwork::LearnNeuralNetwork(NeuralNetwork* neuralNetwork) {
	m_neuralNetwork = neuralNetwork;
	m_layers = m_neuralNetwork->layers();
}

LearnNeuralNetwork::~LearnNeuralNetwork() {}

void LearnNeuralNetwork::learn(vector< vector<double> > x, vector< vector<double> > p, double learningSpeed, Error* error) {
	m_learningSpeed = learningSpeed;

	print_input_values(x, p);
	print_weights(m_neuralNetwork);
	cin.get();
	do {
		for(int j=0; j<x.size(); j++) {
			calculateLayerOutputs(x[j]);

			vector<double> gradients;
			updateOutputLayer(gradients, p[j]);

			updateHiddenLayers(gradients);
			
			//localError += calculateLocalError(m_layerOutputs[m_layerOutputs.size()-1], p[j]);
			error->addLocalError(m_layerOutputs[m_layerOutputs.size()-1], p[j]);
			m_layerOutputs.clear();

			updateWeights();

			/*std::cout << "x1: " << x[j][0] << ", x2: " << x[j][1] << ", p1: " << p[j][0] << std::endl;
			print_weights(m_neuralNetwork);
			cin.get();*/
		}
		cout << error->getError() <<endl;
	} while (!error->isErrorSmallEnough());
}

void LearnNeuralNetwork::calculateLayerOutputs(vector<double> &input) {
	m_layerOutputs.push_back(input);
	m_newWeights.push_back(vector< vector<double> >());
	for(int i=0; i<m_layers.size(); i++) {
		m_layerOutputs.push_back(m_layers[i]->calculate(m_layerOutputs[i]));
		m_newWeights.push_back(vector< vector<double> >());
		for(int k=0; k<m_layers[i]->neurons().size(); k++) {
			m_newWeights[i+1].push_back(vector<double>());
		}
	}
}

void LearnNeuralNetwork::updateOutputLayer(vector<double> &gradients, vector<double> &p) {
	for(int i=0; i<m_layerOutputs[m_layers.size()].size(); i++) {
		Neuron* current = m_layers[m_layers.size()-1]->neuronAt(i);
		double gradient = devirative(m_layerOutputs[m_layers.size()][i]) * (p[i] - m_layerOutputs[m_layers.size()][i]);
		for(int k=0; k<current->weights().size(); k++) {
			//std::cout << "w" << (i+1) << "." << (k+1) << "(" << m_layers.size() << ") = " << m_layers[m_layers.size()-1]->neuronAt(i)->weightAt(k) << " + " << learningSpeed << " * " << gradient << " * " << m_layerOutputs[m_layers.size() - 1][k] << std::endl;
			//m_layers[m_layers.size()-1]->neuronAt(i)->setWeight(k, m_layers[m_layers.size()-1]->neuronAt(i)->weightAt(k) + learningSpeed*gradient*m_layerOutputs[m_layers.size() - 1][k]);
			double newWeightValue = current->weightAt(k) + m_learningSpeed*gradient*m_layerOutputs[m_layers.size() - 1][k];
			m_newWeights[m_layers.size()][i].push_back(newWeightValue);
		}
		//std::cout << "O" << (i+1) << "(" << m_layers.size() << ") = " << m_layers[m_layers.size()-1]->neuronAt(i)->activationValue() << " + " << learningSpeed << " * " << gradient << " * -1" << std::endl;
		current->setActivationValue(current->activationValue() + m_learningSpeed*gradient*(-1));
		gradients.push_back(gradient);
	}
}

void LearnNeuralNetwork::updateHiddenLayers(vector<double>& gradients) {
	vector<double> noviGradienti;
	for(int i=m_layers.size()-2; i>=0; i--) {
		vector<Neuron*> neurons = m_layers[i]->neurons();
		for(int k=0; k<neurons.size(); k++) {
			vector<double> weights = neurons[k]->weights();
			double temp = 0.0;
			for(int m=0; m<gradients.size(); m++) {
				//std::cout << " [" << gradients[m] << " * " << m_layers[i+1]->neuronAt(m)->weightAt(k) << "] ";
				temp += gradients[m] * m_layers[i+1]->neuronAt(m)->weightAt(k);
			}
			//std::cout << endl;
			//std::cout << "G" << (k+1) << "(" << i+1 << ") = " << m_layerOutputs[i+1][k] << " * (1 - " << m_layerOutputs[i+1][k] << ") * " << temp << std::endl;
			double gradient = devirative(m_layerOutputs[i+1][k]) * temp;
			noviGradienti.push_back(gradient);
			for(int l=0; l<weights.size(); l++) {
				//std::cout << "w" << (k+1) << "." << (l+1) << "(" << i+1 << ") = " << weights[l] << " + " << learningSpeed << " * " << gradient << " * " << m_layerOutputs[i][l] << std::endl;
				//neurons[k]->setWeight(l, weights[l] + learningSpeed*gradient*m_layerOutputs[i][l]);
				double newWeightValue = weights[l] + m_learningSpeed*gradient*m_layerOutputs[i][l];
				m_newWeights[i+1][k].push_back(newWeightValue);
			}
			neurons[k]->setActivationValue(neurons[k]->activationValue() + m_learningSpeed*gradient*(-1));
		}
		gradients = noviGradienti;
	}
}

double LearnNeuralNetwork::devirative(double value) {
	//return value * (1 - value);
	return 1 - pow(value, 2);
}

double LearnNeuralNetwork::calculateLocalError(std::vector<double> &outputs, std::vector<double> &expeced) {
	double error = 0.0;
	for(int l=0; l<outputs.size(); l++) {
		error += 0.5 * pow(expeced[l] - outputs[l], 2.0);
	}
	return error;
}

void LearnNeuralNetwork::updateWeights() {
	for(int o=1; o<m_newWeights.size(); o++) {
		for(int p=0; p<m_newWeights[o].size(); p++) {
			for(int r=0; r<m_newWeights[o][p].size(); r++) {
				//std::cout << "w" << (p+1) << "." << (r+1) << "("<< o << ") = " << m_newWeights[o][p][r] << std::endl;
				m_neuralNetwork->layerAt(o-1)->neuronAt(p)->setWeight(r, m_newWeights[o][p][r]);
			}
		}
	}
	m_newWeights.clear();
}
