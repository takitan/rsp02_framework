#pragma once
#include "system/IProcess.hpp"
#include "system/TLVStub.hpp"

namespace rsp{
namespace rsp02{
namespace system{

template<typename T>
class TLVDatalinkUp : public ProducerProcess<T>
{
	private:
		ITLV* tlv;

	public:
		TLVDatalinkUp( ITLV* t) : tlv(t){}

		bool ConcreteProcess( T &product)
		{
			if( !tlv->HasData()) return false;
			if( !tlv->GetResult()) return false;
			product = T( &tlv->GetPV()[-T::pv_offset]);
			return true;
		}
};

template<typename T>
class TLVDatalinkDown : public ConsumerProcess<T>
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
