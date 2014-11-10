#include "stdafx.h"
#include "Window.h"

BOOL CWindow::Create(LPCTSTR lpctszClassName, LPCTSTR lpctszWindowName, DWORD dwStyle, const RECT &rect, HWND hParentWnd, UINT nID, HINSTANCE hInstance){

	m_hWnd = CreateWindow(lpctszClassName, lpctszWindowName, dwStyle, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, hParentWnd, (HMENU)nID, hInstance, (void *)this);
	if (m_hWnd == NULL){
		return FALSE;
	}

	return TRUE;

}

LRESULT CALLBACK CWindow::StaticWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){

	if (uMsg == WM_CREATE){
		if (lParam != NULL){
			LPCREATESTRUCT lpCS = (LPCREATESTRUCT)lParam;
			if (lpCS->lpCreateParams != NULL){
				CWindow *pWindow = (CWindow *)lpCS->lpCreateParams;
				SetProp(hwnd, _T("Object"), (HANDLE)pWindow);
				return 0;
			}
		}
	}
	else if (uMsg == WM_DESTROY){

		PostQuitMessage(0);
		SetProp(hwnd, _T("Object"), NULL);

	}
	else{

		CWindow *pWindow = (CWindow *)GetProp(hwnd, _T("Object"));
		if (pWindow != NULL){

			return pWindow->DynamicWindowProc(hwnd, uMsg, wParam, lParam);

		}
	
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);

}

LRESULT CWindow::DynamicWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){

	return DefWindowProc(hwnd, uMsg, wParam, lParam);

}