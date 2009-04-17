// AHokey.h : main header file for the AHokey application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CAHokeyApp:
// See AHokey.cpp for the implementation of this class
//

class CAHokeyApp : public CWinApp
{
public:
	CAHokeyApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CAHokeyApp theApp;