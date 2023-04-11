#pragma once
#include <climits>
#include "TimeProvider.hpp"

namespace rsp{
namespace rsp02{
namespace fw{
namespace time{

typedef long (*TimeProvider_t)( void);

class TStopWatch
{
	public:
		TStopWatch( void){ StartTime = TimeProvider();}
		virtual ~TStopWatch(){}

		long GetElapsed( void)
		{
			CurrentTime = TimeProvider();
			auto et = CurrentTime - StartTime;
			et = et >=0 ? et : et + LONG_MAX;
			return et;
		}
		long GetCurrentTime( void){ return TimeProvider();}
		bool isElapsed( long ElapsedTime)
		{
			auto et = GetElapsed();
			return et >= ElapsedTime ? true : false;
		}
	private:
		long StartTime = -1L;
		long CurrentTime = -1L;
};

};
};
};
};
