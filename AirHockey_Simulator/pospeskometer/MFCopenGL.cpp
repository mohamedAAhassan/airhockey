#include "StdAfx.h"

MFCopenGL::MFCopenGL(void)
{
	pakec=Pak(Point2(0.40,-2.1),Point2(0.01, -0.03), 0.1,0.999,true,"");
	pakec2=Pak(Point2(0,-1),Point2(0, 0), 0.1,1, false,"Player 1");
	pakec3=Pak(Point2(0,2.5),Point2(0, 0), 0.1,1, false,"Player 2");

	angle = 0.0;
	gol=0.25;

	this->statustxt = "";
	this->g_parser = new Parser;

	not=pakec.getRad()*2;
	resultpl1=0;
	resultpl2=0;

	WIN_X = 0;
	WIN_Y = 0;
	WIN_Z = 0;

	this->network = new NeuralNetwork;

	this->isMouseControl = false;
	this->isAcclControl = false;

	counter = 0;
	resetCounter = 0;
	oldX = 0;
	oldY = 0;
}

MFCopenGL::~MFCopenGL(void)
{
	// delete stuff
	delete this->g_parser;
	g_parser = NULL;
}



void MFCopenGL::animate()
{
	glutPostRedisplay();
}

void MFCopenGL::drawCircle(float radius)
{
   glBegin(GL_LINE_LOOP);
 
   for (int i=0; i < 360; i++)
   {
      float degInRad = i*DEG2RAD;
      glVertex2f(cos(degInRad)*radius,sin(degInRad)*radius);
   }
 
   glEnd();
}

void MFCopenGL::fillCircle(float radius)
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

void MFCopenGL::Risi (void) {

	
	glRotatef(-100,1,0,0);
	//glRotatef(sin(angle/100)*5,0,0,1);
	//glRotatef(sin(angle/100)*15,0,1,0);
	//glRotatef(sin(angle/10)*15,0,0,1);
	//glRotatef(angle/5,0,1,0);
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
		glVertex3f(-gol,DOLZINA+not,VISINA/3);
		glVertex3f(-gol,DOLZINA,VISINA);
		
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

	// pak pos x, pak pos y, pak dir x, pak dir y, njegov pos x, njegov posy
	//out << -pakec.getPos().getX()/(SIRINA*2) <<" "<< -pakec.getPos().getY()/(DOLZINA*2) <<" "<< -pakec.getDir().getX()/(SIRINA*2) <<" "<< -pakec.getDir().getY()/(DOLZINA*2) <<" "<< -pakec2.getPos().getX()/(SIRINA*2) <<" "<< -pakec2.getPos().getY()/(DOLZINA*2) << " ";
	input.clear();
	/*input.push_back((pakec.getPos().getY()+DOLZINA)/(DOLZINA*2));
	input.push_back((pakec.getPos().getX()+SIRINA)/(SIRINA*2));
	input.push_back((pakec.getDir().getY()));
	input.push_back((pakec.getDir().getX()));
	input.push_back((pakec3.getPos().getY()+DOLZINA)/(DOLZINA*2));
	input.push_back((pakec3.getPos().getX()+SIRINA)/(SIRINA*2));*/
	input.push_back(pakec.getPos().getX()/(SIRINA*2.0));
	input.push_back(pakec.getPos().getY()/(DOLZINA*2.0));
	input.push_back(pakec.getDir().getX()/(SIRINA*2.0));
	input.push_back(pakec.getDir().getY()/(DOLZINA*2.0));
	input.push_back(pakec3.getPos().getX()/(SIRINA*2.0));
	input.push_back(pakec3.getPos().getY()/(DOLZINA*2.0));

	output=network->calculate(input);
	//printf("%f, %f", output[1],output[0]);
	//cout<<"<>"<<input[0]<<", "<<input[1]<<", "<<input[2]<<", "<<input[3]<<", "<<input[4]<<", "<<input[5]<<endl;
	//pakec3.setDir(output[1]*DOLZINA/3,output[0]*SIRINA/3);
	pakec3.setDir(output[0]*SIRINA, output[1]*DOLZINA);
	Point2 temp=pakec3.getPos()+pakec3.getDir()*0.05;
	//printf("%f - %f\n", temp.getX(), temp.getY());
	if (abs(temp.getX())>=SIRINA-pakec3.getRad()) {
		if (pakec3.getDir().getX()<0) {
			pakec3.setPos(-SIRINA+pakec3.getRad()+0.001,pakec3.getPos().getY());
		}
		if (pakec3.getDir().getX()>0) {
			pakec3.setPos(SIRINA-pakec3.getRad()-0.001,pakec3.getPos().getY());
		}
		pakec3.setDir(0,0);
	}
	if (abs(temp.getY())>=DOLZINA-pakec3.getRad()) {
		pakec3.setPos(pakec3.getPos().getX(),DOLZINA-pakec3.getRad()-0.001);
		pakec3.setDir(0,0);
	}
	if (temp.getY()<= pakec3.getRad()) {
		pakec3.setPos(pakec3.getPos().getX(),pakec3.getRad()+0.001);
		pakec3.setDir(0,0);
	}
	//pakec3.setDir((pakec.getPos().getX()-pakec3.getPos().getX())/20+sin(angle/11)/50,sin(angle/11)/10);
	//pakec3.setDir(sin(angle/10)/10,0);
	//pakec3.setPos(pakec.getPos().getX(),2+sin(angle/100));

	//     |   |
	//		\_/
	//   ¡| ooo  |'
	//    \ooooo/
	//    ooo ooo
	//    ooo ooo   BUG!
	//    /oo oo\
	//	 .|     |.
	
	preveriTrk(pakec, pakec2);

	preveriTrkeInGol(pakec);
	pakec.UpdatePos();
	//pakec2.UpdatePos();
	pakec2.setDir(0,0);

	glColor3f(0.1,0.1,0.1);
	izrisi(pakec);

	glColor3f(0.1,0.1,0.7);
	izrisi(pakec2);

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
	glColor3f(0.3, 0.3, 0.3);
	napisi(0,0,1, statustxt);

	angle++;
	//pakec2.setDir(pakec2.getDir().getX()*0.9,pakec2.getDir().getY()*0.9);
	
}



