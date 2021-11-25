#pragma once
/////////////////////////////////////////////////////////////////////////////
// CCustomSliderCtrl window

class CCustomStatusBarCtrl : public CStatusBarCtrl
{
// Construction
public:
	CCustomStatusBarCtrl();

// Attributes
public:
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomSliderCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCustomStatusBarCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCustomSliderCtrl)
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	//afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()
};
