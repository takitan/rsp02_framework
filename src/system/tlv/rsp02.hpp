#pragma once
#include <cstdint>
#include <cstring>
#include "fw/util/align.hpp"

/*
struct TLVmessage_t
{
	constexpr static std::size_t pValueSize = 256;
	typedef uint8_t type_t;
	typedef uint8_t dst_t;
	typedef uint16_t len_t;

	dst_t destination;
	type_t type;
	len_t length;
	uint8_t pValue[pValueSize];
	TLVmessage_t():destination(0),type(0),length(0)
	{
		memset(pValue, 0, pValueSize);
	}
};
*/

enum class EDestination : uint8_t
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

template<typename T>
struct SafeProperty
{
	using align = rsp::rsp02::fw::util::align;
	private:
		const void* origin;
	public:
		SafeProperty( const void* org) : origin(org){}
		SafeProperty& operator=(T src)
		{
			align::safe_write( (uint8_t*)origin, src);
			return *this;
		}
		operator T() const
		{
			return align::safe_read<T>( (uint8_t*)origin);
		}
};

template<typename T>
struct SafeArray
{
	using align = rsp::rsp02::fw::util::align;
	private:
		const void* origin;
	public:
		SafeArray( const void* org) : origin(org){}
		operator void*()
		{
			return static_cast<void*>((uint8_t*)origin);
		}
		T &operator[](int i)
		{
			return *((uint8_t*)origin);
		}
};

struct TLVpacketBase_t
{
	const void* Original;

	TLVpacketBase_t(const void* org, int sender) :
		TLVpacketBase_t( const_cast<void*>(org), sender){}
	TLVpacketBase_t(void* org, int sender) :
		Original(org), sender_id(sender){}

	protected:
		int sender_id;
};

template<typename DST_T,typename TYP_T>
struct TLVpacket_t : TLVpacketBase_t
{
	using dst_t = DST_T;
	using typ_t = TYP_T;
	using len_t = uint16_t;
	constexpr static size_t dst_offset = 0;
	constexpr static size_t typ_offset = 1;
	constexpr static size_t len_offset = 2;
	constexpr static size_t pv_offset = 4;

	TLVpacket_t() : TLVpacket_t((const void*)nullptr){}
	TLVpacket_t(const void* org) : TLVpacket_t(org,-1){}
	TLVpacket_t(const void* org, int sender) :
		TLVpacketBase_t(org,sender),
		Destination(pnt(org,dst_offset)),
		Type(pnt(org,typ_offset)),
		Length(pnt(org,len_offset)),
		pValue(pnt(org,pv_offset)){}

	SafeProperty<dst_t> Destination;
	SafeProperty<typ_t> Type;
	SafeProperty<len_t> Length;
	SafeArray<uint8_t> pValue;
	int sender_id;

	private:
		inline const void* pnt(const void* org, size_t ofs){ return (uint8_t*)org+ofs;}
};

/*
template< typename DST_T, typename TYPE_T>
struct TLVpacket_tt
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
*/