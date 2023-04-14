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
#include "fw/time/TimeProvider.hpp"
#include "fw/time/StopWatch.hpp"

constexpr int TLV_SEND_BUF_SZ = 256;
constexpr uint16_t MaxValueLength = 256;

namespace{
	
	struct TCommandInfoEx : public rsp::rsp02::fw::command::TCommandInfo
	{
		void Enter(){ time.Start(); AcceptCount++;}
		void Exit(){ time.Lap(); ExecuteCount++;}
	};

}

class IPendingStrategy
{
	public:
		virtual bool operator()(TCommandInfoEx& info) = 0;
		virtual void Reset() = 0;
};

class ScanoutPending : public IPendingStrategy
{
	private:
		int MaxCount;
		int NowCount;
	public:
		ScanoutPending(int MaxCount=0):MaxCount(MaxCount),NowCount(0){}
		bool operator()()
		{
			return NowCount++ >= MaxCount ? true : false;
		}
		void Reset(){ NowCount = 0;}
};

class TimeoutPending : public IPendingStrategy
{
	using TStopWatch = rsp::rsp02::fw::time::TStopWatch;
	using time_t = rsp::rsp02::time_t;
	private:
		TStopWatch sw;
		time_t Timeout;
	public:
		TimeoutPending(time_t Timeout):sw(TStopWatch()),Timeout(Timeout){}
		bool operator()()
		{
			auto el = sw.GetElapsed();
			return el > Timeout ? true : false;
		}
		void Reset(){ sw.Start();}
};

template< typename CMD_T, typename RES_T>
class TLVCommandBase : public rsp::rsp02::fw::command::ICommand<TLVmessage_t,TLVmessage_t>
{
	using ExecuteStatus = rsp::rsp02::fw::command::ExecuteStatus;
	using ParseStatus = rsp::rsp02::fw::command::ParseStatus;
	using TCommandInfo = rsp::rsp02::fw::command::TCommandInfo;
	using TStopWatch = rsp::rsp02::fw::time::TStopWatch;
	using ILogger = rsp::rsp02::fw::logger::ILogger;

	public:
		using ParseCallback_t = void (*)(const CMD_T&);
		using ExecuteCallback_t = void (*)(const CMD_T&);
		static ParseCallback_t OnParseSuccess = nullptr;
		static ParseCallback_t OnParseFailure = nullptr;
		static ExecuteCallback_t OnExecuteSuccess = nullptr;
		static ExecuteCallback_t OnExecuteFailure = nullptr;

		/** @brief 自身の宛先とコマンド番号を指定してTLVコマンド生成 */
		TLVCommandBase( const char* myName, uint8_t myType, IPendingStrategy* Pending = nullptr)
			: Info(TCommandInfoEx()), myName(myName), myType(myType), isInvoked(false), Pending(Pending)
		{
			this->Pending = Pending==nullptr ? DefaultPending(1) : Pending;
		}

		virtual ~TLVCommandBase(){}

		/** @brief コマンド解釈
		 * 基底クラスで宛先判別とコマンドtype判別を行い、
		 * 自身宛てコマンドだったら具象クラスの実行関数を呼ぶ
		 */
		ParseStatus Parse( TLVmessage_t* tlvcmd, TLVmessage_t* tlvres)
		{
			auto st = GetStatus( tlvcmd, tlvres);
			if( st == ParseStatus::Accept)
			{
				Info.Enter();
				Info.isInvoked = true;
				Pending->Reset();
				logger->Info( "%s(%d):Parse Accept", myName, myType);
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
			if( !isInvoked) return ExecuteStatus::NotInvoked;
			auto st = ConcreteExecute();
			if( st == ExecuteStatus::Pending)
			{
				if( *Pending()) st = ExecuteStatus::Ignore; 
			}
			switch(st)
			{
				case ExecuteStatus::Error:
					logger->Info( "%s(%d):Execute Error", myName, myType);
				case ExecuteStatus::InvalidValue:
					logger->Trace( "%s(%d):Execute Invalid Value", myName, myType);
				case ExecuteStatus::Ignore:
					logger->Trace( "%s(%d):Execute Ignore", myName, myType);
					mOnExecuteFailure();
				// fallthrough
					break;
				case ExecuteStatus::NotInvoked:
					logger->Trace( "%s(%d):Execute NotInvoked", myName, myType);
				case ExecuteStatus::Executing:
					logger->Trace( "%s(%d):Execute Executing", myName, myType);
				case ExecuteStatus::Success:
					logger->Info( "%s(%d):Execute Success", myName, myType);
					mOnExecuteSuccess();
			}
		}

		const TCommandInfo &GetInfo() const
		{
			return static_cast<TCommandInfo>( Info);
		}

	protected:
		/** @brief 自身のコマンドtype */
		EType myType;
		/** @brief 自身の表示名（デバッグ用） */
		const char* myName;

	private:
		/** @brief コマンドParserが受け付けたことをExecuterに伝える*/
		bool isInvoked;
		CMD_T Command;
		RES_T Response;

		ILogger* logger;
		IPendingStrategy* Pending;
		ScanoutPending DefaultPending;

		/** @brief コマンド情報*/
		TCommandInfoEx Info;

		/* @brief 具象コマンド解釈関数*/
		virtual ParseStatus ConcreteParse( const CMD_T &cmd, RES_T &res){ return ParseStatus::Accept;}
		
		/** @brief 具象コマンド実行関数 */
		virtual ExecuteStatus ConcreteExecute(){ return ExecuteStatus::Success;}

		inline void mOnParseSuccess()const{ if( OnParseSuccess) OnParseSuccess( Command);}
		inline void mOnParseFailure()const{ if( OnParseFailure) OnParseFailure( Command);}
		inline void mOnExecuteSuccess()const{ if( OnParseSuccess) OnExecuteSuccess( Command);}
		inline void mOnExecuteFailure()const{ if( OnParseFailure) OnExecuteFailure( Command);}

		void PrepareWorkspace( CMD_T* cmd, RES_T* res)
		{
			Command.destination = static_cast<EDestination>(cmd->destination);
			Command.type = static_cast<EType>(cmd->type);
			Command.length = cmd->length;
			Response.destination = EDestination::Null;
			Response.type = EType::Null;
			Response.length = 0;
		}

		ParseStatus GetStatus( CMD_T* cmd, RES_T* res)
		{
			if( cmd->type != myType) return ParseStatus::OtherCommand;
			if( cmd->length >= CMD_T::MaxLength) return ParseStatus::OverFlowLength;

			return  ConcreteParse( Command, Response);
		}
};


