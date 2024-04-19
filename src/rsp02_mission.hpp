/**
 * @file rsp02_mission.hpp
 * @author Nobuyuki Takita (takitan1972@gmail.com)
 * @brief Mission系定義
 * @version 0.1
 * @date 2024-04-18
 */
#pragma once

#include "rsp02.hpp"
#include "fw/command/CommandTypeBase.hpp"

/** @brief StateID */
enum class StateID : int
{
	Idle		= 0,	//<! Idle
	State1		= 1,	//<! State1
	State2		= 2,	//!< State2
};

/** @brief TLVコマンド */
enum class EType : uint8_t
{
	Null,						//!< 未定義
	TAKE_PHOTO,					//!< 写真撮影要求
	TAKE_PHOTO_RES,				//!< 写真撮影応答
	REQ_IMAGE,					//!< 画像データ要求
	REQ_IMAGE_RES,				//!< 画像データ応答
	SD_FORMAT,					//!< SDカードフォーマット要求
	SD_FORMAT_RES,				//!< SDカードフォーマット応答
	REQ_SD_STATUS,				//!< SDカードステータス要求
	REQ_SD_STATUS_RES,			//!< SDカードステータス応答
	SET_CUR_TIME		= 100,	//!< 自系現在時刻設定要求
	SET_CUR_TIME_RES,			//!< 自系現在時刻設定応答
	GET_HKDATA,					//!< 自系HKデータ要求
	GET_HKDATA_RES,				//!< 自系HKデータ応答
	REQ_PING,					//!< 自系死活確認要求
	REQ_PING_RES,				//!< 自系死活確認応答
	REQ_TEMPERATURE,			//!< 自系温度要求
	REQ_TEMPERATURE_RES,		//!< 自系温度応答
};

using TLVPacket = TLVpacket_t<EDestination, EType>;

/**
 * @brief StateIDから文字列を得る
 * 
 * @param dst StateID
 * @return const char* 対応する文字列
 */
static inline const char* TypeString(EType dst)
{
	switch( dst)
	{
		case EType::Null: 					return "Null";
		case EType::TAKE_PHOTO: 			return "TAKE_PHOTO";
		case EType::TAKE_PHOTO_RES: 		return "TAKE_PHOTO_RES";
		case EType::REQ_IMAGE:				return "REQ_IMAGE";
		case EType::REQ_IMAGE_RES:			return "REQ_IMAGE_RES";
		case EType::SD_FORMAT:				return "SD_FORMAT";
		case EType::SD_FORMAT_RES:			return "SD_FORMAT_RES";
		case EType::REQ_SD_STATUS:			return "REQ_SD_STATUS";
		case EType::REQ_SD_STATUS_RES:		return "REQ_SD_STATUS";
		case EType::SET_CUR_TIME:			return "SET_CUR_TIME";
		case EType::SET_CUR_TIME_RES:		return "SET_CUR_TIME_RES";
		case EType::GET_HKDATA:				return "GET_HKDATA";
		case EType::GET_HKDATA_RES:			return "GET_HKDATA_RES";
		case EType::REQ_PING:				return "REQ_PING";
		case EType::REQ_PING_RES:			return "REQ_PING_RES";
		case EType::REQ_TEMPERATURE:		return "REQ_TEMPERATURE";
		case EType::REQ_TEMPERATURE_RES:	return "REQ_TEMPERATURE_RES";
		default: return "";
	}
}

template<>
inline void TLVpacket_t<EDestination,EType>::print(char* buf)
{
	int p = ::sprintf( buf, "dst:%02x(%s),typ:%02x(%s),length:%04x,pv:",
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
