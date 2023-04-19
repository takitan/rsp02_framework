#pragma once
#include <cstdint>
#include <cstring>
#include "fw/util/align.hpp"

struct TLVmessage_t
{
	typedef uint8_t type_t;
	typedef uint8_t dst_t;
	typedef uint16_t len_t;

	dst_t destination;
	type_t type;
	len_t length;
	uint8_t pValue[];
};

enum class EType : TLVmessage_t::type_t
{
	RequestNull = 0x00,
	RequestPing = 0x01,
	ReplyNull = 0x80,
	ReplyPing = 0x81,
};

enum class EDestination : TLVmessage_t::dst_t
{
	Null = 0,
	Ground = 1,
	Rx = 2,
	Tx1,
	Tx2,
	CDH,
	Mission,
	ParentLora,
	Child1,
	Child2,
};

template< typename DST_T, typename TYPE_T>
struct TLVpacket_t
{
	using align = rsp::rsp02::fw::util::align;
	using dst_t = DST_T;
	using type_t =TYPE_T;
	using len_t = TLVmessage_t::len_t;

	static constexpr int bufsz = 256;
	static constexpr int dst_offset = 0;
	static constexpr int type_offset = dst_offset + sizeof(dst_t);
	static constexpr int len_offset = type_offset + sizeof(type_t);
	static constexpr int pv_offset = len_offset + sizeof(len_t);


	DST_T destination;
	type_t type;
	len_t length;
	alignas(32) uint8_t pValue[bufsz];

	TLVpacket_t():destination(), type(), length(0)
	{
		memset( pValue, uint8_t(0), bufsz);
	}

	TLVpacket_t(dst_t dest, type_t type, len_t len, void* pv)
		:destination(dest), type(type), length(len)
	{
		memcpy( pValue, pv, len);
	}
	TLVpacket_t(uint8_t* buf) :
		destination( static_cast<dst_t>( align::safe_read<8>( &buf[dst_offset]))),
		type( static_cast<type_t>( align::safe_read<8>( &buf[type_offset]))),
		length( align::safe_read<16>( &buf[len_offset]))
	{
		if( length > bufsz) length = bufsz;
		memcpy( this->pValue, &buf[ pv_offset], length);
	}

	TLVpacket_t(const TLVpacket_t &src) :
		destination( src.destination),
		type( src.type),
		length( src.length)
	{
		memcpy( pValue, src.pValue, src.length);
	}

	TLVpacket_t(TLVmessage_t* mes) :
		destination(static_cast<DST_T>(mes->destination)),
		type(static_cast<type_t>(mes->type))
	{
		memcpy( pValue, mes->pValue, mes->length);
	}
};
