#include "stdafx.h"
#include "Resource.h"
#include "Application.h"
#include "Window.h"

#if 1

BOOL CApplication::InitInstance(HINSTANCE hInstance){
	
	m_pMainWindow = NULL;

	CWindow::RegisterWindowClass(hInstance);

	CWindow *pWnd = new CWindow();

	RECT rc;
	rc.left = 0;
	rc.top = 0;
	rc.right = 640;
	rc.bottom = 480;

	if (!pWnd->Create(_T("ObjeqtNote"), WS_OVERLAPPEDWINDOW, &rc, NULL, NULL, hInstance)){
		delete pWnd;
		return FALSE;
	}

	m_pMainWindow = pWnd;

	pWnd->ShowWindow(SW_SHOW);

	return TRUE;

}

int CApplication::ExitInstance(){

	if (m_pMainWindow){

		delete m_pMainWindow;
		m_pMainWindow = NULL;

	}

	return 0;

}

#else

BOOL CApplication::InitInstance(HINSTANCE hInstance, int nCmdShow){

	if (!CWindow::RegisterWndClass(hInstance)){

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

	pWindow->ShowWindow(SW_SHOW);

	m_pWnd = pWindow;

	return TRUE;

}

int CApplication::ExitInstance(){

	if (m_pWnd != NULL){
		delete m_pWnd;
		m_pWnd = NULL;
	}

	return 0;
	
}

#endif