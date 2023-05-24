#include <cstring>
#include <cstdlib>
#include <algorithm>
#include "IProcess.hpp"
#include "tlvcmd.hpp"
#include "ntshell/core/ntlibc.h"
template<typename T>
using IConsumer = rsp::rsp02::system::IConsumer<T>;

namespace detail{

class tlvcmd_impl
{
	public:
		static constexpr int pDataSize = 256;
		tlvcmd_impl( IConsumer<MissionTLV>* c) : cns(c){}
		int ConvertpData( uint8_t* pData, const char *arg)
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

		int operator()( int argc, const char** argv, void* extobj)
		{
			if( argc < 5)
			{
				printf("Less arguments\n");
				return -1;
			}
			char* e = nullptr;
			auto destination = static_cast<EDestination>( strtol( argv[1], &e, 10));
			auto type = static_cast<EType>( strtol( argv[2], &e, 10));
			auto length = (uint16_t)strtol( argv[3], &e, 10);
			uint8_t pData[ pDataSize];
			ConvertpData( pData, argv[4]);
			MissionTLV mtlv(destination, type, length, (void*)pData);
			cns->Accept( mtlv);

			return 1;
		}
	private:
		IConsumer<MissionTLV>* cns;
};
}

tlvcmd::tlvcmd( IConsumer<MissionTLV>* c)
{
	impl = new detail::tlvcmd_impl(c);
}
int tlvcmd::operator()( int argc, const char** argv, void* extobj)
{
	return impl->operator()( argc, argv, extobj);
}
