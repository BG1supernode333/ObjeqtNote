#pragma once

#include "File.h"
#include "Encode.h"

class CTextFile : public CFile{

	private:

		TCHAR *m_pTextBuf;
		int m_iTextLength;
		Encode m_Encode;

	public:
		
		CTextFile(LPCTSTR lpctszFileName, DWORD dwDesiredAccess);
		virtual BOOL ReadAll();
		TCHAR * AllocTextBuffer(int iSize);
		int GetTextLength();
		TCHAR *GetTextStringPointer();

};