#include "graphics.h"
#include "StdAfx.h"


CGraphics::CGraphics()
{
    this->wallHeight = 0.1; // default
    this->currentPos.set(0.0,0.0);

   // glPointSize(4.0);
  //  glLineWidth(2.0);
}

CGraphics::CGraphics(const CGraphics& orig)
{
    this->wallHeight = orig.wallHeight;//
    this->currentPos = orig.currentPos;
}

CGraphics::~CGraphics()
{
    // todo, if necessary
}

void CGraphics::drawWall(double x1, double y1, double x2, double y2)
{ 
    glPushMatrix();
	glBegin(GL_QUADS);
           // glColor4f(0.3,0.3,0.8, 0.5);
            // lowver vertices
            glVertex3f(x1,y1,0);
            glVertex3f(x2,y2,0);

            // upper vertices
            glVertex3f(x2,y2,this->wallHeight);
            glVertex3f(x1,y1,this->wallHeight);
        glEnd();
    glPopMatrix();
}

void CGraphics::drawWall(Point2 p1, Point2 p2)
{
    glPushMatrix();
	glBegin(GL_QUADS);
        //    glColor4f(0.3,0.3,0.8, 0.5);
            // lowver vertices
            glVertex3f(p1.getX(), p1.getY(),0);
            glVertex3f(p2.getX(),p2.getY(),0);

            // upper vertices
            glVertex3f(p2.getX(),p2.getY(),this->wallHeight);
            glVertex3f(p1.getX(),p2.getY(),this->wallHeight);
        glEnd();
    glPopMatrix();
}

void CGraphics::wallTo(double x1, double y1)
{
    glPushMatrix();
        glBegin(GL_QUADS);
       //     glColor4f(0.3,0.3,0.8, 0.5);
            // lowver vertices
            glVertex3f(this->currentPos.getX(),this->currentPos.getY(),0);
            glVertex3f(x1,y1,0);

            // upper vertices
            glVertex3f(x1,y1,this->wallHeight);
            glVertex3f(this->currentPos.getX(),this->currentPos.getY(),this->wallHeight);


        glEnd();
    glPopMatrix();
}
void CGraphics::wallTo(Point2 p)
{
    glPushMatrix();
        glBegin(GL_QUADS);
          //  glColor4f(0.3,0.3,0.8, 0.5);
            // lowver vertices
            glVertex3f(this->currentPos.getX(),this->currentPos.getY(),0);
            glVertex3f(p.getX(), p.getY(), 0);

            // upper vertices
            glVertex3f(p.getX(), p.getY(),this->wallHeight);
            glVertex3f(this->currentPos.getX(),this->currentPos.getY(),this->wallHeight);


        glEnd();
    glPopMatrix();
}

