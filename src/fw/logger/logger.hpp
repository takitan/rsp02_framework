#pragma once
#include <cstdarg>
#include "time/TimeProvider.hpp"

namespace rsp{
namespace rsp02{
namespace fw{
namespace logger{

enum class ELogLevel
{
	Trace,
	Debug,
	Info,
	Warn,
	Error,
	Fatal,
	None,
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

extern const char* LogLevelString(ELogLevel);

}
}
}
}
