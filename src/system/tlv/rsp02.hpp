#pragma once
#include <cstdint>
#include <cstring>
#include <cstdio>
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
		void operator()(T src)
		{
			align::safe_write( (uint8_t*)origin, src);
		}
		T operator()() const
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
		T* operator()() const
		{
			return (T*)const_cast<void*>(origin);
		}
		T &operator[](int i) const
		{
			return ((uint8_t*)origin)[i];
		}
};

struct TLVpacketBase_t
{
	const void* Original;

	TLVpacketBase_t(const void* org, int sender) :
		TLVpacketBase_t( const_cast<void*>(org), sender){}
	TLVpacketBase_t(void* org, int sender) :
		Original(org), sender_id(sender){}

		int sender_id;
};

template<typename DST_T,typename TYP_T>
struct TLVpacket_t : TLVpacketBase_t
{
	using dst_t = DST_T;
	using typ_t = TYP_T;
	using len_t = uint16_t;
	constexpr static size_t HeaderSize = sizeof(dst_t)+sizeof(typ_t)+sizeof(len_t);

	constexpr static size_t dst_offset = 0;
	constexpr static size_t typ_offset = 1;
	constexpr static size_t len_offset = 2;
	constexpr static size_t pv_offset = 4;

	TLVpacket_t() : TLVpacket_t((const void*)nullptr){}
	TLVpacket_t(const void* org) : TLVpacket_t(org,-1){}
	TLVpacket_t(const void* org, int sender) :
		TLVpacketBase_t(org,sender),
		Destination(org_pnt(dst_offset)),
		Type(org_pnt(typ_offset)),
		Length(org_pnt(len_offset)),
		pValue(org_pnt(pv_offset)){}

	SafeProperty<dst_t> Destination;
	SafeProperty<typ_t> Type;
	SafeProperty<len_t> Length;
	SafeArray<uint8_t> pValue;

	void print(char* buf)
	{
		int p = ::sprintf( buf, "dst:%02x,type:%02x,length:%04x,pv:",
			Destination(), Type(), Length());
		len_t len = Length();
		auto pvpnt = pValue();
		for(int i=0;i<len;i++)
		{
			uint8_t pv = pvpnt[i];
			p += ::sprintf( &buf[p], "%02x", pv);
		}
	}

	protected:
		inline const void* org_pnt(size_t ofs){ return (uint8_t*)Original+ofs;}
		inline const void* pv_pnt(size_t ofs){ return (uint8_t*)org_pnt(pv_offset)+ofs;}
};
