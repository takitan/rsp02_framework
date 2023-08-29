#pragma once
#include <cstdarg>
#include "time/time.hpp"
#include "ILogger.hpp"

namespace rsp{
namespace rsp02{
namespace fw{
namespace logger{

class ISink;

class Logger : public ILogger
{
	private:
		Logger( const char* name);

	public:
		/** @brief 実際にログを出力する機構のインターフェース */
		static ISink* Sink;

		/**
		 * @brief Get the Logger object
		 *
		 * @param name logger名称
		 * @return ILogger* ロガーオブジェクト
		 */
		static ILogger* GetLogger(const char* name, bool generate_if_not_found = true);

		virtual ~Logger();
		/**
		 * @brief 可変引数バージョンのログ出力
		 *
		 * fmt以降の引数は、そのままprintfに引き渡される
		 * @param ll ログレベル
		 * @param fmt  フォーマット文字列
		 * @param ... 可変長引数
		 */
		virtual void Log( ELogLevel ll, const char* fmt, ...);

		/**
		 * @brief va_listバージョンのログ出力
		 *
		 * fmt以降の引数は、そのままgvprintfに引き渡される
		 * @param ll ログレベル
		 * @param fmt フォーマット文字列
		 * @param arg va_list
		 */
		virtual void Log( ELogLevel ll, const char* fmt, ::va_list arg);

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
		void Debug(const char* fmt, ...);

		/**
		 * @brief Info出力
		 * @param fmt  フォーマット文字列
		 * @param ... 可変長引数
		 */
		void Info(const char* fmt, ...);

		/**
		 * @brief Warn出力
		 * @param fmt  フォーマット文字列
		 * @param ... 可変長引数
		 */
		void Warn(const char* fmt, ...);

		/**
		 * @brief Error出力
		 * @param fmt  フォーマット文字列
		 * @param ... 可変長引数
		 */
		void Error(const char* fmt, ...);

		/**
		 * @brief Fatal出力
		 * @param fmt  フォーマット文字列
		 * @param ... 可変長引数
		 */
		void Fatal(const char* fmt, ...);

		/**
		 * @brief ログとして出力される最低レベルを設定する
		 * @param lv ログレベル
		 */
		void SetLogLevel( ELogLevel lv);

		bool SetLogLevel( const char* lv);

		const char* Name() const;

		/**
		 * @brief ELogLevelを表す文字列を取得
		 *
		 * @param ll ログレベル
		 * @return const char* ログレベルを表す文字列
		 */
		static const char* LogLevelString(ELogLevel ll);

	protected:
		/** @brief logger名称 */
		char mName[32];
		/** @brief ログレベル*/
		ELogLevel ThresholdLevel;

		/**
		 * @brief 現在時刻を取得
		 *
		 * @return time_t 現在時刻
		 */
		time_t GetTime();
};

}
}
}
}
