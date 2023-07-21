#pragma once
#include <cstdint>
#include <cstring>
#include "fw/util/align.hpp"
#include "tlv/rsp02_mission.hpp"
#include "MissionDefine.hpp"
#include "fw/util/align.hpp"

namespace rsp::rsp02::fw::logger{
class ILogger;
}

struct HogeHogeCommand_t : public MissionTLV
{
	HogeHogeCommand_t(const void* pkt) : MissionTLV(pkt){}
	HogeHogeCommand_t(const void* pkt,int sender) : MissionTLV(pkt,sender){}
};

using HogeHogeResponse_t = HogeHogeCommand_t;

class HogeHoge : public CommandImplBase<HogeHogeCommand_t,HogeHogeResponse_t>
{
	public:
		using ParseStatus = rsp::rsp02::fw::command::ParseStatus;
		using ExecuteStatus = rsp::rsp02::fw::command::ExecuteStatus;
		HogeHoge();

	private:
		ExecuteStatus ConcreteExecute( const HogeHogeCommand_t &cmd);
};