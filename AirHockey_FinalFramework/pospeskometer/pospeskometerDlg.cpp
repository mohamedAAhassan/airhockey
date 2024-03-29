// pospeskometerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "pospeskometer.h"
#include "pospeskometerDlg.h"
#include <fstream>
#include <cmath>
#include "MFCopenGL.h"
#include <vector>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

// OpenGL GLUT interface
MFCopenGL gl;
bool nekaj=false;

/*********************************
	GLUT wrapper functions
	desc: for GLUT callback func
 *********************************/

void display(void)
{
	gl.display();
}

void reshape(int w, int h)
{
	gl.reshape(w, h);
}

void MouseMotion(int x, int y)
{
	gl.MouseMotion(x, y);
}

void animate()
{
	gl.animate();
}


/***********************************
	AboutDlg
	desc: about stuff, what else :)
 **********************************/
// CAboutDlg dialog used for App About
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

Position tocka;
Position prev_tocka;
Position prev_prev_tocka;
vector<Position>tocke;//vector position
vector<Position>sum_tocke;
double tmpcas=0;
double sec=0;
int show=0;//spremenljivka uporabljena v OnPint()
int st_tock;
int krmilo=0;

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CpospeskometerDlg dialog


/*****************************
	CPospeskometerDlg
	desc: communication part
 *****************************/
CpospeskometerDlg::CpospeskometerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CpospeskometerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

//	this->edit = NULL;
//	this->statusLabel = NULL;
	this->port = NULL;
	this->comboPorts = NULL;
	this->comboBaudrate = NULL;
//	this->accStatusLabel = NULL;
//	this->errorLabel = NULL;
///	this->f1 = this->f3 = NULL;

//	this->obmocje = NULL;
//	this->dejanskaHitrost = NULL;
//	this->prejetih = NULL;
//	this->izgubljenih = NULL;
//	this->napacnih = NULL;

	this->received = 0;

//	this->cprejetih = 0;
//	this->cizgubljenih = 0;
//	this->cnapacnih = 0;
	//this->absoluteReceived = 0;
//	this->line = 0;

//	isSearchingAccl = true;
	this->isSyncing = false;
	this->syncingtime = 0;
	this->headerFound = false;

	this->timeSinceComm = 0.0;

	this->path = "";

}

CpospeskometerDlg::~CpospeskometerDlg()
{
	if(this->port != NULL)
	{
		this->port->StopMonitoring();
		delete this->port;
		this->port = NULL;
	}
}

void CpospeskometerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_NAPRAVA, povezana_naprava);
	DDX_Control(pDX, IDC_STATIC17, izpisX);
	DDX_Control(pDX, IDC_STATIC18, izpisY);
}

BEGIN_MESSAGE_MAP(CpospeskometerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_COMM_RXCHAR, OnCommunication)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CpospeskometerDlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CpospeskometerDlg::OnBnClickedButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_RECEIVE, &CpospeskometerDlg::OnBnClickedButtonReceive)
	ON_BN_CLICKED(IDC_BUTTON_DISCONNECT, &CpospeskometerDlg::OnBnClickedButtonDisconnect)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CpospeskometerDlg::OnBnClickedButtonClear)
