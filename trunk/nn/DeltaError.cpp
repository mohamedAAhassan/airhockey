#include "DeltaError.h"

#include <cstdlib>

DeltaError::DeltaError(double max, int samples) : Error(max, samples) {
}

void DeltaError::addLocalError(std::vector<double> &outputs, std::vector<double> &expeced) {
	double error = 0.0;
	for(int i=0; i<outputs.size(); i++) {
		error += expeced[i] - outputs[i];
	}
	m_localError += error / outputs.size();
}

double DeltaError::getError() {
	return abs(Error::getError());
}
