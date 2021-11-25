// ControlHolderWnd.cpp : implementation file
//

#include "stdafx.h"
#include "StatusBar.h"
#include "ControlHolderWnd.h"
#include "IRPluginHelperFunctions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CControlHolderWnd

CControlHolderWnd::CControlHolderWnd()
{
	m_pStatusBarCtrl = NULL;
	m_pStatusBarObject = NULL;
	m_bIsDesignTime = TRUE;
	m_bEnabledRT = TRUE;
}

CControlHolderWnd::~CControlHolderWnd()
{
	DestroySliderCtrl();
}

BEGIN_MESSAGE_MAP(CControlHolderWnd, CWnd)
	//{{AFX_MSG_MAP(CControlHolderWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CControlHolderWnd message handlers
void CControlHolderWnd::DestroySliderCtrl()
{
	if(m_pStatusBarCtrl)
	{
		if(IsWindow(m_pStatusBarCtrl->m_hWnd))
		{
			m_pStatusBarCtrl->ShowWindow(SW_HIDE);
			m_pStatusBarCtrl->DestroyWindow();
		}

		delete m_pStatusBarCtrl;
		m_pStatusBarCtrl = NULL;
	}
}

int CControlHolderWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	
	// TODO: Add your specialized creation code here

	DWORD dwStyle = WS_CHILD |WS_VISIBLE /*| SBARS_SIZEGRIP*/;

	if(m_bIsDesignTime == FALSE)
	{
		if(m_bEnabledRT == FALSE)
		{
			dwStyle |= WS_DISABLED;
		}
	}
	m_pStatusBarCtrl = new CCustomStatusBarCtrl;
	if(!m_pStatusBarCtrl->Create(dwStyle,CRect(0,0,0,0),this,ID_VIEW_STATUS_BAR))
	{
		return -1;
	}
	return 0;
}

void CControlHolderWnd::PositionChild()
{
	if(!m_pStatusBarCtrl) return;
	if(!IsWindow(m_pStatusBarCtrl->m_hWnd)) return;

	CRect rcClient;
	GetClientRect(&rcClient);
	m_pStatusBarCtrl->MoveWindow(&rcClient);
	int m_pParts[2];
	int m_Result = m_pStatusBarCtrl->GetParts(2,m_pParts);
	if (m_Result>=2)
	{
		int aWidths[2] = { rcClient.right-100,-1};
		m_pStatusBarCtrl->SetParts(2,aWidths);
	}
}

void CControlHolderWnd::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	PositionChild();
}

void CControlHolderWnd::DoAutoTab(BOOL bNextField)
{
	if(m_pStatusBarObject)
	{
		IRLUA_PLUGIN_DoAutoTab(m_pStatusBarObject->m_pLuaState,bNextField);
	}
}