#include "graphic.h"

GraphicInterface::GraphicInterface()
{
   // glPointSize(4.0);
   this->currentPos.x = 0.0;
   this->currentPos.y = 0.0;
   this->currentPos.z = 0.0;
}

bool GraphicInterface::init()
{
    glPointSize(4.0);
    return true;
}

void GraphicInterface::drawDot(double x, double y)
{
    glBegin(GL_POINT);
        glVertex3f(x, y, 0.0);
    glEnd();
}

void GraphicInterface::drawDot(const Point3 &p)
{
    glBegin(GL_POINT);
        glVertex3f(p.x, p.y, p.z);
    glEnd();
}

void GraphicInterface::drawDot(const Point3 &p, float r, float g, float b)
{
    glColor3f(r, g, b);
    glBegin(GL_POINT);
        glVertex3f(p.x, p.y, p.z);
    glEnd();
}

void GraphicInterface::moveTo(Point3 p)
{
    this->currentPos = p;
}

void GraphicInterface::lineTo(Point3 p)
{
    glBegin(GL_LINE);
        glVertex3f(this->currentPos.x, this->currentPos.y, this->currentPos.z);
        glVertex3f(p.x, p.y, p.z);
    glEnd();
}

Point3 GraphicInterface::windowToOpenGLCoords(int x, int y)
{
    GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLfloat winX, winY, winZ;
	GLdouble posX, posY, posZ;

	glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
	glGetDoublev( GL_PROJECTION_MATRIX, projection );
	glGetIntegerv( GL_VIEWPORT, viewport );

	winX = (float)x;
	winY = (float)viewport[3] - (float)y;
	glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );

	gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

    return Point3(posX, posY, 0.0);
}

void GraphicInterface::perspective()
{
    glMatrixMode(GL_PROJECTION);   //changes the current matrix to the projection matrix

    //sets up the projection matrix for a perspective transform
    gluPerspective(45,     //view angle
                 1.0,    //aspect ratio
                 10.0,   //near clip
                 200.0); //far clip
    glMatrixMode(GL_MODELVIEW);   //changes the current matrix to the modelview matrix

    glLoadIdentity();
}
