#pragma once

class CFile{

	private:

		HANDLE m_hFile;
		TCHAR m_tszPath[MAX_PATH];
		DWORD m_dwLengthLow;
		DWORD m_dwLengthHigh;
		
	protected:

		BYTE *m_pBuf;

	public:

		CFile();
		CFile(LPCTSTR lpctszFileName, DWORD dwDesiredAccess);
		virtual BOOL Open(LPCTSTR lpctszFileName, DWORD dwDesiredAccess);
		virtual BOOL IsOpen();
		virtual DWORD GetLength();
		virtual BOOL ReadAll();
		virtual void Close();
		virtual void FreeByteBuffer();
};