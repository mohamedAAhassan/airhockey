#ifndef __GRAPHIC_H
#define __GRAPHIC_H

#include <GL/glut.h>

#include "Point3.h"

class GraphicInterface
{
private:
    Point3 currentPos; // za moveTo(), lineTo()

public:
    GraphicInterface();

    bool init();

    void drawDot(double x, double y);
    void drawDot(const Point3 &p);
    void drawDot(const Point3 &p, float r, float g, float b);

    void moveTo(Point3 p);
    void lineTo(Point3 p);

    Point3 windowToOpenGLCoords(int x, int y);
    void perspective();
};
#endif
