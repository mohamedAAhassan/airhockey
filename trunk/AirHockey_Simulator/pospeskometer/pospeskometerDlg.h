// pospeskometerDlg.h : header file
//
#include <fstream>

#include "enumser.h"
#include "afxwin.h"

#pragma once

using namespace std;


// CpospeskometerDlg dialog
class CpospeskometerDlg : public CDialog
{
// Construction
public:
	CpospeskometerDlg(CWnd* pParent = NULL);	// standard constructor
	~CpospeskometerDlg();

// Dialog Data
	enum { IDD = IDD_POSPESKOMETER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()


	// our own variables
	CEdit *console;
	CComboBox *comboPorts;
	CComboBox *comboBaudrate;
	CEdit *parseStatus;

	CSerialPort *port;
	char buffer[15];

//	CString bufferString;  /// delete

	int received;
//	int cprejetih;
//	int cizgubljenih;
//	int cnapacnih;
	//int absoluteReceived;
	int line;

	//bool isSearchingAccl;
	bool isSyncing;
	int syncingtime;

	
	bool headerFound;

//	fstream *f1, *f3;

	CString path;

	// for port enumeration
	CStringArray sPorts; // list of serial ports avaliable

	// our own methods
	void setEditText(CString str);
	void setStatusLabelText(CString str);
	void enumeratePorts();


	void sendDataToSerial();
	void sendDataToSerial(char *str);
	void readDataFromSerial();
	bool writeToFile(fstream *file1, fstream *file2, char data[15]); //(char* filename, CString data)
	

	void checksum(char *array, int len, char &kv_a, char &kv_b);
	bool checksumStatus(char *array, int len, char &kv_a, char &kv_b);

	void processErrors(char *buffer, int line, CString &snum_a, CString &snum_b);
//	CString parseStatus(char byte);

	short toShort(char byte);

	short returnCoordinate(char byte1, char byte2);
	CString returnCoordinateString(char byte1, char byte2, bool unsign = false);
	CString returnTimeString(char byte1, char byte2);
	double returnTime(char byte1, char byte2);
	CString SelectFile();

	void writeByte(fstream *handle, double a,double b,double c,char byte[30]);
	void PreveriSum();

	void connect();
	void disconnect();

	bool automaticConnection();

	void exitApp();

	int pool();

	void startGame();

	CString koordinatax;
	CString koordinatay;

	double timeSinceComm;



public:
	afx_msg LONG OnCommunication(UINT, LONG);
	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnBnClickedButtonSend();
	afx_msg void OnBnClickedButtonReceive();
	afx_msg void OnBnClickedButtonDisconnect();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedButtonContinious();

	afx_msg void OnBnClickedSelect();
	CButton drawall;
	afx_msg void OnObmocje();
	afx_msg void OnObmocje32774();
	afx_msg void OnHitrostvzorcenja40hz();
	afx_msg void OnHitrostvzorcenja160hz();
	afx_msg void OnHitrostvzorcenja640hz();
	afx_msg void OnHitrostvzorcenja2560hz();
	afx_msg void OnFileExit();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnFileConnect();
	afx_msg void OnFileDisconnect();
	afx_msg void OnBnClickedButtonAuto();
	afx_msg void OnStnClickedStaticDejanskahitrost();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	CStatic povezana_naprava;
	afx_msg void OnBnClickedButtonPlay();
	CStatic izpisX;
	CStatic izpisY;
	afx_msg void OnBnClickedButton8();
	afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnActivateApp(BOOL bActive, DWORD dwThreadID);
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButtonOpenscript();
	afx_msg void OnHelpAbout();
};
