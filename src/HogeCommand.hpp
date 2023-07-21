#pragma once
#include <cstdint>
#include <cstring>
#include "fw/util/align.hpp"
#include "rsp02_mission.hpp"
#include "MissionDefine.hpp"

namespace rsp::rsp02::fw::logger{
class ISink;
}

struct HogeCommand_t : public MissionTLV
{
	constexpr static int PayloadSize = 10;
	HogeCommand_t( const void* pkt) : MissionTLV(pkt){}
	HogeCommand_t( const void* pkt, int sender) : MissionTLV(pkt,sender){}
};

struct HogeResponse_t
{
	constexpr static int PayloadSize = 10;
	MissionTLV::dst_t Destination;
	MissionTLV::typ_t Type;
	MissionTLV::len_t Length;
	int sender_id;
	uint8_t pValue[PayloadSize];
	HogeResponse_t( MissionTLV::dst_t dst, MissionTLV::typ_t typ, MissionTLV::len_t len) :
		Destination(dst), Type(typ), Length(len){}
};

class Hoge : public CommandImplBase<HogeCommand_t,HogeResponse_t>
{
	public:
		using ParseStatus = rsp::rsp02::fw::command::ParseStatus;
		using ExecuteStatus = rsp::rsp02::fw::command::ExecuteStatus;
		Hoge();

	private:
		ExecuteStatus ConcreteExecute( const HogeCommand_t &cmd);
};
