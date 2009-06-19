#pragma once
#include <GL/glut.h>

#include "NeuralNetwork.h"
#include "graphics.h"
#include "Point2.h"
#include "Pak.h"
#include "Kij.h"

class MFCopenGL
{
private:
	Pak pakec;
	Pak pakec2;
	Pak pakec3;

	int counter;
	int resetCounter;
	double oldX;
	double oldY;

	NeuralNetwork* network;//=new NeuralNetwork();
	vector<double> input;
	vector<double> output;

	GLfloat angle;// = 0.0;
	double gol;//=0.25;

	double not; //=pakec.getRad()*2;
	int resultpl1, resultpl2; //=0;

	char* statustxt;

	GLfloat WIN_X; //= 0;
	GLfloat WIN_Y; //= 0;
	GLfloat WIN_Z;// = 0;

	struct table_s {
	  GLfloat width;
	  GLfloat height;
	  GLfloat depth;
	  GLfloat goal;
	  GLfloat border;
	};

	CGraphics g_graphics;
	
	Parser *g_parser;

	bool isMouseControl;
	bool isAcclControl;

	double deltaTimeAccl;

public:
	MFCopenGL(void);
	~MFCopenGL(void);

//	void display();
	void animate();
//	void resize(int width, int height);

	void preveriTrk(Pak &prvi, Pak &drugi);
	void napisi(double x, double y, double z, char *string);
	void preveriTrkeInGol(Pak &prvi);
	void izrisi(Pak prvi);

	void Risi (void);
	void fillCircle(float radius);
	void drawCircle(float radius);

	void reshape (int w, int h);
	void display (void);
	void init (void);
	void MouseMotion(int x, int y);

	Pak* getUserPak();

	void setMouseControl();
	void unsetMouseControl();
	bool getMouseControlStatus();

	Parser* getParser() const;

	bool draw;

	CPolygonsList g_list;
};
