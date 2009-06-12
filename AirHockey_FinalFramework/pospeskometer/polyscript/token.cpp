#include "token.h"

#include "stdafx.h"

// ctor
Token::Token(const string &lexem, int column, int row, int lex_type, bool eof)
        : lexem(lexem), column(column), row(row), lex_type(lex_type), eof(eof) { }

Token::Token() : lexem("") { }

bool Token::getEof()
{
    return this->eof;
}

int Token::getType()
{
    return this->lex_type;
}

string Token::getLexem()
{
    return this->lexem;
}

string Token::getTokenInfo()
{
    string tip;
    switch(this->lex_type)
    {
            case LEXERROR:
            tip = "leksikalna napaka";
            break;

            case IGNORE:
            tip = "prazen znak";
            break;

            case INTEGER:
            tip = "stevilo";
            break;

            case TERMINATOR:
            tip = "terminator";
            break;

//            case OPERATOR:
         //   tip = "operator";
         //   break;

            case SEPARATOR:
            tip = "separator";
            break;

      //      case IDENTIFICATOR:
       //     tip = "";
       //     break;

            case STRING:
            tip = "niz";
            break;
    }

    return lexem + " - vrstica: " + toString(column) + " stolpec: " +  toString(row) + " tip: " + tip;
}
