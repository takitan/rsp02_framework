/**
 * @file SystemManager.hpp
 * @author Nobuyuki Takita (takitan1972@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-04-18
 * 
 * メインループ
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once
#include <vector>
#include <algorithm>
#include "Process.hpp"
#include "fw/time/StopWatch.hpp"
#include "fw/logger/Logger.hpp"

namespace rsp{
namespace rsp02{
namespace system{

enum class SystemStatus : int
{
	Null,		//!< 無意味(未評価)
	Normal,		//!< 1scan動作正常終了
	Error,		//!< 1scan動作異状あり
	Through,	//!< scanタイミングではない
};

struct SystemInfo
{
	using time_t = rsp::rsp02::time_t;

	SystemStatus Status;
	time_t StartTime;
	time_t PreviousStartTime;
	time_t ActualPeriod;
	time_t ProcessTime;
	void* Option;
};

template<typename T>
class TSystemManager
{
	using time_t = rsp::rsp02::time_t;
	using StopWatch = rsp::rsp02::fw::time::StopWatch;

	public:
		using SystemManagerCallback_t = void (*)(const SystemInfo &Info);
		SystemManagerCallback_t PeriodStartCallback;
		SystemManagerCallback_t PeriodCompletionCallback;

		TSystemManager( time_t lp) :
			PeriodStartCallback(nullptr),
			PeriodCompletionCallback(nullptr),
			PeriodicTimer( lp),
			logger(fw::logger::Logger::GetLogger("SystemManager"))
			{
				logger->SetLogLevel( fw::logger::ELogLevel::Info);
			}

		SystemStatus Process()
		{
			//if( !PeriodicTimer.isPeriod()) return SystemStatus::Through;
			logger->Trace("main loop");
			Info.ActualPeriod = PeriodicTimer.LapAndGetElapsed();
			PeriodicTimer.Start();
			StopWatch sw;
			Info.Status = SystemStatus::Null;
			mPeriodStart();
			Info.PreviousStartTime = Info.StartTime;
			Info.StartTime = sw.Start();
			for( auto it=process.begin(); it!=process.end(); ++it)
			{
				(*it)->Perform();
			}
			Info.Status = SystemStatus::Normal;
			Info.ProcessTime = sw.LapAndGetElapsed();
			mPeriodCompletion();
			return Info.Status;
		}

		void RegisterProcess( IProcess* p)
		{
			if( p == nullptr) return;
			p->SetID( process.size());
			process.push_back( p);
			// 思いつく限りの簡単な方法でIDを振っているが、
			// Process削除できるようにしない限り、これでいいはず
		}

		IProcess* GetProcess( int process_id)
		{
			auto it = std::find_if(
				std::cbegin(process),
				std::cend(process),
				[process_id](IProcess* p){ return p->GetInfo().ProcessID == process_id;});
			if( it == std::cend(process)) return nullptr;
			else return *it;
		}

		const SystemInfo &GetInfo() const
		{
			return Info;
		}

	private:
		SystemInfo Info;
		StopWatch PeriodicTimer;
		std::vector<IProcess*> process;
		rsp::rsp02::fw::logger::ILogger* logger;

		void mPeriodStart()
		{
			if( PeriodStartCallback) PeriodStartCallback( Info);
		}

		void mPeriodCompletion()
		{
			if( PeriodCompletionCallback) PeriodCompletionCallback( Info);
		}
};

}
}
}
