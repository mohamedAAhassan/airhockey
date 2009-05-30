// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "AHokey.h"
#include "ChildView.h"
#include "NeuralNetwork.h"
#include <iostream>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int stevec=0;

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



// CChildView message handlers

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
	SetTimer(1, 50, 0);	   // 1, 50, 0
	runGame = true;        // Igra se je zaèela

	playTime.min = 2;
	playTime.sec = 0;
	pl1Score = 0;
	pl2Score = 0;
	old_mal1_x = -2;
	old_mal1_y = -2;
	startTick = GetTickCount();
	SetCursorPos(481,280); // miško postavimo v sredino igralne mize
	ShowCursor(FALSE);     // skrijemo kurzor miške
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
	    
	  pl1Malet.lastposX=pl1Malet.posX;
	  pl1Malet.lastposY=pl1Malet.posY;
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

	  dc->SelectObject(pl2Malet.mPen);
	  dc->SelectObject(&pl2Malet.mBrush);
	  dc->Ellipse(pl2Malet.posX-20,pl2Malet.posY-20,pl2Malet.posX+20,pl2Malet.posY+20);
	  dc->Ellipse(pl2Malet.posX-17,pl2Malet.posY-17,pl2Malet.posX+17,pl2Malet.posY+17);
	  dc->Ellipse(pl2Malet.posX-10,pl2Malet.posY-10,pl2Malet.posX+10,pl2Malet.posY+10);
	}

	///////////////////////////////////////////////////////////////////////////
	// Izris èasa in rezultata
	///////////////////////////////////////////////////////////////////////////
	CString str;

    CFont* old_font = dc->SelectObject(&timeFont); 
	dc->SetTextColor(RGB(18,87,11));
	if(playTime.sec/10 < 1)
	 str.Format(_T("0%d:0%d"),playTime.min, playTime.sec);
	else
	 str.Format(_T("0%d:%d"),playTime.min, playTime.sec);

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
	int posX;
	if (rand()%2 == 0) posX = puck.posX + 100;
	//else posX = puck.posX - rand()%100;
	else posX = puck.posX - 100;
	int posY;
    if (rand()%2 == 0) posY = puck.posY + 100;
	//else posY = puck.posY - rand()%100;
	else posY = puck.posY - 100;

	puck.dirX = (double)posX - puck.posX;
	puck.dirY = (double)posY - puck.posY;
	double d = vcLength(puck.dirX, puck.dirY);
	puck.dirX /= d;
	puck.dirY /= d;
	puck.velocity = rand()%3+17;
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
//-----------------------------------------------------------------------------
void CChildView::EstimateNewPuckPossition(void)
///////////////////////////////////////////////////////////////////////////////
// Približek funkcije za izraèun položaja paka, vdolž smernega vektorja.
// Položaj je odvisen od hitrosti paka, v igri je potrebno upoštevati dejansko
// formulo za hitrost in izraèunati morebitno kolizijo z ro bom mize. 
///////////////////////////////////////////////////////////////////////////////
{
	puck.velocity*=0.995;
	puck.par = puck.velocity;
	puck.lastposX=puck.posX;
	puck.lastposY=puck.posY;
	 puck.posX += (int)puck.par*puck.dirX;
	 puck.posY += (int)puck.par*puck.dirY;
		pl2Malet.lastposY=pl2Malet.posY;
		//pl2Malet.posY=puck.posY;
	data.clear();
	data.push_back(puck.posX/825.0);
	data.push_back(puck.posY/415.0);
	data.push_back(puck.dirX/825.0);
	data.push_back(puck.dirY/415.0);
	data.push_back(pl1Malet.posX/825.0);
	data.push_back(pl1Malet.posY/415.0);

	//cout << "input: " << puck.posX/825.0 <<" "<<puck.posY/415.0<<" "<<puck.dirX/825.0<<" "<<puck.dirY/415.0<<" "<<pl1Malet.posX/825.0<<" "<<pl1Malet.posY/415.0 <<endl;
	result = network->calculate(data);
	cout << "x: " << result[0]*825 << ", y: " << result[1]*415 <<endl;
	pl1Malet.posX+=result[0]*825;
	pl1Malet.posY+=result[1]*415;
	result.clear();

	if(pl1Malet.posX < 45) {
		 pl1Malet.posX=46;
	 }
	 if(pl1Malet.posX > 825/2.0) {
		 pl1Malet.posX=825/2.0;
	 }
	 if(pl1Malet.posY < 45) {
		 pl1Malet.posY=46;
	 }
	 if(puck.posY > 415) {
		 pl1Malet.posY=414;
	 }
		
		
	 if(!validPuckPos()){
	
	 if(puck.posX < 45) {
		 puck.posX=46;
		 puck.dirX*=-1;
	 }
	 if(puck.posX > 825) {
		 puck.posX=824;
		 puck.dirX*=-1;
	 }
	 if(puck.posY < 45) {
		 puck.posY=46;
		 puck.dirY*=-1;
	 }
	 if(puck.posY > 415) {
		 puck.posY=414;
		 puck.dirY*=-1;
	 }
	 }
	 else {
		if(vcLength((puck.posX-pl1Malet.posX),(puck.posY-pl1Malet.posY))<=(puck.radius+pl1Malet.radius))
		{
		double dx=puck.posX-pl1Malet.posX;
		double dy=puck.posY-pl1Malet.posY;
		double razdalja=dx*dx+dy*dy;
		double k1=(dx*puck.dirX+dy*puck.dirY)/razdalja;
		double k2=(dx*puck.dirY-dy*puck.dirX)/razdalja;
		double k3=(dx*(pl1Malet.posX-pl1Malet.lastposX)+dy*(pl1Malet.posY-pl1Malet.lastposY))/razdalja;
		double k4=(dx*(pl1Malet.posY-pl1Malet.lastposY)-dy*(pl1Malet.posX-pl1Malet.lastposX))/razdalja;
		puck.dirY=(k3*dy+k2*dx);
		puck.dirX=(k3*dx-k2*dy);
		puck.velocity+=((pl1Malet.lastposX*-1)+pl1Malet.posX);
		puck.par = puck.velocity;
	    puck.posX += (int)puck.par*puck.dirX;
	    puck.posY += (int)puck.par*puck.dirY;
		}
		/*if(vcLength((puck.posX-pl2Malet.posX),(puck.posY-pl2Malet.posY))<=(puck.radius+pl2Malet.radius))
		{
		double dx=puck.posX-pl1Malet.posX;
		double dy=puck.posY-pl1Malet.posY;
		double razdalja=dx*dx+dy*dy;
		double k1=(dx*puck.dirX+dy*puck.dirY)/razdalja;
		double k2=(dx*puck.dirY-dy*puck.dirX)/razdalja;
		double k3=(dx*(pl1Malet.posX-pl2Malet.lastposX)/5+dy*(pl2Malet.posY-pl2Malet.lastposY)/5)/razdalja;
		double k4=(dx*(pl1Malet.posY-pl2Malet.lastposY)/5-dy*(pl2Malet.posX-pl2Malet.lastposX)/5)/razdalja;
		puck.dirY=(k3*dy+k2*dx);
		puck.dirX=(k3*dx-k2*dy);
		puck.velocity+=((pl2Malet.lastposX*-1)+pl2Malet.posX);
		puck.par = puck.velocity;
	    puck.posX += (int)puck.par*puck.dirX;
	    puck.posY += (int)puck.par*puck.dirY;
		}*/
	 }
}
//-----------------------------------------------------------------------------
void CChildView::OnShowWindow(BOOL bShow, UINT nStatus)
///////////////////////////////////////////////////////////////////////////////
// Inicializacija zaèetnih položajev igralcev in njihivih barv izrisa
///////////////////////////////////////////////////////////////////////////////
{
	CWnd::OnShowWindow(bShow, nStatus);

	AllocConsole();
	freopen ("CONOUT$", "w", stdout );

	tableBorPen = new CPen(PS_SOLID, 2, RGB(0,0,0));
	midLinePen = new CPen(PS_SOLID, 8, RGB(250,103,96));
	tableBlLine = new CPen(PS_SOLID, 4, RGB(183,199,245));
	redLinePen = new CPen(PS_SOLID, 2, RGB(254,174,183));
	tableBrush.CreateSolidBrush(RGB(242,240,240));

	//network = new NeuralNetwork(6, 1, 10, 2);
	network = new NeuralNetwork;
	if(!network->load("utezi_500_1x10.txt")) {
		MessageBox(_T("nn load error"),_T("error"), NULL);
	}

	// Nastavitev zacetnega polozaja prvega igralca
	pl1Malet.posX = 331;
	pl1Malet.posY = 230;
	pl1Malet.radius = MALET_RADIUS;
	pl1Malet.mPen = new CPen(PS_SOLID, 1, RGB(141,39,7));
	pl1Malet.mBrush.CreateSolidBrush(RGB(255,0,0));

    // Nastavitev zacetnega polozaja drugega igralca
	pl2Malet.posX = 531;
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
	int tick = GetTickCount();

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
		  ShowCursor(TRUE);     // skrijemo kurzor miške
	   }
	  }
	  else playTime.sec--;

	  startTick = tick;
	}
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
	CWnd::OnTimer(nIDEvent);
	EstimateNewPuckPossition();  // doloèitev položaja paka
    DetermineGoal();
    //if((pl1Score>6) || (pl2Score>6))
	//  KillTimer(1);

	//////////////////////// Ponovno aktiviramo timer /////////////////////////
	//SetTimer(1, 10, 0);     // Odkomentirati v primeru poèasnih funkcij
	///////////////////////////////////////////////////////////////////////////
	calcTime();
	Invalidate();
}


