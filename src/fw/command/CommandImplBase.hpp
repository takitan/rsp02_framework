/*
 * TlvCommandBase.h
 *
 *  Created on: 2021/10/26
 *      Author: takit
 */

#pragma once
#include <functional>
#include "system/rsp02.hpp"
#include "fw/command/ICommand.hpp"
#include "fw/logger/Logger.hpp"
#include "fw/time/TimeProvider.hpp"
#include "fw/time/StopWatch.hpp"
#include "fw/command/ExecutionStrategy.hpp"
#include "fw/logger/Logger.hpp"
#include "fw/util/assert.hpp"

namespace rsp{
namespace rsp02{
namespace fw{
namespace command{

template<typename TLV_T>
struct TCommandInfoEx : public rsp::rsp02::fw::command::TCommandInfo<TLV_T>
{
	using rsp::rsp02::fw::command::TCommandInfo<TLV_T>::TCommandInfo;
	void Enter(){this->time.Start();this->AcceptCount++;}
	void Exit(){this->time.Lap(); this->ExecuteCount++;}
};

namespace fw::logger{
	class ISink;
}
constexpr int TLV_SEND_BUF_SZ = 256;
constexpr uint16_t MaxValueLength = 256;

template< typename CMD_T, typename RES_T, typename TLV_T>
class CommandImplBase : public rsp::rsp02::fw::command::ICommand<TLV_T>
{
	using dst_t = typename TLV_T::dst_t;
	using type_t = typename TLV_T::type_t;
	using len_t = typename TLV_T::len_t;
	using ExecuteStatus = rsp::rsp02::fw::command::ExecuteStatus;
	using ParseStatus = rsp::rsp02::fw::command::ParseStatus;
	using TCommandInfo = rsp::rsp02::fw::command::TCommandInfo<TLV_T>;
	using TStopWatch = rsp::rsp02::fw::time::TStopWatch;
	using ILogger = rsp::rsp02::fw::logger::ILogger;
	using Logger = rsp::rsp02::fw::logger::Logger;

	public:
		using ParseCallback_t = void (*)(const CMD_T&);
		using ExecuteCallback_t = void (*)(const CMD_T&);
		ParseCallback_t OnParseSuccess = nullptr;
		ParseCallback_t OnParseFailure = nullptr;
		ExecuteCallback_t OnExecuteSuccess = nullptr;
		ExecuteCallback_t OnExecuteFailure = nullptr;

		/**
		 * @brief Construct a new CommandImplBase object
		 *
		 * @param name コマンド名称
		 * @param dst 宛先
		 * @param type コマンドタイプ
		 * @param ex 実行種別(nullptrだったらOnceForAll)
		 * @param logger ロガー(nullptrだったらNullLogger)
		 */
		CommandImplBase( const char* name, dst_t dst, type_t type, IExecutionStrategy* ex=nullptr) :
			Info(TCommandInfoEx<TLV_T>( name,dst,type))
		{
			this->ExecutionStrategy = ex==nullptr ? new OnceAndForAll : ex;
			this->logger = Logger::GetLogger( name);
		}

		virtual ~CommandImplBase(){}

		/** @brief コマンド解釈
		 * 基底クラスで宛先判別とコマンドtype判別を行い、
		 * 自身宛てコマンドだったら具象クラスの実行関数を呼ぶ
		 */
		ParseStatus Parse( const TLV_T &tlvcmd, TLV_T &tlvres)
		{
			auto st = Validate( tlvcmd);
			if( st == ParseStatus::Accept)
			{
				Info.Enter();
				Info.isInvoked = true;
				ExecutionStrategy->Reset();
				logger->Info( "%s(%d):Parse Accept", Info.Name, Info.Type);
				mOnParseSuccess();
			}
			else
			{
				logger->Trace( "%s(%d):Parse Deny", Info.Name, Info.Type);
				mOnParseFailure();
			}
			return st;
		}

		ExecuteStatus Execute()
		{
			ExecuteStatus st;
			if( !Info.isInvoked) return ExecuteStatus::NotInvoked;
			if( (*ExecutionStrategy)( Info.isInvoked)) st = ExecuteStatus::Ignore;

			st = ConcreteExecute( Command, Response);

			switch(st)
			{
				case ExecuteStatus::Executing:
					logger->Trace( "%s(%d):Executing", Info.Name, Info.Type);
				case ExecuteStatus::Error:
				case ExecuteStatus::InvalidValue:
					logger->Info( "%s(%d):Execute fail", Info.Name, Info.Type);
					mOnExecuteFailure();
					break;
				case ExecuteStatus::Success:
					logger->Info( "%s(%d):Execute Success", Info.Name, Info.Type);
					mOnExecuteSuccess();
				default:
					;
			}
			return st;
		}

		const TCommandInfo &GetInfo() const
		{
			return Info;
		}

		bool TestInvoked( bool clear=true)
		{
			auto r = Info.isInvoked;
			if( clear) Info.isInvoked = false;
			return r;
		}

		void SetSendRequestFunc( typename ICommand<TLV_T>::SendRequestFunc_t srf)
		{
			SendRequestFunc = srf;
		}

	private:
		ParseStatus Validate( const TLV_T &cmd)
		{

			if( cmd.destination != Info.Dest) return ParseStatus::OtherDestination;
			if( cmd.type != Info.Type) return ParseStatus::OtherCommand;
#if 0
			// 実際のところ、このレイヤでのエラーを返す機構がないから、変換コンストラクタでのバッファオーバーフロー対策をあてこんで
			// ここでは握りつぶしておく
			if( cmd.length >= sizeof( CMD_T::Payload)) return ParseStatus::OverFlowLength;
#endif
			Command = CMD_T(cmd);
			return  ConcreteParse( Command, Response);
		}

	protected:
		/** @brief ロガー*/
		ILogger* logger;
		void SendRequest()
		{
			if( !SendRequestFunc) return;
			logger->Info( "%s(%d):Send Response Request", Info.Name, Info.Type);
			SendRequestFunc( Response);
		}
	private:
		CMD_T Command;
		RES_T Response;
		typename ICommand<TLV_T>::SendRequestFunc_t SendRequestFunc;

		/** @brief コマンド情報*/
		TCommandInfoEx<TLV_T> Info;

		IExecutionStrategy* ExecutionStrategy;

		/* @brief 具象コマンド解釈関数*/
		virtual ParseStatus ConcreteParse( const CMD_T &cmd, const RES_T &res){ (void)cmd;(void)res;return ParseStatus::Accept;}

		/** @brief 具象コマンド実行関数 */
		virtual ExecuteStatus ConcreteExecute(const CMD_T &cmd, const RES_T &res){ (void)cmd;(void)res;return ExecuteStatus::Success;}

		inline void mOnParseSuccess()const
		{
			if( OnParseSuccess) OnParseSuccess( Command);
		}
		inline void mOnParseFailure()const
		{
			if( OnParseFailure) OnParseFailure( Command);
		}
		inline void mOnExecuteSuccess()const
		{
			if( OnParseSuccess) OnExecuteSuccess( Command);
		}
		inline void mOnExecuteFailure()const
		{
			if( OnParseFailure) OnExecuteFailure( Command);
		}
};

}
}
}
}

