//
#include <cmath>
#include <iostream>
#include "graphics.h"
#include "Point2.h"
#include "Pak.h"
#include "Kij.h"


using namespace std;

#define SIRINA 1.2
#define DOLZINA 3
#define VISINA 0.1

Pak pakec=Pak(Point2(0.40,-2.1),Point2(0.01, -0.03), 0.1,0.999, SIRINA, DOLZINA);
//Pak pakec2=Pak(Point2(0,-1),Point2(0, 0), 0.1,1, SIRINA, DOLZINA);
Kij pakec2=Kij(Point2(0,-1),Point2(0, 0), 0.12,1, SIRINA, DOLZINA);

CGraphics g_graphics;
CPolygonsList g_list;

GLfloat angle = 0.0;
double gol=0.25;


GLfloat WIN_X = 0;
GLfloat WIN_Y = 0;
GLfloat WIN_Z = 0;

struct table_s {
  GLfloat width;
  GLfloat height;
  GLfloat depth;
  GLfloat goal;
  GLfloat border;
};

bool initGame();

//const float DEG2RAD = 3.14159/180; // in graphics
 
void drawCircle(float radius)
{
   glBegin(GL_LINE_LOOP);
 
   for (int i=0; i < 360; i++)
   {
      float degInRad = i*DEG2RAD;
      glVertex2f(cos(degInRad)*radius,sin(degInRad)*radius);
   }
 
   glEnd();
}
void fillCircle(float radius)
{
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0, 0);
 
   for (int i=0; i <= 360; i++)
   {
      float degInRad = i*DEG2RAD;
      glVertex2f(cos(degInRad)*radius,sin(degInRad)*radius);
   }
 
   glEnd();
}

