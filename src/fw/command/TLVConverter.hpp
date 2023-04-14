#pragma once
#include <queue>
#include "TLV_library/RspTLV.hpp"
#include "RSP02.hpp"

template<typename T>
class TLVDataLink
{
	private:
	#ifdef FOR_BBM
		RspTLV Receiver(PC_12, PD_2, EDestination::CDH);
	#endif
	#ifdef FOR_EM
		RspTLV Receiver(PC_10, PC_11, EDestination::CDH);
	#endif
		std::queue<MissionTLV> RecvBuf(2);

		MissionTLV RecvBuf;
		MissionTLV SendBuf;
		bool PacketReady;
		bool SendRequest;
		bool PushPacket()
		{
			if( RecvBuf.size > 2) return false;
			auto packet = MissionTLV( &Receiver.pValue[-MissionTLV::pValueOffset]);
			RecvBuf.emplace_back();
			return true;
		}

	public:
		TLVDataLink()
		void Process()
		{
			if( !Receiver.HasData()) return;
			if( !Receiver.result) return;
			auto PacketReady = ConstructDatalinkPacket();
			if( !PacketReady)
			{
				Receiver.send(EDestination::CDH,|0x80,&reply_msg ,1);
			}
		}

		MissionTLV* Recv()
		{
			if( !PacketReady) return nullptr;

			PacketReady = false;
			return &RecvBuf;
		}
		template<typename T>
		bool Send( T packet)
		{

		}




		}
}