/**
 * @file PrintfSink.hpp
 * @author Nobuyuki Takita (takitan1972@gmail.com)
 * @brief printfベースのログシステムの定義
 * @version 0.1
 * @date 2023-04-13
 */
#pragma once
#include "ISink.hpp"
#include "fw/time/time.hpp"

namespace rsp{
namespace rsp02{
namespace fw{
namespace logger{


struct va_list;
/** @class
 * @brief printfベースのログシステム
 *
 * ログは、printfにより標準出力に出力される
 */
class PrintfSink : public ISink{
	public:
		/**
		 * @brief Construct a new PrintfSink object
		 */
		PrintfSink();
		/**
		 * @brief Destroy the PrintfSink object
		 */
		virtual ~PrintfSink(){}
	private:
		/**
		 * @brief va_listバージョンのログ出力
		 *
		 * fmt以降の引数は、そのままgvprintfに引き渡される
		 * @param name ロガー名称
		 * @param ll ログレベル
		 * @param fmt フォーマット文字列
		 * @param arg va_list
		 */
		void Sink( time_t time, const char* name, const char*  ll, const char* fmt, ::va_list arg);
		void operator()( time_t time, const char* name, const char*  ll, const char* fmt, ::va_list arg);
};

}
}
}
}
