#include "stdafx.h"
#include "ObjeqtNote.h"
#include "Resource.h"
#include "Window.h"

#if 1

ATOM CWindow::RegisterWindowClass(HINSTANCE hInstance){

	WNDCLASS wc;

	wc.lpszClassName = _T("CWindow_DefaultWindow");
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = CWindow::StaticWindowProc;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wc.hCursor = LoadCursor(hInstance, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;

	return CWindow::RegisterWindowClass(&wc);

}

ATOM CWindow::RegisterWindowClass(WNDCLASS *lpWC){

	return RegisterClass(lpWC);

}

LRESULT CALLBACK CWindow::StaticWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){

	CWindow *pWindow = NULL;
	HANDLE h = NULL;

	switch (uMsg){

		case WM_CREATE:

			{

				h = GetProp(hwnd, _T("CWindow_Object"));
				if (h != NULL){
					return DefWindowProc(hwnd, uMsg, wParam, lParam);
				}

				LPCREATESTRUCT lpCS = (LPCREATESTRUCT)lParam;
				if (lpCS == NULL){
					return DefWindowProc(hwnd, uMsg, wParam, lParam);
				}

				if (lpCS->lpCreateParams == NULL){
					return DefWindowProc(hwnd, uMsg, wParam, lParam);
				}

				pWindow = (CWindow *)lpCS->lpCreateParams;
				SetProp(hwnd, _T("CWindow_Object"), (HANDLE)pWindow);

			}

			break;

		case WM_DESTROY:

			{

				h = GetProp(hwnd, _T("CWindow_Object"));
				if (h == NULL){
					return DefWindowProc(hwnd, uMsg, wParam, lParam);
				}

				pWindow = (CWindow *)h;
				SetProp(hwnd, _T("CWindow_Object"), NULL);

			}

			break;

		default:

			{

				h = GetProp(hwnd, _T("CWindow_Object"));
				if (h == NULL){
					return DefWindowProc(hwnd, uMsg, wParam, lParam);
				}
				pWindow = (CWindow *)h;

			}

			break;

	}

	return pWindow->DynamicWindowProc(hwnd, uMsg, wParam, lParam);

}

HWND CWindow::GetHandle(){

	return m_hWnd;

}

LRESULT CWindow::DynamicWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){

	switch (uMsg){

		case WM_CREATE:

			{

				return 0;

			}
			
			break;

		case WM_DESTROY:

			{

				PostQuitMessage(0);

			}

			break;

		default:

			{

				break;

			}

			break;

	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);

}

BOOL CWindow::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, const RECT *pRC, CWindow *pParentWindow, int nID, HINSTANCE hInstance){

	HWND hParentWnd = NULL;

	if (pParentWindow != NULL){
		hParentWnd = pParentWindow->GetHandle();
	}

	m_hWnd = CreateWindow(_T("CWindow_DefaultWindow"), lpctszWindowName, dwStyle, pRC->left, pRC->top ,pRC->right - pRC->left, pRC->bottom - pRC->top, hParentWnd, (HMENU)nID, hInstance, this);
	if (m_hWnd == NULL){
		return FALSE;
	}

	return TRUE;

}

BOOL CWindow::ShowWindow(int nCmdShow){

	return ::ShowWindow(m_hWnd, nCmdShow);

}

void CWindow::UpdateWindow(){

	::UpdateWindow(m_hWnd);

}

void CWindow::MoveWindow(int x, int y, int iWidth, int iHeight, BOOL bRepaint){

	::MoveWindow(m_hWnd, x, y, iWidth, iHeight, bRepaint);

}

BOOL CWindow::DestroyWindow(){

	BOOL b = ::DestroyWindow(m_hWnd);
	return b;

}

int CWindow::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

	return 0;

}

void CWindow::OnDestroy(HWND hwnd){

}

#else

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

	switch (uMsg){

		case WM_CREATE:

			return OnCreate(hwnd, (LPCREATESTRUCT)lParam);

		case WM_DESTROY:

			OnDestroy();
			
			break;

		default:

			break;

	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);

}

int CWindow::OnCreate(HWND hwnd, LPCREATESTRUCT lpCS){

	HWND hEdit;
	RECT rc;

	GetClientRect(hwnd, &rc);
		
	hEdit = CreateWindow(_T("EDIT"), _T(""), WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | ES_WANTRETURN | ES_MULTILINE | ES_AUTOHSCROLL | ES_AUTOVSCROLL, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, hwnd, (HMENU)IDE_EDIT, lpCS->hInstance, NULL);
	if (hEdit == NULL){

		return -1;

	}

	return 0;

}

void CWindow::OnDestroy(){

	PostQuitMessage(0);

}

LRESULT CALLBACK CWindow::StaticWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){

	if (uMsg == WM_CREATE){
		if (lParam != NULL){
			LPCREATESTRUCT lpCS = (LPCREATESTRUCT)lParam;
			if (lpCS->lpCreateParams != NULL){
				CWindow *pWindow = (CWindow *)lpCS->lpCreateParams;
				SetProp(hwnd, _T("Object"), (HANDLE)pWindow);
				return pWindow->DynamicWindowProc(hwnd, uMsg, wParam, lParam);
			}
		}
	}
	else if (uMsg == WM_DESTROY){

		CWindow *pWindow = (CWindow *)GetProp(hwnd, _T("Object"));
		SetProp(hwnd, _T("Object"), NULL);
		return pWindow->DynamicWindowProc(hwnd, uMsg, wParam, lParam);

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

#endif