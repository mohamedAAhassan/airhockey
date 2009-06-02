#include "scanner.h"

#include "stdafx.h"

// ctor
Scanner::Scanner(string input) : input(input), row(1), column(1)
{
    this->initAutomat();

   // cout<<"rm: "<<input.at(input.end()-1)<<endl;
 //   this->input.erase(input.end()-1);
  //  int pos = input.find(';');
   // cout<<"pozicija: "<<pos<<endl;
}

Scanner::Scanner() :  row(1), column(1)
{
    this->input = "";
    this->initAutomat();
}

void Scanner::setInput(string _input)
{
    this->input.assign(_input);
    this->nextToken();
  //  this->initAutomat();
}



void Scanner::initAutomat()  // inicializacija tabele prehodov in tabele koncnih stanj
{
    // tabela prehodov je prazna
    for(int i=0; i<=MAX_STATE; i++)
    {
            for(int j=0; j<256; j++)
            automata[i][j] = NO_EDGE;
    }

    // ce smo v stanju 0 ali 1 ali 7 ob cifri, gremo v stanje 1
    for(int i='0'; i<='9'; i++)
            automata[0][i] = automata[1][i] /*=  automata[7][i]*/ = 1;

    automata[0]['-']  = 1;

    // pri '.' tudi gremo v stanje 1
    automata[0]['.'] =  automata[1]['.'] = 1;


    // ce smo v stanju 0 ali 2 ob znaku, gremo v stanje 2
    for(int i='a'; i<'z'; i++)  // x je identifikator, y in z nista v abecedi
            automata[0][i] = automata[2][i] = 2;

    // ce smo v stanju 2 ob cifri, gremo v stanje 1
    for(int i='0'; i<='9'; i++)
            automata[2][i] = 2;


    // ce smo v stanju 0 ob -, gremo v stanje 3
 //   automata[0]['-']  = 3;

    // ce smo v stanju 3 ob >, gremo v stanje 4
  //  automata[3]['>'] = 4;
  automata[0][','] = 4;

    // ce smo v stanju 0 ob :, gremo v 4 (separator)
    automata[0][':'] = 4;

    // ce smo v stanju 0 ob +, gremo v 4 (separator)
    automata[0]['+'] = 4;


    // terminator, gremo v 6
    automata[0][';'] = 6;


    // ce smo v stanju 0 ob praznem mestu, gremo v 7
    automata[0]['\n'] = automata[0][' '] = automata[0]['\t'] = 7;

    // ce smo v stanju 6 ob praznem mestu, gremo v stanje 6
    automata[7]['\n'] = automata[7][' '] = automata[7]['\t'] = 7;

    ////////////////////////////

    // stanje 0 ni koncno, vrnemo leks. napako
    finite[0] = LEXERROR; // this->tLexError;

    // stanje 1 je koncno, vrnemo osnovni leks. simbol integer
    finite[1] = INTEGER; //this->tInteger;

    // stanje 2 je koncno, vrnemo os. leks. simb. niz
    finite[2] = STRING; //this->tOperator;

    // stanje 4 je koncno, vrnemo leks. simb. separator
    finite[4] = SEPARATOR; //this->tSeparator;

     // stanje 4 je koncno, vrnemo leks. simb. separator
    finite[6] = TERMINATOR; //this->tSeparator;

    // stanje 4 je koncno, to se prezre
    finite[7] = IGNORE; //this->tIgnore;
}


// naaslednje stanje vemo, ce poznamo trenutno stanje in znak na vhodu
// z pogledom v tabelo
int Scanner::getNextState(int aState, int aChar) const
{
    if(aChar == -2)
            return NO_EDGE;

    return this->automata[aState][aChar]; // achar je dejansko ascii vrednost ;)
}

// ali je koncno stanje?
bool Scanner::isFiniteState(int aState) const
{
    return this->finite[aState] != LEXERROR;
}

int Scanner::getFiniteState(int aState) const
{
    return finite[aState];
}

// preberi naslednji znak na vhodu
int Scanner::read()
{
    int temp = (int)input[0]; //[input.size()-1];//input->get(); // get() -> extracts character in vrne vred.
    // pobrisi zadnji znak
    input.erase(0, 1);
    column ++; // stolpec ++

    if(temp = '\n')
    {
            row ++; // vrstica = vrstica +1
            column = 1; // stolpec = 1;
    }

    return temp;
}

bool Scanner::eof()
{
    return input.size() == 0 ? true : false; //peek() == -1; // ce je znak, ki ga preberemom, leks. -1, smo na koncu
}

int Scanner::peek()
{
    //    return input->peek(); // samp prebere znak v inputu in ga vrne, ga ne brise
    return (int)input[0]; //[input.size()-1];
}

Token Scanner::nextToken()
{
    return lastToken = nextTokenImp();
}

Token Scanner::currentToken()
{
    return lastToken;
}


Token Scanner::nextTokenImp()
{
    int currentState = START_STATE;
    string lexem;

    int startColumn = this->column;
    int startRow = this->row;

    do
    {
            // ob trenutnem stanju in vhodnemu znaku pojdi v novo stanje
            int tempState = this->getNextState(currentState, peek());

            if (tempState != NO_EDGE)
            {
                // prehod v novo stanje mozen
                currentState = tempState;

                // zdruzi prebrani znak v lexem
                lexem += this->peek();
                (char)this->read();
            }
            else
            {
                // prehod ni mozen; ali je stanje koncno?
                if(this->isFiniteState(currentState))
                {
                        // stanje je koncno in vracamo osonovni leks. simbol
                        // se je lex. simbol niz, preverimo, ce je rezervirana beseda
                        Token token(lexem, startColumn, startRow, this->getFiniteState(currentState), eof());

                        if(token.getType() == IGNORE)
                        // presledke in nove vrstice prezremo
                            return this->nextToken();
                        else
                        {
                       /* if(currentState == STRING)
                        {
                                if(!this->isReservedWord(lexem))
                                return Token("ERROR: " + lexem + " ni rezervirana beseda.", startColumn, startRow,  LEXERROR, eof()); // ce ni, vrnemo sint. napako
                        }*/

                            return token;
                        }
                }
                else
                        // stanje ni koncno, vrnemo leks. napako
                        return Token("ERROR:" + lexem, startColumn, startRow,  LEXERROR, eof());

            }
    } while(true);
}

