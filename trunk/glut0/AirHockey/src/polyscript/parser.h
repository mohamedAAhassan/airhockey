#ifndef __PARSER_H
#define __PARSER_H

#include <cmath>
#include <cstdlib>
#include "scanner.h"
#include "polygon.h"

#include "../stdafx.h"

class Parser
{
    private:
        Scanner *scanner;

        bool E(CPolygonsList &list);
        bool T(CPolygonsList &list, CPolygon *currentPoly);
        bool TT(CPolygonsList &list, CPolygon *currentPoly);
        bool L(CPolygonsList &list, CPolygon *currentPoly);
        bool F(CPolygonsList &list, CPolygon *currentPoly);
        bool N();


    public:
        Parser(Scanner *scanner);
        Parser();
        void setScanner(Scanner *scanner);
        bool parse();
        bool parse(CPolygonsList &list, string str);

		void compileFile(CPolygonsList &list, char *file);
		void compileString(CPolygonsList &list, string str);

        Vertex crossProduct(const Vertex &a, const Vertex &b);
        bool rightTurn(Vertex &p1, Vertex &p2, Vertex &p3);
};

#endif