void MFCopenGL::MouseMotion(int x, int y)
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
	  pakec2.setDir((posX-pakec2.getPos().getX())/SIRINA,(posY-pakec2.getPos().getY())/DOLZINA);
	  pakec2.UpdatePos();
	  //printf("%i\n", posX);

  }
}


void MFCopenGL::init (void) {
	//g_parser->compileFile(this->g_list, "test.poly");
    
    glEnable (GL_DEPTH_TEST);
    glEnable (GL_LIGHTING);
    glEnable (GL_LIGHT0);
    glEnable (GL_LIGHT1);
    glShadeModel (GL_SMOOTH);
    glEnable(GL_COLOR_MATERIAL);
    glEnable (GL_BLEND); glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	AllocConsole();
	freopen ("CONOUT$", "w", stdout ); 
}

void MFCopenGL::display (void) {
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

	bool ignore = false;
	srand(time(NULL));
	if(resetCounter == 200) {
		double newPX = (rand()%1000)/1000.0;
		if(rand()%2 == 0) {
			newPX = -newPX;
		}
		double newPY = (rand()%2000)/1000.0;
		pakec.setPos(newPX, newPY);
		cout << "new pos: " << newPX << "  " << newPY <<endl;
		double newDX = (rand()%500+100)/10000.0;
		if(rand()%2 == 0) {
			newDX = -newDX;
		}
		double newDY = -(rand()%500+100)/10000.0;
		pakec.setDir(newDX, newDY);
		cout << "new dir: " << newDX << "  " << newDY <<endl;
		resetCounter = 0;
		ignore = true;
	}
	resetCounter++;

	if(ignore != true) {
		ofstream out("vzorci.txt", ios_base::app); 
		double deltaX = pakec2.getPos().getX() - oldX;
		double deltaY = pakec2.getPos().getY() - oldY;
		if(oldX != 0 && oldY != 0) {
			out << -deltaX/(2.0*SIRINA) << " " << -deltaY/(2.0*DOLZINA) <<endl;
		}
		out << -pakec.getPos().getX()/(2.0*SIRINA) <<" "<< -pakec.getPos().getY()/(2.0*DOLZINA) <<" "<< -pakec.getDir().getX()/(2.0*SIRINA) <<" "<< -pakec.getDir().getY()/(2.0*DOLZINA) <<" "<< -pakec2.getPos().getX()/(2.0*SIRINA) <<" "<< -pakec.getPos().getY()/(2.0*DOLZINA) << " ";
		cout << -pakec.getPos().getX()/(2.0*SIRINA) <<" "<< -pakec.getPos().getY()/(2.0*DOLZINA) <<" "<< -pakec.getDir().getX()/(2.0*SIRINA) <<" "<< -pakec.getDir().getY()/(2.0*DOLZINA) <<" "<< -pakec2.getPos().getX()/(2.0*SIRINA) <<" "<< -pakec.getPos().getY()/(2.0*DOLZINA) << endl;
		oldX = pakec2.getPos().getX();
		oldY = pakec2.getPos().getY();
		out.close();
	}

	if (g_list.size() > 0)
        this->g_graphics.drawPolys(this->g_list, 0.0,0.0,0.0);

    glutSwapBuffers();
}

