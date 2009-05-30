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
	MALET pl1Malet;   // igralna plo��ica prvega igralca
	MALET pl2Malet;   // igralna plo��ica drugega igralca
	PUCK puck;        // pak

	NeuralNetwork *network;
    vector<double> data;
	vector<double> result;

	bool runGame;     // indikator, �e se je igra za�ela
	int old_mal1_x;   // pomo�ne spremenljivke za ra�unanje nove pozicije igral�eve plo��ice
	int old_mal1_y;
	CPen *tableBorPen;   // Karakteristika �rte za obrobo mize
	CPen* midLinePen;    // Karakteristika sredinske �tre
	CPen *tableBlLine;   // Karakteristika modre �rte
	CPen *redLinePen;    // Karakteristika �rte za rde�e oznake na mizi
	CFont timeFont;      // Font za izpis �asa igre
	CFont scoreFont;     // Font za izpis rezultata
	CBrush tableBrush;   // Karakteristika ozadja mize
	MYTIME playTime;     // �as, ki ga imamo na voljo za kon�anje igre
	int pl1Score;        // To�ke igralca 1
	int pl2Score;        // To�ke igralca 2
	int startTick;		 // za�eten �as, ko se igra za�ne


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
	// Preverimo, �e lahko gre pak v gol
	bool PossibleGoal(void);
};

