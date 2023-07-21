#pragma once
#include "system/Process.hpp"
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
		TLVDatalinkUp( ITLV* t, rsp::rsp02::time_t prd = 0) : ProducerProcess<T>(prd), tlv(t){}

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
		TLVDatalinkDown( ITLV* t, rsp::rsp02::time_t prd = 0) : ConsumerProcess<T>(prd), tlv(t){}
	protected:
		bool ConcreteProcess( T &packet)
		{
			auto pkt = (rsp02TLV*)&packet;
			return tlv->send(
				pkt->Destination,
				pkt->Type,
				(void*)(pkt->pValue),
				pkt->Length) ? true : false;
		}
	private:
		ITLV* tlv;
};

}
}
}
