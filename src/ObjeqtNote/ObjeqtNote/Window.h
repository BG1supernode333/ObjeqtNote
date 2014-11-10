#pragma once

class CWindow{

	private:

		HWND m_hWnd;

	public:

		BOOL Create(LPCTSTR lpctszClassName, LPCTSTR lpctszWindowName, DWORD dwStyle, const RECT & rect, HWND hParentWnd, UINT nID, HINSTANCE hInstance);

};