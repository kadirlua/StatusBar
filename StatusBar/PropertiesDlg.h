#pragma once
// PropertiesDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPropertiesDlg dialog

class CPropertiesDlg : public CDialog
{
// Construction
public:
	CPropertiesDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPropertiesDlg)
	enum { IDD = IDD_PROPERTIES };
	//
	//HICON hicon;
	int m_nType;
	CString strPaneText;
	CString strTimePaneText;
	//}}AFX_DATA

	CString m_strHelpPath;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropertiesDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPropertiesDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
