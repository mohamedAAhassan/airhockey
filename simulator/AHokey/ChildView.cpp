// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "AHokey.h"
#include "ChildView.h"
#include <fstream> 
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;
// CChildView

CChildView::CChildView()
: runGame(false)
, old_mal1_x(0)
, old_mal1_y(0)
, tableBorPen(NULL)
, midLinePen(NULL)
, tableBlLine(NULL)
, redLinePen(NULL)
{
	oldX = 0;
	oldY = 0;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_KEYUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SHOWWINDOW()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

int nekaj=0;

// CChildView message handlers
//********************double ToString(za testiranje---spreminja double v string, ki ga lahko izpisemo z MessageBox)*********************//
CString ToString( double value)
{
  BSTR bstr;
  VarBstrFromR8( value, GetThreadLocale( ), 0, &bstr);
  CString s = bstr;
  SysFreeString( bstr);
  return s;
}

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	

	return TRUE;
}
//-----------------------------------------------------------------------------
void CChildView::OnPaint() 
///////////////////////////////////////////////////////////////////////////////
// Funkcija poskrbi za brisanje ekrana in izris nove vsebine.
///////////////////////////////////////////////////////////////////////////////
{
	CPaintDC dc(this); // device context for painting


	CMemDC dc1(&dc );   // dovoli double buffering - prikaz brez utripanja
	PaintScreen( &dc1 );

}
//-----------------------------------------------------------------------------
void CChildView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
///////////////////////////////////////////////////////////////////////////////
// Funkcija za startanje igre. Proži se s pritiskom na katerokoli tipko.
///////////////////////////////////////////////////////////////////////////////
{
	CWnd::OnKeyUp(nChar, nRepCnt, nFlags);
	SetTimer(1, 10, 0);	   // 1, 50, 0
	runGame = true;        // Igra se je zaèela

	//playTime.min = 1;
	//playTime.sec = 0;
	pl1Score = 0;
	pl2Score = 0;
	old_mal1_x = -2;
	old_mal1_y = -2;
	//startTick = GetTickCount();
	SetCursorPos(pl1Malet.posX,pl1Malet.posY+50); // miško postavimo v sredino igralne mize
	//ShowCursor(FALSE);     // skrijemo kurzor miške
}
//-----------------------------------------------------------------------------
void CChildView::OnMouseMove(UINT nFlags, CPoint point)
///////////////////////////////////////////////////////////////////////////////
// Funkcija prestreza premike miške, s katero kontroliramo prvega igralca.
// hkrati poskrbi za to, da igralec ostane v mejah, ki jih doloèa igrišèe.
///////////////////////////////////////////////////////////////////////////////
{

	CWnd::OnMouseMove(nFlags, point);

	if(runGame){
	  int DiffX, DiffY;
	  if(old_mal1_x<0){
	    old_mal1_x = point.x;
		old_mal1_y = point.y;
		DiffX = DiffY = 0;
	  }
	  else{
	    DiffX = point.x - old_mal1_x;
        DiffY = point.y - old_mal1_y;
	    old_mal1_x = point.x;
		old_mal1_y = point.y;
	  }
	    
	 pl1Malet.posX +=DiffX;
	 if(pl1Malet.posX < 50) pl1Malet.posX = 50;
	 else if(pl1Malet.posX > 410) pl1Malet.posX = 410; 

	 pl1Malet.posY += DiffY;
	 if(pl1Malet.posY < 50) pl1Malet.posY = 50;
	 else if(pl1Malet.posY > 410) pl1Malet.posY = 410; 

	 Invalidate();
	}
}
//-----------------------------------------------------------------------------
void CChildView::PaintScreen(CMemDC *dc)
///////////////////////////////////////////////////////////////////////////////
// Funkcija skrbi za izris dogajanja na ekranu. Funkcija uporablja double 
// buffering.
///////////////////////////////////////////////////////////////////////////////
{
	//////////////////////////////////////////////////////////////////////////////
	// Izris igrišèa
	//////////////////////////////////////////////////////////////////////////////
	dc->SelectObject(tableBrush);
	dc->Rectangle(31,31,839,429);

	dc->SelectObject(midLinePen);
	dc->MoveTo(431,33);
	dc->LineTo(431,427);

	dc->SelectObject(tableBlLine);
	dc->MoveTo(331,32);    // 354 - 3
	dc->LineTo(331,428);
	dc->MoveTo(533,32);    // 354 - 3
	dc->LineTo(533,428);

	dc->SelectObject(redLinePen);
	int cX = 210, cY = 110; 
	dc->Ellipse(cX-40, cY-40, cX+40, cY+40);
	dc->Ellipse(cX-3, cY-3, cX+3, cY+3);
    cY = 350;
	dc->Ellipse(cX-40, cY-40, cX+40, cY+40);
	dc->Ellipse(cX-3, cY-3, cX+3, cY+3);

	cX = 660, cY = 110; 
	dc->Ellipse(cX-40, cY-40, cX+40, cY+40);
	dc->Ellipse(cX-3, cY-3, cX+3, cY+3);
    cY = 350;
	dc->Ellipse(cX-40, cY-40, cX+40, cY+40);
	dc->Ellipse(cX-3, cY-3, cX+3, cY+3);
    // Izriši prvi gol
	dc->MoveTo(31,184);
	dc->LineTo(71,184);
	dc->LineTo(71,284);
	dc->LineTo(31,284);
    // Izriši drugi gol
	dc->MoveTo(840,184);
	dc->LineTo(800,184);
	dc->LineTo(800,284);
	dc->LineTo(840,284);



	dc->SelectObject(tableBorPen);
	dc->MoveTo(30,30);
	dc->LineTo(840,30);
	dc->LineTo(840,184);   // 180
	dc->MoveTo(840,284);   // 280
	dc->LineTo(840,430);
	dc->LineTo(30,430);
	dc->LineTo(30,284);    // 280
	dc->MoveTo(30,184);    // 180
	dc->LineTo(30,29);


	///////////////////////////////////////////////////////////////////////////
	// Izris igralcev
	///////////////////////////////////////////////////////////////////////////
	if(runGame){
	  dc->SelectObject(&puck.pBrush);
	  dc->SelectObject(puck.pPen);
	  dc->Ellipse(puck.posX-15,puck.posY-15,puck.posX+15, puck.posY+15);
	  dc->Ellipse(puck.posX-12,puck.posY-12,puck.posX+12, puck.posY+12);

	  dc->SelectObject(pl1Malet.mPen);
	  dc->SelectObject(&pl1Malet.mBrush);
	  dc->Ellipse(pl1Malet.posX-20,pl1Malet.posY-20,pl1Malet.posX+20,pl1Malet.posY+20);
	  dc->Ellipse(pl1Malet.posX-17,pl1Malet.posY-17,pl1Malet.posX+17,pl1Malet.posY+17);
	  dc->Ellipse(pl1Malet.posX-10,pl1Malet.posY-10,pl1Malet.posX+10,pl1Malet.posY+10);

	  /*dc->SelectObject(pl2Malet.mPen);
	  dc->SelectObject(&pl2Malet.mBrush);
	  dc->Ellipse(pl2Malet.posX-20,pl2Malet.posY-20,pl2Malet.posX+20,pl2Malet.posY+20);
	  dc->Ellipse(pl2Malet.posX-17,pl2Malet.posY-17,pl2Malet.posX+17,pl2Malet.posY+17);
	  dc->Ellipse(pl2Malet.posX-10,pl2Malet.posY-10,pl2Malet.posX+10,pl2Malet.posY+10);*/
	

	}

	///////////////////////////////////////////////////////////////////////////
	// Izris èasa in rezultata
	///////////////////////////////////////////////////////////////////////////
	CString str;

    CFont* old_font = dc->SelectObject(&timeFont); 
	dc->SetTextColor(RGB(18,87,11));
	/*if(playTime.sec/10 < 1)
	 str.Format(_T("0%d:0%d"),playTime.min, playTime.sec);
	else
	 str.Format(_T("0%d:%d"),playTime.min, playTime.sec);
*/
	dc->TextOut(393, 3, str);    
    dc->SelectObject(old_font);

    old_font = dc->SelectObject(&scoreFont); 
	dc->SetTextColor(RGB(255,0,0));
	str.Format(_T("%d"),pl1Score);
	dc->TextOut(205, 6, str);

	dc->SetTextColor(RGB(42,0,254));
	str.Format(_T("%d"),pl2Score);
	dc->TextOut(655, 6, str);

    dc->SelectObject(old_font);
	




}
//-----------------------------------------------------------------------------
BOOL CChildView::OnEraseBkgnd(CDC* pDC)
///////////////////////////////////////////////////////////////////////////////
// Redefinicija funkcije za brisanje ozadja, potrebna za double buffering.
///////////////////////////////////////////////////////////////////////////////
{
	// Prepreèimo zapolnitev ozadja in s tem prepreèimo utripanje

	//return CWnd::OnEraseBkgnd(pDC);,
	return true;
}
//-----------------------------------------------------------------------------
double CChildView::vcLength(double cX, double cY)
///////////////////////////////////////////////////////////////////////////////
// Izraèun dolžine vektorja.
///////////////////////////////////////////////////////////////////////////////
{
	return sqrt(cX*cX + cY*cY);
}
//-----------------------------------------------------------------------------
void CChildView::generateNewPuckDirection(void)
///////////////////////////////////////////////////////////////////////////////
// Generiraj novi nakljuèni smerni vektor paka. V igri ta funkcija odpade.
///////////////////////////////////////////////////////////////////////////////
{
	int posX=rand()%100;
	if (rand()%2 == 0) posX = puck.posX + 100;
	else posX = puck.posX - rand()%100;

	int posY=rand()%400;
    if (rand()%2 == 0) posY = puck.posY;
	else posY = puck.posY - rand()%100;

	puck.posX = 550+rand()%100;
	puck.posY = rand()%400;
	puck.dirX = (double)posX - puck.posX;

	puck.dirY = (double)posY - puck.posY;
	double d = vcLength(puck.dirX, puck.dirY);
	puck.dirX /= d;
	puck.dirY /= d;
	puck.velocity = 7;
	if(rand()%2==1)
		puck.dirY=-puck.dirY;
	if(puck.dirX>0)
		puck.dirX=-puck.dirX;
	puck.par = 5;
}
//-----------------------------------------------------------------------------
bool CChildView::PossibleGoal(void)
///////////////////////////////////////////////////////////////////////////////
// Funkcija preveri, èe lahko gre pak v gol
///////////////////////////////////////////////////////////////////////////////
{
	if((puck.posY > GOAL_UPPER_Y) && (puck.posY < GOAL_LOWER_Y)) return true;

	return false;
}
//-----------------------------------------------------------------------------
bool CChildView::validPuckPos(void)
///////////////////////////////////////////////////////////////////////////////
// Preverimo, èe je pak na igrišèu.
///////////////////////////////////////////////////////////////////////////////
{   
	if(PossibleGoal()) return true;
	if(puck.posX < 45) return false;
	if(puck.posX > 825) return false;
	if(puck.posY < 45) return false;
	if(puck.posY > 415) return false;
	
	return true;
}
//**************************************************************************************************************//
void CChildView::odbojstene(void)
{

	 if(puck.posX < 40 )
	{
			puck.posX=40;//vcasih pride do buga in pak prekoraci igralno povrsino
			puck.dirX =  - puck.dirX;
	}
	else if( puck.posX > 827)
	{
			puck.posX=827;
			puck.dirX =  - puck.dirX;
	}
	else if(puck.posY<49 )
	{
			puck.posY=49;
			puck.dirY = - puck.dirY;
	}
	else if( puck.posY>417)
	{
			puck.posY=417;
			puck.dirY = - puck.dirY;
	}
}
void CChildView::odbojmaleta(void)
{
	int x1,y1,x2,y2;
	x1=puck.posX-pl1Malet.posX;
	y1=puck.posY-pl1Malet.posY;
	x2=puck.posX-pl2Malet.posX;
	y2=puck.posY-pl2Malet.posY;	
	if(vcLength(x1,y1)<(puck.radius+pl1Malet.radius))
	{ 
		puck.posX = pl1Malet.posX+x1;
		puck.posY = pl1Malet.posY+y1;
		puck.dirX =  x1/vcLength(x1,y1);
		puck.dirY =  y1/vcLength(x1,y1);
	}
	/*else if(vcLength(x2,y2)<(puck.radius+pl2Malet.radius))
	{
		puck.posX = pl2Malet.posX+x2;
		puck.posY = pl2Malet.posY+y2;
		puck.dirX =  x2/vcLength(x2,y2);
		puck.dirY =  y2/vcLength(x2,y2);
	}*/
}


	//*********premik modrega maleta je nakljucen********************************************************************