void MFCopenGL::reshape (int w, int h) {
    glViewport (0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective (30, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
    glMatrixMode (GL_MODELVIEW);
}

void MFCopenGL::preveriTrk(Pak &prvi, Pak &drugi) {
	double  x21,y21,vx21,vy21;

	x21 = prvi.getPos().getX() - drugi.getPos().getX();
		y21 = prvi.getPos().getY()- drugi.getPos().getY();
		vx21 = prvi.getDir().getX() - drugi.getDir().getX();
		vy21 = prvi.getDir().getY() - drugi.getDir().getY();

		if ((vx21 * x21 + vy21 * y21) >= 0)
		{
			return;
		}
	Point2 razdalja=prvi.getPos()-drugi.getPos();
	if (razdalja.Lenght()<=(prvi.getRad()+drugi.getRad())) {
		if (prvi.getLastTrk()>10) {
			prvi.setLastTrk();
			double deltaY = (prvi.getPos().getY() - drugi.getPos().getY());
            double deltaX = (prvi.getPos().getX() - drugi.getPos().getX());
            double Distance = deltaX * deltaX + deltaY * deltaY;
            double k1= (deltaX * prvi.getDir().getX() + deltaY * prvi.getDir().getY()) / Distance;
            double k2 = (deltaX * prvi.getDir().getY() - deltaY * prvi.getDir().getX()) / Distance;
            double k3 = (deltaX * drugi.getDir().getX() + deltaY * drugi.getDir().getY()) / Distance;
            double k4 = (deltaX * drugi.getDir().getY() - deltaY * drugi.getDir().getX()) / Distance;
            prvi.setDir(k3 * deltaX - k2 * deltaY,k3 * deltaY + k2 * deltaX);
			prvi.UpdatePos();
			prvi.setPos(prvi.getPos().getX()+prvi.getRad()*prvi.getDir().getX(),prvi.getPos().getY()+prvi.getRad()*prvi.getDir().getY());
			Point2 razdalja=prvi.getPos()-drugi.getPos();
			if (razdalja.Lenght()<=(prvi.getRad()+drugi.getRad())) {
				
				//prvi.setPos(prvi.getPos().getX()+razdalja.Lenght()*prvi.getDir().getX()*10,prvi.getPos().getY()+razdalja.Lenght()*prvi.getDir().getY()*10);
				prvi.setPos(prvi.getPos().getX()+prvi.getRad()*prvi.getDir().getX(),prvi.getPos().getY()+prvi.getRad()*prvi.getDir().getY());
			}
		}
	}
}

void MFCopenGL::napisi(double x, double y, double z, char *string)
{
  int len, i;
  glRasterPos3f(x, y, z);
  len = (int) strlen(string);
  for (i = 0; i < len; i++)
  {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
  }
}


void MFCopenGL::preveriTrkeInGol(Pak &prvi) {
	if (abs((prvi.getPos()+prvi.getDir()).getX())>=SIRINA-prvi.getRad()) {
		prvi.setDir(prvi.getDir().getX()*-1, prvi.getDir().getY());
	}
	if (abs((prvi.getPos()+prvi.getDir()).getY())>=DOLZINA-prvi.getRad()) {
		if (abs(prvi.getPos().getX())<gol) {
			prvi.setDir(0,0);
			if (prvi.getPos().getY()<0) {
				resultpl2++;
				prvi.setPos(0,-1);
			}
			else {
				resultpl1++;
				prvi.setPos(0,1);
			}
			if ((resultpl1>6||resultpl2>6)) {
				statustxt="Konec igre!";
				prvi.setPos(-10000,-10000);
				
			}
		}
		else {
			prvi.setDir(prvi.getDir().getX(), prvi.getDir().getY()*-1);
		}
		//prvi.setDir(prvi.getDir().getX(), prvi.getDir().getY()*-1);
	}
}

void MFCopenGL::izrisi(Pak prvi) {
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

Pak* MFCopenGL::getUserPak() 
{
	return &(this->pakec2);
}

void MFCopenGL::setMouseControl()
{
	this->isMouseControl = true;
}

void MFCopenGL::unsetMouseControl()
{
	this->isMouseControl = false;
}

bool MFCopenGL::getMouseControlStatus()
{
	return this->isMouseControl;
}

Parser* MFCopenGL::getParser() const
{
	return this->g_parser;
}