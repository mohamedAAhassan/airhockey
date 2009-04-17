#include "nnetparser.h"

using namespace std;

//template<typename T>
CNNParser::CNNParser(string filename) : filename(filename) { }

int CNNParser::splitIntoTokens(int start, string input, string &output) // returns position, saves token into output
{
    output = "";
    for(unsigned i=start; i<input.size(); i++)
    {
        if(input[i] != ' ' && input[i] != '\n' && input[i] != '\t' && input[i] != '\0' && input[i] != '\r') /// !!!
            output += input[i];
        else
            return i + 1;
    }


    return output == "" ? -1 : input.size();
  //return input.size();
}

unsigned i=0;

//template<typename T>
bool CNNParser::parse()
{
    ifstream file;
    file.open(this->filename.c_str());

    if(!file.is_open())
        return false;

    string buff;

    while(!file.eof())
    {

        getline(file, buff);

        unsigned j = 0; // counter for columns
        // split line into tokens
        string token;
        int spos = this->splitIntoTokens(0, buff, token);

        if(spos == -1)
            return true;

        this->patterns.addRows(1);  // add line to matrix

        if(this->patterns.getN() <= j)
            this->patterns.addColumns(1);
        this->patterns.insert(atof(token.c_str()), i, j);

        while(buff.size() != (unsigned)spos)
        {
            j ++;

            if(this->patterns.getN() <= j)
                this->patterns.addColumns(1);

            spos = this->splitIntoTokens(spos, buff, token);

            this->patterns.insert(atof(token.c_str()), i, j);

        }
        i ++;
    }

    return true;
}

//template<typename T>
CMatrix<double> CNNParser::getPatterns() const
{
    return this->patterns;
}

//template<typename T>
CMatrix<double>* CNNParser::getPatternsPtr()
{
    return &(this->patterns);
}
