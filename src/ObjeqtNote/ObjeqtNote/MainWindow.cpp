#include "stdafx.h"
#include "Resource.h"
#include "MainWindow.h"
#include "FileDialog.h"

ATOM CMainWindow::RegisterWindowClass(HINSTANCE hInstance, HICON hIcon, HCURSOR hCursor, HBRUSH hbrBackground, LPCTSTR lpctszMenuName){

	WNDCLASS wc;

	wc.lpszClassName = _T("CMainWindow_DefaultWindow");
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

LRESULT CMainWindow::DynamicWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){

	/*static HINSTANCE hi;
	static HBITMAP hbmp;
	static HDC hdc;
	static HDC hMemDC;
	static HBITMAP hold;
	*/
	switch (uMsg){

		case WM_CREATE:

			{

				LPCREATESTRUCT lpCS;

				lpCS = (LPCREATESTRUCT)lParam;
//				hi = lpCS->hInstance;
/*
				hbmp = (HBITMAP)LoadImage(hi, _T("sample.bmp"), IMAGE_BITMAP, 300, 300, LR_LOADFROMFILE);
				hdc = GetDC(m_hStc);
				hMemDC = CreateCompatibleDC(hdc);
				hold = (HBITMAP)SelectObject(hMemDC, hbmp);
*/
				return OnCreate(hwnd, lpCS);

			}
			
			break;

		case WM_DESTROY:

			{

				OnDestroy(hwnd);

			}

			break;

		case WM_PAINT:
			{
/*				
				BitBlt(hdc, 0, 0, 300, 200, hMemDC, 0, 0, SRCCOPY);
				SelectObject(hMemDC, hold);
				DeleteDC(hMemDC);
				ReleaseDC(m_hStc, hdc);
				DeleteObject(hbmp);
				*/
			}
			break;

		case WM_COMMAND:

			{

				return OnCommand(hwnd, LOWORD(wParam), HIWORD(wParam), (HWND)lParam);

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

BOOL CMainWindow::Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HINSTANCE hInstance){

	m_hWnd = CreateWindow(_T("CMainWindow_DefaultWindow"), lpctszWindowName, dwStyle, x, y, iWidth, iHeight, NULL, NULL, hInstance, this);
	if (m_hWnd == NULL){
		return FALSE;
	}

	return TRUE;

}

int CMainWindow::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct){

	m_pChild1 = new CChildWindow();
	BOOL b1 = m_pChild1->Create(_T("Child1"), WS_CAPTION | WS_THICKFRAME, 500, 0, 200, 200, lpCreateStruct->hInstance);

	m_pChild2 = new CChildWindow();
	BOOL b2 = m_pChild2->Create(_T("Child2"), WS_CHILD | WS_VISIBLE | WS_POPUP, 500, 400, 200, 200, lpCreateStruct->hInstance);

	m_pChild1->ShowWindow(SW_SHOW);
	m_pChild2->ShowWindow(SW_SHOW);

	BOOL bx = b2;
#if 0

	RECT rc;

	GetClientRect(hwnd, &rc);

	int h = rc.bottom - rc.top;
	int q = h / 3;

	HWND hEdt = CreateWindow(_T("EDIT"), _T(""), WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | ES_WANTRETURN | ES_MULTILINE | ES_AUTOHSCROLL | ES_AUTOVSCROLL, rc.left, rc.top, rc.right - rc.left, q, hwnd, 0/*(HMENU)IDE_EDIT*/, lpCreateStruct->hInstance, NULL);
	m_hStc = CreateWindow(_T("STATIC"), _T(""), WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | ES_WANTRETURN | ES_MULTILINE | ES_AUTOHSCROLL | ES_AUTOVSCROLL, rc.left, q, rc.right - rc.left, q, hwnd, 0/*(HMENU)IDE_EDIT*/, lpCreateStruct->hInstance, NULL);
	HWND hEdt2 = CreateWindow(_T("EDIT"), _T(""), WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | ES_WANTRETURN | ES_MULTILINE | ES_AUTOHSCROLL | ES_AUTOVSCROLL, rc.left, q * 2, rc.right - rc.left, q, hwnd, 0/*(HMENU)IDE_EDIT*/, lpCreateStruct->hInstance, NULL);
	
#endif

	return 0;

}

void CMainWindow::OnDestroy(HWND hwnd){

	if (m_pChild1){
		m_pChild1->DestroyWindow();
		delete m_pChild1;
		m_pChild1 = NULL;
	}

	if (m_pChild2){
		m_pChild2->DestroyWindow();
		delete m_pChild2;
		m_pChild2 = NULL;
	}

	PostQuitMessage(0);

}

BOOL CMainWindow::OnCommand(HWND hwnd, UINT nID, UINT nNotifyCode, HWND hWndControl){

	switch (nID){

		case ID_FILE_OPEN:

			OnFileOpen(hwnd);

			break;

		default:

			break;

	}

	return TRUE;

}

void CMainWindow::OnFileOpen(HWND hwnd){

	int iRet;

	CFileDialog selDlg(_T(""), hwnd, _T("Text files (*.txt)\0*.txt\0All files (*.*)\0*.*\0\0"));

	iRet = selDlg.DoModal();

	if (iRet == IDOK){

		MessageBox(hwnd, selDlg.m_tszPath, _T("ObjeqtNote"), MB_OK);

	}

}