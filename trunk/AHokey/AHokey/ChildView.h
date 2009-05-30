// ChildView.h : interface of the CChildView class
//


#pragma once
#include "afxwin.h"
#include "MemDC.h"
#include "globals.h"
#include "NeuralNetwork.h"
#include <math.h>


// CChildView window

class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:

// Operations
public:

// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();

	// Generated message map functions
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	MALET pl1Malet;   // igralna plošèica prvega igralca
	MALET pl2Malet;   // igralna plošèica drugega igralca
	PUCK puck;        // pak

	NeuralNetwork *network;
    vector<double> data;
	vector<double> result;

	bool runGame;     // indikator, èe se je igra zaèela
	int old_mal1_x;   // pomožne spremenljivke za raèunanje nove pozicije igralèeve plošèice
	int old_mal1_y;
	CPen *tableBorPen;   // Karakteristika èrte za obrobo mize
	CPen* midLinePen;    // Karakteristika sredinske ètre
	CPen *tableBlLine;   // Karakteristika modre èrte
	CPen *redLinePen;    // Karakteristika èrte za rdeèe oznake na mizi
	CFont timeFont;      // Font za izpis èasa igre
	CFont scoreFont;     // Font za izpis rezultata
	CBrush tableBrush;   // Karakteristika ozadja mize
	MYTIME playTime;     // Èas, ki ga imamo na voljo za konèanje igre
	int pl1Score;        // Toèke igralca 1
	int pl2Score;        // Toèke igralca 2
	int startTick;		 // zaèeten èas, ko se igra zaène


	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	void PaintScreen(CMemDC * dc);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	// Izracun dolzine vektorja
	double vcLength(double cX, double cY);
	void generateNewPuckDirection(void);
	void EstimateNewPuckPossition(void);
	bool validPuckPos(void);
	void calcTime(void);
	void DetermineGoal();
	bool isLeftGoal();
	bool isRightGoal();
	// Preverimo, èe lahko gre pak v gol
	bool PossibleGoal(void);
};

