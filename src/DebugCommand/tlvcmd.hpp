#pragma once
#include "system/Process.hpp"
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
			printf( "tlvres %02x,%02x,%04x,", packet.Destination(), packet.Type(), packet.Length());
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
