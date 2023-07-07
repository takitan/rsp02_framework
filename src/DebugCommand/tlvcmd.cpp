#include <cstring>
#include <cstdlib>
#include <algorithm>
#include "IProcess.hpp"
#include "rsp02.hpp"
#include "tlvcmd.hpp"
#include "ntshell/core/ntlibc.h"
template<typename T>
using IConsumer = rsp::rsp02::system::IConsumer<T>;

namespace{
constexpr int pDataSize = 256;
IConsumer<MissionTLV>* cns;

/**
 * @brief tlvcmd用ｐData変換関数
 *
 * tlvcmdでは、pDataとして16進数文字列を受け入れる
 * pData = {0x00,0x01,0x02,0xff}と設定したいときの文字列は、
 * "000102ff"となる。
 * (大文字・小文字は区別されない)
 *
 * @param pData 変換後のデータ
 * @param arg 返還前の文字列データ
 * @return データの長さ(TLVコマンドのlengthに相当)
 */
bool ConvertpData( uint8_t* pData, uint16_t &len, const char *arg)
{
	std::size_t sz = strlen( arg);
	// 文字数は偶数じゃないとダメ
	if( sz%1) return false;

	char* idx = nullptr;
	int i;
	for( i=0; i<sz; i+=2)
	{
		char tk[3] = {0,0,0};
		memcpy( tk, &arg[i], 2);
		pData[i/2] = strtol( tk, &idx, 16);
		if( *idx != NULL) return false;
	}
	len = sz/2;
	return true;
}

}

tlvcmd::tlvcmd( IConsumer<MissionTLV>* c)
{
	cns =
}

int tlvcmd::operator()( int argc, const char** argv, void* extobj)
{
	if( argc < 5)
	{
		printf("Less arguments\n");
		return -1;
	}
	char* e = nullptr;
	EDestination dst;
	if( !str2dst( argv[1], dst))
	{
		printf( "Destination of %s is invalid.\n", argv[1]);
		return -1;
	};
	auto t = strtol( argv[2], &e, 10);
	if( *e != NULL)
	{
		printf( "Type of %s is invalid.\n", argv[2]);
		return -2;
	}
	auto type = static_cast<EType>( t);

	auto length = (uint16_t)strtol( argv[3], &e, 10);
	if( *e != NULL)
	{
		printf( "Length of %s is invalid.\n", argv[3]);
		return -3;
	}
	uint8_t pData[ pDataSize];
	if( !ConvertpData( pData, length, argv[4]))
	{
		printf( "pData of %s is invalid.\n", argv[4]);
		return -4;
	}

	MissionTLV mtlv(dst, type, length, (void*)pData);
	cns->Accept( mtlv);

	return 1;
}
