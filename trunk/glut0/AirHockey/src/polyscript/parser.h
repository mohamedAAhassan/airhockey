#ifndef __PARSER_H
#define __PARSER_H

#include <cmath>
#include <cstdlib>
#include "scanner.h"
#include "polygon.h"

class Parser
{
    private:
        Scanner *scanner;

        bool E(CPolygonsList &list);//(double &val);
       // bool D(double &val);
       // bool DD(double inVal, double &val);
        bool T(CPolygonsList &list, CPolygon *currentPoly);//(double &val);
        bool TT(CPolygonsList &list, CPolygon *currentPoly);//(double inVal, double &val);
       // bool B(double &val);
        //bool BB(double inVal, double &val);
       // bool C(double &val);
        bool L(CPolygonsList &list, CPolygon *currentPoly);
        bool F(CPolygonsList &list, CPolygon *currentPoly);//(double &val);
        bool N();//(string &val);
       // bool O1(string &val);
       // bool O2(string &val);

       // bool __OK_D(double &val, string func);

       // double op(string lexem, double a, double b);
       // double func(string lexem, double val);

       // double identificatorValue;*/


    public:
        Parser(Scanner *scanner);
        Parser();
        void setScanner(Scanner *scanner);
        bool parse(/*double &val*/);
        bool parse(CPolygonsList &list, string str);

        Vertex crossProduct(const Vertex &a, const Vertex &b);
        bool rightTurn(Vertex &p1, Vertex &p2, Vertex &p3);
};

#endif
