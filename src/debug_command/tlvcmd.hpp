#pragma once
#include "middle/con_pro/Process.hpp"
#include "GlobalDefine.hpp"
#include "middle/debug/IShellCommand.hpp"

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
		tlvcmd();
		int operator()( int argc, const char** argv, void* extobj);
	private:
			TLVBuf<16> buf;
			static constexpr int pDataSize = 256;
			int ConvertpData( uint8_t* pData, const char *arg);

};

namespace rsp{
namespace rsp02{
namespace system{

class TDebugOutput : public ConsumerProcess<rsp02TLV>
{
	public:
		TDebugOutput( rsp::rsp02::time_t prd = 0) : ConsumerProcess<rsp02TLV>("DebugOutput", prd){}
	protected:
		bool ConcreteProcess( rsp02TLV &packet)
		{
			auto dst = packet.Destination();
			auto typ = packet.Type();
			auto len = packet.Length();
			printf( "tlvres %s(%02x),%02x,%04x,",
				DestinationString(dst),static_cast<std::underlying_type<EDestination>::type>(typ),
				typ,
				len);
			print_pData( packet);
			return true;
		}
	private:
		void print_pData( rsp02TLV &packet)
		{
			typename rsp02TLV::len_t len;
			for( int i=0;i<len;i++)
			{
				printf( "%02x", packet.pValue[i]);
			} 
			printf( "\n");
		}
};

}
}
}
