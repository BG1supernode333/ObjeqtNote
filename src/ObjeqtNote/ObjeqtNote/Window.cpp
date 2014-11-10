#include "stdafx.h"
#include "Resource.h"
#include "Window.h"

BOOL CWindow::Create(LPCTSTR lpctszClassName, LPCTSTR lpctszWindowName, DWORD dwStyle, const RECT &rect, HWND hParentWnd, UINT nID, HINSTANCE hInstance){

	m_hWnd = CreateWindow(lpctszClassName, lpctszWindowName, dwStyle, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, hParentWnd, (HMENU)nID, hInstance, (void *)this);
	if (m_hWnd == NULL){
		return FALSE;
	}

	return TRUE;

}

BOOL CWindow::ShowWindow(int nCmdShow){

	return ::ShowWindow(m_hWnd, nCmdShow);

}

LRESULT CWindow::DynamicWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){

	return DefWindowProc(hwnd, uMsg, wParam, lParam);

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

ATOM CWindow::RegisterWndClass(HINSTANCE hInstance){

	WNDCLASS wc;

	wc.lpszClassName = _T("ObjeqtNote");
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = CWindow::StaticWindowProc;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_OBJEQTNOTE));
	wc.hCursor = LoadCursor(hInstance, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = MAKEINTRESOURCE(IDC_OBJEQTNOTE);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;

	return RegisterClass(&wc);

}