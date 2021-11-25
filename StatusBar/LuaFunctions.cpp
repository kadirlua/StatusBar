#include "stdafx.h"
#include "LuaFunctions.h"
#include "StatusBarObject.h"
#include "IRPluginHelperFunctions.h"

int StatusBar_GetPaneText(lua_State *luaState)
{
	IRLUA_PLUGIN_ResetLastError(luaState);
	int nLastError = 0;

	CString strObjectName;
	CString sText="";

	int index = 0;
	int type;
	IRLUA_PLUGIN_CheckNumArgs(luaState,2);
	strObjectName = IRLUA_PLUGIN_CheckString(luaState,1);
	index = (int)IRLUA_PLUGIN_CheckNumber(luaState,2);

	CIRPluginObject* pObject = NULL;
	pObject = IRLUA_PLUGIN_GetObjectPtr(luaState,strObjectName);
	if(pObject)
	{
		int nSize = 1000;
		char szObjectID[1000];
		pObject->GetObjectID(szObjectID,&nSize);

		if(lstrcmp(szObjectID,"IR_STATUSBAR_OBJECT") == 0)
		{
			CStatusBarObject* pStatusBar = (CStatusBarObject*) pObject;
			if(pStatusBar->m_pStatusBarHolder)
			{
				if(pStatusBar->m_pStatusBarHolder->m_pStatusBarCtrl)
				{
					if(IsWindow(pStatusBar->m_pStatusBarHolder->m_pStatusBarCtrl->m_hWnd))
					{
						sText = pStatusBar->m_pStatusBarHolder->m_pStatusBarCtrl->GetText(index,&type);
						//pStatusBar->m_pStatusBarHolder->m_pStatusBarCtrl->GetPaneText(index,sText);
					}
				}
			}
		} else
		{
			nLastError = 1100; // "The specified object could not be found."
		}
	} else
	{
		nLastError = 1100; // "The specified object could not be found."
	}

	IRLUA_PLUGIN_SetLastError(luaState,nLastError);
	lua_pushstring(luaState,sText);
return 1;
};

int StatusBar_SetPaneText(lua_State *luaState)
{
	IRLUA_PLUGIN_ResetLastError(luaState);
	int nLastError = 0;

	CString strObjectName;
	LPCSTR sText = "";
	int index = 0;

	IRLUA_PLUGIN_CheckNumArgs(luaState,3);
	strObjectName = IRLUA_PLUGIN_CheckString(luaState,1);
	index = (int)IRLUA_PLUGIN_CheckNumber(luaState,2);
	sText = IRLUA_PLUGIN_CheckString(luaState,3);
	
	CIRPluginObject* pObject = NULL;
	pObject = IRLUA_PLUGIN_GetObjectPtr(luaState,strObjectName);
	if(pObject)
	{
		int nSize = 1000;
		char szObjectID[1000];
		pObject->GetObjectID(szObjectID,&nSize);

		if(lstrcmp(szObjectID,"IR_STATUSBAR_OBJECT") == 0)
		{
			CStatusBarObject* pStatusBar = (CStatusBarObject*) pObject;
			if(pStatusBar->m_pStatusBarHolder)
			{
				if(pStatusBar->m_pStatusBarHolder->m_pStatusBarCtrl)
				{
					if(IsWindow(pStatusBar->m_pStatusBarHolder->m_pStatusBarCtrl->m_hWnd))
					{
						pStatusBar->m_pStatusBarHolder->m_pStatusBarCtrl->SendMessage(SB_SETTEXT,index,(LPARAM)sText);
						//pStatusBar->m_pStatusBarHolder->m_pStatusBarCtrl->SetPaneText(index,sText,1);
					}
				}
			}
			//IRLUA_PLUGIN_RedrawObject(luaState,strObjectName);
		} else
		{
			nLastError = 1100; // "The specified object could not be found."
		}
	} else
	{
		nLastError = 1100; // "The specified object could not be found."
	}

	IRLUA_PLUGIN_SetLastError(luaState,nLastError);
return 0;
};

// LUA FUNCTIONS:

luaL_reg lib_StatusBar[] = {
	{"GetPaneText",StatusBar_GetPaneText},
	{"SetPaneText",StatusBar_SetPaneText},
		{NULL, NULL}
	};

void StatusBar_RegisterLuaFunctions(lua_State* luaState)
{
	luaL_openlib(luaState, "StatusBar", lib_StatusBar, 0);
}