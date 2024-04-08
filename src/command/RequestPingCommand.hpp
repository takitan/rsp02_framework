#pragma once
#include <cstdint>
#include <cstring>
#include "fw/util/align.hpp"
#include "rsp02_mission.hpp"
#include "GlobalDefine.hpp"

namespace rsp::rsp02::fw::logger{
class ISink;
}

struct RequestPingCommand_t : public TLVPacket
{
	constexpr static size_t PayloadSize = 10;
	RequestPingCommand_t(){}
	RequestPingCommand_t( const void* pkt) : TLVPacket(pkt){}
	RequestPingCommand_t( const void* pkt, int sender) : TLVPacket(pkt,sender){}
};

struct RequestPingResponse_t : public TLVPacket
{
	constexpr static size_t PayloadSize = 10;
	RequestPingResponse_t(){}
	RequestPingResponse_t( const void* pkt) : TLVPacket(pkt){}
	RequestPingResponse_t( const void* pkt, int sender) : TLVPacket(pkt,sender){}
};

class TRequestPingCommand : public CommandImplBase<RequestPingCommand_t,RequestPingResponse_t>
{
	public:
		using ParseStatus = rsp::rsp02::fw::command::ParseStatus;
		using ExecuteStatus = rsp::rsp02::fw::command::ExecuteStatus;
		TRequestPingCommand();

	private:
		uint8_t buffer[RequestPingResponse_t::HeaderSize + RequestPingResponse_t::PayloadSize];
		RequestPingResponse_t Response;
		ExecuteStatus ConcreteExecute( const RequestPingCommand_t &cmd);
};
