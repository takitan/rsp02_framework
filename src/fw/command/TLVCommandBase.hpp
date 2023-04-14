/*
 * TlvCommandBase.h
 *
 *  Created on: 2021/10/26
 *      Author: takit
 */

#pragma once

#include "rsp02.hpp"
#include "ICommand.hpp"
#include "fw/logger/logger.hpp"
#include "fw/logger/NullLogger.hpp"
#include "fw/time/TimeProvider.hpp"
#include "fw/time/StopWatch.hpp"
#include "fw/command/ExecutionStrategy.hpp"

namespace{
	
	struct TCommandInfoEx : public rsp::rsp02::fw::command::TCommandInfo
	{
		void Enter(){ time.Start(); AcceptCount++;}
		void Exit(){ time.Lap(); ExecuteCount++;}
	};

}

constexpr int TLV_SEND_BUF_SZ = 256;
constexpr uint16_t MaxValueLength = 256;

template< typename CMD_T, typename RES_T>
class TLVCommandBase : public rsp::rsp02::fw::command::ICommand<TLVmessage_t,TLVmessage_t>
{
	using ExecuteStatus = rsp::rsp02::fw::command::ExecuteStatus;
	using ParseStatus = rsp::rsp02::fw::command::ParseStatus;
	using TCommandInfo = rsp::rsp02::fw::command::TCommandInfo;
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
		 * @brief Construct a new TLVCommandBase object
		 * 
		 * @param name コマンド名称
		 * @param dst 宛先
		 * @param type コマンドタイプ
		 * @param ex 実行種別(nullptrだったらOnceForAll)
		 * @param logger ロガー(nullptrだったらNullLogger)
		 */
		TLVCommandBase( const char* name, EDestination dst, EType type, IExecutionStrategy* ex, ILogger* logger)
			: Info(TCommandInfoEx(name,dst,type))
		{
			this->ExecutionStrategy = ex==nullptr ? &DefaultStrategy : ex;
			this->Logger = logger==nullptr ? &DefaultLogger : logger;
		}
		/**
		 * @brief Construct a new TLVCommandBase object
		 * 
		 * Loggerはデフォルト(NullLogger)
		 * @param name コマンド名称
		 * @param dst 宛先
		 * @param type コマンドタイプ
		 * @param ex 実行種別(nullptrだったらOnceForAll)
		 */
		TLVCommandBase( const char* name, EDestination dst, EType type, IExecutionStrategy* ex)
			: TLVCommandBase( name, dst, type, ex, nullptr){}
		/**
		 * @brief Construct a new TLVCommandBase object
		 * 
		 * ExecutionStrategyはデフォルト(OnceForAll)
		 * Loggerはデフォルト(NullLogger)
		 * @param name コマンド名称
		 * @param dst 宛先
		 * @param type コマンドタイプ
		 */
		TLVCommandBase( const char* name, EDestination dst, EType type)
			: TLVCommandBase( name, dst, type, nullptr, nullptr){}

		virtual ~TLVCommandBase(){}

		/** @brief コマンド解釈
		 * 基底クラスで宛先判別とコマンドtype判別を行い、
		 * 自身宛てコマンドだったら具象クラスの実行関数を呼ぶ
		 */
		ParseStatus Parse( TLVmessage_t* tlvcmd, TLVmessage_t* tlvres)
		{
			Command = MissionTLV(*tlvcmd);
			Response = MissionTLV(*tlvres);
			auto st = GetStatus( tlvcmd, tlvres);
			if( st == ParseStatus::Accept)
			{
				Info.Enter();
				Info.isInvoked = true;
				ExecutionStrategy->Reset();
				logger->Info( "%s(%d):Parse Accept", Info.Name, Info.Type);
				mOnParseSuccess( tlvcmd);
			}
			else
			{
				mOnParseFailure( tlvcmd);
			}
			return st;
		}

		ExecuteStatus Execute()
		{
			ExecuteStatus st;
			if( !Info.isInvoked) return ExecuteStatus::NotInvoked;
			if( *ExecutionStrategy( Info.isInvoked)) st = ExecuteStatus::Ignore; 
			st = ConcreteExecute();

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
			return static_cast<TCommandInfo>( Info);
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
		MissionTLV TLVCommand;
		MissionTLV TLVResponse;
		CMD_T Command;
		RES_T Response;

		/** @brief コマンド情報*/
		TCommandInfoEx Info;
	
		ILogger* logger;
		TNullLogger DefaultLogger;
	
		IExecutionStrategy* ExecutionStrategy;
		OnceAndForAll DefaultStrategy;

		/* @brief 具象コマンド解釈関数*/
		virtual ParseStatus ConcreteParse( const CMD_T &cmd, RES_T &res){ return ParseStatus::Accept;}
		
		/** @brief 具象コマンド実行関数 */
		virtual ExecuteStatus ConcreteExecute(const CMD_T &cmd, RES_T &res){ return ExecuteStatus::Success;}

		inline void mOnParseSuccess()const{ if( OnParseSuccess) OnParseSuccess( Command);}
		inline void mOnParseFailure()const{ if( OnParseFailure) OnParseFailure( Command);}
		inline void mOnExecuteSuccess()const{ if( OnParseSuccess) OnExecuteSuccess( Command);}
		inline void mOnExecuteFailure()const{ if( OnParseFailure) OnExecuteFailure( Command);}

		void PrepareWorkspace( TLVmessage_t* cmd, TLVmessage_t* res)
		{
			Command.dest = static_cast<EDestination>(cmd->destination);
			Command.type = static_cast<EType>(cmd->type);
			Command.length = cmd->length;
			Response.destination = EDestination::Null;
			Response.type = EType::RequestNull;
			Response.length = 0;
		}

		ParseStatus GetStatus( TLVmessage_t* cmd, TLVmessage_t* res)
		{
			if( cmd->destination != Info.Dest) return ParseStatus::OtherDestination;
			if( cmd->type != Info.Type) return ParseStatus::OtherCommand;
			if( cmd->length >= CMD_T::MaxLength) return ParseStatus::OverFlowLength;

			return  ConcreteParse( Command, Response);
		}
};


