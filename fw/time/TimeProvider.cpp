/**
 * @file TimeProvider.cpp
 * @author Nobuyuki Takita (takitan1972@gmail.com)
 * @brief オーバーライド可能な時刻取得手段とそのデフォルトを定義する
 * @version 0.1
 * @date 2023-04-13
 */
#include <ctime>
#include "TimeProvider.hpp"

namespace rsp{
namespace rsp02{
namespace fw{
namespace time{

/**
 * @brief デフォルトの時刻取得手段
 * 
 * 現時点では、非ターゲット環境での動作を優先しているため、いわゆるC標準関数で
 * 取得する手段を提供する。
 * (これは、変更される可能性が高い)
 * @return time_t 現在時刻
 */
time_t DefaultTimeProviderMilliSeconds( void)
{
	auto time = (dtime_t)clock();
	return (time_t)( time / (CLOCKS_PER_SEC/1000));
}

/** デフォルトの時刻提供手段を提供する */
TimeProvider_t TimeProvider = rsp::rsp02::fw::time::DefaultTimeProviderMilliSeconds;

}
}
}
}
