#include "stdafx.h"
#include "Encode.h"

Encode CEncode::m_Encode;
int CEncode::m_iDecodeAfterLength;

Encode CEncode::CheckEncode(LPBYTE lpBytes, DWORD dwSize){

	int iState = 0;

	m_Encode = ENCODE_ASCII;

	for (DWORD i = 0; i < dwSize; i++){

		if (iState == 0){
			if (CheckJmsShiftJISByteType(lpBytes[i]) == BYTETYPE_JMS_SHIFT_JIS_1){
				iState = 1;
			}
		}
		else if (iState == 1){
			if (CheckJmsShiftJISByteType(lpBytes[i]) == BYTETYPE_JMS_SHIFT_JIS_2){
				m_Encode = ENCODE_JMS_SHIFT_JIS;
				return m_Encode;
			}
		}
		else{
			iState = 0;
		}

	}

	m_Encode = ENCODE_ASCII;

	return m_Encode;

}

ByteType CEncode::CheckJmsShiftJISByteType(BYTE b){

	if (b >= 0x81 && b <= 0x9f || b >= 0xe0 && b <= 0xfc){
		return BYTETYPE_JMS_SHIFT_JIS_1;
	}
	else if (b != 0x7f && b >= 0x40 && b <= 0xfc){
		return BYTETYPE_JMS_SHIFT_JIS_2;
	}

	return BYTETYPE_NONE;

}

int CEncode::GetDecodeAfterLength(LPBYTE lpBytes, Encode srcEncode){

	if (srcEncode == Encode::ENCODE_JMS_SHIFT_JIS){

		m_iDecodeAfterLength = MultiByteToWideChar(CP_ACP, 0, (LPSTR)lpBytes, -1, NULL, 0);
		return m_iDecodeAfterLength;

	}

}

int CEncode::Decode(LPTSTR lptszDest, LPBYTE lpSrcBytes, Encode srcEncode){

	int iLen;

	if (srcEncode == Encode::ENCODE_JMS_SHIFT_JIS){

		iLen = MultiByteToWideChar(CP_ACP, 0, (LPSTR)lpSrcBytes, -1, lptszDest, m_iDecodeAfterLength);
		lptszDest[iLen - 1] = _T('\0');
		return iLen;

	}

}