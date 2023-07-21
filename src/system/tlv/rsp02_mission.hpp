#pragma once

#include "rsp02.hpp"
#include "fw/command/CommandTypeBase.hpp"

enum class EType : uint8_t
{
	RequestNull = 0x00,
	RequestPing = 0x01,
	ReplyNull = 0x80,
	ReplyPing = 0x81,
};
using rsp02TLV = TLVpacket_t<uint8_t,uint8_t>;
using MissionTLV = TLVpacket_t<EDestination, EType>;
//using CommandTypeBase = rsp::rsp02::fw::command::CommandTypeBase_t<EDestination,EType>;
