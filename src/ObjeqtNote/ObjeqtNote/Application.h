#pragma once

#include "Window.h"

class CApplication{

	protected:

		CWindow *m_pMainWindow;

	public:

		virtual BOOL InitInstance(HINSTANCE hInstance);
		virtual int ExitInstance();

};
