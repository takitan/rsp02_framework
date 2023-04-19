#pragma once
#include <cstdint>
#include <cstring>
#include "fw/util/align.hpp"
#include "MissionDefine.hpp"
#include "fw/command/CommandImplBase.hpp"
#include "fw/command/CommandTypeBase.hpp"

struct HogeHogeCommand_t : public rsp::rsp02::fw::command::CommandTypeBase_t<MissionTLV>
{
	using CommandTypeBase_t<MissionTLV>::CommandTypeBase_t;
	struct Payload_t
	{
		uint8_t hage;
		uint32_t hige;
		uint8_t huge;
		uint16_t hege;
		uint32_t hoge;
		Payload_t(){}
		Payload_t(const uint8_t* pValue) :
			hage( align::safe_read<8>(&pValue[0])),
			hige( align::safe_read<32>(&pValue[1])),
			huge( align::safe_read<8>(&pValue[5])),
			hege( align::safe_read<16>(&pValue[6])),
			hoge( align::safe_read<32>(&pValue[8])){}
	}Payload;
	HogeHogeCommand_t(){}
	HogeHogeCommand_t( const MissionTLV &packet) : CommandTypeBase_t( packet), Payload( packet.pValue){}
	HogeHogeCommand_t( const MissionTLV* packet) : CommandTypeBase_t( packet), Payload( packet->pValue){}
};

using HogeHogeResponse_t = HogeHogeCommand_t;

class HogeHoge : public CommandImplBase<HogeHogeCommand_t,HogeHogeResponse_t>
{
	using ParseStatus = rsp::rsp02::fw::command::ParseStatus;
	using ExecuteStatus = rsp::rsp02::fw::command::ExecuteStatus;
	public:
		HogeHoge():CommandImplBase( "HogeHoge", EDestination::Ground, EType::RequestPing){}

	private:
		ExecuteStatus ConcreteExecute( const HogeHogeCommand_t &cmd, HogeHogeResponse_t &res)
		{
			return ExecuteStatus::Success;
		}
};