void CGraphics::drawPolys(CPolygonsList &list, double x, double y, double z)
{
    glPushMatrix();
        glTranslatef(x, y, z);

        glColor4f(1.0, 0.40, 0.24, 0.6);

        // izrisi vse poligone (loop)
        for (int i=0; i<list.size(); i++)
        {
            // izrisi vsak vertex v vsakem poligonu :)
            for (int j=0; j<list.getPolys()[i].size()-1; j++)
            {
                // lik1: 0 0, 0.2 0.3, 0.3 0;/
                // lik1: 0 0, 0.2 0.3, 0.3 0 + lik2: -0.1 0, -0.3 0.1, -0.1 0.3, 0 0.2, 0 0.1;/
                // lik1: 0 0, 0.2 0.3, 0.3 0 + lik2: 0 0, -0.5 0, -0.5 0.5, 0 0.5;/
                // lik3: 0 0.3, 0.2 0.2, 0.2 -0.2, 0.1 -0.3, -0.2 -0.1;/
                // lik4: 0 0, 0.2 0.3, 0.5 0.3, 0.6 0.1;/
                // lik5: 0 0, 0.5 1.3, 1 0;/

				//akec3.setDir(output[1]*DOLZINA/3,output[0]*SIRINA/3);

               //  lik2: 0 0, -0.5 0, -0.5 0.9, 0 0.5;
				this->moveTo(list.getPolys()[i].getTransformedVertex(j, SIRINA*2, DOLZINA*2));//  getVertices()[j]);
                this->wallTo(Point2(list.getPolys()[i].getTransformedVertex(j+1, SIRINA*2, DOLZINA*2))); //  getVertices()[j+1]));
            //    this->drawWall(Point2(list.getPolys()[i].getVertices()[j]), Point2(list.getPolys()[i].getVertices()[j+1]));

				//this->moveTo(list.getPolys()[i].getTransformedVertex(j, 1, 1));//  getVertices()[j]);
                //this->wallTo(Point2(list.getPolys()[i].getTransformedVertex(j+1, 1, 1))); //  getVertices()[j+1]));

                if ( j == list.getPolys()[i].size()-2)
                {
                      this->moveTo(list.getPolys()[i].getTransformedVertex(j+1, SIRINA*2, DOLZINA*2));  //getVertices()[j+1]);
                      this->wallTo(Point2(list.getPolys()[i].getTransformedVertex(0, SIRINA*2, DOLZINA*2))); //  getVertices()[0]));

                    //  this->moveTo(list.getPolys()[i].getTransformedVertex(j+1, 1, 1));  //getVertices()[j+1]);
                    //  this->wallTo(Point2(list.getPolys()[i].getTransformedVertex(0, 1, 1))); //  getVertices()[0]));
                   // this->drawWall(Point2(list.getPolys()[i].getVertices()[j+1]), Point2(list.getPolys()[i].getVertices()[0]));
                }

                //list.getPolys()[i].getVertices()[j]
            }
        }


    glPopMatrix();
}

// 2D stuff implementation
void CGraphics::drawDot(double x, double y)
{
    glPushMatrix();
        glBegin(GL_POINT);
            glVertex3f(x, y, 0.0);
        glEnd();
    glPopMatrix();
}

void CGraphics::drawDot(Point2 &p)
{
    glPushMatrix();
        glBegin(GL_POINT);
            glVertex3f(p.getX(), p.getY(), 0.0);
        glEnd();
    glPopMatrix();
}

void CGraphics::drawDot(Point2 &p, float r, float g, float b)
{
    glPushMatrix();
        glColor3f(r, g, b);
        glBegin(GL_POINT);
            glVertex3f(p.getX(), p.getY(), 0.0);
        glEnd();
    glPopMatrix();
}

void CGraphics::moveTo(Point2 p)
{
    this->currentPos = p;
}

void CGraphics::lineTo(Point2 p)
{
    glPushMatrix();
        glBegin(GL_LINE);
            glVertex3f(this->currentPos.getX(), this->currentPos.getY(), 0.0);
            glVertex3f(p.getX(), p.getY(), 0.0);
        glEnd();
    glPopMatrix();
}



void CGraphics::drawCircle(double x, double y, double z, double r, unsigned tris)
{
    glPushMatrix();
        glTranslatef(x, y, z);
        unsigned it_val = 360/tris;
        //  glBegin(GL_LINE_LOOP);
        glBegin(GL_TRIANGLE_FAN);
        for (int i=0; i < 360; i+=it_val) //0.017453278 9
        {
           double degInRad = i*DEG2RAD;
           glVertex3f(cos(degInRad)*r,sin(degInRad)*r, 0.0);
        }
        glEnd();
   glPopMatrix();


}
void CGraphics::drawCircle(Point2 &p, double r, unsigned tris)
{
    glPushMatrix();
        glTranslatef(p.getX(), p.getY(), 0.0);
        unsigned it_val = 360/tris;
        //  glBegin(GL_LINE_LOOP);
        glBegin(GL_TRIANGLE_FAN);
        for (int i=0; i < 360; i+=it_val) //0.017453278 9
        {
           double degInRad = i*DEG2RAD;
           glVertex3f(cos(degInRad)*r,sin(degInRad)*r, 0.0);
        }
        glEnd();
   glPopMatrix();
}

// color
void CGraphics::setColor(const Color &color)
{
    glColor3f(color.r, color.g, color.b);
}

void CGraphics::setColor(float r, float g, float b)
{
    glColor3f(r, g, b);
}

