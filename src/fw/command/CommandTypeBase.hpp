#pragma once

namespace rsp{
namespace rsp02{
namespace fw{
namespace command{
/*
template<typename T, size_t OFFSET>
struct SafeProperty
{
	using align = rsp::rsp02::fw::util::align;
	private:
		void* origin;
	public:
		SafeProperty( void* org) : origin(org){}
		SafeProperty& operator=(T src)
		{
			align::safe_write( (uint8_t*)origin+OFFSET, src);
			return *this;
		}
		operator T()
		{
			uint8_t hoge;
			return align::safe_read<T>( (uint8_t*)origin+OFFSET);
		}
};

template<typename T, size_t OFFSET>
struct SafeArray
{
	using align = rsp::rsp02::fw::util::align;
	private:
		void* origin;
	public:
		SafeArray( void* org) : origin(org){}
		operator void*()
		{
			return static_cast<void*>(((uint8_t*)origin+OFFSET));
		}
		T &operator[](int i)
		{
			return *((uint8_t*)origin+OFFSET);
		}
};

template<typename DST_T,typename TYP_T>
struct CommandTypeBase_t
{
	using LEN_T = uint16_t;
	constexpr static size_t dst_offset = 0;
	constexpr static size_t typ_offset = 1;
	constexpr static size_t len_offset = 2;
	constexpr static size_t pv_offset = 4;
	void* packet;

	CommandTypeBase_t(){}
	CommandTypeBase_t(void* pkt) :
		packet(pkt),
		Destination(pkt),
		Type(pkt),
		Length(pkt),
		pValue(pkt){}

	SafeProperty<DST_T, dst_offset> Destination;
	SafeProperty<TYP_T, typ_offset> Type;
	SafeProperty<LEN_T, len_offset> Length;
	SafeArray<uint8_t,pv_offset> pValue;
};
*/
}
}
}
}
