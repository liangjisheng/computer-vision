
// 0202-1.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMy02021App:
// See 0202-1.cpp for the implementation of this class
//

class CMy02021App : public CWinApp
{
public:
	CMy02021App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMy02021App theApp;