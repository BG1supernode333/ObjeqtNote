#pragma once

#include <commdlg.h>

#if 0

#include <string>

using namespace std;

#if UNICODE
#define tstring wstring
#else
#define tstring string
#endif

#endif

class CFileDialog{

	public:

		OPENFILENAME m_ofn;
		TCHAR m_tszPath[MAX_PATH];

		CFileDialog();
		CFileDialog(LPCTSTR lpctszDefaultPath, HWND hwndOwner, LPCTSTR lpctszFilter);

		INT_PTR DoModal();

};