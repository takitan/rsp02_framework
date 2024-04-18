/**
 * @file rsp02_attitude.hpp
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
	REQ_MAG_TORQUE,				//!< 磁気トルカ作動要求
	REA_MAG_TORQUE_RES,			//!< 磁気トルカ作動応答
	REQ_BDOT,					//!< Bdot制御実行要求
	REQ_BDOT_RES,				//!< Bdot制御実行応答
	REQ_GAIN_CONTROL,			//!< 電流ゲイン設定要求
	REQ_GAIN_CONTROL_RES,		//!< 電流ゲイン設定応答
	REQ_ANG_CONTROL,			//!< 角速度収束判定しきい値設定要求
	REQ_ANG_CONTROL_RES,		//!< 角速度収束判定しきい値設定応答
	REQ_INIT_SENSOR,			//!< センサ初期化要求
	REQ_INIT_SENSOR_RES,		//!< センサ初期化応答
	REQ_CHANGE_FILTER,			//!< フィルタ定数設定要求
	REQ_CHANGE_FILTER_RES,		//!< フィルタ定数設定応答
	REQ_ABORT_BDOT,				//!< Bdot制御停止要求
	REQ_ABORT_BDOT_RES,			//!< Bdot制御停止応答
	REQ_ATT_DATA,				//!< 姿勢データ送信要求
	REQ_ATT_DATA_RES,			//!< 姿勢データ送信応答
	SET_CUR_TIME		= 100,	//!< 自系現在時刻設定要求
	SET_CUR_TIME_RES,			//!< 自系現在時刻設定応答
	GET_HKDATA,					//!< 自系HKデータ要求
	GET_HKDATA_RES,				//!< 自系HKデータ応答
	REQ_PING,					//!< 自系死活確認要求
	REQ_PING_RES,				//!< 自系死活確認応答
	REQ_TEMPERATURE,			//!< 自系温度要求
	REQ_TEMPERATURE_RES,		//!< 自系温度応答
};
/*
REQ_MAG_TORQUE,
REA_MAG_TORQUE_RES,
REQ_BDOT,
REQ_BDOT_RES,
REQ_GAIN_CONTROL,
REQ_GAIN_CONTROL_RES,
REQ_ANG_CONTROL,
REQ_ANG_CONTROL_RES,
REQ_INIT_SENSOR,
REQ_INIT_SENSOR_RES,
REQ_CHANGE_FILTER,
REQ_CHANGE_FILTER_RES,
REQ_ABORT_BDOT,
REQ_ABORT_BDOT_RES,
REQ_ATT_DATA,
REQ_ATT_DATA_RES,

*/
using TLVPacket = TLVpacket_t<EDestination, EType>;
//using CommandTypeBase = rsp::rsp02::fw::command::CommandTypeBase_t<EType,EType>;

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
