/**
 * @file PrintfLogger.hpp
 * @author Nobuyuki Takita (takitan1972@gmail.com)
 * @brief printfベースのログシステムの定義
 * @version 0.1
 * @date 2023-04-13 
 */
#pragma once
#include "logger.hpp"
#include "time/TimeProvider.hpp"

namespace rsp{
namespace rsp02{
namespace fw{
namespace logger{


/** @class
 * @brief printfベースのログシステム
 * 
 * ログは、printfにより標準出力に出力される
 */
class TPrintfLogger : public ILogger{
	public:
		/**
		 * @brief Construct a new TPrintfLogger object
		 */
		TPrintfLogger();
		/**
		 * @brief Destroy the TPrintfLogger object
		 */
		virtual ~TPrintfLogger(){}

		/**
		 * @brief 可変引数バージョンのログ出力
		 * 
		 * fmt以降の引数は、そのままprintfに引き渡される
		 * @param ll ログレベル
		 * @param fmt  フォーマット文字列
		 * @param ... 可変長引数
		 */
		void Log( ELogLevel ll, const char* fmt, ...);

		/**
		 * @brief va_listバージョンのログ出力
		 * 
		 * fmt以降の引数は、そのままgvprintfに引き渡される
		 * @param ll ログレベル
		 * @param fmt フォーマット文字列
		 * @param arg va_list
		 */
		void Log( ELogLevel ll, const char* fmt, va_list arg);

		/**
		 * @brief Trace出力
		 * @param fmt  フォーマット文字列
		 * @param ... 可変長引数
		 */
		void Trace( const char* fmt, ...);

		/**
		 * @brief Debug出力
		 * @param fmt  フォーマット文字列
		 * @param ... 可変長引数
		 */
		void Debug( const char* fmt, ...);

		/**
		 * @brief Info出力
		 * @param fmt  フォーマット文字列
		 * @param ... 可変長引数
		 */
		void Info( const char* fmt, ...);

		/**
		 * @brief Warn出力
		 * @param fmt  フォーマット文字列
		 * @param ... 可変長引数
		 */
		void Warn( const char* fmt, ...);

		/**
		 * @brief Error出力
		 * @param fmt  フォーマット文字列
		 * @param ... 可変長引数
		 */
		void Error( const char* fmt, ...);

		/**
		 * @brief Fatal出力
		 * @param fmt  フォーマット文字列
		 * @param ... 可変長引数
		 */
		void Fatal( const char* fmt, ...);

		/**
		 * @brief ログとして出力される最低レベルを設定する
		 * @param lv ログレベル
		 */
		void SetLogLevel( ELogLevel lv);

		/**
		 * @brief 時刻取得手段を設定する
		 * @param time_provider 時刻同期手段へのポインタ
		 */
		void SetTimeProvider( ILogger::TimeProvider_t time_provider);

	private:
		/** @brief ログとして出力される最低レベル*/
		ELogLevel LogLevel;
		/** @brief 時刻取得手段*/
		TimeProvider_t TimeProvider;
};

}
}
}
}
