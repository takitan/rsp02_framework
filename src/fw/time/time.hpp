#pragma once
#include <cstdint>

namespace rsp{
namespace rsp02{

/** timeフレームワークの時間の型*/
using time_t = int32_t;
/**
 * @brief timeフレームワークの倍精度時間の型
 * 
 * 経過時間計算時に内部的に使用することを想定するが、
 * それ以外への利用についての制限は特にない
 */
using dtime_t = int64_t;

}
}
