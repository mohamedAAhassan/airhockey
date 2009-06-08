#ifndef DELTAERROR_H_
#define DELTAERROR_H_

#include "Error.h"

#include <vector>

class DeltaError : public Error {
	public:
		DeltaError(double, int);
		
		void addLocalError(std::vector<double>&, std::vector<double>&);
		double getError();
};

#endif