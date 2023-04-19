#pragma once
#include "system/IProcess.hpp"
#include "system/TLVStub.hpp"

namespace rsp{
namespace rsp02{
namespace system{

template<typename T>
class TLVDatalinkUp : public IProcess, public IPacket<T>
{
	private:
		ITLV* tlv;
		IPacket<T>* PostProcess;
		ProcessInfo_t Info;

	public:
		TLVDatalinkUp( ITLV* t) : tlv(t){}

		bool Process()
		{
			if( !tlv->HasData()) return false;
			if( !tlv->GetResult()) return false;
			T packet( &tlv->GetPV()[-T::pv_offset]);
			PostProcess->Accept( packet);
		}

		const ProcessInfo_t &GetInfo() const{ return Info;}

		void SetPostProcess( IPacket<T>* p){ PostProcess = p;}
		bool Accept( T &packet){ (void)packet;}
};

template<typename T>
class TLVDatalinkDown : public ProcessBase<T>
{
	public:
		TLVDatalinkDown( ITLV* t) : tlv(t){}
	protected:
		bool ConcreteProcess( T &packet)
		{
			return tlv->send(
				(TLVmessage_t::dst_t)packet.destination,
				(TLVmessage_t::type_t)packet.type,
				packet.pValue,
				(TLVmessage_t::len_t)packet.length) ? true : false;
		}
	private:
		ITLV* tlv;
};

}
}
}
