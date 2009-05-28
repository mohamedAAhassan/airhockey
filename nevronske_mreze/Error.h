#ifndef ERROR_H_
#define ERROR_H_

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Error {
	public:
		Error(double, int);
		~Error();
		
		void addLocalError(std::vector<double>&, std::vector<double>&);
		double getError();
		bool isErrorSmallEnough();
	private:
		int m_samples;
		double m_max;
		double m_localError;
};

#endif