#pragma once

#include "Window.h"

class CApplication{

	//private:
	public:

		CWindow *m_pWnd;

	public:

		BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
		ATOM RegisterWndClass(HINSTANCE hInstance);

};
