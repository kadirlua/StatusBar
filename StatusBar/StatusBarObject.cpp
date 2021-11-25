// SliderObject.cpp: implementation of the CSliderObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "StatusBar.h"
#include "StatusBarObject.h"
#include "LuaFunctions.h"
#include "PropertiesDlg.h"
#include "Token.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStatusBarObject::CStatusBarObject()
{
	for(int i = 0; i < NUM_OB_EVENTS; i++)
		m_pEvents[i] = NULL;

	m_pEvents[0] = new IRPluginEventInfo;
	lstrcpy(m_pEvents[0]->m_szName,"On Focus");
	lstrcpy(m_pEvents[0]->m_szArgs,"");

	lstrcpy(m_szObjectID,"IR_STATUSBAR_OBJECT");

	m_pStatusBarHolder = NULL;
	m_nType = BST_UNCHECKED;
	strPaneText = "";
	strTimePaneText = "";

}

CStatusBarObject::~CStatusBarObject()
{
	for(int i = 0; i < NUM_OB_EVENTS; i++)
	{
		delete m_pEvents[i];
		m_pEvents[i] = NULL;
	}

	DestroyStatusBarCtrl();
}

void CStatusBarObject::DestroyStatusBarCtrl()
{
	if(m_pStatusBarHolder)
	{
		if(IsWindow(m_pStatusBarHolder->m_hWnd))
		{
			m_pStatusBarHolder->ShowWindow(SW_HIDE);
			m_pStatusBarHolder->DestroyWindow();
		}

		delete m_pStatusBarHolder;
		m_pStatusBarHolder = NULL;
	}
}

HWND CStatusBarObject::GetWindowHandle()
{
	if(m_pStatusBarHolder)
	{
		if(IsWindow(m_pStatusBarHolder->m_hWnd))
		{
			//To work with sizing
			return m_pStatusBarHolder->m_hWnd;
			/*
			if(m_pSliderHolder->m_pSliderCtrl)
			{
				if(IsWindow(m_pSliderHolder->m_pSliderCtrl->m_hWnd))
				{
					return m_pSliderHolder->m_pSliderCtrl->m_hWnd;
				}
			}
			*/
		}
	} 
	return NULL;
}

void CStatusBarObject::DrawDesign(HDC hDC, HWND hMainWnd, RECT rcObRect,BOOL bVisible,BOOL bEnabled)
{
	if(bVisible)
	{
		bEnabled = FALSE; // Always disabled at design-time

		if(!m_pStatusBarHolder)
			m_pStatusBarHolder = new CControlHolderWnd;
		
		m_pStatusBarHolder->m_bIsDesignTime = TRUE;

		DWORD dwStyle;

		dwStyle = WS_CHILD|WS_VISIBLE;
		if(!bEnabled)
		{
			dwStyle |= WS_DISABLED;
		}

		if(!IsWindow(m_pStatusBarHolder->m_hWnd))
		{
			if(!m_pStatusBarHolder->Create(NULL,"",dwStyle,rcObRect,CWnd::FromHandle(hMainWnd),
				6262))
			{
				DestroyStatusBarCtrl();
				return;
			} else
			{
				m_pStatusBarHolder->m_pStatusBarObject = this;
				m_pStatusBarHolder->m_pStatusBarCtrl->SetText(strPaneText,0,0);
				if (m_nType == BST_CHECKED)
				{
					int aWidths[2] = { rcObRect.right-100,-1};
					m_pStatusBarHolder->m_pStatusBarCtrl->SetParts(2,aWidths);
					m_pStatusBarHolder->m_pStatusBarCtrl->SetText(strTimePaneText,1,0);
				}
			}
		}

		m_pStatusBarHolder->MoveWindow(&rcObRect);
	} else
	{
		DestroyStatusBarCtrl();
	}
}

void CStatusBarObject::DrawRuntime(HDC hDC, HWND hMainWnd, RECT rcObRect,BOOL bVisible,BOOL bEnabled)
{
	if(!m_pStatusBarHolder)
		m_pStatusBarHolder = new CControlHolderWnd;

	m_pStatusBarHolder->m_bIsDesignTime = FALSE;
	m_pStatusBarHolder->m_bEnabledRT = bEnabled;

	DWORD dwStyle;

	dwStyle = WS_CHILD;
	
	if(bVisible)
	{
		dwStyle |= WS_VISIBLE;
	}

	if(!IsWindow(m_pStatusBarHolder->m_hWnd))
	{
		if(!m_pStatusBarHolder->CreateEx(WS_EX_TRANSPARENT,NULL,"",dwStyle,rcObRect,CWnd::FromHandle(hMainWnd),
			6262))
		{
			DestroyStatusBarCtrl();
			return;
		} else
		{
			m_pStatusBarHolder->m_pStatusBarObject = this;
			m_pStatusBarHolder->m_pStatusBarCtrl->SetText(strPaneText,0,0);
			if (m_nType == BST_CHECKED)
			{
				int aWidths[2] = { rcObRect.right-100,-1};
				m_pStatusBarHolder->m_pStatusBarCtrl->SetParts(2,aWidths);
				m_pStatusBarHolder->m_pStatusBarCtrl->SetText(strTimePaneText,1,0);
			}
		}
	}

	m_pStatusBarHolder->MoveWindow(&rcObRect);

	ShowWindow(bVisible);
}

