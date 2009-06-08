#ifndef ERROR_H_
#define ERROR_H_

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Error {
	public:
		Error(double, int);
		virtual ~Error();
		
		virtual void addLocalError(std::vector<double>&, std::vector<double>&);
		virtual double getError();
		bool isErrorSmallEnough();
	protected:
		int m_samples;
		double m_max;
		double m_localError;
};

#endif