/**
 * @file StopWatch.hpp
 * @author Nobuyuki Takita (takitan1972@gmail.com)
 * @brief 簡易的な経過時間測定手段を提供する
 * @version 0.1
 * @date 2023-04-13
 */
#pragma once
#include <climits>
#include <cstdint>
#include "time.hpp"
#include "TimeProvider.hpp"

namespace rsp{
namespace rsp02{
namespace fw{
namespace time{

/** @brief RSP02の統一の時刻取得手段 */
typedef time_t (*TimeProvider_t)( void);

/**
 * @class StopWatch
 * @brief 簡易的な経過時間測定クラス
 */
class StopWatch
{
	public:
		/** 勝手にスタートする*/
		StopWatch(){ Start();}
		StopWatch(time_t p) : Period(p){}
		virtual ~StopWatch(){}

		/** @brief スタート時刻の登録
		 * @return time_t 現在時刻
		 */
		time_t Start(){ return StartTime = TimeProvider();}

		/** @brief 計時時刻の登録
		 * @return time_t 現在時刻
		 */
		time_t Lap(){ return CurrentTime = TimeProvider();}

		/** @brief 経過時刻を登録しつつ経過時間を取得する
		 * @return time_t 経過時間
		*/
		time_t LapAndGetElapsed(){ Lap();return GetElapsed();}

		/**
		 * @brief 経過時間を取得する
		 *
		 * @return time_t 経過時間
		 */
		time_t GetElapsed( void)
		{
			auto et = (dtime_t)CurrentTime - (dtime_t)StartTime;
			return (time_t)et;
		}
		/**
		 * @brief 現在時刻を取得する
		 *
		 * @return time_t 現在時刻
		 */
		time_t GetCurrentTime( void){ return TimeProvider();}

		/**
		 * @brief 経過時間が指定時間を超えているかを判定する
		 *
		 * @param ElapsedTime 指定経過時間
		 * @return true 超えている
		 * @return false 超えていない
		 */
		bool isElapsed( time_t ElapsedTime = -1)
		{
			ElapsedTime = ElapsedTime==-1 ? Period : ElapsedTime;
			if( StartTime < 0) Start();
			auto et = LapAndGetElapsed();
			return et >= ElapsedTime;
		}

		bool isPeriod()
		{
			// 初回呼び出し時を開始時刻とする
			if( StartTime < 0)
			{
				Start();
				return true;
			}
			if( isElapsed( Period))
			{
				Start();
				return true;
			}
			else
			{
				return false;
			};
		}
	private:
		time_t Period = 0;
		time_t StartTime = -1L;
		time_t CurrentTime = -1L;
};

}
}
}
}
