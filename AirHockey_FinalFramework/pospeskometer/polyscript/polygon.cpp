#include "polygon.h"

#include "stdafx.h"

/***************************
    CPolygon class
 ***************************/
CPolygon::CPolygon() {  }

CPolygon::CPolygon(string name) : name(name) {  }

void CPolygon::setName(string name)
{
    this->name = name;
}

string CPolygon::getName() const
{
    return this->name;
}

void CPolygon::addVertex(double x, double y)
{
    this->vertices.push_back(Vertex(x, y));
}

void CPolygon::dump() const
{
    cout<<endl<<this->name<<':'<<endl;
    for (int i=0; i<this->vertices.size(); vertices[i++].dump()) ;
}

unsigned CPolygon::size() const
{
    return this->vertices.size();
}

vector<Vertex> CPolygon::getVertices() const
{
    return this->vertices;
}

Vertex CPolygon::getTransformedVertex(unsigned i, double a, double b)
{
	return Vertex((this->vertices[i].x -0.5) * a, (this->vertices[i].y - 0.5) * b);
	//return Vertex();
}


/***************************
    CPolygonList class
 ***************************/
void CPolygonsList::addPolygon(const CPolygon &poly)
{
    this->polys.push_back(poly);
}

void CPolygonsList::dump() const
{
    for (unsigned i=0; i<this->polys.size(); polys[i++].dump()) ;
}

bool CPolygonsList::contains(string name)
{
    for ( int i=0; i<this->polys.size(); i++ )
    {
        if ( polys[i].getName() == name )
            return true;
    }

    return false;
}

unsigned CPolygonsList::size() const
{
    return this->polys.size();
}

vector<CPolygon> CPolygonsList::getPolys() const
{
    return this->polys;
}