#pragma once
#include <cstdint>
#include <cstring>
#include "fw/util/align.hpp"
#include "MissionDefine.hpp"
#include "fw/command/CommandImplBase.hpp"
#include "fw/command/CommandTypeBase.hpp"

namespace rsp::rsp02::fw::logger{
class ISink;
}

struct HogeCommand_t : public rsp::rsp02::fw::command::CommandTypeBase_t<MissionTLV>
{
	using CommandTypeBase_t<MissionTLV>::CommandTypeBase_t;
	constexpr static std::size_t PayloadSize = 10;
	struct Payload_t
	{
		uint8_t data[PayloadSize];
		Payload_t(){}
		Payload_t(const uint8_t* pValue, len_t len)
		{
			if( len > PayloadSize) len = PayloadSize;
			memcpy( data, pValue, len);
		}
	}Payload;
	HogeCommand_t(){}
	HogeCommand_t( const MissionTLV &packet) : CommandTypeBase_t( packet), Payload( packet.pValue, length){}
	HogeCommand_t( const MissionTLV* packet) : CommandTypeBase_t( packet), Payload( packet->pValue, length){}
	operator MissionTLV() const
	{
		return MissionTLV(this->destination, this->type, this->length, (void*)(&this->Payload));
	}
};

using HogeResponse_t = HogeCommand_t;

class Hoge : public CommandImplBase<HogeCommand_t,HogeResponse_t>
{
	public:
		using ParseStatus = rsp::rsp02::fw::command::ParseStatus;
		using ExecuteStatus = rsp::rsp02::fw::command::ExecuteStatus;
		Hoge();

	private:
		ExecuteStatus ConcreteExecute( const HogeCommand_t &cmd, HogeResponse_t &res);
};
