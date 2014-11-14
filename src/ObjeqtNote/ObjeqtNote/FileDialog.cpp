#include "stdafx.h"
#include "FileDialog.h"

CFileDialog::CFileDialog(){

	ZeroMemory(&m_ofn, sizeof(m_ofn));

}

CFileDialog::CFileDialog(LPCTSTR lpctszDefaultPath, HWND hwndOwner, LPCTSTR lpctszFilter){

	ZeroMemory(&m_ofn, sizeof(m_ofn));
	ZeroMemory(m_tszPath, sizeof(TCHAR) * MAX_PATH);

	_tcscpy(m_tszPath, lpctszDefaultPath);

	m_ofn.lStructSize = sizeof(OPENFILENAME);
	m_ofn.hwndOwner = hwndOwner;
	m_ofn.lpstrFilter = lpctszFilter;
	m_ofn.lpstrFile = m_tszPath;
	m_ofn.nMaxFile = MAX_PATH;
	m_ofn.Flags = OFN_FILEMUSTEXIST;
	
}
INT_PTR CFileDialog::DoModal(){

	BOOL bRet;

	bRet = ::GetOpenFileName(&m_ofn);
	if (!bRet){
		return IDCANCEL;
	}

	return IDOK;

}