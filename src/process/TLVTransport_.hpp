#pragma once
#include <cstring>
#include <queue>
#include <algorithm>
#include "rsp02.hpp"
#include "system/Process.hpp"

namespace rsp{
namespace rsp02{
namespace system{



/*
template<typename T>
class TLVTransport : public ProcessBase<T,2>
{
	public:
		TLVTransport(){}

	protected:
		bool ConcreteProcess( T &packet)
		{
			auto &info = UpStreamInfo;
			TTimeKeeper tk( info);
			if( !tlv.HasData()) return false;
			if( !tlv.result) return false;
			auto mes = T(&tlv.pValue[-T::pv_offset]);
			UpperProcess->Accept( mes);
			info.TotalPacket ++;
			return true;
		}

		bool DownStream()
		{
			StreamInfo_t &info = DownStreamInfo;
			std::vector<T> &queue = DownStreamQueue;
			const std::size_t szmax = DownStreamQueueSizeMax;

			TTimeKeeper tk( info);
			if( queue.empty()) return false;
			auto packet = queue.pop();
			tlv.send(
				static_cast<TLVmessage_t::dst_t>( packet.destination),
				static_cast<TLVmessage_t::type_t>( packet.type),
				static_cast<uint8_t*>( packet.pValue),
				packet.length
			);
			DownStreamInfo.TotalPacket ++;
			return true;
		}

		void SetUpperProcess( CommandKernel<T>* up_process)
		{
			UpperProcess = up_process;
		}

		bool Invoke( T &packet)
		{
			if( DownStreamQueue.size > DownStreamQueueSizeMax)
			{
				DownStreamInfo.QueueOverflow ++;
				return false;
			}
			DownStreamQueue.push_back( packet);
		}
};
*/

}
}
}
