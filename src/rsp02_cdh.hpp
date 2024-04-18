#pragma once
/**
 * @file rsp02_cdh.hpp
 * @author Nobuyuki Takita (takitan1972@gmail.com)
 * @brief C&DH系定義
 * @version 0.1
 * @date 2024-04-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */

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
	ReqNull				= 0,	//!< 未定義
	RESET_MAINOBC,				//!< 衛星全体リセット要求
	RESET_MAINOBC_RES,			//!< 衛星全体リセット応答
	EXPAND_ANTENNA,				//!< アンテナ展開要求
	EXPAND_ANTENNA_RES,			//!< アンテナ展開応答
	SET_FDIR,					//!< 異常処置設定要求
	SET_FDIR_RES,				//!< 異常処置設定応答
	POWER,						//!< 搭載機器電源設定要求
	POWER_RES,					//!< 搭載機器電源設定応答
	SEND_CW,					//!< CW送信要求
	SEND_CW_RES,				//!< CW送信応答
	SEND_GMSK,					//!< GMSK送信要求
	SEND_GMSD_RES,				//!< GMSK送信応答
	ABORT_DOWNLINK,				//!< 送信キャンセル要求
	ABORT_DOWNLINK_RES,			//!< 送信キャンセル応答
	SET_CW_SPEED,				//!< CW送信速度設定要求
	SET_CW_SPEED_RES,			//!< CW送信速度設定応答
	SELECT_TXOBC,				//!< 送信機切替要求
	SELECT_TXOBC_RES,			//!< 送信機切替応答
	TX_RESET,					//!< 送信機リセット要求
	TX_RESET_RES,				//!< 送信機リセット応答
	COMM_TEST,					//!< 衛星内通信テスト要求
	COMM_TEST_RES,				//!< 衛星内通信テスト応答
	GET_HKDATA_FULL,			//!< 全系HKデータ要求
	GET_HKDATA_FULL_RES,		//!< 全系HKデータ応答
	SET_CUR_TIME		= 100,	//!< 自系現在時刻設定要求
	SET_CUR_TIME_RES,			//!< 自系現在時刻設定応答
	GET_HKDATA,					//!< 自系HKデータ要求
	GET_HKDATA_RES,				//!< 自系HKデータ応答
	REQ_PING,					//!< 自系死活確認要求
	REQ_PING_RES,				//!< 自系死活確認応答
	REQ_TEMPERATURE,			//!< 自系温度要求
	REQ_TEMPERATURE_RES,		//!< 自系温度応答
};

using CdhTLV = TLVpacket_t<EDestination, EType>;

static inline const char* TypeString(EType dst)
{
	switch( dst)
	{
		case EType::ReqNull:				return "ReqNull";
		case EType::RESET_MAINOBC:			return "RESET_MAINOBC";
		case EType::RESET_MAINOBC_RES:		return "RESET_MAINOBC_RES";
		case EType::EXPAND_ANTENNA:			return "EXPAND_ANTENNA";
		case EType::EXPAND_ANTENNA_RES:		return "EXPAND_ANTENNA_RES";
		case EType::SET_FDIR:				return "SET_FDIR";
		case EType::SET_FDIR_RES:			return "SET_FDIR_RES";
		case EType::POWER:					return "POWER";
		case EType::POWER_RES:				return "POWER_RES";
		case EType::SEND_CW:				return "SEND_CW";
		case EType::SEND_CW_RES:			return "SEND_CW_RES";
		case EType::SEND_GMSK:				return "SEND_GMSK";
		case EType::SEND_GMSD_RES:			return "SEND_GMSD_RES";
		case EType::ABORT_DOWNLINK:			return "ABORT_DOWNLINK";
		case EType::ABORT_DOWNLINK_RES:		return "ABORT_DOWNLINK_RES";
		case EType::SET_CW_SPEED:			return "SET_CW_SPEED";
		case EType::SET_CW_SPEED_RES:		return "SET_CW_SPEED_RES";
		case EType::SELECT_TXOBC:			return "SELECT_TXOBC";
		case EType::SELECT_TXOBC_RES:		return "SELECT_TXOBC_RES";
		case EType::TX_RESET:				return "TX_RESET";
		case EType::TX_RESET_RES:			return "TX_RESET_RES";
		case EType::COMM_TEST:				return "COMM_TEST";
		case EType::COMM_TEST_RES:			return "COMM_TEST_RES";
		case EType::GET_HKDATA_FULL:		return "GET_HKDATA_FULL";
		case EType::GET_HKDATA_FULL_RES:	return "GET_HKDATA_FULL_RES";
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
