#include "stdafx.h"

#include "TextFile.h"
#include "Encode.h"

CTextFile::CTextFile(LPCTSTR lpctszFileName, DWORD dwDesiredAccess) : CFile(lpctszFileName, dwDesiredAccess){

	//CFile(lpctszFileName, dwDesiredAccess);
	//CFile::CFile(lpctszFileName, dwDesiredAccess);

}

BOOL CTextFile::ReadAll(){

	BOOL bRet;

	bRet = CFile::ReadAll();
	if (!bRet){
		return FALSE;
	}

#if 0 // privateなのでそういうgetterいるか・・・。
	if (m_dwLengthHigh > 0){	// ひとまず対応しない
		return FALSE;
	}
#endif

	CEncode::CheckEncode(m_pBuf, GetLength());

	if (CEncode::m_Encode == ENCODE_JMS_SHIFT_JIS){
		int before, after;
		before = CEncode::GetDecodeAfterLength(m_pBuf, Encode::ENCODE_JMS_SHIFT_JIS);
		AllocTextBuffer(before);
		after = CEncode::Decode(m_pTextBuf, m_pBuf, Encode::ENCODE_JMS_SHIFT_JIS);
		if (before != after){
			return FALSE;
		}
		m_iTextLength = after - 1;
		m_Encode = ENCODE_JMS_SHIFT_JIS;
	}

	return TRUE;

}

TCHAR * CTextFile::AllocTextBuffer(int iSize){

	m_pTextBuf = new TCHAR[iSize];

	return m_pTextBuf;

}

int CTextFile::GetTextLength(){

	return m_iTextLength;

}

TCHAR * CTextFile::GetTextStringPointer(){

	return m_pTextBuf;

}