#pragma once

enum ByteType{
	BYTETYPE_NONE = 0,
	BYTETYPE_JMS_SHIFT_JIS_1,
	BYTETYPE_JMS_SHIFT_JIS_2
};

enum Encode{
	ENCODE_ASCII = 0,
	ENCODE_JMS_SHIFT_JIS,
};

class CEncode{

	public:
		
		static Encode m_Encode;
		static int m_iDecodeAfterLength;
		static Encode CheckEncode(LPBYTE lpBytes, DWORD dwSize);
		static ByteType CheckJmsShiftJISByteType(BYTE b);
		static int GetDecodeAfterLength(LPBYTE lpBytes, Encode srcEncode);
		static int Decode(LPTSTR lptszDest, LPBYTE lpSrcBytes, Encode srcEncode);

};