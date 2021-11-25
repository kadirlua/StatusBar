// CustomSliderCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "StatusBar.h"
#include "CustomStatusBarCtrl.h"
#include "ControlHolderWnd.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustomSliderCtrl

CCustomStatusBarCtrl::CCustomStatusBarCtrl()
{
}

CCustomStatusBarCtrl::~CCustomStatusBarCtrl()
{
}

BEGIN_MESSAGE_MAP(CCustomStatusBarCtrl, CStatusBarCtrl)
	//{{AFX_MSG_MAP(CCustomSliderCtrl)
	ON_WM_SETFOCUS()
	//ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomSliderCtrl message handlers


void CCustomStatusBarCtrl::OnSetFocus(CWnd* pOldWnd) 
{
	CStatusBarCtrl::OnSetFocus(pOldWnd);
	
	// TODO: Add your message handler code here
	CControlHolderWnd* pParent = (CControlHolderWnd*) GetParent();

	if(pParent)
	{
		pParent->m_pStatusBarObject->FireEvent("On Focus","");
	}
}

/*void CCustomStatusBarCtrl::OnSize(UINT nType, int cx, int cy) 
{
	CStatusBarCtrl::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	CControlHolderWnd* pParent = (CControlHolderWnd*) GetParent();

	if(pParent)
	{
		CRect rcClient;
		GetClientRect(&rcClient);
		int aWidths[2] = { rcClient.right-100,-1};
		pParent->m_pStatusBarCtrl->SetParts(2,aWidths);
	}
}*/