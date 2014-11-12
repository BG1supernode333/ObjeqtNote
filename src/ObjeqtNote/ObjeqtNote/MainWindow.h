#pragma once

#include "Window.h"

class CMainWindow : public CWindow{

	public:

		static ATOM RegisterWindowClass(HINSTANCE hInstance, HICON hIcon, HCURSOR hCursor, HBRUSH hbrBackground, LPCTSTR lpctszMenuName);
		LRESULT DynamicWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		BOOL Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HINSTANCE hInstance);
		int OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
		HWND m_hStc;

};