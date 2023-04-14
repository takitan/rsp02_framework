/*
 * TlvCommandBase.h
 *
 *  Created on: 2021/10/26
 *      Author: takit
 */

#pragma once
#include "fw/time/StopWatch.hpp"

namespace rsp{
namespace rsp02{
namespace fw{
namespace command{

constexpr int TLV_SEND_BUF_SZ = 256;

//#include "mission.hpp"
//#include "RSP02.hpp"
//#include "RspTLV.hpp"
//#include "mbed.h"
//#include "DebugSys/inc/hardware.h"
//#include "DebugSys/inc/uart_interface.h"

enum class ParseStatus
{
	Accept = 0,
	OtherCommand,
	OtherDestination,
	OverFlowLength,
	InvalidValue,
};

enum class ExecuteStatus
{
	Success = 0,
	Pending,
	Executing,
	NotInvoked,
	InvalidValue,
	Ignore,
	Error,
};

struct TCommandInfo
{
	using TStopWatch = rsp::rsp02::fw::time::TStopWatch;
	const char* Name;
	EDestination Dest;
	EType Type;
	long AcceptCount;
	long ExecuteCount;
	TStopWatch time;
	bool isInvoked;
	TCommandInfo( const char* nam, const EDestination dst, const EType typ)
		: Name(nam), Dest(dst), Type(typ), AcceptCount(0), ExecuteCount(0), time(), isInvoked(false){}
};

template< typename CMD_T, typename RES_T>
class ICommand
{
public:
	virtual ~ICommand(){}

	virtual ParseStatus Parse( CMD_T* cmd, RES_T* res) = 0;
	/** @brief コマンド実行関数 */
	virtual ExecuteStatus Execute() = 0;
	/** @brief コマンドの現在ステータス参照*/
	virtual const TCommandInfo &GetInfo() const = 0;
	/** @brief コマンド実行中かどうかを問い合わせ、必要に応じて実行中フラグをクリアする
	 * @param clear true 実行中フラグをクリアする(default)
	 * @param clear false 実行中フラグをクリアしない
	*/
	virtual bool TestInvoked(bool clear=true) = 0;
};

}
}
}
}

