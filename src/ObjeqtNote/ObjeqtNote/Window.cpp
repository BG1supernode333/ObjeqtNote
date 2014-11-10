#include "stdafx.h"
#include "Window.h"

BOOL CWindow::Create(LPCTSTR lpctszClassName, LPCTSTR lpctszWindowName, DWORD dwStyle, const RECT &rect, HWND hParentWnd, UINT nID, HINSTANCE hInstance){

	m_hWnd = CreateWindow(lpctszClassName, lpctszWindowName, dwStyle, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, hParentWnd, (HMENU)nID, hInstance, NULL);
	if (m_hWnd == NULL){
		return FALSE;
	}

	return TRUE;

}