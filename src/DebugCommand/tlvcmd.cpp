#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <memory>
#include "IProcess.hpp"
#include "tlvcmd.hpp"
#include "ntshell/core/ntlibc.h"
template<typename T>
using IConsumer = rsp::rsp02::system::IConsumer<T>;


tlvcmd::tlvcmd( IConsumer<MissionTLV>* c) : cns(c){}

int tlvcmd::ConvertpData( uint8_t* pData, const char *arg)
{
	char* idx = nullptr;
	int sz = std::min( (std::size_t)pDataSize, strlen( arg)/2);
	int i;
	for( i=0; i<sz; i++)
	{
		char tk[3] = {0,0,0};
		memcpy( tk, &arg[i*2], 2);
		pData[i] = strtol( tk, &idx, 16);
	}
	return i;
}

int tlvcmd::operator()( int argc, const char** argv, void* extobj)
{
	(void)extobj;
	if( argc < 5)
	{
		printf("Less arguments\n");
		return -1;
	}
	char* e = nullptr;
	buf.Destination = static_cast<EDestination>( strtol( argv[1], &e, 10));
	if( e!='\0')
	{
		printf( "Destination is invalid.\n");
		return -1;
	}
	buf.Type = static_cast<EType>( strtol( argv[2], &e, 10));
	if( e!='\0')
	{
		printf( "Type is invalid.\n");
		return -1;
	}
	buf.Length = (uint16_t)strtol( argv[3], &e, 10);
	if( e!='\0')
	{
		printf( "Length is invalid.\n");
		return -1;
	}
	ConvertpData( buf.pValue, argv[4]);
	MissionTLV mtlv( &buf);
	cns->Accept( mtlv);

	return 1;
}
