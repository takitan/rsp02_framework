#include <cstdio>
#include "PrintfLogger.hpp"
#include "time/TimeProvider.hpp"

namespace rsp{
namespace rsp02{
namespace fw{
namespace logger{

using namespace rsp::rsp02::fw::time;

void TPrintfLogger::SetTimeProvider( TimeProvider_t tp)
{
	TimeProvider = tp;
} 

TPrintfLogger::TPrintfLogger():LogLevel(ELogLevel::Debug), TimeProvider(rsp::rsp02::fw::time::TimeProvider){}

void TPrintfLogger::Log( ELogLevel ll, const char* fmt, ...)
{
	va_list arg;
	va_start( arg, fmt);
	Log( ll, fmt, arg);
	va_end( arg);
}

void TPrintfLogger::Log( ELogLevel ll, const char* fmt, va_list arg)
{
	if( ll < LogLevel) return;
	printf( "%ld,%s,", TimeProvider(), LogLevelString(ll));
	vprintf( fmt, arg);
	printf( "\n");
}

void TPrintfLogger::Trace( const char* fmt, ...)
{
	va_list arg;
	va_start( arg, fmt);
	Log( ELogLevel::Trace, fmt, arg);
	va_end( arg);
}

void TPrintfLogger::Debug( const char* fmt, ...)
{
	va_list arg;
	va_start( arg, fmt);
	Log( ELogLevel::Debug, fmt, arg);
	va_end( arg);
}

void TPrintfLogger::Info( const char* fmt, ...)
{
	va_list arg;
	va_start( arg, fmt);
	Log( ELogLevel::Info, fmt, arg);
	va_end( arg);
}

void TPrintfLogger::Warn( const char* fmt, ...)
{
	va_list arg;
	va_start( arg, fmt);
	Log( ELogLevel::Warn, fmt, arg);
	va_end( arg);
}

void TPrintfLogger::Error( const char* fmt, ...)
{
	va_list arg;
	va_start( arg, fmt);
	Log( ELogLevel::Error, fmt, arg);
	va_end( arg);
}

void TPrintfLogger::Fatal( const char* fmt, ...)
{
	va_list arg;
	va_start( arg, fmt);
	Log( ELogLevel::Fatal, fmt, arg);
	va_end( arg);
}
void TPrintfLogger::SetLogLevel( ELogLevel lv)
{
	LogLevel = lv;
}

}
}
}
}
