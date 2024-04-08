#pragma once
#include <cstdint>
#include <cstring>
#include "fw/util/align.hpp"
#include "TLV_library/rsp02_mission.hpp"
#include "GlobalDefine.hpp"
#include "fw/util/align.hpp"

namespace rsp::rsp02::fw::logger{
class ILogger;
}

struct RequestTakePhotoCommand_t : public TLVPacket
{
	constexpr static int PayloadSize = 3;
	RequestTakePhotoCommand_t() : RequestTakePhotoCommand_t((const void*)nullptr){}
	RequestTakePhotoCommand_t(const void* pkt) : RequestTakePhotoCommand_t(pkt,-1){}
	RequestTakePhotoCommand_t(const void* pkt,int sender) : TLVPacket(pkt,sender),
		NumOfPicture(pv_pnt(0)),
		Dummy0(pv_pnt(1)),
		Dummy1(pv_pnt(2))
	{}

	SafeProperty<uint8_t> NumOfPicture;
	SafeProperty<uint8_t> Dummy0;
	SafeProperty<uint8_t> Dummy1;
};

struct RequestTakePhotoResponse_t : public TLVPacket
{
	constexpr static int PayloadSize = 3;
	RequestTakePhotoResponse_t() : RequestTakePhotoResponse_t((const void*)nullptr){}
	RequestTakePhotoResponse_t(const void* pkt) : RequestTakePhotoResponse_t(pkt,-1){}
	RequestTakePhotoResponse_t(const void* pkt,int sender) : TLVPacket(pkt,sender),
		NumOfPicture(pv_pnt(0)),
		Dummy0(pv_pnt(1)),
		Dummy1(pv_pnt(2))
	{}

	SafeProperty<uint8_t> NumOfPicture;
	SafeProperty<uint8_t> Dummy0;
	SafeProperty<uint8_t> Dummy1;
};

class TRequestTakePhotoCommand : public CommandImplBase<RequestTakePhotoCommand_t,RequestTakePhotoResponse_t>
{
	public:
		using ParseStatus = rsp::rsp02::fw::command::ParseStatus;
		using ExecuteStatus = rsp::rsp02::fw::command::ExecuteStatus;
		TRequestTakePhotoCommand();

	private:
		uint8_t buffer[RequestTakePhotoResponse_t::HeaderSize + RequestTakePhotoResponse_t::PayloadSize];
		RequestTakePhotoResponse_t Response;
		ExecuteStatus ConcreteExecute( const RequestTakePhotoCommand_t &cmd);
};