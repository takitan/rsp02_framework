#pragma once
#include "system/Process.hpp"
#include "system/TLVStub.hpp"
#include "fw/logger/Logger.hpp"
#include "fw/time/StopWatch.hpp"

namespace rsp{
namespace rsp02{
namespace system{

template<typename T>
class TLVDatalinkUp : public ProducerProcess<T>
{
	private:
		ITLV* tlv;
		fw::logger::ILogger *logger;
		fw::time::StopWatch sw;
	public:
		TLVDatalinkUp( ITLV* t, rsp::rsp02::time_t prd = 0) :
			ProducerProcess<T>(prd), tlv(t),
			logger(fw::logger::Logger::GetLogger("TLVDatalinkUP")),
			sw(1000){}

		bool ConcreteProcess( T &product)
		{
			//if( !tlv->HasData()) return false;
			//if( !tlv->GetResult()) return false;
			if( !sw.isPeriod()) return false;
			//product = T( &tlv->GetPV()[-T::pv_offset]);
			rsp02TLV prd;
			tlv->recv( prd, -1);
			product = T(prd.Original);
			logger->Info("TLVmessage is incoming,dst=%d,type=%d,length=%d",
				(typename T::dst_t)product.Destination,
				(typename T::typ_t)product.Type,
				(typename T::len_t)product.Length);
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
