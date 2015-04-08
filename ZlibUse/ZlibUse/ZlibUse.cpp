
#include "ZlibUse.h"

bool ZlibUse::compress( char *source, int sourcelen, vector< char > &dest )
{
	dest.clear();

	z_stream strm;
	strm.zalloc = Z_NULL;
	strm.zfree = Z_NULL;
	strm.opaque = Z_NULL;

	int ret = deflateInit( &strm, Z_DEFAULT_COMPRESSION );
	if ( ret != Z_OK )
		return false;

	strm.next_in = (Bytef*)source;
	strm.avail_in = sourcelen;

	char buf[ ms_iChunkLen ];
	do
	{
		strm.next_out = (Bytef*)buf;
		strm.avail_out = ms_iChunkLen;

		ret = deflate( &strm, Z_FINISH );
		assert( ret != Z_STREAM_ERROR );

		unsigned int outLen = ms_iChunkLen - strm.avail_out;
		copy( buf, buf + outLen, back_inserter( dest ) );
	} while ( !strm.avail_out );
	
	deflateEnd( &strm );
	return true;
}
bool ZlibUse::decompress( char *source, int sourcelen, vector< char > &dest )
{
	dest.clear();

	z_stream strm;
	strm.zalloc = Z_NULL;
	strm.zfree = Z_NULL;
	strm.opaque = Z_NULL;
	strm.avail_in = 0;
	strm.avail_out = Z_NULL;

	int ret = inflateInit( &strm );
	if ( ret != Z_OK )
		return false;

	strm.next_in = (Bytef*)source;
	strm.avail_in = sourcelen;

	char buf[ ms_iChunkLen ];
	do
	{
		strm.next_out = (Bytef*)buf;
		strm.avail_out = ms_iChunkLen;

		switch ( ret )
		{
		case Z_DATA_ERROR:
		case Z_MEM_ERROR:
			inflateEnd( &strm );
			return false;
		}

		ret = inflate( &strm, Z_NO_FLUSH );
		assert( ret != Z_STREAM_ERROR );

		unsigned int outLen = ms_iChunkLen - strm.avail_out;
		copy( buf, buf + outLen, back_inserter( dest ) );
	} while ( !strm.avail_out );

	inflateEnd( &strm );
	return true;
}

bool ZlibUse::compress( istream &source, ostream &dest )
{
	source.seekg( 0, source.end );
	int sourcelen = source.tellg();
	source.seekg( 0, source.beg );

	vector< char > sourceBuf;
	sourceBuf.resize( sourcelen );
	source.read( (char*)&(sourceBuf[ 0 ]), sourcelen );

	vector< char > destBuf;
	if ( !compress( (char*)&sourceBuf[ 0 ], sourcelen, destBuf ) )
		return false;

	dest.write( (char*)&destBuf[ 0 ], destBuf.size() );
	return true;
}
bool ZlibUse::decompress( istream &source, ostream &dest )
{
	source.seekg( 0, source.end );
	int sourcelen = source.tellg();
	source.seekg( 0, source.beg );

	vector< char > sourceBuf;
	sourceBuf.resize( sourcelen );
	source.read( (char*)&sourceBuf[ 0 ], sourcelen );

	vector< char > destBuf;
	if ( !decompress( (char*)&sourceBuf[ 0 ], sourcelen, destBuf ) )
		return false;

	dest.write( (char*)&destBuf[ 0 ], destBuf.size() );
	return true;
}
