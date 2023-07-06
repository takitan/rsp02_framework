#include <cstdarg>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include "Logger.hpp"
#include "ISink.hpp"
#include "fw/time/TimeProvider.hpp"
#include "fw/logger/NullSink.hpp"

namespace rsp{
namespace rsp02{
namespace fw{
namespace logger{

Logger::Logger( const char* name) : ThresholdLevel(ELogLevel::Debug)
{
	::strncpy( mName, name, sizeof(mName));
}

Logger::~Logger(){}
namespace{
NullSink DefaultSink;
}

ISink* Logger::Sink = &DefaultSink;

static bool hagehige( const char* s1, const char* s2)
{
	static volatile bool hoge;
	hoge = ::strcmp(s1,s2)==0;
	return hoge;
}

ILogger* Logger::GetLogger( const char* name, bool generate_if_not_found)
{
	static std::vector<ILogger*> list;
	printf("Logger:GetLogger:cap=%lu,sz=%lu\n",list.capacity(),list.size());
	auto it = std::find_if(
		std::begin(list),
		std::end(list),
		[name](ILogger* l)
		{
			//return ::strcmp(l->Name(), name)==0;
			bool hige = hagehige(l->Name(),name);
			return hige;
		});
	if( it!=std::end(list))
	{
		printf("Logger:%s already exists\n", name);
		return (*it);
	}
	if( generate_if_not_found)
	{
		auto l = new Logger( name);
		list.push_back(l);
		printf( "Logger:%s is created, %d Logger exists\n",l->Name(),list.size());
		return l;
	}
	else
	{
		return nullptr;
	}
}

void Logger::Log( ELogLevel ll, const char* fmt, ::va_list arg)
{
	if( ll > ThresholdLevel) return;
	(*Sink)( GetTime(), mName, LogLevelString(ll), fmt, arg);
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
	Log( ELogLevel::Info, fmt, arg);
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

void Logger::SetLogLevel( ELogLevel ll)
{
	ThresholdLevel = ll;
}

bool Logger::SetLogLevel( const char* ll)
{
	if( strcasecmp( ll, "Trace")==0){ ThresholdLevel = ELogLevel::Trace; return true;}
	if( strcasecmp( ll, "Debug")==0){ ThresholdLevel = ELogLevel::Debug; return true;}
	if( strcasecmp( ll, "Info")==0){ ThresholdLevel = ELogLevel::Info; return true;}
	if( strcasecmp( ll, "Warn")==0){ ThresholdLevel = ELogLevel::Warn; return true;}
	if( strcasecmp( ll, "Error")==0){ ThresholdLevel = ELogLevel::Error; return true;}
	if( strcasecmp( ll, "Fatal")==0){ ThresholdLevel = ELogLevel::Fatal; return true;}
	if( strcasecmp( ll, "None")==0){ ThresholdLevel = ELogLevel::None; return true;}
	return false;
}

const char* Logger::Name() const
{
	return mName;
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
