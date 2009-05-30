#ifndef POLYGON_H_INCLUDED
#define POLYGON_H_INCLUDED

#include <iostream>
#include <vector>

using namespace std;

struct Vertex
{
    double x, y, z;

    Vertex(double x, double y) : x(x), y(y), z(0) { }
    Vertex(double x, double y, double z) : x(x), y(y), z(z) { } // za vektorski produkt
    Vertex() : x(0), y(0), z(0) { }

    Vertex operator-(const Vertex &p)
    {
       return Vertex(this->x - p.x, this->y - p.y, this->z - p.z);
    }

    void dump() const
    {
        cout<<"x: "<<x<<"   y: "<<y<<endl;
    }
};

class CPolygon
{
private:


    vector<Vertex> vertices;
    string name;

public:
    CPolygon();
    CPolygon(string name);

    void setName(string name);
    string getName() const;
    void addVertex(double x, double y);
    void dump() const;
    unsigned size() const;
    vector<Vertex> getVertices() const;

};

class CPolygonsList
{
private:
    vector<CPolygon> polys;

public:
    void addPolygon(const CPolygon &poly);
    void dump() const;
    unsigned size() const;
    bool contains(string name);
    vector<CPolygon> getPolys() const;
};


#endif // POLYGON_H_INCLUDED
