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
	Null		= 0,
	Ground		= 1,
	Rx			= 2,
	Tx1			= 3,
	Tx2			= 4,
	CDH			= 5,
	Mission		= 6,
	ParentLora	= 7,
	Child1		= 8,
	Child2		= 9,
	NumOfDestination,
};

enum class ECMDType : uint8_t
{
	Null			= 0x00,
	COMM_TEST		= 0x01,
	GET_HKDATA		= 0x11,
	RESET_MAINOBC	= 0x12,
	EXPAND_ANTENNA	= 0x13,
	SET_FDIR		= 0x16,
	POWER			= 0x20,
	GET_LEVEL		= 0x74,
	CHECK_FCS		= 0x77,
	CHECK_DEST		= 0x78,
	TX_TEST			= 0x79,
	RX_SW_RESET		= 0x7a,
	SEND_CW			= 0x81,
	SEND_GMSK		= 0x85,
	ABORT_DOWNLINK	= 0x86,
	SET_CW_SPEED	= 0x87,
	SELECT_TXOBC	= 0x91,
	TX_RESET		= 0x92,
	CHANGE_TX_MODE	= 0x93,
	TLVMSG			= 0xe1,
	TIME_SYNC		= 0xe2,
	NumOfCMDType,
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
struct SafePropertyEx
{
	using align = rsp::rsp02::fw::util::align;
	private:
		T value;
	public:
		SafePropertyEx(){}
		void operator()(T src)
		{
			value = src;
		}
		T operator()() const
		{
			return value;
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

struct PacketBase_t
{
	const void* Original;

	PacketBase_t(const void* org, int sender) :
		PacketBase_t( const_cast<void*>(org), sender){}
	PacketBase_t(void* org, int sender) :
		Original(org), sender_id(sender){}
		int sender_id;

	PacketBase_t( const PacketBase_t &dst)
	{
		Original = dst.Original;
		sender_id = dst.sender_id;
	}

	protected:
		inline const void* org_pnt(size_t ofs){ return (uint8_t*)Original+ofs;}
		inline const void* pv_pnt(uint8_t* org, size_t ofs){ return org+ofs;}
};

/**
 * @brief 地上局がC系に送信するコマンド
 * @tparam TYP_T コマンドタイプの型
 */
template<typename TYP_T>
struct CMDpacket_t : PacketBase_t
{
	using typ_t = TYP_T;
	constexpr static size_t typ_offset = 0;
	constexpr static size_t par_offset = 1;

	CMDpacket_t() : CMDpacket_t((const void*)nullptr, 0){}
	CMDpacket_t(const void* org, uint16_t len) : CMDpacket_t(org,len, -1){}
	CMDpacket_t(const void* org, uint16_t len, int sender) :
		PacketBase_t(org,sender),
		Type(org_pnt(typ_offset)),
		Length(len),
		pParam(org_pnt(par_offset)){}
	// コマンドのタイプ	
	SafeProperty<typ_t> Type;
	SafePropertyEx<uint16_t> Length;
	// コマンドパラメータ(可変長)
	SafeArray<uint8_t> pParam;

	/**
	 * @brief パケットを表示用に整形する
	 * 
	 * @param buf 整形済テキストの格納バッファ
	 * @pre bufには、必要十分なサイズを用意しておくこと
	 */
	void print(char* buf)
	{
		int p = ::sprintf( buf, "dst:%02x(%s),type:%02x,length:%04x,pv:",
			(uint8_t)Destination(), DestinationString(Destination()),
			(uint8_t)Type(), Length());
		len_t len = Length();
		auto pvpnt = pValue();
		for(int i=0;i<len;i++)
		{
			uint8_t pv = pvpnt[i];
			p += ::sprintf( &buf[p], "%02x", pv);
		}
	}
};

/**
 * @brief C系間から地上局に返すレスポンス
 * @tparam TYP_T コマンドタイプの型
 */
template<typename TYP_T>
struct RESpacket_t : PacketBase_t
{
	using typ_t = TYP_T;
	constexpr static size_t typ_offset = 0;
	constexpr static size_t par_offset = 1;

	RESpacket_t() : RESpacket_t((const void*)nullptr){}
	RESpacket_t(const void* org) : RESpacket_t(org,-1){}
	RESpacket_t(const void* org, int sender) :
		PacketBase_t(org,sender),
		Type(org_pnt(typ_offset)),
		pParam(org_pnt(par_offset)){}
	// コマンドのタイプ	
	SafeProperty<typ_t> Type;
	// コマンドパラメータ(可変長)
	SafeProperty<uint8_t> Param;

	/**
	 * @brief パケットを表示用に整形する
	 * 
	 * @param buf 整形済テキストの格納バッファ
	 * @pre bufには、必要十分なサイズを用意しておくこと
	 */
	void print(char* buf)
	{
		int p = ::sprintf( buf, "type:%02x,length:%04x,pv:",
			(uint8_t)Destination(), DestinationString(Destination()),
			(uint8_t)Type(), Length());
		len_t len = Length();
		auto pvpnt = pValue();
		for(int i=0;i<len;i++)
		{
			uint8_t pv = pvpnt[i];
			p += ::sprintf( &buf[p], "%02x", pv);
		}
	}
};

/**
 * @brief TLVコマンドレスポンス
 * 
 * @tparam DST_T Destinationの型
 * @tparam TYP_T コマンドタイプの型
 */
template<typename DST_T,typename TYP_T>
struct TLVpacket_t : PacketBase_t
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
		PacketBase_t(org,sender),
		Destination(org_pnt(dst_offset)),
		Type(org_pnt(typ_offset)),
		Length(org_pnt(len_offset)),
		pValue(org_pnt(pv_offset)){}

	SafeProperty<dst_t> Destination;
	SafeProperty<typ_t> Type;
	SafeProperty<len_t> Length;
	SafeArray<uint8_t> pValue;

	/**
	 * @brief パケットを表示用に整形する
	 * 
	 * @param buf 整形済テキストの格納バッファ
	 * @pre bufには、必要十分なサイズを用意しておくこと
	 */
	void print(char* buf)
	{
		int p = ::sprintf( buf, "dst:%02x(%s),type:%02x,length:%04x,pv:",
			(uint8_t)Destination(), DestinationString(Destination()),
			(uint8_t)Type(), Length());
		len_t len = Length();
		auto pvpnt = pValue();
		for(int i=0;i<len;i++)
		{
			uint8_t pv = pvpnt[i];
			p += ::sprintf( &buf[p], "%02x", pv);
		}
	}
};

using rsp02TLV = TLVpacket_t<EDestination,uint8_t>;

static inline const char* DestinationString(EDestination dst)
{
	switch( dst)
	{
		case EDestination::Null: return "Null!";
		case EDestination::Ground: return "Ground";
		case EDestination::Rx: return "Rx";
		case EDestination::Tx1: return "Tx1";
		case EDestination::Tx2: return "Tx2";
		case EDestination::CDH: return "CDH";
		case EDestination::Mission: return "Mission";
		case EDestination::ParentLora: return "ParentLora";
		case EDestination::Child1: return "Child1";
		case EDestination::Child2: return "Child2";
		default: return "";
	}
}
