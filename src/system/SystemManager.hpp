#pragma once
#include <vector>
#include "system/Process.hpp"
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
class SystemManager
{
	using time_t = rsp::rsp02::time_t;
	using StopWatch = rsp::rsp02::fw::time::StopWatch;

	public:
		using SystemManagerCallback_t = void (*)(const SystemInfo &Info);
		SystemManagerCallback_t PeriodStartCallback;
		SystemManagerCallback_t PeriodCompletionCallback;

		SystemManager( time_t lp) :
			PeriodStartCallback(nullptr),
			PeriodCompletionCallback(nullptr),
			PeriodicTimer( lp),
			logger(fw::logger::Logger::GetLogger("SystemManager")){}

		SystemStatus Process()
		{
			//if( !PeriodicTimer.isPeriod()) return SystemStatus::Through;
			logger->Info("main loop");
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
			process.push_back( p);
			// 思いつく限りの簡単な方法でIDを振っているが、
			// Process削除できるようにしない限り、これでいいはず
			p->ProcessID = process.size();
		}
		const SystemStatus &GetInfo() const
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
