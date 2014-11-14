#include "stdafx.h"
#include "File.h"

CFile::CFile(){

	m_hFile = NULL;
	m_pBuf = NULL;

}

CFile::CFile(LPCTSTR lpctszFileName, DWORD dwDesiredAccess){

	m_hFile = NULL;
	m_pBuf = NULL;

	_tcscpy(m_tszPath, lpctszFileName);

	if (dwDesiredAccess == GENERIC_READ){
		m_hFile = CreateFile(m_tszPath, dwDesiredAccess, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	}

}

BOOL CFile::Open(LPCTSTR lpctszFileName, DWORD dwDesiredAccess){

	_tcscpy(m_tszPath, lpctszFileName);

	if (dwDesiredAccess == GENERIC_READ){
		m_hFile = CreateFile(m_tszPath, dwDesiredAccess, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	}

	if (m_hFile == INVALID_HANDLE_VALUE){
		return FALSE;
	}

	return TRUE;

}

BOOL CFile::IsOpen(){

	if (m_hFile != INVALID_HANDLE_VALUE){
		return TRUE;
	}
	else{
		return FALSE;
	}

}

DWORD CFile::GetLength(){

	m_dwLengthLow = GetFileSize(m_hFile, &m_dwLengthHigh);

	return m_dwLengthLow;

}

BOOL CFile::ReadAll(){

	DWORD dwReadSize = 0;
	
	m_pBuf = new BYTE[m_dwLengthLow + 1];

	ReadFile(m_hFile, m_pBuf, m_dwLengthLow, &dwReadSize, NULL);

	m_pBuf[dwReadSize] = '\0';

	if (dwReadSize != m_dwLengthLow){

		return FALSE;

	}

	return TRUE;

}

void CFile::Close(){

	FreeByteBuffer();

	if (m_hFile != NULL){
		::CloseHandle(m_hFile);
		m_hFile = NULL;
	}

	m_dwLengthLow = 0;
	m_dwLengthHigh = 0;

	ZeroMemory(m_tszPath, sizeof(TCHAR) * MAX_PATH);

}

void CFile::FreeByteBuffer(){

	if (m_pBuf != NULL){
		delete [] m_pBuf;
		m_pBuf = NULL;
	}

}