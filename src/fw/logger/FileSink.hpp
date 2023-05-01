/**
 * @file PrintfLogger.hpp
 * @author Nobuyuki Takita (takitan1972@gmail.com)
 * @brief printfベースのログシステムの定義
 * @version 0.1
 * @date 2023-04-13
 */
#pragma once
#include <cstdarg>
#include "ISink.hpp"
#include "time/time.hpp"

namespace rsp{
namespace rsp02{
namespace fw{
namespace logger{

struct FILE;
/** @class
 * @brief printfベースのログシステム
 *
 * ログは、printfにより標準出力に出力される
 */
class FileSink : public ISink{
	public:
		/**
		 * @brief Construct a new FileSink object
		 */
		FileSink(const char* fname, std::size_t maxlines);
		/**
		 * @brief Destroy the FileSink object
		 */
		virtual ~FileSink(){}
		/**
		 * @brief va_listバージョンのログ出力
		 *
		 * fmt以降の引数は、そのままgvprintfに引き渡される
		 * @param name ロガー名称
		 * @param ll ログレベル
		 * @param fmt フォーマット文字列
		 * @param arg va_list
		 */
		void Sink( time_t time, const char* name, const char* ll, const char* fmt, ::va_list arg);

		void operator()( time_t time, const char* name, const char* ll, const char* fmt, ::va_list arg);
	private:
		const char* FileName;
		std::size_t MaxLines;
		std::size_t LineCount( ::FILE* fp);
};

}
}
}
}
