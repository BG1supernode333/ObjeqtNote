#include "stdafx.h"
#include "Resource.h"
#include "Application.h"
#include "Window.h"

BOOL CApplication::InitInstance(HINSTANCE hInstance, int nCmdShow){

	if (!RegisterWndClass(hInstance)){

		return FALSE;

	}

	CWindow *pWindow = new CWindow();

	RECT rc;
	rc.left = 0;
	rc.top = 0;
	rc.right = 640;
	rc.bottom = 480;

	BOOL bRet;

	bRet = pWindow->Create(_T("ObjeqtNote"), _T("ObjeqtNote"), WS_OVERLAPPEDWINDOW, rc, NULL, NULL, hInstance);
	if (!bRet){
		return FALSE;
	}

	ShowWindow(pWindow->m_hWnd, SW_SHOW);

	m_pWnd = pWindow;

	return TRUE;

}

ATOM CApplication::RegisterWndClass(HINSTANCE hInstance){

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