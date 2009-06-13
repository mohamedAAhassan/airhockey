#ifndef __VERTEX_H
#define __VERTEX_H

#include "Point3.h"

class Vertex
{
//private:
public:
    Point3 point;

//public:
    Vertex();
    Vertex(const Point3 &p);
    Vertex(Vertex &vtx);

    bool operator<(const Vertex& vtx) const;
    bool operator>(const Vertex& vtx) const;
    bool operator==(const Vertex& vtx) const;
    Vertex operator=(const Vertex& vtx);
    Vertex* operator=(const Vertex *vtx);
};

#endif
