#pragma once
#include <climits>
#include <cstdint>

namespace rsp{
namespace rsp02{

/** timeフレームワークの時間の型*/
typedef int32_t time_t;
/**
 * @brief timeフレームワークの倍精度時間の型
 * 
 * 経過時間計算時に内部的に使用することを想定するが、
 * それ以外への利用についての制限は特にない
 */
typedef int64_t dtime_t;

}
}

namespace rsp{
namespace rsp02{
namespace fw{
namespace time{


/** 時間取得関数の型*/
typedef time_t (*TimeProvider_t)(void);

/**
 * @brief 時刻取得手段へのポインタ
 * 
 * timeフレームワークが参照する現在時刻取得手段へのポインタ
 * デフォルトでは、@see DefaultTimeProvider が設定されているが、
 * フレームワーク利用者が上書きすれば、ユーザ定義の時刻取得関数を利用することができる
 * 
 */
extern TimeProvider_t TimeProvider;

}
}
}
}
