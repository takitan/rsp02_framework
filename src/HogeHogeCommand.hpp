#pragma once
#include <cstdint>
#include <cstring>
#include "fw/util/align.hpp"
#include "tlv/rsp02_mission.hpp"
#include "MissionDefine.hpp"

namespace rsp::rsp02::fw::logger{
class ILogger;
}

struct HogeHogeCommand_t : public CommandTypeBase
{
	struct Payload_t
	{
		uint8_t hage;
		uint32_t hige;
		uint8_t huge;
		uint16_t hege;
		uint32_t hoge;
		Payload_t(){}
		Payload_t(const uint8_t* pValue) :
			SAFE_INIT(hage,pValue[0]),
			SAFE_INIT(hige,pValue[1]),
			SAFE_INIT(huge,pValue[5]),
			SAFE_INIT(hege,pValue[6]),
			SAFE_INIT(hoge,pValue[8]){}
	}Payload;
	HogeHogeCommand_t() = default;
	HogeHogeCommand_t (HogeHogeCommand_t &&) = default;
	// コピーコンストラクタ
	inline HogeHogeCommand_t( const HogeHogeCommand_t &) = default;
	// ムーブコンストラクタ
	HogeHogeCommand_t &operator=(const HogeHogeCommand_t &) = default;

	HogeHogeCommand_t(EDestination d, EType t, len_t l) : CommandTypeBase( d, t, l){}
	HogeHogeCommand_t( const MissionTLV &packet) : CommandTypeBase( packet), Payload( packet.pValue){}
	HogeHogeCommand_t( const MissionTLV* packet) : CommandTypeBase( packet), Payload( packet->pValue){}

	operator MissionTLV() const
	{
		return MissionTLV(this->destination, this->type, this->length, (void*)(&this->Payload));
	}
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