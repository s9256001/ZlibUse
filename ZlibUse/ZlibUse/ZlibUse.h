
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
	static const int ms_iChunkLen = 16384;	// 輸出緩衝區區塊大小

	// 壓縮
	// @source: 待壓縮的資料
	// @sourcelen: 待壓縮的資料大小
	// @dest: 壓縮完的資料
	static bool compress( char *source, int sourcelen, vector< char > &dest );
	// 解壓縮
	// @source: 待解壓縮的資料
	// @sourcelen: 待解壓縮的資料大小
	// @dest: 解壓縮完的資料
	static bool decompress( char *source, int sourcelen, vector< char > &dest );

	// 壓縮(串流版)
	// @source: 輸入串流(待壓縮的資料)
	// @dest: 輸出串流(壓縮完的資料)
	static bool compress( istream &source, ostream &dest );
	// 解壓縮(串流版)
	// @source: 輸入串流(待解壓縮的資料)
	// @dest: 輸出串流(解壓縮完的資料)
	static bool decompress( istream &source, ostream &dest );
};
