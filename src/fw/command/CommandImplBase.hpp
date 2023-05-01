/*
 * TlvCommandBase.h
 *
 *  Created on: 2021/10/26
 *      Author: takit
 */

#pragma once

#include "system/rsp02.hpp"
#include "fw/command/ICommand.hpp"
#include "fw/logger/Logger.hpp"
#include "fw/time/TimeProvider.hpp"
#include "fw/time/StopWatch.hpp"
#include "fw/command/ExecutionStrategy.hpp"

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
		using TNullLogger = rsp::rsp02::fw::logger::TNullLogger;

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
		CommandImplBase( const char* name, dst_t dst, type_t type, IExecutionStrategy* ex=nullptr, ILogger* logger=nullptr) :
			Info(TCommandInfoEx<TLV_T>( name,dst,type))
		{
			this->ExecutionStrategy = ex==nullptr ? &DefaultStrategy : ex;
			this->Logger = logger==nullptr ? &DefaultLogger : logger;
		}
		virtual ~CommandImplBase(){}

		/** @brief コマンド解釈
		 * 基底クラスで宛先判別とコマンドtype判別を行い、
		 * 自身宛てコマンドだったら具象クラスの実行関数を呼ぶ
		 */
		ParseStatus Parse( TLV_T &tlvcmd)
		{
			auto st = Validate( tlvcmd);
			if( st == ParseStatus::Accept)
			{
				Info.Enter();
				Info.isInvoked = true;
				ExecutionStrategy->Reset();
				logger->Info( "%s(%d):Parse Accept", Info.Name, Info.Type);
				//mOnParseSuccess( tlvcmd);
			}
			else
			{
				//mOnParseFailure( tlvcmd);
			}
			return st;
		}

		ExecuteStatus Execute()
		{
			ExecuteStatus st;
			if( !Info.isInvoked) return ExecuteStatus::NotInvoked;
			if( (*ExecutionStrategy)( Info.isInvoked)) st = ExecuteStatus::Ignore;

			st = ConcreteExecute( TLVCommand);

			switch(st)
			{
				case ExecuteStatus::Error:
					logger->Info( "%s(%d):Execute Error", Info.Name, Info.Type);
				case ExecuteStatus::InvalidValue:
					logger->Trace( "%s(%d):Execute Invalid Value", Info.Name, Info.Type);
				case ExecuteStatus::Ignore:
					logger->Trace( "%s(%d):Execute Ignore", Info.Name, Info.Type);
					mOnExecuteFailure();
				// fallthrough
					break;
				case ExecuteStatus::NotInvoked:
					logger->Trace( "%s(%d):Execute NotInvoked", Info.Name, Info.Type);
				case ExecuteStatus::Executing:
					logger->Trace( "%s(%d):Execute Executing", Info.Name, Info.Type);
				case ExecuteStatus::Success:
					logger->Info( "%s(%d):Execute Success", Info.Name, Info.Type);
					mOnExecuteSuccess();
			}
		}

		const TCommandInfo &GetInfo() const
		{
			return Info;
		}

		bool TestInvoked( bool clear=true)
		{
			auto r = Info.isInvoked;
			Info.isInvoked = r ? false : Info.isInvoked;
			return r;
		}

	protected:
		/** @brief ロガー*/
		ILogger* Logger;

	private:
		CMD_T TLVCommand;
		RES_T TLVResponse;

		/** @brief コマンド情報*/
		TCommandInfoEx<TLV_T> Info;

		ILogger* logger;
		TNullLogger DefaultLogger;

		IExecutionStrategy* ExecutionStrategy;
		OnceAndForAll DefaultStrategy;

		/* @brief 具象コマンド解釈関数*/
		virtual ParseStatus ConcreteParse( const CMD_T &cmd){ return ParseStatus::Accept;}

		/** @brief 具象コマンド実行関数 */
		virtual ExecuteStatus ConcreteExecute(const CMD_T &cmd){ return ExecuteStatus::Success;}

		inline void mOnParseSuccess()const{ if( OnParseSuccess) OnParseSuccess( TLVCommand);}
		inline void mOnParseFailure()const{ if( OnParseFailure) OnParseFailure( TLVCommand);}
		inline void mOnExecuteSuccess()const{ if( OnParseSuccess) OnExecuteSuccess( TLVCommand);}
		inline void mOnExecuteFailure()const{ if( OnParseFailure) OnExecuteFailure( TLVCommand);}

		ParseStatus Validate( const TLV_T &cmd)
		{
			if( cmd.destination != Info.Dest) return ParseStatus::OtherDestination;
			if( cmd.type != Info.Type) return ParseStatus::OtherCommand;
			if( cmd.length >= sizeof( CMD_T::Payload)) return ParseStatus::OverFlowLength;
			TLVCommand = CMD_T(cmd);
			return  ConcreteParse( TLVCommand);
		}
};

}
}
}
}