void Risi (void) {

	glRotatef(-100,1,0,0);
	glRotatef(sin(angle/100)*5,0,0,1);
	//glRotatef(angle/5,0,0,1);
	//glRotatef(angle/5,0,1,0);
	//glRotatef(-pakec.getPos().getX()*3,0,0,1);
	glBegin(GL_QUADS);


	glColor3f(1, 1, 1);
	
		glVertex3f(-SIRINA,DOLZINA,0);
		glVertex3f(SIRINA,DOLZINA,0);
		glVertex3f(SIRINA,-DOLZINA,0);
		glVertex3f(-SIRINA,-DOLZINA,0);

		// Stranice
	glColor4f(0.3,0.3,0.8, 0.5);
			//Zgornja
		glVertex3f(-SIRINA,DOLZINA,0);
		glVertex3f(-gol,DOLZINA,0);
		glVertex3f(-gol,DOLZINA,VISINA);
		glVertex3f(-SIRINA,DOLZINA,VISINA);

		glVertex3f(gol,DOLZINA,0);
		glVertex3f(SIRINA,DOLZINA,0);
		glVertex3f(SIRINA,DOLZINA,VISINA);
		glVertex3f(gol,DOLZINA,VISINA);
		
			//Stranska
		glVertex3f(SIRINA,DOLZINA,0);
		glVertex3f(SIRINA,-DOLZINA,0);

		glVertex3f(SIRINA,-DOLZINA,VISINA);
		glVertex3f(SIRINA,DOLZINA,VISINA);

			// Spodnja
		glNormal3f(-1, 0, 0);
		glVertex3f(SIRINA,-DOLZINA,0);
		glVertex3f(gol,-DOLZINA,0);
		glVertex3f(gol,-DOLZINA,VISINA);
		glVertex3f(SIRINA,-DOLZINA,VISINA);

		glNormal3f(-1, 0, 0);
		glVertex3f(-SIRINA,-DOLZINA,0);
		glVertex3f(-gol,-DOLZINA,0);
		glVertex3f(-gol,-DOLZINA,VISINA);
		glVertex3f(-SIRINA,-DOLZINA,VISINA);

				// stranska
		glVertex3f(-SIRINA,-DOLZINA,0);
		glVertex3f(-SIRINA,DOLZINA,0);
		glVertex3f(-SIRINA,DOLZINA,VISINA);
		glVertex3f(-SIRINA,-DOLZINA,VISINA);

	glEnd();


	
	// �rte na igri��u
	glBegin(GL_QUADS);

	glColor3f(0.8,0.6,0.6);
	glVertex3f(-SIRINA,0.06,0.005);
	glVertex3f(SIRINA,0.06,0.005);
	glVertex3f(SIRINA,-0.06,0.005);
	glVertex3f(-SIRINA,-0.06,0.005);

	glColor3f(0.6,0.6,0.8);
	glVertex3f(-SIRINA,0.60,0.005);
	glVertex3f(SIRINA,0.60,0.005);
	glVertex3f(SIRINA,0.64,0.005);
	glVertex3f(-SIRINA,0.64,0.005);

	glColor3f(0.6,0.6,0.8);
	glVertex3f(-SIRINA,-0.60,0.005);
	glVertex3f(SIRINA,-0.60,0.005);
	glVertex3f(SIRINA,-0.64,0.005);
	glVertex3f(-SIRINA,-0.64,0.005);
	glEnd();

	// Goli
	glColor3f(0.8,0.6,0.6);
	glBegin(GL_LINES);
	glVertex3f(gol+0.005, 3, 0.005);
	glVertex3f(gol+0.005, 2.5, 0.005);

	glVertex3f(-gol-0.005, 3, 0.005);
	glVertex3f(-gol-0.005, 2.5, 0.005);

	glVertex3f(gol+0.005, 2.5, 0.005);
	glVertex3f(-gol-0.005, 2.5, 0.005);

	glVertex3f(gol+0.005, -3, 0.005);
	glVertex3f(gol+0.005, -2.5, 0.005);

	glVertex3f(-gol-0.005, -3, 0.005);
	glVertex3f(-gol-0.005, -2.5, 0.005);

	glVertex3f(gol+0.005, -2.5, 0.005);
	glVertex3f(-gol-0.005, -2.5, 0.005);

	glEnd( );
	
	glPushMatrix();
	glTranslatef((float)SIRINA/2,(float)DOLZINA/2,0.005);
	drawCircle((float)SIRINA/4);
	drawCircle((float)SIRINA/50);
	glTranslatef((float)(-SIRINA),0,0);
	drawCircle((float)SIRINA/4);
	drawCircle((float)SIRINA/50);
	glTranslatef(0,(float)(-DOLZINA),0);
	drawCircle((float)SIRINA/4);
	drawCircle((float)SIRINA/50);
	glTranslatef((float)SIRINA,0,0);
	drawCircle((float)SIRINA/4);
	drawCircle((float)SIRINA/50);

	glPopMatrix();

       // g_graphics.moveTo(Point2(0.0,0.0));
      //  g_graphics.wallTo(0.7, 0.7);
        if (g_list.size() > 0)
            g_graphics.drawPolys(g_list, 0.0,0.0,0.0);

	// Pak
	// Preveri trk
	
	Point2 razdalja=pakec.getPos()-pakec2.getPos();
	if (razdalja.Lenght()<=(pakec.getRad()+pakec2.getRad())) {
		// teh trk :D
		//if (pakec2.getDir().Lenght()>0.1) {
			double deltaY = (pakec.getPos().getY() - pakec2.getPos().getY());
            double deltaX = (pakec.getPos().getX() - pakec2.getPos().getX());
            double Distance = deltaX * deltaX + deltaY * deltaY;
            double k1= (deltaX * pakec.getDir().getX() + deltaY * pakec.getDir().getY()) / Distance;
            double k2 = (deltaX * pakec.getDir().getY() - deltaY * pakec.getDir().getX()) / Distance;
            double k3 = (deltaX * pakec2.getDir().getX() + deltaY * pakec2.getDir().getY()) / Distance;
            double k4 = (deltaX * pakec2.getDir().getY() - deltaY * pakec2.getDir().getX()) / Distance;
            pakec.setDir(k3 * deltaX - k2 * deltaY,k3 * deltaY + k2 * deltaX);
			if (razdalja.Lenght()<=(pakec.getRad()+pakec2.getRad())) { 
				pakec.setPos(pakec.getPos()+razdalja*0.5);
			}
            //pakec2.setDir(k1 * deltaX - k4 * deltaY,k1 * deltaY + k4 * deltaX);
		/*}
		else {


			double dist = (pakec.getPos()-pakec2.getPos()).Lenght();
				double sumRadii = (pakec.getRad()+pakec2.getRad());
				dist -= sumRadii;
				if(pakec.getDir().Lenght() < dist){
				  //return false;
				}
			Point2 C = pakec2.getPos()-pakec.getPos();
			Point2 N=pakec.getDir();
						// D = N . C = ||C|| * cos(angle between N and C)
						double D = N.dot(C);

						// Another early escape: Make sure that A is moving
						// towards B! If the dot product between the movevec and
						// B.center - A.center is less that or equal to 0,
						// A isn't isn't moving towards B
						if(D <= 0){
						  // return false
						}

						// Find the length of the vector C
						double lengthC = C.Lenght();

						double F = (lengthC * lengthC) - (D * D);

						// Escape test: if the closest that A will get to B
						// is more than the sum of their radii, there's no
						// way they are going collide
						
						double sumRadiiSquared = sumRadii * sumRadii;
						if(F >= sumRadiiSquared){
						  //return false;
						}

						// We now have F and sumRadii, two sides of a right triangle.
						// Use these to find the third side, sqrt(T)
						double T = sumRadiiSquared - F;
						
						// If there is no such right triangle with sides length of
						// sumRadii and sqrt(f), T will probably be less than 0.
						// Better to check now than perform a square root of a
						// negative number.
						if(T < 0){
						  //return false;
						}

						// Therefore the distance the circle has to travel along
						// movevec is D - sqrt(T)
						double distance = D - sqrt(T);

						// Get the magnitude of the movement vector
						double mag = pakec.getDir().Lenght();
			
						// Finally, make sure that the distance A has to move
						// to touch B is not greater than the magnitude of the
						// movement vector.
						if(mag < distance){
						  //return false;
						}
						
						// Set the length of the movevec so that the circles will just
						// touch
						//movevec.normalize();
						//movevec.times(distance);
						distance*=5;
						std::cout<<distance<<"\n";
						pakec.setDir(pakec.getDir().getX()*distance,pakec.getDir().getY()*distance);
								}*/
								

			
	}
	


	pakec.UpdatePos();
	//pakec2.UpdatePos();
	glColor3f(0.1,0.1,0.1);
	glPushMatrix();
	glTranslatef(pakec.getPos().getX() ,pakec.getPos().getY(), 0.0);
			GLUquadricObj* cyl;
			cyl = gluNewQuadric();
			gluQuadricDrawStyle(cyl, GLU_SMOOTH);
			gluCylinder(cyl, pakec.getRad(), pakec.getRad(), 0.05, 16, 2);
			glTranslatef(0,0,0.05);
			fillCircle(pakec.getRad());
			glBegin(GL_LINES);
			glColor3f(1.0,0.1,0.7);
			glVertex3f(0,0,0);
			glVertex3f(pakec.getDir().getX()*20, pakec.getDir().getY()*20,0);
			glEnd();
			glPopMatrix();
			glPushMatrix();
			glColor3f(0.1,0.1,0.7);
	glTranslatef(pakec2.getPos().getX() ,pakec2.getPos().getY(), 0.0);
//	printf("%d\n", pakec2.getPos().getX());
			gluQuadricDrawStyle(cyl, GLU_SMOOTH);
			gluCylinder(cyl, pakec2.getRad(), pakec2.getRad(), 0.05, 16, 2);
			glTranslatef(0,0,0.05);
			fillCircle(pakec2.getRad());
			glBegin(GL_LINES);
			glColor3f(1.0,0.1,0.7);
			glVertex3f(0,0,0);
			glVertex3f(pakec2.getDir().getX()*20, pakec2.getDir().getY()*20,0);
			glEnd();
			glPopMatrix();


			

	angle++;
	
}

