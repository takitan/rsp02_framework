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
	OtherCommand = -3,
	OtherDestination = -2,
	OverFlowLength = -1,
	Accept = 0,
};

enum class ExecuteStatus
{
	NotInvoked = -4,
	InvalidValue = -3,
	Ignore = -2,
	Error = -1,
	Success = 0,
	Pending = 1,
	Executing = 2,
};

struct TCommandInfo
{
	using TStopWatch = rsp::rsp02::fw::time::TStopWatch;
	long AcceptCount;
	long ExecuteCount;
	TStopWatch time;
	bool isInvoked;
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
};

}
}
}
}

