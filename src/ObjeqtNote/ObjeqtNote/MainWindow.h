#pragma once

#include "Window.h"
#include "ChildWindow.h"

class CMainWindow : public CWindow{

	private:

		CChildWindow *m_pChild1;
		CChildWindow *m_pChild2;

	public:

		static ATOM RegisterWindowClass(HINSTANCE hInstance, HICON hIcon, HCURSOR hCursor, HBRUSH hbrBackground, LPCTSTR lpctszMenuName);
		LRESULT DynamicWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		BOOL Create(LPCTSTR lpctszWindowName, DWORD dwStyle, int x, int y, int iWidth, int iHeight, HINSTANCE hInstance);
		virtual int OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
		virtual void OnDestroy(HWND hwnd);
		virtual BOOL OnCommand(HWND hwnd, UINT nID, UINT nNotifyCode, HWND hWndControl);
		void OnFileOpen(HWND hwnd);

		HWND m_hStc;

};