void CChildView::pl2premikmalet(void)
{
	/*int k=rand();
	if(k%5==1)
	{
		if(puck.posY>pl2Malet.posY)
			pl2Malet.posY+=3;
		else
			pl2Malet.posY-=3;
	}*/
}

//-----------------------------------------------------------------------------
void CChildView::EstimateNewPuckPossition(void)
///////////////////////////////////////////////////////////////////////////////
// Približek funkcije za izraèun položaja paka, vdolž smernega vektorja.
// Položaj je odvisen od hitrosti paka, v igri je potrebno upoštevati dejansko
// formulo za hitrost in izraèunati morebitno kolizijo z robom mize. 
///////////////////////////////////////////////////////////////////////////////
{
	puck.par = puck.velocity;
	 puck.posX += (int)puck.par*puck.dirX;
	 puck.posY += (int)puck.par*puck.dirY;
	 
	 //*****************************************************preverjanje ce je pag znotraj ali zunaj izgralne povrsine*****************
	 if(!validPuckPos())
	 {
		odbojstene();
		//generateNewPuckDirection();
	 }
	 else
	 {
		//pl2premikmalet();
		odbojmaleta();
	}

}
//-----------------------------------------------------------------------------
void CChildView::OnShowWindow(BOOL bShow, UINT nStatus)
///////////////////////////////////////////////////////////////////////////////
// Inicializacija zaèetnih položajev igralcev in njihivih barv izrisa
///////////////////////////////////////////////////////////////////////////////
{
	CWnd::OnShowWindow(bShow, nStatus);

	tableBorPen = new CPen(PS_SOLID, 2, RGB(0,0,0));
	midLinePen = new CPen(PS_SOLID, 8, RGB(250,103,96));
	tableBlLine = new CPen(PS_SOLID, 4, RGB(183,199,245));
	redLinePen = new CPen(PS_SOLID, 2, RGB(254,174,183));
	tableBrush.CreateSolidBrush(RGB(242,240,240));

	// Nastavitev zacetnega polozaja prvega igralca
	pl1Malet.posX = 331;
	pl1Malet.posY = 230;
	pl1Malet.radius = MALET_RADIUS;
	pl1Malet.mPen = new CPen(PS_SOLID, 1, RGB(141,39,7));
	pl1Malet.mBrush.CreateSolidBrush(RGB(255,0,0));

    // Nastavitev zacetnega polozaja drugega igralca
	pl2Malet.posX=730;///********modri malet damo blizje k njegovemu golu********//
	pl2Malet.posY = 230;
	pl2Malet.radius = MALET_RADIUS;
	pl2Malet.mPen = new CPen(PS_SOLID, 1, RGB(7,29,141));
	pl2Malet.mBrush.CreateSolidBrush(RGB(42,0,254));

	puck.posX = 431;
	puck.posY = 230;
	puck.radius = PUCK_RADIUS;
	puck.pPen = new CPen(PS_SOLID, 1, RGB(245,224,167));
	puck.pBrush.CreateSolidBrush(RGB(255,255,0));

   

    timeFont.CreateFont(22, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
    0, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,   DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN, _T("Alien Encounters"));

    scoreFont.CreateFont(20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, 
    0, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,   DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN, _T("Alien Encounters"));

	playTime.min = 0;
	playTime.sec = 0;
	pl1Score = 0;
	pl2Score = 0;

	generateNewPuckDirection();
}
//-----------------------------------------------------------------------------
bool CChildView::isLeftGoal()
///////////////////////////////////////////////////////////////////////////////
// Preverimo, èe je prišlo do gola pri rdeèem tekmovalcu.
///////////////////////////////////////////////////////////////////////////////
{
	if((puck.posX < LEFT_UP_CORNER_X)&&(puck.posY < (GOAL_LOWER_Y-puck.radius))&&(puck.posY>(GOAL_UPPER_Y+puck.radius) ))
      return true;

	return false;
}
//-----------------------------------------------------------------------------
bool CChildView::isRightGoal()
///////////////////////////////////////////////////////////////////////////////
// Preverimo, èe je prišlo do gola pri rdeèem tekmovalcu.
///////////////////////////////////////////////////////////////////////////////
{
	if((puck.posX > RIGHT_D_CORNER_X)&&
	   (puck.posY < GOAL_LOWER_Y-puck.radius)&&(puck.posY>GOAL_UPPER_Y+puck.radius ))
    return true;

	return false;
}
//-----------------------------------------------------------------------------
void CChildView::DetermineGoal()
///////////////////////////////////////////////////////////////////////////////
// Preverimo, èe je prišlo do gola.
///////////////////////////////////////////////////////////////////////////////
{
	if(isLeftGoal()){
	  pl1Score++;
	  puck.posX = 431;
	  puck.posY = 230;
	  generateNewPuckDirection();
	}
	else
	 if(isRightGoal()){
	   pl2Score++;
	   puck.posX = 431;
	   puck.posY = 230;
	   generateNewPuckDirection();
	 }
}
//-----------------------------------------------------------------------------
void CChildView::calcTime(void)
///////////////////////////////////////////////////////////////////////////////
// Izraèunamo koliko èasa je minilo od zadnjega klica timerja
///////////////////////////////////////////////////////////////////////////////
{
	/*int tick = GetTickCount();

	if((tick-startTick) >= 1000){
	  if(playTime.sec == 0){
	   playTime.min--;

	   if(playTime.min >= 0)
		  playTime.sec = 59;
	   else{
	      KillTimer(1);  // Igra je konèana
		  playTime.min=0;
		  playTime.sec=0;
		  runGame = false;
		  //ShowCursor(TRUE);     // skrijemo kurzor miške
	   }
	  }
	  else playTime.sec--;

	  startTick = tick;
	}*/
}
//-----------------------------------------------------------------------------
void CChildView::OnTimer(UINT_PTR nIDEvent)
///////////////////////////////////////////////////////////////////////////////
// Glavna rutina, ki nadzoruje premikanje paka in racuna odziv nasprotnika
// Ko se bo dodajala dodatna funkcionalnost je treba odkomentirati ukaza, ki 
// zaèasno deaktivirata, nato pa ponovno aktivirata timer.
///////////////////////////////////////////////////////////////////////////////
{
	/////////////////////////// deaktivirajmo timer ///////////////////////////
	//KillTimer(1);             // Odkomentirati v primeru poèasnih funkcij
	///////////////////////////////////////////////////////////////////////////
	//CWnd::OnTimer(nIDEvent);
	EstimateNewPuckPossition();  // doloèitev položaja paka

    DetermineGoal();
//************************************belezenje podatkov*****************************************************************************//
	if(nekaj%6>1)//hitrost belezenja podatkov
	  {
		ofstream out("test.txt",ios_base::app); 
		double deltaX = puck.posX - oldX;
		double deltaY = puck.posY - oldY;
		if(oldX != 0 && oldY != 0) {
			out << deltaX/825.0 << " " << deltaY/415.0 <<endl;
		}
		out << puck.posX/825.0 <<" "<<puck.posY/415.0<<" "<<puck.dirX/825.0<<" "<<puck.dirY/415.0<<" "<<pl1Malet.posX/825.0<<" "<<pl1Malet.posY/415.0 << " ";
		oldX = puck.posX;
		oldY = puck.posY;
		out.close();
	  }

	if(nekaj>200)
	{
		nekaj=0;
		generateNewPuckDirection();
	}
	else
		nekaj++;
    //if((pl1Score>6) || (pl2Score>6))
	//  KillTimer(1);

	//////////////////////// Ponovno aktiviramo timer /////////////////////////
	//SetTimer(1, 10, 0);     // Odkomentirati v primeru poèasnih funkcij
	///////////////////////////////////////////////////////////////////////////
	calcTime();
	Invalidate();
}


