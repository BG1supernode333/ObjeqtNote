#include "stdafx.h"
#include "Resource.h"
#include "MainApplication.h"
#include "MainWindow.h"

BOOL CMainApplication::InitInstance(HINSTANCE hInstance){

	CMainWindow::RegisterWindowClass(hInstance,
		LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION)),
		LoadCursor(hInstance, IDC_ARROW),
		(HBRUSH)GetStockObject(WHITE_BRUSH),
		MAKEINTRESOURCE(IDC_OBJEQTNOTE)
	);

	CChildWindow::RegisterWindowClass(hInstance,
		LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION)),
		LoadCursor(hInstance, IDC_ARROW),
		(HBRUSH)GetStockObject(GRAY_BRUSH),
		NULL
		);


	CMainWindow *pMainWnd = new CMainWindow();

	BOOL bRet = pMainWnd->Create(_T("Main"), WS_OVERLAPPEDWINDOW/* | WS_HSCROLL | WS_VSCROLL*/, 0, 0, 640, 480, hInstance);
	if (!bRet){

		delete pMainWnd;
		pMainWnd = NULL;
		return FALSE;

	}

	m_pMainWindow = pMainWnd;

	pMainWnd->ShowWindow(SW_SHOW);

	pMainWnd->UpdateWindow();

	//pMainWnd->MoveWindow(0, 0, 640, 480, TRUE);

	return TRUE;

}