#pragma once

class CWindow{

	protected:

		HWND m_hWnd;

	public:

		static ATOM RegisterWindowClass(HINSTANCE hInstance);
		static ATOM RegisterWindowClass(WNDCLASS *lpWC);
		static LRESULT CALLBACK StaticWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		HWND GetHandle();
		virtual LRESULT DynamicWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		virtual BOOL Create(LPCTSTR lpctszWindowName, DWORD dwStyle, const RECT *pRC, CWindow *pParentWindow, int nID, HINSTANCE hInstance);
		BOOL ShowWindow(int nCmdShow);
		void UpdateWindow();
		void MoveWindow(int x, int y, int iWidth, int iHeight, BOOL bRepaint);
		virtual int OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);

};