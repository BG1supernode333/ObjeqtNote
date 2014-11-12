#include "stdafx.h"
#include "ChildWindow.h"

ATOM CChildWindow::RegisterWindowClass(HINSTANCE hInstance, HICON hIcon, HCURSOR hCursor, HBRUSH hbrBackground, LPCTSTR lpctszMenuName){

	WNDCLASS wc;

	wc.lpszClassName = _T("CChildWindow_DefaultWindow");
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = CWindow::StaticWindowProc;
	wc.hInstance = hInstance;
	wc.hIcon = hIcon;
	wc.hCursor = hCursor;
	wc.hbrBackground = hbrBackground;
	wc.lpszMenuName = lpctszMenuName;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;

	return CWindow::RegisterWindowClass(&wc);

}

LRESULT CChildWindow::DynamicWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){

	switch (uMsg){

		case WM_CREATE:

			{

				LPCREATESTRUCT lpCS;

				lpCS = (LPCREATESTRUCT)lParam;

				return OnCreate(hwnd, lpCS);

			}

			break;

		case WM_DESTROY:

			{

				MessageBox(hwnd, _T("a"), _T("a"), MB_OK);
			}

			break;

		default:

			{

			}

			break;

	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);

}

BOOL CChildWindow::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HINSTANCE hInstance){

	m_hWnd = CreateWindow(_T("CChildWindow_DefaultWindow"), lpctszWindowName, dwStyle, x, y, iWidth, iHeight, NULL, NULL, hInstance, this);
	if (m_hWnd == NULL){
		return FALSE;
	}

	return TRUE;

}