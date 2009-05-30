#ifndef globalsH
#define globalsH

#define MALET_RADIUS 20
#define PUCK_RADIUS 15

#define LEFT_UP_CORNER_X 30
#define LEFT_UP_CORNER_Y 30
#define RIGHT_D_CORNER_X 840
#define RIGHT_D_CORNER_Y 430

#define GOAL_UPPER_Y 184
#define GOAL_LOWER_Y 284

typedef struct stMALET{
	double posX,posY;        // Položaj valja na igralni mizi
	int lastposX, lastposY;
	int radius;			  // Radij igralèevega valja
	CPen *mPen;
	CBrush mBrush;
}MALET;

typedef struct stPUCK{
	double posX, posY;      // Polozaj paka na mizi
	int lastposX, lastposY;
	double dirX, dirY;   // Vektor smeri
	double velocity;     // Hitrost premika paka
	double par;          // Parameter premika
	int radius;			 // radij paka
	CPen *pPen;
	CBrush pBrush;
}PUCK;

typedef struct stTIME{
	int min;
	int sec;
}MYTIME;


#endif globalsH