//	ON_BN_CLICKED(IDC_BUTTON_CONTINIOUS, &CpospeskometerDlg::OnBnClickedButtonContinious)

	ON_BN_CLICKED(IDC_SELECT, &CpospeskometerDlg::OnBnClickedSelect)
	ON_COMMAND(ID_OBMOCJE_, &CpospeskometerDlg::OnObmocje)
	ON_COMMAND(ID_OBMOCJE_32774, &CpospeskometerDlg::OnObmocje32774)
	ON_COMMAND(ID_HITROSTVZORCENJA_40HZ, &CpospeskometerDlg::OnHitrostvzorcenja40hz)
	ON_COMMAND(ID_HITROSTVZORCENJA_160HZ, &CpospeskometerDlg::OnHitrostvzorcenja160hz)
	ON_COMMAND(ID_HITROSTVZORCENJA_640HZ, &CpospeskometerDlg::OnHitrostvzorcenja640hz)
	ON_COMMAND(ID_HITROSTVZORCENJA_2560HZ, &CpospeskometerDlg::OnHitrostvzorcenja2560hz)
	ON_COMMAND(ID_FILE_EXIT, &CpospeskometerDlg::OnFileExit)
	ON_BN_CLICKED(IDCANCEL, &CpospeskometerDlg::OnBnClickedCancel)
	ON_COMMAND(ID_FILE_CONNECT, &CpospeskometerDlg::OnFileConnect)
	ON_COMMAND(ID_FILE_DISCONNECT, &CpospeskometerDlg::OnFileDisconnect)
	ON_BN_CLICKED(IDC_BUTTON_AUTO, &CpospeskometerDlg::OnBnClickedButtonAuto)
	ON_STN_CLICKED(IDC_STATIC_DEJANSKAHITROST, &CpospeskometerDlg::OnStnClickedStaticDejanskahitrost)
//	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BUTTON_PLAY, &CpospeskometerDlg::OnBnClickedButtonPlay)
	ON_BN_CLICKED(IDC_BUTTON8, &CpospeskometerDlg::OnBnClickedButton8)
	ON_WM_WINDOWPOSCHANGED()
	ON_WM_ACTIVATE()
	ON_WM_ACTIVATEAPP()
	ON_BN_CLICKED(IDC_BUTTON3, &CpospeskometerDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CpospeskometerDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON7, &CpospeskometerDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON_OPENSCRIPT, &CpospeskometerDlg::OnBnClickedButtonOpenscript)
	ON_COMMAND(ID_HELP_ABOUT, &CpospeskometerDlg::OnHelpAbout)
END_MESSAGE_MAP()


// CpospeskometerDlg message handlers

