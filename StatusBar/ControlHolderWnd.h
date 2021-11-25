#pragma once

/////////////////////////////////////////////////////////////////////////////
// CControlHolderWnd window
#include "IRPluginObject.h"
#include "CustomStatusBarCtrl.h"

class CControlHolderWnd : public CWnd
{
// Construction
public:
	CControlHolderWnd();
// Attributes
public:
	CCustomStatusBarCtrl *m_pStatusBarCtrl;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CControlHolderWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CControlHolderWnd();
	void DestroySliderCtrl();
	void PositionChild();

	CIRPluginObject* m_pStatusBarObject;
	void DoAutoTab(BOOL bNextField);

	BOOL m_bIsDesignTime;
	BOOL m_bEnabledRT;

	// Generated message map functions
	
protected:
	//{{AFX_MSG(CControlHolderWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
