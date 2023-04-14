#pragma once
#include "fw/time/StopWatch.hpp"

class IExecutionStrategy
{
	public:
		virtual bool operator()(bool&) = 0;
		virtual void Reset() = 0;
};

class OnceAndForAll : public IExecutionStrategy
{
	public:
		bool operator()( bool &isInvoked)
		{
			isInvoked = false;
			return false;
		}
		void Reset(){}
};

class ContinueUntillScanout : public IExecutionStrategy
{
	private:
		int MaxCount;
		int NowCount;
	public:
		ContinueUntillScanout(int MaxCount=0):MaxCount(MaxCount),NowCount(0){}
		bool operator()(bool &isInvoked)
		{
			if( NowCount++ >= MaxCount)
			{
				isInvoked = false;
				return true;
			}
			else
			{
				return false;
			}
		}
		void Reset(){ NowCount = 0;}
};

class ContinueUntillTimeout : public IExecutionStrategy
{
	using TStopWatch = rsp::rsp02::fw::time::TStopWatch;
	using time_t = rsp::rsp02::time_t;
	private:
		TStopWatch sw;
		time_t Timeout;
	public:
		ContinueUntillTimeout(time_t Timeout):sw(TStopWatch()),Timeout(Timeout){}
		bool operator()(bool &isInvoked)
		{
			auto el = sw.GetElapsed();
			if( el > Timeout)
			{
				isInvoked = false;
				return true;
			}
			else
			{
				return false;
			}
		}
		void Reset(){ sw.Start();}
};
