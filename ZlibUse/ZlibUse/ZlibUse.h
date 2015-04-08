
#pragma once

#include "../../zlib-1.2.8/zlib.h"
#include <assert.h>
#include <vector>
#include <iostream>
using namespace std;

#pragma comment( lib, "../../zlib-1.2.8/contrib/vstudio/vc9/x86/ZlibStatDebug/zlibstat.lib" )

class ZlibUse
{
public:
	static const int ms_iChunkLen = 16384;	// ��X�w�İϰ϶��j�p

	// ���Y
	// @source: �����Y�����
	// @sourcelen: �����Y����Ƥj�p
	// @dest: ���Y�������
	static bool compress( char *source, int sourcelen, vector< char > &dest );
	// �����Y
	// @source: �ݸ����Y�����
	// @sourcelen: �ݸ����Y����Ƥj�p
	// @dest: �����Y�������
	static bool decompress( char *source, int sourcelen, vector< char > &dest );

	// ���Y(��y��)
	// @source: ��J��y(�����Y�����)
	// @dest: ��X��y(���Y�������)
	static bool compress( istream &source, ostream &dest );
	// �����Y(��y��)
	// @source: ��J��y(�ݸ����Y�����)
	// @dest: ��X��y(�����Y�������)
	static bool decompress( istream &source, ostream &dest );
};
