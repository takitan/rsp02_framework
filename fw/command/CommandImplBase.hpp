/*
 * TlvCommandBase.h
 *
 *  Created on: 2021/10/26
 *      Author: takit
 */

#pragma once
#include <functional>
#include <cstdio>
#include "rsp02.hpp"
#include "fw/command/ICommand.hpp"
#include "fw/logger/Logger.hpp"
#include "fw/time/TimeProvider.hpp"
#include "fw/time/StopWatch.hpp"
#include "fw/command/ExecutionStrategy.hpp"
#include "fw/logger/Logger.hpp"
#include "fw/util/assert.hpp"
#include "fw/util/raii.hpp"

namespace rsp{
namespace rsp02{
namespace fw{
namespace command{

template<typename TLV_T>
struct CommandInfoEx : public rsp::rsp02::fw::command::CommandInfo<TLV_T>
{
	using rsp::rsp02::fw::command::CommandInfo<TLV_T>::CommandInfo;
	void Enter(){this->time.Start();this->AcceptCount++;}
	void Exit(){this->time.Lap(); this->ExecuteCount++;}
};

namespace fw::logger{
	class ISink;
}
constexpr int TLV_SEND_BUF_SZ = 256;
constexpr uint16_t MaxValueLength = 256;

#define RETURN_AFTER_CLEAR(x)	util::raii raii([this](){this->x=false;})

template< typename CMD_T, typename RES_T, typename TLV_T>
class CommandImplBase : public rsp::rsp02::fw::command::ICommand<TLV_T>
{
	using dst_t = typename TLV_T::dst_t;
	using typ_t = typename TLV_T::typ_t;
	using len_t = typename TLV_T::len_t;
	using ExecuteStatus = rsp::rsp02::fw::command::ExecuteStatus;
	using ParseStatus = rsp::rsp02::fw::command::ParseStatus;
	using TCommandInfo = rsp::rsp02::fw::command::CommandInfo<TLV_T>;
	using StopWatch = rsp::rsp02::fw::time::StopWatch;
	using ILogger = rsp::rsp02::fw::logger::ILogger;
	using Logger = rsp::rsp02::fw::logger::Logger;

	public:
		using ParseCallback_t = std::function<void(const CMD_T&)>;
		using ExecuteCallback_t = std::function<void(const RES_T&)>;
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
		CommandImplBase( const char* name, dst_t dst, typ_t type, IExecutionStrategy* ex=nullptr) :
			Info(CommandInfoEx<TLV_T>( name,dst,type))
		{
			this->ExecutionStrategy = ex==nullptr ? new OnceAndForAll : ex;
			this->logger = Logger::GetLogger( "Command");
		}

		virtual ~CommandImplBase(){}

		/** @brief コマンド解釈
		 * 基底クラスで宛先判別とコマンドtype判別を行い、
		 * 自身宛てコマンドだったら具象クラスの実行関数を呼ぶ
		 */
		bool Parse( const TLV_T &tlvcmd, TLV_T &tlvres)
		{
			(void)tlvres;
			auto st = VaridateArgs( tlvcmd);
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
				logger->Trace( "%s(%d):Parse Fail", Info.Name, Info.Type);
				mOnParseFailure();
			}
			if( isSendRequested)
			{
				tlvres = TLV_T(Response.Original);
			}
			RETURN_AFTER_CLEAR(isSendRequested);
			return isSendRequested;
		}

		bool Execute(const TLV_T& tlvcmd, TLV_T& tlvres)
		{
			ExecuteStatus st;
			if( !Info.isInvoked) return false;
			if( (*ExecutionStrategy)( Info.isInvoked)) st = ExecuteStatus::Ignore;
			Command = CMD_T(tlvcmd.Original);
			st = ConcreteExecute( Command);

			switch(st)
			{
				case ExecuteStatus::Executing:
					logger->Trace( "%s(%d):Executing", Info.Name, Info.Type);
					break;
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
			if( isSendRequested)
			{
				tlvres = TLV_T(Response.Original);
			}
			RETURN_AFTER_CLEAR(isSendRequested);
			return isSendRequested;
		}

		const TCommandInfo GetInfo() const
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
		ParseStatus VaridateArgs( const TLV_T &cmd)
		{

			if( cmd.Destination() != Info.Dest) return ParseStatus::OtherDestination;
			if( cmd.Type() != Info.Type) return ParseStatus::OtherCommand;
#if 0
			// 実際のところ、このレイヤでのエラーを返す機構がないから、変換コンストラクタでのバッファオーバーフロー対策をあてこんで
			// ここでは握りつぶしておく
			if( cmd.length >= sizeof( CMD_T::Payload)) return ParseStatus::OverFlowLength;
#endif
			Command = CMD_T(cmd.Original);
			return  ConcreteParse( Command);
		}

	protected:
		bool isSendRequested = false;
		/** @brief ロガー*/
		ILogger* logger;
		void SendRequest( const RES_T &res)
		{
			Response = res;
			isSendRequested = true;
			//if( !SendRequestFunc) return;
			logger->Info( "%s(%d):Send Request", Info.Name, Info.Type);
		}

	private:
		CMD_T Command;
		RES_T Response;
		typename ICommand<TLV_T>::SendRequestFunc_t SendRequestFunc;

		/** @brief コマンド情報*/
		CommandInfoEx<TLV_T> Info;

		IExecutionStrategy* ExecutionStrategy;

		/* @brief 具象コマンド解釈関数*/
		virtual ParseStatus ConcreteParse( const CMD_T &cmd){ (void)cmd;;return ParseStatus::Accept;}

		/** @brief 具象コマンド実行関数 */
		virtual ExecuteStatus ConcreteExecute(const CMD_T &cmd){ (void)cmd;return ExecuteStatus::Success;}

		inline void mOnParseSuccess()const
		{
			//if( OnParseSuccess) OnParseSuccess( Command);
		}
		inline void mOnParseFailure()const
		{
			//if( OnParseFailure) OnParseFailure( Command);
		}
		inline void mOnExecuteSuccess()const
		{
			//if( OnParseSuccess) OnExecuteSuccess( Response);
		}
		inline void mOnExecuteFailure()const
		{
			//if( OnParseFailure) OnExecuteFailure( Response);
		}
};

}
}
}
}

