#pragma once
#include <cstdint>
#include <cstring>
#include "fw/command/TLVCommandBase.hpp"

static constexpr int HogePayLoadSize = 10;

struct HogeCommand_t
{
	uint8_t Payload[ HogePayLoadSize];
};

struct HogeResponse_t
{
	uint8_t Payload[ HogePayLoadSize];
};

class Hoge : TLVCommandBase<HogeCommand_t,HogeResponse_t>
{
	using ParseStatus = rsp::rsp02::fw::command::ParseStatus;
	using ExecuteStatus = rsp::rsp02::fw::command::ExecuteStatus;
	public:
		Hoge():TLVCommandBase( "Hoge", EDestination::Ground, EType::RequestPing){}

	private:
		ExecuteStatus ConcreteExecute( const HogeCommand_t &cmd, HogeResponse_t &res)
		{
			memcpy( res.Payload, cmd.Payload, 10);
			return ExecuteStatus::Success;
		}
};