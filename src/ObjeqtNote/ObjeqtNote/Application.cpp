#include "stdafx.h"
#include "Resource.h"
#include "Application.h"
#include "Window.h"

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