#ifndef __TOKEN_H
#define __TOKEN_H

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

template <typename T>
inline string toString(const T& t)
{
  stringstream ss;
  ss<<t;
  return ss.str();
}

enum Type
{
    LEXERROR = -1,
    IGNORE = 7,
    INTEGER = 1,
  //  OPERATOR = 2,
    SEPARATOR = 4,
    TERMINATOR = 6,
    STRING = 2
};

class Token
{

private:
    string lexem; // leks. el.
    int column;   // stolpec, kjer se pojavi prvi znak lexema
    int row;      // vrstica, kjer se pojavi prvi znak lexema
    int lex_type;    // osnovni lex. simbol(tip?)
    bool eof;     // konec datoteke

public:
    // ctor
    Token(const string &lexem, int column, int row, int lex_type, bool eof);
    Token();
    bool getEof();
    int getType();
    string getLexem();
    string getTokenInfo();
};

#endif

