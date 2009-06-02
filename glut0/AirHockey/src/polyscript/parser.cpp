//#include "parser.h"

#include "stdafx.h"


// ctor
Parser::Parser(Scanner *scanner) : scanner(scanner)
{
    scanner->nextToken();
}

Parser::Parser()
{
    this->scanner = new Scanner;
}

void Parser::setScanner(Scanner *scanner)
{
    this->scanner = scanner;
    this->scanner->nextToken();
}


bool Parser::parse(CPolygonsList &list, string str)
{
    this->scanner->setInput(str);
    return E(list) && scanner->currentToken().getEof();
}

bool Parser::E(CPolygonsList &list)//(double &val)
{
    string a = scanner->currentToken().getLexem();
    if(scanner->currentToken().getType() == STRING || scanner->currentToken().getLexem() == "") // lik zacnemo z imenom ali pa lika sploh ne podamo
    {
        CPolygon *poly = new CPolygon(scanner->currentToken().getLexem()); // DELETE does not exist yet!
        scanner->nextToken();

        if(scanner->currentToken().getLexem() == ":")
        {
            scanner->nextToken();
            return T(list, poly);
        }

        delete poly;
        poly = NULL;

        cout<<"Error: expected ':' "<<endl;
        cout<<scanner->currentToken().getTokenInfo()<<endl;
        return false;
    }

    cout<<"Error: expected identifier "<<endl;
    return false;
}

bool Parser::T(CPolygonsList &list, CPolygon *currentPoly)
{
    bool ok = F(list, currentPoly);
    return ok && TT(list, currentPoly);
}

bool Parser::TT(CPolygonsList &list, CPolygon *currentPoly)//(double inVal, double &val)
{
    if ( scanner->currentToken().getLexem() == "," )
    {
        scanner->nextToken();
      //  double tempVal;
        bool ok = F(list, currentPoly);
        return ok && TT(list, currentPoly);   // vrni vrednost, glede na operator
    }
    else
    {
        return true; // epsilon
    }
}

bool Parser::L(CPolygonsList &list, CPolygon *currentPoly)//(double inVal, double &val)
{
    if ( scanner->currentToken().getLexem() == "+" )
    {
        // lik daj na seznam likov
        list.addPolygon(*currentPoly);

        // pobrisi trenutni poly
        delete currentPoly;
        currentPoly = NULL;
       // return true;
       scanner->nextToken();
       return E(list);
    }
    else if ( scanner->currentToken().getLexem() == ";" )
    {
        // lik daj na seznam likov
        list.addPolygon(*currentPoly);

        // pobrisi trenutni poly
        delete currentPoly;
        currentPoly = NULL;

        return true;
    }
    else
    {
      //  val = inVal;
        return true; // epsilon
    }
}

bool Parser::F(CPolygonsList &list, CPolygon *currentPoly)//(double &val)
{
    if ( scanner->currentToken().getType() == INTEGER )
    {
        double x = atof(scanner->currentToken().getLexem().c_str());
        scanner->nextToken();

        if ( scanner->currentToken().getType() == INTEGER )
        {
            double y = atof(scanner->currentToken().getLexem().c_str());
            if (!list.contains(currentPoly->getName())) // ze obstaja lik z tem imenom?
            {
                if ( currentPoly->size() > 3 )
                {
                        Vertex v(x, y);

                            if ( this->rightTurn(currentPoly->getVertices().at(currentPoly->size()-1), v, currentPoly->getVertices().at(currentPoly->size()-2) ))
                            {
                                // ni ok
                                cout<<"Semantic error, polygon should not be convex!"<<endl;
                                return false;
                            }


                        else
                        {
                            // ok
                            currentPoly->addVertex(x, y);

                            scanner->nextToken();
                            return L(list, currentPoly);
                        }
                    }
                    else
                    {
                        currentPoly->addVertex(x, y);

                        scanner->nextToken();
                        return L(list, currentPoly);
                    }
                }
                cout<<"Semantic error, polygon with given name alreadys exists!"<<endl;
                return false;
        }

        cout<<"Error: expected coordinate y"<<endl;
        return false;
    }

    cout<<"Error: expected coordinate y"<<endl;
    return false;
}

Vertex Parser::crossProduct(const Vertex &a, const Vertex &b)
{
    return Vertex(
        a.y*b.z - a.z*b.y,
        a.z*b.x - a.x*b.z,
        a.x*b.y - a.y*b.x
        );
}

bool Parser::rightTurn(Vertex &p1, Vertex &p2, Vertex &p3)
{
       // Point3 cross = crossProduct(p3-p1, p2-p1);
    Vertex cross = crossProduct( p2-p1,p3-p1);
    return cross.z <= 0 ? true : false;
      //  return true;
}

void Parser::compileString(CPolygonsList &list, string str)
{



   // Parser parser;
   // string i_str;
    //bool p = this->parse(list, str);

    if (!this->parse(list, str))
       cout<<"Error while compiling."<<endl;


    cout<<endl<<"------------ DONE -------------"<<endl;
    list.dump();
}

void Parser::compileFile(CPolygonsList &list, char *file)
{
    fstream polyfile(file, fstream::in);

    if (!polyfile.is_open())
        cout<<"Error opening polygon file. "<<endl;

   // Parser parser;
    string i_str;
    bool p;

    int line = 1;
    while (!polyfile.eof())
    {
        // read line and parse it :)
        getline(polyfile, i_str);
        p = this->parse(list, i_str);

        if (!p)
       // {
            cout<<"Error, polygon at line: "<< line << endl;
          //  break;
      //  }

        line ++;
    }


    cout<<endl<<"------------ DONE -------------"<<endl;
    list.dump();
}





