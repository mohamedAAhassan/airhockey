#include "Vertex.h"

Vertex::Vertex() {}

Vertex::Vertex(const Point3 &p)
{
    this->point = p;
}

Vertex::Vertex(Vertex &vtx) : point(vtx.point) {}

bool Vertex::operator<(const Vertex& vtx) const
{
    return this->point.angle < vtx.point.angle;
}

bool Vertex::operator>(const Vertex& vtx) const
{
    return this->point.angle > vtx.point.angle;
}


bool Vertex::operator==(const Vertex& vtx) const
{
    return this->point.r == vtx.point.r && this->point.angle == vtx.point.angle;
}

Vertex Vertex::operator=(const Vertex& vtx)
{
    this->point = vtx.point;

    return *this;
}

Vertex* Vertex::operator=(const Vertex *vtx)
{
    this->point = vtx->point;

    return this;
}
