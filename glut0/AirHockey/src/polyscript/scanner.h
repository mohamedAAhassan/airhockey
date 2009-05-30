#ifndef __SCANNER_H
#define __SCANNER_H

#include "token.h"

#define MAX_STATE 7
#define START_STATE 0
#define NO_EDGE -1


class Scanner
{
private:
    string input;
    Token lastToken; // trenutni osnovni leks. simbol
    int row, column;  // stolpec, vrstica vhodne datoteke

    int automata[MAX_STATE+1][256]; // tabela prehodov
    int finite[MAX_STATE+1]; // tabela koncnih stanj
//    string reswdWords[RESERWED_WORDS]; // = { "f", "sin", "cos", "tan", "ctg", "log", "sqrt" };

    void initAutomat();  // inicializacija tabele prehodov in tabele koncnih stanj
    bool isReservedWord(string s);

    // naaslednje stanje vemo, ce poznamo trenutno stanje in znak na vhodu
    // z pogledom v tabelo
    int getNextState(int aState, int aChar) const;
    // ali je koncno stanje?
    bool isFiniteState(int aState) const;
    int getFiniteState(int aState) const;
    // preberi naslednji znak na vhodu
    int read();
    bool eof();
    int peek();




    // poisci naslednji osnovni leks. simbol
public:
    // ctor
    Scanner(string input);
    Scanner();
    void setInput(string _input);
    Token nextTokenImp();
    Token nextToken();
    Token currentToken();
};

#endif
