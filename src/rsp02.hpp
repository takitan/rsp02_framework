#pragma once
#include <cstdint>

struct TLVmessage_t
{
	typedef uint8_t type_t;
	typedef uint8_t dest_t;
	typedef uint16_t len_t;

	dest_t destination;
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

enum class EDestination : TLVmessage_t::dest_t
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

template<int N>
struct byte_type{};

template<>
struct byte_type<8>{ typedef uint8_t type;};

template<>
struct byte_type<16>{ typedef uint16_t type;};

template<>
struct byte_type<32>{ typedef uint32_t type;};


struct MissionTLV
{
	static constexpr int bufsz = 256;
	static constexpr int dest_offset = 0;
	static constexpr int type_offset = 1;
	static constexpr int length_offset = 2;
	static constexpr int pValue_offset = 4;

	using len_t = TLVmessage_t::len_t;
	EDestination dest;
	EType type;
	len_t length;
	alignas(32) uint8_t pValue[bufsz];

	MissionTLV():dest(EDestination::Null), type(EType::RequestNull), length(0){}

	MissionTLV(EDestination dest, EType type, len_t len, void* pv)
		:dest(dest), type(type), length(len)
	{
		memcpy( pValue, pv, len);
	}
	MissionTLV(uint8_t* buf)
	{
		dest = static_cast<EDestination>( Align<8>( &buf[dest_offset]));
		type = static_cast<EType>( Align<8>( &buf[type_offset]));
		length = Align<16>( &buf[length_offset]);
		length = length > bufsz : bufsz : 
		memcpy( this->pValue, &buf[ pValue_offset], length);

	}
	MissionTLV(const MissionTLV &) = default;

	MissionTLV(const TLVmessage_t &mes)
		:dest(static_cast<EDestination>(mes.destination)),
		 type(static_cast<EType>(mes.type)),
		 length(mes.length)
	{
		memcpy( pValue, mes.pValue, mes.length);
	}

	private:
		template<int N>
		typename byte_type<N>::type Align( uint8_t* byte)
		{
			alignas(32) uint8_t dat[N];
			for( int i=0;i<N;i++) dat[i] = byte[i];
			return *(typename byte_type<N>::type*)dat
		}
};
