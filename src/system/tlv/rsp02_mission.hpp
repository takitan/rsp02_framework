#pragma once

#include "rsp02.hpp"
#include "fw/command/CommandTypeBase.hpp"

enum class EType : uint8_t
{
	ReqNull = 0x00,
	ReqPing = 0x01,
	ReqTakePhoto = 0x02,
	RepNull = 0x80,
	RepPing = 0x81,
	RepTakePhoto = 0x82,
};
using MissionTLV = TLVpacket_t<EDestination, EType>;
//using CommandTypeBase = rsp::rsp02::fw::command::CommandTypeBase_t<EType,EType>;

static inline const char* TypeString(EType dst)
{
	switch( dst)
	{
		case EType::ReqNull: return "ReqNull!";
		case EType::ReqPing: return "ReqPing";
		case EType::ReqTakePhoto: return "ReqTakePhoto";
		case EType::RepNull: return "RepNull";
		case EType::RepPing: return "RepPing";
		case EType::RepTakePhoto: return "RepTakePhoto";
		default: return "";
	}
}

template<>
void TLVpacket_t<EDestination,EType>::print(char* buf)
	{
		int p = ::sprintf( buf, "dst:%02x(%s),typ:%02x,length:%04x,pv:",
			(uint8_t)Destination(), DestinationString(Destination()),
			(uint8_t)Type(), TypeString(Type()),
			Length());
		len_t len = Length();
		auto pvpnt = pValue();
		for(int i=0;i<len;i++)
		{
			uint8_t pv = pvpnt[i];
			p += ::sprintf( &buf[p], "%02x", pv);
		}
	}
