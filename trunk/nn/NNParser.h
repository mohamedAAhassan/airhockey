#ifndef __NNET_PARSER
#define __NNET_PARSER

#include <fstream>
#include <cstring>
#include <cstdlib>
#include <string>
#include "Matrix.h"

class CNNParser
{
private:
    CMatrix<double> patterns; // storage for patterns
    string filename;


public:
    CNNParser(string filename);
    int splitIntoTokens(int start, string input, string &output);

    bool parse();

    CMatrix<double> getPatterns() const;
    CMatrix<double>* getPatternsPtr();
};

#endif
