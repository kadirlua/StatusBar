#pragma once

#include "IRPluginObject.h"
#include "ControlHolderWnd.h"

#define NUM_OB_EVENTS 1

class CStatusBarObject : public CIRPluginObject  
{
public:
	CStatusBarObject();
	virtual ~CStatusBarObject();

	virtual void GetDefaultSize(SIZE* pSize) {pSize->cx=250;pSize->cy=24;};
	virtual BOOL IsWindowedObject() {return TRUE;};
	virtual HWND GetWindowHandle();

	virtual void DrawDesign(HDC hDC, HWND hMainWnd, RECT rcObRect,BOOL bVisible,BOOL bEnabled);
	virtual void DrawRuntime(HDC hDC, HWND hMainWnd, RECT rcObRect,BOOL bVisible,BOOL bEnabled);
	// Unused: virtual void HideInternalObject();
	virtual int GetCustomProperties(char* szBuffer, int* pnBufferSize);
	virtual void SetCustomProperties(char* szPropsList);
	virtual BOOL ShowProperties(char* szPluginFolder);
	virtual BOOL GetEvent(int nIndex, IRPluginEventInfo* pEventInfo);
	virtual int GetNumEvents();
	virtual int RegisterLUAFunctions(lua_State* L);
	virtual void HideInternalObject();
	virtual BOOL LetAMSHandleCursorChange() {return FALSE;};
	virtual BOOL LetAMSHandleSounds() {return FALSE;};
	virtual BOOL LetAMSHandleTooltip() {return TRUE;};
	virtual BOOL CanSetFocus() {return TRUE;};
	virtual void DoSetFocus();
	virtual void ShowWindow(BOOL bVisible);

	// Events from above...
	virtual void OnMouseOver(HWND hWndParent,POINT ptMousePos,RECT rcObRect)  {;};
	virtual void OnMouseLeave(HWND hWndParent,POINT ptMousePos,RECT rcObRect)  {;};
	virtual void OnLBtnDown(HWND hWndParent,POINT ptMousePos,RECT rcObRect) {;};
	virtual void OnLBtnUp(HWND hWndParent,POINT ptMousePos,RECT rcObRect)  {;};
	virtual void OnLBtnDoubleClick(HWND hWndParent,POINT ptMousePos,RECT rcObRect) {;};
	virtual void OnRBtnDown(HWND hWndParent,POINT ptMousePos,RECT rcObRect) {;};
	virtual void OnRBtnUp(HWND hWndParent,POINT ptMousePos,RECT rcObRect) {;};
	virtual void OnRBtnDoubleClick(HWND hWndParent,POINT ptMousePos,RECT rcObRect) {;};

protected:
	IRPluginEventInfo* m_pEvents[NUM_OB_EVENTS];
	char m_szPropertiesString[1000];
	void DestroyStatusBarCtrl();
public:
	CControlHolderWnd* m_pStatusBarHolder;
	int m_nType;
	CString strPaneText;
	CString strTimePaneText;
	//HICON hicon;
	//HICON hiconExtra;
};