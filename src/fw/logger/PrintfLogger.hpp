#pragma once
#include "logger.hpp"
#include "time/TimeProvider.hpp"

namespace rsp{
namespace rsp02{
namespace fw{
namespace logger{

class TPrintfLogger : public ILogger
{
	public:
		TPrintfLogger();
		virtual ~TPrintfLogger(){}

		void Log( ELogLevel ll, const char* fmt, ...);
		void Log( ELogLevel ll, const char* fmt, va_list arg);
		void Trace( const char* fmt, ...);
		void Debug( const char* fmt, ...);
		void Info( const char* fmt, ...);
		void Warn( const char* fmt, ...);
		void Error( const char* fmt, ...);
		void Fatal( const char* fmt, ...);
		void SetLogLevel( ELogLevel lv);
		void SetTimeProvider( ILogger::TimeProvider_t time_provider);

	private:
		ELogLevel LogLevel;
		TimeProvider_t TimeProvider;
};

}
}
}
}
