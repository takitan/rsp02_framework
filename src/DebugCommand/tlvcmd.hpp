#pragma once
#include "system/IProcess.hpp"
#include "MissionDefine.hpp"
#include "system/debug/IShellCommand.hpp"

template<size_t N>
struct TLVBuf
{
	EDestination Destination;
	EType Type;
	uint16_t Length;
	uint8_t pValue[N];
};

class tlvcmd : public rsp::rsp02::system::IShellCommand
{
	public:
		tlvcmd( rsp::rsp02::system::IConsumer<MissionTLV>* c);
		int operator()( int argc, const char** argv, void* extobj);
	private:
			TLVBuf<16> buf;
			rsp::rsp02::system::IConsumer<MissionTLV>* cns;
			static constexpr int pDataSize = 256;
			int ConvertpData( uint8_t* pData, const char *arg);

};
