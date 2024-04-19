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

*/
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
		case EType::REQ_MAG_TORQUE:			return "REQ_MAG_TORQUE";
		case EType::REA_MAG_TORQUE_RES:		return "REA_MAG_TORQUE_RES";
		case EType::REQ_BDOT:				return "REQ_BDOT";
		case EType::REQ_BDOT_RES:			return "REQ_BDOT_RES";
		case EType::REQ_GAIN_CONTROL:		return "REQ_GAIN_CONTROL";
		case EType::REQ_GAIN_CONTROL_RES:	return "REQ_GAIN_CONTROL_RES";
		case EType::REQ_ANG_CONTROL:		return "REQ_ANG_CONTROL";
		case EType::REQ_ANG_CONTROL_RES:	return "REQ_ANG_CONTROL_RES";
		case EType::REQ_INIT_SENSOR:		return "REQ_INIT_SENSOR";
		case EType::REQ_INIT_SENSOR_RES:	return "REQ_INIT_SENSOR_RES";
		case EType::REQ_CHANGE_FILTER:		return "REQ_CHANGE_FILTER";
		case EType::REQ_CHANGE_FILTER_RES:	return "REQ_CHANGE_FILTER_RES";
		case EType::REQ_ABORT_BDOT:			return "REQ_ABORT_BDOT";
		case EType::REQ_ABORT_BDOT_RES:		return "REQ_ABORT_BDOT_RES";
		case EType::REQ_ATT_DATA:			return "REQ_ATT_DATA";
		case EType::REQ_ATT_DATA_RES:		return "REQ_ATT_DATA_RES";
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
