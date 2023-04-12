#pragma once
#include <climits>

namespace rsp{
namespace rsp02{
namespace fw{
namespace time{

/** このtimeライブラリの時間の型*/
using time_t = long;

/** 時間取得関数の型*/
using TimeProvider_t = time_t (*)(void);

/** 時間取得関数*/
inline TimeProvider_t TimeProvider;

struct TimeKeeper
{
	public:
		time_t EnterTime;
		time_t ExitTime;
		time_t StayTime;
		void Enter(){ EnterTime = TimeProvider();}
		void Exit(){ ExitTime = TimeProvider(); StayTime = CalcStayTime();}
		TimeKeeper():EnterTime(0L),ExitTime(0L),StayTime(0L){}

	private:
		inline long CalcStayTime()
		{
			return ExitTime < EnterTime
				? ExitTime + (LONG_MAX - EnterTime) + 1
				: ExitTime - EnterTime;
		}

};

}
}
}
}
