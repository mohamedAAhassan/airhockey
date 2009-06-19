#ifndef _GRAPHICS_H
#define	_GRAPHICS_H

#define DEG2RAD 0.017453278

#define SIRINA 1.2
#define DOLZINA 3
#define VISINA 0.1

#include <GL/glut.h>
#include <cmath>
#include "Point2.h"
#include "polyscript/parser.h"

#define RED 1.0, 0.0, 0.0
#define GREEN 0.0, 1.0, 0.0
#define BLUE 0.0, 0.0, 1.0
#define WHITE 1.0, 1.0, 1.0
#define BLACK 0.0, 0.0, 0.0

struct Color
{
    float r, g, b;

    void set(float _r, float _g, float _b)
    {
        r = _r; g = _g; b = _b;
    }
};

class CGraphics {
public:
    CGraphics();
    CGraphics(const CGraphics& orig);

    // 3D stuff
    void drawWall(double x1, double y1, double x2, double y2);
    void drawWall(Point2 p1, Point2 p2);
    void wallTo(double x1, double y1);
    void wallTo(Point2 p);
    void drawPolys(CPolygonsList &list, double x, double y, double z);

    virtual ~CGraphics();

    // 2D stuff
    void drawDot(double x, double y);
    void drawDot(Point2 &p);
    void drawDot(Point2 &p, float r, float g, float b);

    void drawCircle(double x, double y, double z, double r, unsigned tris);
    void drawCircle(Point2 &p, double r, unsigned tris);

    void moveTo(Point2 p);
    void lineTo(Point2 p);

    void setColor(const Color &color);
    void setColor(float r, float g, float b);
    
private:
    double wallHeight;
    Point2 currentPos; // za moveTo(), lineTo()

};

#endif	/* _GRAPHICS_H */

