#include "stdafx.h"
#include "Resource.h"
#include "Application.h"

BOOL CApplication::InitInstance(HINSTANCE hInstance, int nCmdShow){

	if (!RegisterWndClass(hInstance)){

		return FALSE;

	}

	MessageBox(NULL, _T("RegisterWndClass Success!"), _T("ObjeqtNote"), MB_OK);

	return FALSE;

}

ATOM CApplication::RegisterWndClass(HINSTANCE hInstance){

	WNDCLASS wc;

	wc.lpszClassName = _T("ObjeqtNote");
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = DefWindowProc;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_OBJEQTNOTE));
	wc.hCursor = LoadCursor(hInstance, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = MAKEINTRESOURCE(IDC_OBJEQTNOTE);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;

	return RegisterClass(&wc);

}