BOOL CpospeskometerDlg::OnInitDialog()
{
	show=0;
	prev_tocka.setPos();
	CDialog::OnInitDialog();
//	SetWindowPos(&CWnd::wndTopMost, 0, 0, 620, 780, SWP_SHOWWINDOW);

	// Add "About..." menu item to system menu.
	show=0;
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	this->parseStatus = (CEdit*)GetDlgItem(IDC_EDIT_PARSESTATUS); // get parse status handle
	this->console = (CEdit*)GetDlgItem(IDC_EDIT1); // get label handl
	this->comboPorts = (CComboBox*)GetDlgItem(IDC_COMBO_PORTS);
	this->comboBaudrate = (CComboBox*)GetDlgItem(IDC_COMBO_BAUDRATE);

	// other initialization
	this->enumeratePorts();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CpospeskometerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
		CDialog::OnSysCommand(nID, lParam);
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CpospeskometerDlg::OnPaint()
{
CPaintDC dc(this);

	// narise kvadrat
	/*dc.SetDCPenColor(RGB(0, 0, 0));
	dc.SetDCBrushColor(RGB(255, 255, 255));
	dc.SelectStockObject(DC_BRUSH);
	dc.SelectStockObject(DC_PEN);
	dc.Rectangle(0, 0, 500, 500);*/
	//

	/*if ( timeSinceComm > 0.0 )
	{


		if ( clock() - this->timeSinceComm  > 5.0)
		{
			MessageBox("Accelerometer comm failed, switching to mouse ...", "Error", NULL);
		}
	}*/

	//CBrush brush1(RGB(60, 200, 200));
	if(krmilo==2)
	{
		tocka=prev_tocka;
		koordinatax.Format("%f", tocka.PremikX);
		koordinatay.Format("%f", tocka.PremikY);
		povezana_naprava.SetWindowTextA("pospeskometer("+koordinatax+","+koordinatay+")");
	}
	else if(krmilo==1)
	{
				koordinatax.Format("%f", tocka.PremikX);
				koordinatay.Format("%f", tocka.PremikY);
				povezana_naprava.SetWindowTextA("miska("+koordinatax+","+koordinatay+")");
	}
	else
	{
		tocka=prev_tocka;
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CpospeskometerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CpospeskometerDlg::setEditText(CString str)
{
/// obsolete
}

void CpospeskometerDlg::setStatusLabelText(CString str)
{
//	if(this->statusLabel != NULL)
//		this->statusLabel->SetWindowTextA(_T(str));
}

void CpospeskometerDlg::OnBnClickedButtonConnect()
{
	this->connect();
}

void CpospeskometerDlg::OnBnClickedButtonSend()
{
	this->sendDataToSerial();
}

void CpospeskometerDlg::OnBnClickedButtonReceive()
{
	//this->port->StartMonitoring();
	//this->readDataFromSerial();
}

void CpospeskometerDlg::OnBnClickedButtonDisconnect()
{
	this->disconnect();
	gl.setMouseControl();
}

void CpospeskometerDlg::enumeratePorts()
{
	// enumerate
	if(CEnumerateSerial::UsingRegistry(this->sPorts))
		for(int i=0; i<sPorts.GetSize(); i++)
			this->comboPorts->InsertString(i, sPorts[i].GetString());
	else
		MessageBox("Enumeration of serial ports failed!", "Error!", NULL);
}

void CpospeskometerDlg::sendDataToSerial()
{
// obsolete
}

void CpospeskometerDlg::sendDataToSerial(char *str)
{
	if(this->port != NULL)
		port->WriteToPort(str);
	else
		MessageBox("Serial port is closed!", "Error!", NULL);
}

void CpospeskometerDlg::writeByte(fstream *handle, double a,double b,double c,char byte[30])
{
	if ( handle != NULL)
		(*handle) <<a<<' '<<b<<' '<<c<<' '<<byte<<endl;
}

void CpospeskometerDlg::PreveriSum()
{
	int sum=5;
	if(tocka.x>prev_tocka.x-sum && tocka.x<prev_tocka.x+sum)
	{
		tocka.x=prev_tocka.x;
	}
	if(tocka.y>prev_tocka.y-sum && tocka.y<prev_tocka.y+sum)
	{
		tocka.y=prev_tocka.y;
	}
	if(tocka.z>prev_tocka.z-sum && tocka.z<prev_tocka.z+sum)
	{
		tocka.z=prev_tocka.z;
	}

}
void CpospeskometerDlg::readDataFromSerial()
{
 /// obsolete
}
 ////// obsolete
 /// obsolete
void CpospeskometerDlg::checksum(char *array, int len, char &kv_a, char &kv_b)
{
	kv_a = 0;
	kv_b = 0;
	for(int i=0; i<len; i++)
	{
		kv_a += array[i];
		kv_b += kv_a;
	}
}


//// ne vrne samo izr. kv_a in kv_b ampak tudi info, ali se izrac. checksum ujema z checksumom na kontrolerju
bool CpospeskometerDlg::checksumStatus(char *array, int len, char &kv_a, char &kv_b)
{
		/*
		KV_A=0; KV_B=0;
		for (i=0; i<13; i++) {
		  KV_A=KV_A+sporočilo[i]
		  KV_B=KV_B+KV_A
		}
		*/
	kv_a = 0;
	kv_b = 0;
	for(int i=0; i<len; i++)
	{
		kv_a += array[i];
		kv_b += kv_a;
	}

	return kv_a == array[len] && kv_b == array[len+1] ? true : false;
}

void CpospeskometerDlg::processErrors(char *buffer, int line, CString &snum_a, CString &snum_b)
{
	/************ checksum **************/
//	char kv_a, kv_b; // prostor za izracunane kontrolne vsote
//	bool checksumStatus = this->checksumStatus(buffer, 13, kv_a, kv_b); // izracuna checksum in vrne status

	//snum_a.Format("%d", this->toShort((unsigned short)kv_a)); // vrne niz za checksum po ref.	 
//	snum_b.Format("%d", this->toShort((unsigned short)kv_b));

//	CString numStr;

	//CString numStr; // niz za stevilko vrstice
//	if(!checksumStatus) // napaka, kontrolne vsote se ne ujemajo
//	{
//		this->cnapacnih ++;
	//	numStr.Format("%d", cnapacnih);
	//	this->napacnih->SetWindowTextA(_T("Broken packets: " + numStr));




	//	numStr.Format("%d", line);
	//	this->errorLabel->ReplaceSel("Error: checksum missmatch, line: " + numStr + "\r\n");
	//}

	/*********** statusni byte ***************/
	// byte na mestu z indkesom 2 (3 element, takoj za glavi) je status
	//if ( (buffer[2] & 1) != 0) // ce bit 1 statusa razlicen od 0
	//{
		/// ... 0000 -> ok
		/// ... 0001 -> prejnsji vzorec ni bil poslan
	//	numStr.Format("%d", line);
	//	this->errorLabel->ReplaceSel("Error: previous sample has not been sent, line: " + numStr + "\r\n");
	//}
//	else if ( (buffer[2] & 2) != 0) // ce bit 2 statusa razlicen od 0 
//	{
		/// ... 0000 -> ok
		/// ... 0010 -> prejnsji vzorec zgresen ( 2 == 0010 )
	//	this->cizgubljenih ++;
	//	numStr.Format("%d", cizgubljenih);
	//	this->izgubljenih->SetWindowTextA(_T("Packets lost: " + numStr));

	//	numStr.Format("%d", line);
	//	this->errorLabel->ReplaceSel("Error: previous sample has been missed, line: " + numStr + "\r\n");
//	}
}

/*CString CpospeskometerDlg::parseStatus(char byte)
{



	CString status = "";
	//int tmp = byte & 255;

	switch( byte & 255  )  // statussni_byte IN(and) 1111 1111
	{
	case 0: // 0000 0000 IN 1111 1111 == 0
		status = "-2 do 2g, 40Hz";
		break;

	case 128: // 1000 0000 IN 1111 1111 == 1000 0000 == 128 ... itd. :)
		status = "-6 do 6g, 40Hz";
		break;

	case 32:
		status = "-2 do 2g, 160Hz";
		break;

	case 16:
		status = "-2 do 2g, 640Hz";
		break;

	case 160:
		status = "-6 do 6g, 160Hz";
		break;

	case 144:
		status = "-6 do 6g, 640Hz";
		break;

	case 48:
		status = "-2 do 2g, 2560Hz";
		break;

	case 176:
		status = "-6 do 6g, 2560Hz";
		break;

	default:
		status = "STATUS ERROR";
	}

	return status;
}*/

short CpospeskometerDlg::toShort(char byte)
{
	 return byte < 0 ? (unsigned short)byte-65280 : (short)byte;
}



short CpospeskometerDlg::returnCoordinate(char byte1, char byte2)
{
	short abc = ((unsigned char)byte1 << 8) + (unsigned char)byte2;
	return abc;
}

CString CpospeskometerDlg::returnCoordinateString(char byte1, char byte2, bool unsign)
{
	CString coordStr;

	if(unsign)
		coordStr.Format("%u", (unsigned short)(((unsigned char)byte1 << 8) + (unsigned char)byte2)); // zdruzi bufferje, pretvori v desetisko in vrni celo koordinato
	else
		coordStr.Format("%i", (short)(((unsigned char)byte1 << 8) + (unsigned char)byte2)); // zdruzi bufferje, pretvori v desetisko in vrni celo koordinato

	return coordStr;
}

CString CpospeskometerDlg::returnTimeString(char byte1, char byte2)
{
	double cas=0;
	/**/
	CString coordStr;
	
	cas=this->returnCoordinate(byte1, byte2);
	cas/=65625;
	if(tmpcas>cas)
		sec++;
	tmpcas=cas;
	cas=sec+cas;
	coordStr.Format( _T("%f"), cas );
	return coordStr;
}

double CpospeskometerDlg::returnTime(char byte1, char byte2)
{
	double cas=0;
	cas = this->returnCoordinate(byte1, byte2);// / 65625;
	cas/=65625;
	if(tmpcas>cas)
		sec++;
	tmpcas=cas;
	cas=sec+cas;

	return cas;
}

TCHAR filtri[] = _T("Tekstovne datoteke (*.txt)|*.txt|(*.poly)|*.poly||"); //filtri za datoteke
CString CpospeskometerDlg::SelectFile()
{
	CString pot;
	CFileDialog dlg(true, _T("txt"), _T("*.txt"), OFN_PATHMUSTEXIST|OFN_HIDEREADONLY|OFN_EXTENSIONDIFFERENT, filtri);
	//CFileDialog dlg(
	dlg.m_ofn.lpstrTitle = _T("Izberi...");

	if(dlg.DoModal() == IDOK)
	{
		pot = dlg.GetPathName();

		if(pot==_T(""))
		{
			MessageBox(_T("Napaka: odprta ni nobena datoteka!"));
			return "";

		}
	}

	return pot;
}

bool CpospeskometerDlg::writeToFile(fstream *file1, fstream *file2, char data[15]) //(char* filename, CString data)
{
	if (file1 == NULL || file2 == NULL)
		return false;
	else
	{
		if(!file1->is_open() || !file2->is_open())
			return false;  // ce datoteka ni odprta, vrne false
		else
		{
			file1->write(data, 15); // zapise zapis v datoteko
			//CTime currentTime = CTime::GetCurrentTime();
			double t = CTime::GetCurrentTime().GetTime();
			CString dt;
			dt.Format("%d", t);
			file2->write(dt, dt.GetLength());
		}
	}

	return true;
}

void CpospeskometerDlg::OnBnClickedSelect()
{
	/*this->path = this->SelectFile();

	if(this->path != "")
	{
		this->f1 = new fstream;
		this->f3 = new fstream;

		f1->open(this->path, fstream::binary | fstream::out);
			
		this->path.Delete(this->path.GetLength()-4, 4);
		this->path += "_time.txt";

		f3->open(this->path, fstream::out);
	}*/
	//else
	//{
	//}
}




// event ob kliku gumba clear
void CpospeskometerDlg::OnBnClickedButtonClear()
{
 /// obsolete
}




			CString tmpWord="";
LONG CpospeskometerDlg::OnCommunication(WPARAM ch, LPARAM port)
{
	this->timeSinceComm = clock();

	//if (this->port != NULL)
//	{
		if(isSyncing)
		{
//			this->errorLabel->ReplaceSel("Packets broken, attempting to sync... \r\n");

			if (this->syncingtime > 100)
			{
				MessageBox("Sync failed, switching to mouse.", "Error", NULL);
				this->isSyncing = false;
				this->port->StopMonitoring();
				gl.setMouseControl();
			}
			else
			{
				gl.unsetMouseControl();
			}
			if ((char)ch == (char)255 && this->headerFound) // nasli smo prvi byte glave drugic
			{
				this->buffer[received] = (char)ch;
				this->received ++;
				this->isSyncing = false; // nasli smo glavo, prenehaj z sihronizacijo, zacni z komun.
				this->headerFound = false;

//				this->errorLabel->ReplaceSel("Oh the joy! Sync successful!\r\n ");

				this->syncingtime = 0;
			}
			else if ((char)ch == (char)255) // nasli smo prvi byte glave prvic
			{
				this->headerFound = true;
				this->buffer[received] = (char)ch;
				this->received ++;
				this->syncingtime ++;
			}
			else 
			{
				this->headerFound = false;
				this->received = 0;
				this->syncingtime ++;
			}
		}


		else if (!this->isSyncing)
		{
			if (this->received == 15 || this->received == 1) // na indeksu 0 in 1 preverimo glavo paketa
			{
				if ( ch != 255 ) // se nam je pokvaril paket?
					this->isSyncing = true; // postavimo sihronizacijsko zastavico
			}
			CString oneChar;
			CString skv_a, skv_b;
//			this->errorLabel->SetWindowTextA(""); // clear error console
		//	CString status; // noter vrnemo niz, ki vsebuje podatke o statusu(vzorcenje itd.)

			double x,y,z,cas;
			CString str;

			if (this->received > 14)
			{
				//////////
				//	this->console->ReplaceSel(tmpWord + "\r\n");
				//	tmpWord = "";
				//////////////////////////

			//	this->processErrors(this->buffer, line, skv_a, skv_b);


				this->received = 0; // resetira stevec rel. prejetih zlogov
				this->line ++;

				////////////////// risanje //////////////////
					x = this->returnCoordinate(this->buffer[4], this->buffer[3]);
					y =  this->returnCoordinate(this->buffer[6], this->buffer[5]);
					z =  0;
					cas = this->returnTime(this->buffer[10], this->buffer[9]);
					if(x<200&&x>-200)x=0;
					if(y<200&&y>-200)y=0;
					PreveriSum();
					tocka.setPos(prev_tocka,x,y,z,cas);
					tocka.checkPos(prev_tocka);
					gl.getUserPak()->setPos(tocka.PremikX,tocka.PremikY);
					gl.getUserPak()->setDir((tocka.PremikX-prev_tocka.PremikX)/3,(tocka.PremikY-prev_tocka.PremikY)/3);
					gl.getUserPak()->UpdatePos();
					prev_tocka=tocka;	


			this->buffer[this->received] = (char)ch;
			this->received ++;
		}                       
	}   ///// !!!! (test it)

	return 0;
}


int CpospeskometerDlg::pool()
{
	SerialMap::CSerialPort poolSerial;

	DWORD count=0;

	for (int i=0; i<this->sPorts.GetSize(); i++)
	{
		try
		{
 			poolSerial.Open((int)(this->sPorts[i][3])-48, 1200, SerialMap::CSerialPort::NoParity, 8, SerialMap::CSerialPort::OneStopBit, SerialMap::CSerialPort::XonXoffFlowControl);
 			poolSerial.Set0WriteTimeout();
 			poolSerial.Set0ReadTimeout();
			count = poolSerial.Read(this->buffer, 15); 

			if (count == 15) // prebrali smo 15 bajtov, preverimo, ce najdemo glavo
			{
				for (int j=0; j<15; j ++)
				{
					if ((this->buffer[j] == -1) && (j<14) )
					{
						if (this->buffer[j+1] == -1)
							// glava najdena, vrnemo st. porta
							return (int)(this->sPorts[i][3])-48; // 47... -48 + 1
					}
				}
			}
		}
        catch (SerialMap::CSerialException* pEx)
        {
              //  TRACE(_T("Handle Exception, Message:%s\n"), pEx->GetErrorMessage().operator LPCTSTR());
               // pEx->Delete();
        }

	}

	return -1;
}

void CpospeskometerDlg::OnObmocje()
{
	this->sendDataToSerial("2");
}

void CpospeskometerDlg::OnObmocje32774()
{
	this->sendDataToSerial("6");
}

void CpospeskometerDlg::OnHitrostvzorcenja40hz()
{
	this->sendDataToSerial("a");
}

void CpospeskometerDlg::OnHitrostvzorcenja160hz()
{
	this->sendDataToSerial("b");
}

void CpospeskometerDlg::OnHitrostvzorcenja640hz()
{
	this->sendDataToSerial("c");
}

void CpospeskometerDlg::OnHitrostvzorcenja2560hz()
{
	this->sendDataToSerial("d");
}

void CpospeskometerDlg::OnFileExit()
{
	this->exitApp();
}

void CpospeskometerDlg::OnBnClickedCancel()
{
	this->exitApp();
}

void CpospeskometerDlg::connect()
{
	if ( this->port == NULL )
	{
		if ( this->comboPorts->GetCurSel() != CB_ERR && this->comboBaudrate->GetCurSel() != CB_ERR)
		{
			this->port = new CSerialPort;

			tocke.clear();
			show=0;
			sec=0;

			CString itemBaudrate; // current item string
			CString itemPort;

			//CString str;
			prev_tocka.setPos();

			this->comboBaudrate->GetLBText(this->comboBaudrate->GetCurSel(), itemBaudrate); // get selection from baudrate combo
			this->comboPorts->GetLBText(this->comboPorts->GetCurSel(), itemPort); // get selection from baudrate combo

			if (this->port->InitPort(this, (int)(itemPort[3])-48, atoi((LPCSTR)itemBaudrate)))
			{
				// OK
				this->port->StartMonitoring();
				this->setStatusLabelText("Status: port opened, " + itemPort + ", speed: " +  itemBaudrate + "kb/s");
			}
			else
			{
				// ERROR
				this->setStatusLabelText("Status: error opening port");
				delete this->port;
				this->port = NULL;
			}
		}
		else MessageBox("Please select baudrate and/or port.", "Error", NULL);
	}
	else
		MessageBox("Port already open.", "Error", NULL);

	
}

bool CpospeskometerDlg::automaticConnection()
{
	
	if ( this->port == NULL)
	{
		if ( this->comboBaudrate->GetCurSel() != CB_ERR)
		{
			this->port = new CSerialPort;

			tocke.clear();
			show=0;
			sec=0;
			
			CString itemBaudrate=""; // current item string
			//CString itemPort;

			//CString str;
			prev_tocka.setPos();
			this->comboBaudrate->GetLBText(this->comboBaudrate->GetCurSel(), itemBaudrate); // get selection from baudrate combo
			//this->comboPorts->GetLBText(this->comboPorts->GetCurSel(), itemPort); // get selection from baudrate combo
			int port = this->pool();

			if (port != -1)
			{
				if (this->port->InitPort(this, port, atoi((LPCSTR)itemBaudrate)))
				{
					// OK
					this->port->StartMonitoring();
					CString itemPort;
					itemPort.Format("%i", port);
					this->setStatusLabelText("Status: port opened, " + itemPort + ", speed: " +  itemBaudrate + "kb/s");
					return true;
				}
				else
				{
					// ERROR
					this->setStatusLabelText("Status: error opening port");
					delete this->port;
					this->port = NULL;
					return false;
				}
			}
			else
			{
				MessageBox("Accelerometer device not found. Switching to mouse.", "Error", NULL);
				return false;

			}
		}
			this->port = new CSerialPort;

			tocke.clear();
			show=0;
			sec=0;
			
			//CString itemBaudrate=""; // current item string
			//CString itemPort;

			//CString str;
			prev_tocka.setPos();
		//	this->comboBaudrate->GetLBText(this->comboBaudrate->GetCurSel(), itemBaudrate); // get selection from baudrate combo
			//this->comboPorts->GetLBText(this->comboPorts->GetCurSel(), itemPort); // get selection from baudrate combo
			int port = this->pool();

			if (port != -1)
			{
				if (this->port->InitPort(this, port, 1200))
				{
					// OK
					this->port->StartMonitoring();
					CString itemPort;
					itemPort.Format("%i", port);
					this->setStatusLabelText("Status: port opened, " + itemPort + ", speed: 1200 (default)"  + "kb/s");
					return true;
				}
				else
				{
					// ERROR
					this->setStatusLabelText("Status: error opening port");
					delete this->port;
					this->port = NULL;
					return false;
				}
			}
			else
			{
				MessageBox("Accelerometer device not found. Switching to mouse.", "Error", NULL);
				return false;

			}
	}
	{
		MessageBox("Port already open.", "Error", NULL);
		return false;
	}
}

void CpospeskometerDlg::disconnect()
{
	// button disconnect: check if we have serial port object
	if(this->port != NULL)
	{
		this->port->StopMonitoring();
		//delete this->port; // delete serial port object
		//this->port = NULL; // set pointer to NULL
		//this->port->~CSerialPort();
		//delete this->port;
		//this->port = NULL;
//		this->statusLabel->SetWindowTextA(_T("Status: Connected, not monitoring"));
	}
}
void CpospeskometerDlg::OnFileConnect()
{
	if(!this->automaticConnection())	// ce vrne false, pojdi na misko
		gl.setMouseControl();
	else
		gl.unsetMouseControl();

	this->startGame();
}

void CpospeskometerDlg::OnFileDisconnect()
{
	this->disconnect();
	gl.setMouseControl();
}


void CpospeskometerDlg::exitApp()
{
	//this->disconnect();
	OnCancel();
}
void CpospeskometerDlg::OnBnClickedButtonAuto()
{
	if(!this->automaticConnection())	// ce vrne false, pojdi na misko
		gl.setMouseControl();
	else
		gl.unsetMouseControl();

	this->startGame();
}

void CpospeskometerDlg::OnStnClickedStaticDejanskahitrost()
{
	// TODO: Add your control notification handler code here
}


void CpospeskometerDlg::OnBnClickedButtonPlay()
{
	prev_tocka.setPos();
	this->startGame();
}

void CpospeskometerDlg::startGame()
{
	//glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize (1024, 768);
    glutInitWindowPosition (100, 100);
	glutCreateWindow ("AirHockey 3D :D");
    glutPassiveMotionFunc(MouseMotion);
    gl.init ();
    glutDisplayFunc (display);
    glutIdleFunc (display);

    glutReshapeFunc (reshape);
    glutMainLoop ();
}
void CpospeskometerDlg::OnBnClickedButton8()
{
	
					//this->SetWindowPos(&CWnd::wndBottom, 0,0, 0, 0,SWP_MOVE|SWP_SIZE|SWP_ACTIVATE);
	nekaj=true;
	// TODO: Add your control notification handler code here
	gl.getUserPak()->setPos(gl.getUserPak()->getPos().getX()+0.01,gl.getUserPak()->getPos().getY()+0.01);
}

void CpospeskometerDlg::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
	CDialog::OnWindowPosChanged(lpwndpos);

	// TODO: Add your message handler code here
}

void CpospeskometerDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialog::OnActivate(nState, pWndOther, bMinimized);

	// TODO: Add your message handler code here
}

void CpospeskometerDlg::OnActivateApp(BOOL bActive, DWORD dwThreadID)
{
	CDialog::OnActivateApp(bActive, dwThreadID);

	// TODO: Add your message handler code here
}


void CpospeskometerDlg::OnBnClickedButton3()
{
		this->connect();
}

void CpospeskometerDlg::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here
	gl.setMouseControl();
	this->startGame();
}

void CpospeskometerDlg::OnBnClickedButton7()
{
			//this->statusLabel->SetWindowTextA(_T(str));
	CString str;
	this->console->GetWindowTextA(str);
	//MessageBox(str, ":)", NULL);

	gl.getParser()->compileString(gl.g_list, (LPCTSTR)str);
	this->parseStatus->SetWindowTextA(gl.getParser()->g_Error.c_str());
	//this->parseStatus->SetW
}

void CpospeskometerDlg::OnBnClickedButtonOpenscript()
{
	this->path = this->SelectFile();

	if ( this->path != "")
	{
		gl.getParser()->compileFile(gl.g_list,  (char *)(LPCTSTR)this->path);
		this->parseStatus->SetWindowTextA(gl.getParser()->g_Error.c_str());
	}
}

void CpospeskometerDlg::OnHelpAbout()
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}
