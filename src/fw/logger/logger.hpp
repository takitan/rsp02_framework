#pragma once
#include <cstdarg>
#include "time/TimeProvider.hpp"

namespace rsp{
namespace rsp02{
namespace fw{
namespace logger{

/**
 * @brief ログレベル
 * 
 * Traceが最低レベルで、Fatalが最高レベル
 * 
 * 出力するログのレベルを設定することにより、再コンパイルせずに、
 * ログ情報の制限を行う。
 */
enum class ELogLevel
{
	Trace,		//<! Trace情報などの膨大な情報を出力するレベル
	Debug,		//!< Debugに役立つ情報を出力するレベル
	Info,		//!< 運用中にわかると便利な情報を出力するレベル
	Warn,		//!< 運用中の警告を出力するレベル
	Error,		//!< 運用中のエラーを出力するレベル
	Fatal,		//!< 運用中の渋滞なエラーを出力するレベル
	None,		//!< すべてのログを出力しないことを表すレベル
};

class ILogger
{
	public:
		using TimeProvider_t = rsp::rsp02::fw::time::TimeProvider_t;
		virtual void Log( ELogLevel ll, const char* fmt, ...) = 0;
		virtual void Log( ELogLevel ll, const char* fmt, va_list arg) = 0;
		virtual void Trace(const char* fmt, ...) = 0;
		virtual void Debug(const char* fmt, ...) = 0;
		virtual void Info(const char* fmt, ...) = 0;
		virtual void Warn(const char* fmt, ...) = 0;
		virtual void Error(const char* fmt, ...) = 0;
		virtual void Fatal(const char* fmt, ...) = 0;
		virtual void SetLogLevel( ELogLevel lv) = 0;
		virtual void SetTimeProvider( TimeProvider_t tp) = 0;
};

/**
 * @brief ログレベルを文字列に変換する関数
 * @param ログレベル
 * @return const char* ログレベルを表す文字列 
 */
extern const char* LogLevelString(ELogLevel);

}
}
}
}
