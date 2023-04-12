#if 0
/*
 * RequestPing.cpp
 *
 *  Created on: 2021/10/27
 *      Author: takit
 */

#include "RequestPing.h"

/** @brief 自身の宛先のデフォルト値 */
static const uint8_t DefaultDestination	= EDestination::Mission;
/** @brief 自身のコマンドtypeのデフォルト値 */
static const uint8_t DefaultType = EType::CmdRequestPing;
static const char* DefaultName = "RequestPing";

RequestPing::RequestPing() : RequestPing( DefaultName, DefaultDestination, DefaultType){}

RequestPing::RequestPing( const char* myName, uint8_t myDestination, uint8_t myType)
				: TlvCommandBase( myName, myDestination, myType){}

RequestPing::~RequestPing(){}


void RequestPing::ConcreteExecute( TLVmessage_t* cmd, TLVmessage_t* res)
{
	// RequestPingの返答先は地上
	res->destination = EDestination::Ground;
	// 返答のtypeはReplyPing
	res->type = EType::CmdReplyPing;
	// コマンド仕様のpingのデータ長
	res->length = 10;
	// 冗長だが、敢えてコマンド仕様書と同じことを書く
	RequestPingPayload* cp = (RequestPingPayload*)cmd->pValue;
	RequestPingPayload* rp = (RequestPingPayload*)res->pValue;
	// 規定データ長だけコピー
	memcpy( (void*)rp, (void*)cp, res->length);
}

#endif
