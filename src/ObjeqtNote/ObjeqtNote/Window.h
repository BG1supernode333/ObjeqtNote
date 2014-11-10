#pragma once

class CWindow{

	//private:
	public:
	
		HWND m_hWnd;

	public:

		BOOL Create(LPCTSTR lpctszClassName, LPCTSTR lpctszWindowName, DWORD dwStyle, const RECT & rect, HWND hParentWnd, UINT nID, HINSTANCE hInstance);
		BOOL ShowWindow(int nCmdShow);
		LRESULT DynamicWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		int OnCreate(HWND hwnd, LPCREATESTRUCT lpCS);
		void OnDestroy();
		static LRESULT CALLBACK StaticWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		static ATOM RegisterWndClass(HINSTANCE hInstance);

};