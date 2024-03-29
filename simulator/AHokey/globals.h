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
	int posX,posY;        // Polo�aj valja na igralni mizi
	int radius;			  // Radij igral�evega valja
	double dirX,dirY;
	CPen *mPen;
	CBrush mBrush;
}MALET;

typedef struct stPUCK{
	int posX, posY;      // Polozaj paka na mizi
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