void MouseMotion(int x, int y)
{
	
  WIN_X = x;
  WIN_Y = y;
 
glutPostRedisplay();
GLint viewport[4];
  GLdouble modelview[16];
  GLdouble projection[16];
  GLdouble posX, posY, posZ;

  glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
  glGetDoublev(GL_PROJECTION_MATRIX, projection);
  glGetIntegerv(GL_VIEWPORT, viewport);

  WIN_Y = (float)viewport[3] - (float)WIN_Y;
  glReadPixels((int)WIN_X, (int)WIN_Y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &WIN_Z);

  gluUnProject(WIN_X, WIN_Y, WIN_Z, modelview, projection, viewport, &posX, &posY, &posZ);
  if ((abs(posX)<=SIRINA-pakec.getRad())&&((posY<=0)&&(posY>-DOLZINA))){
	  pakec2.setDir((posX-pakec2.getPos().getX())/5,(posY-pakec2.getPos().getY())/5);
	  pakec2.UpdatePos();
	  pakec2.setPos(posX, posY);
  }
  
}

void init (void) {
glEnable (GL_DEPTH_TEST);
glEnable (GL_LIGHTING);
glEnable (GL_LIGHT0);
glEnable (GL_LIGHT1);
glShadeModel (GL_SMOOTH);
glEnable(GL_COLOR_MATERIAL);
glEnable (GL_BLEND); glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
void display (void) {
glClearDepth(1);
glClearColor (0.9,0.9,1,1.0);
glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glLoadIdentity();
GLfloat DiffuseLight[] = {1, 1,1}; //set DiffuseLight[] to the specified values
GLfloat AmbientLight[] = {1, 1, 1}; //set AmbientLight[] to the specified values
GLfloat LightPosition[] = {0, 0, 1, 0}; //set the LightPosition to the specified values
glLightfv (GL_LIGHT0, GL_DIFFUSE, DiffuseLight); //change the light accordingly
glLightfv (GL_LIGHT1, GL_AMBIENT, AmbientLight); //change the light accordingly
glLightfv (GL_LIGHT0, GL_POSITION, LightPosition); //change the light accordingly
gluLookAt (0.0, 2.5, 5.5,
		   0.0, 0.0, 0.0,
		   0.0, 1.0, 0.0);
Risi();
glutSwapBuffers();
}

void reshape (int w, int h) {
glViewport (0, 0, (GLsizei)w, (GLsizei)h);
glMatrixMode (GL_PROJECTION);
glLoadIdentity ();
gluPerspective (30, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
glMatrixMode (GL_MODELVIEW);
}

int main (int argc, char **argv) {
    initGame();
glutInit (&argc, argv);
glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
glutInitWindowSize (1024, 768);
glutInitWindowPosition (100, 100);
glutCreateWindow ("A basic OpenGL Window");
glutPassiveMotionFunc(MouseMotion);
init ();
glutDisplayFunc (display);
glutIdleFunc (display);

glutReshapeFunc (reshape);
glutMainLoop ();
return 0;
}

bool initGame()
{

    // init stuff
    // polys
    Parser parser;
    string i_str;
    bool p;
    cout<<"Insert script: "<<endl;
    getline(cin, i_str, '/');
    p = parser.parse(g_list, i_str);
    cout<<endl<<"------------ DONE -------------"<<endl;
    p ? cout<<"SUCCESS"<<endl : cout<<"FAIL";
    g_list.dump();
    // ok
    return true;
}

