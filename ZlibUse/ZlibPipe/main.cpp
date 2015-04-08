

#include "../ZlibUse/ZlibUse.h"
#include <stdlib.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>
using namespace std;

#pragma comment( lib, "../Debug/ZlibUse.lib" )

int main( int argc, char **argv )
{
	// 避免end-of-line轉換
	_setmode( _fileno( stdin ), O_BINARY );
	_setmode( _fileno( stdout ), O_BINARY );

	// 壓縮
	if ( argc == 1 )
	{
		if ( !ZlibUse::compress( cin, cout ) )
			cerr << "compress failed!" << endl;
	}
	// 解壓縮
	else if ( argc == 2 && !strcmp( argv[ 1 ], "-d" ) )
	{
		if ( !ZlibUse::decompress( cin, cout ) )
			cerr << "decompress failed!" << endl;
	}
	// 告知用法
	else
		cerr << "zlibpipe usage: zlibpipe [-d] < source > dest" << endl;

	return 0;
}
