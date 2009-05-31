#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include "Point2.h"
#include "Pak.h"


#define SIRINA 1.2
#define DOLZINA 3
#define VISINA 0.1

Pak pakec=Pak(Point2(0.40,-2.1),Point2(0.01, -0.03), 0.1,0.999,true,"");
Pak pakec2=Pak(Point2(0,-1),Point2(0, 0), 0.1,1, false,"Player 1");
Pak pakec3=Pak(Point2(0,1.5),Point2(0, 0), 0.1,1, false,"Player 2");

//Kij pakec2=Kij(Point2(0,-1),Point2(0, 0), 0.12,1, SIRINA, DOLZINA);

GLfloat angle = 0.0;
double gol=0.25;
double not=pakec.getRad()*2;
int resultpl1=0,resultpl2=0;

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

void preveriTrk(Pak &prvi, Pak &drugi) {
	Point2 razdalja=prvi.getPos()-drugi.getPos();
	if (razdalja.Lenght()<=(prvi.getRad()+drugi.getRad())) {
			double deltaY = (prvi.getPos().getY() - drugi.getPos().getY());
            double deltaX = (prvi.getPos().getX() - drugi.getPos().getX());
            double Distance = deltaX * deltaX + deltaY * deltaY;
            double k1= (deltaX * prvi.getDir().getX() + deltaY * prvi.getDir().getY()) / Distance;
            double k2 = (deltaX * prvi.getDir().getY() - deltaY * prvi.getDir().getX()) / Distance;
            double k3 = (deltaX * drugi.getDir().getX() + deltaY * drugi.getDir().getY()) / Distance;
            double k4 = (deltaX * drugi.getDir().getY() - deltaY * drugi.getDir().getX()) / Distance;
            prvi.setDir(k3 * deltaX - k2 * deltaY,k3 * deltaY + k2 * deltaX);
			prvi.UpdatePos();
	}
}


const float DEG2RAD = 3.14159/180;
 
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

void napisi(double x, double y, double z, char *string)
{
  int len, i;
  glRasterPos3f(x, y, z);
  len = (int) strlen(string);
  for (i = 0; i < len; i++)
  {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
  }
}
void izrisi(Pak prvi) {
	glPushMatrix();
	glTranslatef(prvi.getPos().getX() ,prvi.getPos().getY(), 0.0);
			GLUquadricObj* cyl;
			cyl = gluNewQuadric();
			gluQuadricDrawStyle(cyl, GLU_SMOOTH);
			gluCylinder(cyl, prvi.getRad(), prvi.getRad(), 0.05, 16, 2);
			glTranslatef(0,0,0.05);
			fillCircle(prvi.getRad());
			//napisi(prvi.getPos().getX()/3,prvi.getPos().getY()/3,0.1, prvi.getIme());
			//glBegin(GL_LINES);
			//glColor3f(1.0,0.1,0.7);
			//glVertex3f(0,0,0);
			//glVertex3f(prvi.getDir().getX()*20, prvi.getDir().getY()*20,0);
			//glEnd();
			glPopMatrix();
}

void preveriTrkeInGol(Pak &prvi) {

	if (abs((prvi.getPos()+prvi.getDir()).getX())>=SIRINA-prvi.getRad()) {
		prvi.setDir(prvi.getDir().getX()*-1, prvi.getDir().getY());
	}
	if (abs((prvi.getPos()+prvi.getDir()).getY())>=DOLZINA-prvi.getRad()) {
		if (abs(prvi.getPos().getX())<gol) {
			if (prvi.getPos().getY()<0) {
				resultpl2++;
			}
			else {
				resultpl1++;
			}
			prvi.setPos(0,0);
		}
		else {
			prvi.setDir(prvi.getDir().getX(), prvi.getDir().getY()*-1);
		}
	}
}




