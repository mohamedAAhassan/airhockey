#include "Error.h"

Error::Error(double max, int samples) : m_max(max), m_samples(samples) {
	m_localError = 0;
}

Error::~Error() {
	
}

void Error::addLocalError(std::vector<double> &outputs, std::vector<double> &expeced) {
	double error = 0.0;
	for(int i=0; i<outputs.size(); i++) {
		error += 0.5 * pow(expeced[i] - outputs[i], 2.0);
	}
	m_localError += error;
}

double Error::getError() {
	return m_localError / (double)m_samples;
}

bool Error::isErrorSmallEnough() {
	bool t = getError() <= m_max;
	m_localError = 0;
	return t;
}
