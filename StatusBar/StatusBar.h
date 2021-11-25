// StatusBar.h : main header file for the StatusBar DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CStatusBarApp
// See StatusBar.cpp for the implementation of this class
//

class CStatusBarApp : public CWinApp
{
public:
	CStatusBarApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