void Risi (void) {

	
	glRotatef(-100,1,0,0);
	glRotatef(sin(angle/100)*5,0,0,1);
	//glRotatef(angle/5,0,0,1);
	//glRotatef(angle/5,0,1,0);
	//glRotatef(-pakec.getPos().getX()*3,0,0,1);
	glBegin(GL_QUADS);

	//rezultat



	glColor3f(1, 1, 1);
	
		glVertex3f(-SIRINA,DOLZINA,0);
		glVertex3f(SIRINA,DOLZINA,0);
		glVertex3f(SIRINA,-DOLZINA,0);
		glVertex3f(-SIRINA,-DOLZINA,0);

		// Zagolje :D
		glVertex3f(-gol,-DOLZINA,0);
		glVertex3f(gol,-DOLZINA,0);
		glVertex3f(gol,-DOLZINA-not,0);
		glVertex3f(-gol,-DOLZINA-not,0);

		glVertex3f(-gol,DOLZINA,0);
		glVertex3f(gol,DOLZINA,0);
		glVertex3f(gol,DOLZINA+not,0);
		glVertex3f(-gol,DOLZINA+not,0);


		glColor4f(0.3,0.3,0.8, 0.5);
		//Stranice zagolja

		glVertex3f(gol,-DOLZINA,0);
		glVertex3f(gol,-DOLZINA-not,0);
		glVertex3f(gol,-DOLZINA-not,VISINA/3);
		glVertex3f(gol,-DOLZINA,VISINA);

		glVertex3f(gol,-DOLZINA-not,0);
		glVertex3f(gol,-DOLZINA-not,VISINA/3);
		glVertex3f(-gol,-DOLZINA-not,VISINA/3);
		glVertex3f(-gol,-DOLZINA-not,0);

		glVertex3f(-gol,-DOLZINA,0);
		glVertex3f(-gol,-DOLZINA-not,0);
		glVertex3f(-gol,-DOLZINA-not,VISINA/3);
		glVertex3f(-gol,-DOLZINA,VISINA);

		glVertex3f(gol,DOLZINA,0);
		glVertex3f(gol,DOLZINA+not,0);
		glVertex3f(gol,DOLZINA+not,VISINA/3);
		glVertex3f(gol,DOLZINA,VISINA);

		glVertex3f(gol,DOLZINA+not,0);
		glVertex3f(gol,DOLZINA+not,VISINA/3);
		glVertex3f(-gol,DOLZINA+not,VISINA/3);
		glVertex3f(-gol,DOLZINA+not,0);

		glVertex3f(-gol,DOLZINA,0);
		glVertex3f(-gol,DOLZINA+not,0);
		glVertex3f(-gol,DOLZINA+not,VISINA);
		glVertex3f(-gol,DOLZINA,VISINA/3);
		
		// Stranice
	
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


	
	// Èrte na igrišèu
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

	glColor3f(0.5,0.5,0.5);
	glVertex3f(-gol,-DOLZINA,0.005);
	glVertex3f(gol,-DOLZINA,0.005);
	glVertex3f(gol,-DOLZINA-0.003,0.005);
	glVertex3f(-gol,-DOLZINA-0.003,0.005);

	glVertex3f(-gol,DOLZINA,0.005);
	glVertex3f(gol,DOLZINA,0.005);
	glVertex3f(gol,DOLZINA+0.003,0.005);
	glVertex3f(-gol,DOLZINA+0.003,0.005);

	glColor3f(0.8,0.6,0.6);
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

	// Pak
	// Preveri trk
	pakec3.setDir((pakec.getPos().getX()-pakec3.getPos().getX())/20+sin(angle/10)/50,sin(angle/10)/70);
	//pakec3.setPos(pakec.getPos().getX(),2+sin(angle/100));
	
	preveriTrk(pakec, pakec2);
	preveriTrk(pakec, pakec3);


	preveriTrkeInGol(pakec);
	pakec.UpdatePos();
	pakec3.UpdatePos();
	//pakec2.UpdatePos();
	pakec2.setDir(0,0);

	glColor3f(0.1,0.1,0.1);
	izrisi(pakec);

	glColor3f(0.1,0.1,0.7);
	izrisi(pakec2);

	glColor3f(0.5,0.1,0.1);
	izrisi(pakec3);

	glColor3f(0.3, 0.3, 1);
	glRasterPos3f(-SIRINA/3,DOLZINA,VISINA+0.2);
	char buffer[2];
	sprintf(buffer, "%i", resultpl1);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, buffer[0]);
	glColor3f(0, 0, 0);
	glRasterPos3f(0,DOLZINA,VISINA+0.2);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '-');
	glColor3f(1, 0.3, 0.3);
	glRasterPos3f(SIRINA/3,DOLZINA,VISINA+0.2);
	sprintf(buffer, "%i", resultpl2);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, buffer[0]);

	angle++;
	//pakec2.setDir(pakec2.getDir().getX()*0.9,pakec2.getDir().getY()*0.9);
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
	  //printf("%i\n", posX);

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
