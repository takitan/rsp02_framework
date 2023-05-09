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

template< typename TLV_T>
struct TCommandInfo
{
	public:
	using dst_t = typename TLV_T::dst_t;
	using type_t = typename TLV_T::type_t;
	using len_t = typename TLV_T::len_t;
	using TStopWatch = rsp::rsp02::fw::time::TStopWatch;

	const char* Name;
	dst_t Dest;
	type_t Type;
	long AcceptCount;
	long ExecuteCount;
	TStopWatch time;
	bool isInvoked;
	TCommandInfo( const char* nam, const dst_t dst, const type_t typ)
		: Name(nam), Dest(dst), Type(typ), AcceptCount(0), ExecuteCount(0), time(), isInvoked(false){}
};

template< typename TLV_T>
class ICommand
{
public:
	using SendRequestFunc_t = std::function<void(const TLV_T&)>;
	virtual ~ICommand(){}

	virtual ParseStatus Parse( const TLV_T &cmd, TLV_T &res) = 0;
	/** @brief コマンド実行関数 */
	virtual ExecuteStatus Execute() = 0;
	/** @brief コマンドの現在ステータス参照*/
	virtual const TCommandInfo<TLV_T> &GetInfo() const = 0;
	/** @brief コマンド実行中かどうかを問い合わせ、必要に応じて実行中フラグをクリアする
	 * @param clear true 実行中フラグをクリアする(default)
	 * @param clear false 実行中フラグをクリアしない
	*/
	virtual bool TestInvoked(bool clear=true) = 0;

	virtual void SetSendRequestFunc( SendRequestFunc_t srf) = 0;
};

}
}
}
}

