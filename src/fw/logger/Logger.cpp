#include <cstdarg>
#include "Logger.hpp"
#include "ISink.hpp"
#include "fw/time/TimeProvider.hpp"

namespace rsp{
namespace rsp02{
namespace fw{
namespace logger{

Logger::Logger( ISink* s) : Sink(s), ThresholdLevel(ELogLevel::Debug){}
Logger::~Logger(){}


void Logger::Log( ELogLevel ll, const char* fmt, ::va_list arg)
{
	if( ll < ThresholdLevel) return;
	(*Sink)( GetTime(), Name, LogLevelString(ll), fmt, arg);
}

void Logger::Log( ELogLevel ll, const char* fmt, ...)
{
	std::va_list arg;
	va_start( arg, fmt);
	Log( ll, fmt, arg);
	va_end( arg);
}
void Logger::Trace(const char* fmt, ...)
{
	std::va_list arg;
	va_start( arg, fmt);
	Log( ELogLevel::Trace, fmt, arg);
	va_end( arg);
}

void Logger::Debug(const char* fmt, ...)
{
	std::va_list arg;
	va_start( arg, fmt);
	Log( ELogLevel::Debug, fmt, arg);
	va_end( arg);
}

void Logger::Info(const char* fmt, ...)
{
	std::va_list arg;
	va_start( arg, fmt);
	Log( ELogLevel::Trace, fmt, arg);
	va_end( arg);
}
void Logger::Warn(const char* fmt, ...)
{
	std::va_list arg;
	va_start( arg, fmt);
	Log( ELogLevel::Warn, fmt, arg);
	va_end( arg);
}
void Logger::Error(const char* fmt, ...)
{
	std::va_list arg;
	va_start( arg, fmt);
	Log( ELogLevel::Error, fmt, arg);
	va_end( arg);
}
void Logger::Fatal(const char* fmt, ...)
{
	std::va_list arg;
	va_start( arg, fmt);
	Log( ELogLevel::Fatal, fmt, arg);
	va_end( arg);
}

time_t Logger::GetTime()
{
	return fw::time::TimeProvider();
}

const char* Logger::LogLevelString(ELogLevel ll)
{
	switch( ll)
	{
		case ELogLevel::Trace: return "Trace";
		case ELogLevel::Debug: return "Debug";
		case ELogLevel::Info: return "Info";
		case ELogLevel::Warn: return "Warn";
		case ELogLevel::Error: return "Error";
		case ELogLevel::Fatal: return "Fatal";
		case ELogLevel::None: return "None";
		default: return "";
	}

}

}
}
}
}
