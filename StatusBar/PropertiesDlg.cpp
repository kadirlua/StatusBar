// PropertiesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "StatusBar.h"
#include "StatusBarObject.h"
#include "PropertiesDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropertiesDlg dialog


CPropertiesDlg::CPropertiesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPropertiesDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPropertiesDlg)
	/*m_nMaximum = 0;
	m_nMinimum = 0;*/
	//}}AFX_DATA_INIT
	m_nType = BST_UNCHECKED;
	strPaneText = "";
	strTimePaneText = "";
	m_strHelpPath.Empty();
}


void CPropertiesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropertiesDlg)
	/*DDX_Control(pDX, IDC_SPIN_MINIMUM, c_spinMin);
	DDX_Control(pDX, IDC_SPIN_MAXIMUM, c_spinMax);
	DDX_Text(pDX, IDC_MAXIMUM, m_nMaximum);
	DDX_Text(pDX, IDC_MINIMUM, m_nMinimum);*/
	DDX_Check(pDX,IDC_EXTRA_PANE,m_nType);
	DDX_Text(pDX, IDC_PANE_TEXT, strPaneText);
	DDX_Text(pDX, IDC_TIME_PANE_TEXT, strTimePaneText);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPropertiesDlg, CDialog)
	//{{AFX_MSG_MAP(CPropertiesDlg)
	ON_BN_CLICKED(IDC_BTN_HELP, OnBtnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropertiesDlg message handlers

BOOL CPropertiesDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	//c_EditStrText.SetWindowTextA(strText);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPropertiesDlg::OnBtnHelp() 
{
	// TODO: Add your control notification handler code here
	if(GetFileAttributes(m_strHelpPath) != -1)
	{
		ShellExecute(m_hWnd,"open",m_strHelpPath,NULL,NULL,SW_NORMAL);
	}
}
