#include <iostream>
#include <fstream>

#include <vector>
#include <cstdlib>
#include <cstdio>
#include "graphic.h"
#include <ctime>

#define WIDTH 500
#define HEIGHT 500



using namespace std;


vector<Point3> points;


bool init();
void display();
void idle();
void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void saveToFile(char *filename, string str);
string genPoly(vector<Point3> p);

char filename[50];



GraphicInterface gIf;
int LIMIT_AREA = 60;

int main(int argc, char **argv)
{
//    srand(time(NULL));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(50, 50);
	glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("PolyGen - Quick'n'dirty polygon script generator");

    glutMouseFunc(mouse);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);

    if(!init())
    {
        cout<<"Error: init failed!"<<endl;
        return -1;
    }

    gIf.perspective();
    glutMainLoop();

    return 0;
}

bool init()
{
    cout<< "==================================================="<<endl;
    cout<< "Welcome to quick'n'dirty polygon generator! :)"<<endl;
    cout<< " LEFT mouse button - add vertex "<<endl;
    cout<< " MIDDLE mouse button - clear "<<endl;
    cout<< " RIGHT mouse button - generate and save polygon "<<endl;
    cout<< " Have fun =) "<<endl;
    cout<< "==================================================="<<endl<<endl;
    cout<<"Enter output file name and/or location: "<<endl;
    cin>>filename;
    cout<<endl;

    if(!gIf.init())
        return false;

    return true;
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
		    Point3 glCords(x, y, 0.0); // = gIf.windowToOpenGLCoords(x, y);
			points.push_back(glCords);//(gIf.windowToOpenGLCoords(x, y));
	//		cout<<"Event at: "<<glCords.x<<' '<<glCords.y<<endl;
		}
	}
	else if(button == GLUT_RIGHT_BUTTON)
	{
        if (state == GLUT_DOWN)
        {
            saveToFile(filename, genPoly(points));

        }
	}
    else if(button == GLUT_MIDDLE_BUTTON)
	{
	    points.clear();

	}
}

void keyboard(unsigned char key, int x, int y)
{
	/*switch(key)
	{
	// Backspace
	case 'c' :
        glutIgnoreKeyRepeat(true);
		points.clear();
		g_sklad.release();
		break;

	case 'q' :
        glutIgnoreKeyRepeat(true);
        LIMIT_AREA += 10;
        break;

    case 'w' :
        glutIgnoreKeyRepeat(true);
        if(LIMIT_AREA > 10)
            LIMIT_AREA -= 10;
		break;

	}*/

}


void idle()
{
    glutPostRedisplay();
}

inline Point3 crossProduct(const Point3 &a, const Point3 &b)
{
    return Point3(
        a.y*b.z - a.z*b.y,
        a.z*b.x - a.x*b.z,
        a.x*b.y - a.y*b.x
        );
}

void display()
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0,0,-200);

    glColor3f(1.0, 0.0, 0.0);

        for(int i=0; i<(int)points.size()-1; i++)
        {
                // gIf.drawDot(e->v->point, 0.0, 1.0, 0.0);
                glColor3f(1.0, 0.0, 0.0);
                gIf.drawDot(gIf.windowToOpenGLCoords(points[i].x, points[i].y));
                glColor3f(0.4, 0.4, 0.6);
                gIf.moveTo(gIf.windowToOpenGLCoords(points[i].x, points[i].y));
                gIf.lineTo(gIf.windowToOpenGLCoords(points[i+1].x, points[i+1].y));

                if ( i == (int)points.size()-2)
                {
                    gIf.moveTo(gIf.windowToOpenGLCoords(points[i+1].x, points[i+1].y));
                    gIf.lineTo(gIf.windowToOpenGLCoords(points[0].x, points[0].y));
                }
        }

    glutSwapBuffers();
    glFlush();
}

string genPoly(vector<Point3> p)
{
    string polystr = "generatedpoly: ";
    char buffer[20];

    for ( int i=0; i<points.size(); i++)
    {
        sprintf (buffer, "%f", points[i].x / (WIDTH));
        polystr += string(buffer);

        polystr += " ";

        sprintf (buffer, "%f", points[i].y / (HEIGHT));
        polystr += string(buffer);

        polystr += ",";
    }

    polystr.erase(polystr.size()-1);
    polystr += ";";

    cout<<polystr<<endl;

    return polystr;
}

void saveToFile(char *filename, string str)
{
    fstream file(filename, fstream::out);
    if (!file.is_open())
    {
        cout<<"Error opening file, call your mom :D"<<endl;
        return;
    }

    file << str;

    cout<<"Output saved to "<<filename<<endl;

    file.close();
}
