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

constexpr int TLV_SEND_BUF_SZ = 256;
constexpr uint16_t MaxValueLength = 256;

namespace{
	
	struct TCommandInfoEx : public rsp::rsp02::fw::command::TCommandInfo
	{
		void Enter(){ time.Enter(); AcceptCount++;}
		void Exit(){ time.Exit(); ExecuteCount++;}
	};

}

template< typename CMD_T, typename RES_T>
class TLVCommandBase : public rsp::rsp02::fw::command::ICommand<TLVmessage_t,TLVmessage_t>
{
	using ExecuteStatus = rsp::rsp02::fw::command::ExecuteStatus;
	using ParseStatus = rsp::rsp02::fw::command::ParseStatus;
	using TCommandInfo = rsp::rsp02::fw::command::TCommandInfo;
	using TimeKeeper = rsp::rsp02::fw::time::TimeKeeper;
	using ILogger = rsp::rsp02::fw::logger::ILogger;

	public:
		using ParseCallback_t = void (*)(const CMD_T&);
		using ExecuteCallback_t = void (*)(const CMD_T&);
		inline static ParseCallback_t OnParseSuccess = nullptr;
		inline static ParseCallback_t OnParseFailure = nullptr;
		inline static ExecuteCallback_t OnExecuteSuccess = nullptr;
		inline static ExecuteCallback_t OnExecuteFailure = nullptr;

		/** @brief 自身の宛先とコマンド番号を指定してTLVコマンド生成 */
		TLVCommandBase( const char* myName, uint8_t myDestination, uint8_t myType)
			: Info(TCommandInfoEx()), myName(myName), myDestination(myDestination), myType(myType), isInvoked(false)
		{}

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
		/** @brief 自身の宛先 */
		EDestination myDestination;
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

		ParseStatus GetStatus( CMD_T* cmd, RES_T* res)
		{
			if( cmd->destination != myDestination) return ParseStatus::OtherDestination;
			if( cmd->type != myType) return ParseStatus::OtherCommand;
			if( cmd->length >= CMD_T::MaxLength) return ParseStatus::OverFlowLength;
			Command.destination = static_cast<EDestination>(cmd->destination);
			Command.type = static_cast<EType>(cmd->type);
			Command.length = cmd->length;
			Response.destination = EDestination::Null;
			Response.type = EType::Null;
			Response.length = 0;
			return  ConcreteParse( Command, Response);
		}
};