void CStatusBarObject::ShowWindow(BOOL bVisible)
{
	if(bVisible)
	{
		if(m_pStatusBarHolder)
		{
			if(m_pStatusBarHolder->m_pStatusBarCtrl)
			{
				if(IsWindow(m_pStatusBarHolder->m_pStatusBarCtrl->m_hWnd))
				{
					m_pStatusBarHolder->m_pStatusBarCtrl->ShowWindow(SW_SHOW);
				}
			}
			if(IsWindow(m_pStatusBarHolder->m_hWnd))
			{
				m_pStatusBarHolder->ShowWindow(SW_SHOW);
			}
		}
	} else
	{
		if(m_pStatusBarHolder)
		{
			if(m_pStatusBarHolder->m_pStatusBarCtrl)
			{
				if(IsWindow(m_pStatusBarHolder->m_pStatusBarCtrl->m_hWnd))
				{
					m_pStatusBarHolder->m_pStatusBarCtrl->ShowWindow(SW_HIDE);
				}
			}
			if(IsWindow(m_pStatusBarHolder->m_hWnd))
			{
				m_pStatusBarHolder->ShowWindow(SW_HIDE);
			}
		}
	}
}

void CStatusBarObject::DoSetFocus()
{
	if(m_pStatusBarHolder)
	{
		if(IsWindow(m_pStatusBarHolder->m_hWnd))
		{
			if(m_pStatusBarHolder->m_pStatusBarCtrl)
			{
				if(IsWindow(m_pStatusBarHolder->m_pStatusBarCtrl->m_hWnd))
				{
					m_pStatusBarHolder->m_pStatusBarCtrl->SetFocus();
				}
			}
		}
	}
}

void CStatusBarObject::HideInternalObject()
{
	DestroyStatusBarCtrl();
}


BOOL CStatusBarObject::GetEvent(int nIndex, IRPluginEventInfo* pEventInfo)
{
	if((nIndex >= 0) && nIndex < NUM_OB_EVENTS)
	{
		if(m_pEvents[nIndex])
		{
			lstrcpy(pEventInfo->m_szName,m_pEvents[nIndex]->m_szName);
			lstrcpy(pEventInfo->m_szArgs,m_pEvents[nIndex]->m_szArgs);
			return TRUE;
		} else
		{
			return FALSE;
		}
	} else
	{
		return NULL;
	}
}

int CStatusBarObject::GetCustomProperties(char* szBuffer, int* pnBufferSize)
{
	memset(m_szPropertiesString,0,1000);

	wsprintf(m_szPropertiesString,"%d,%s,%s",m_nType,strPaneText,strTimePaneText);
	
	int nLength = lstrlen(m_szPropertiesString);
	if(*pnBufferSize < nLength)
	{
		*pnBufferSize = nLength;
		return -1;
	} else
	{
		memset(szBuffer,0,*pnBufferSize);
		lstrcpy(szBuffer,m_szPropertiesString);
		return nLength;
	}
	return 0;
}

void CStatusBarObject::SetCustomProperties(char* szPropsList)
{

	int nTokens = 0;
	CString sToken;

	CToken tok(szPropsList);
	tok.SetToken(",");

	while(tok.MoreTokens())
	{
		switch(nTokens)
		{
		case 0: // strtext
			m_nType = atoi(tok.GetNextToken());
			break;
		case 1:
			strPaneText = tok.GetNextToken();
			break;
		case 2:
			strTimePaneText = tok.GetNextToken();
			break;
		}
		nTokens++;
	}
}

BOOL CStatusBarObject::ShowProperties(char* szPluginFolder)
{
	BOOL bRet = FALSE;
	CPropertiesDlg dlgProps;

	CString strHelpFile;

	strHelpFile.Format("%s",szPluginFolder);
	strHelpFile.TrimRight("\\");
	strHelpFile += "\\GroupBox_Help.htm";
	
	dlgProps.m_nType = m_nType;
	dlgProps.strPaneText = strPaneText;
	dlgProps.strTimePaneText = strTimePaneText;
	if(dlgProps.DoModal() == IDOK)
	{
		bRet = TRUE;
		m_nType = dlgProps.m_nType;
		strPaneText = dlgProps.strPaneText;
		strTimePaneText = dlgProps.strTimePaneText;
	} else
	{
		bRet = FALSE;
	}
	return bRet;
}

int CStatusBarObject::GetNumEvents()
{
	return NUM_OB_EVENTS;
}

int CStatusBarObject::RegisterLUAFunctions(lua_State* L)
{
	// Always call base class first
	CIRPluginObject::RegisterLUAFunctions(L);

	StatusBar_RegisterLuaFunctions(L);

	return 0;
}