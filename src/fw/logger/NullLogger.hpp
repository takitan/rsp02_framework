#pragma once
#include "logger.hpp"
#include "time/TimeProvider.hpp"

namespace rsp{
namespace rsp02{
namespace fw{
namespace logger{

class TNullLogger : public ILogger
{
	public:
		TNullLogger(){};
		virtual ~TNullLogger(){}

		void Log( ELogLevel ll, const char* fmt, ...){(void)ll;(void)fmt;}
		void Log( ELogLevel ll, const char* fmt, va_list arg){(void)ll;(void)fmt;(void)arg;}
		void Trace( const char* fmt, ...){(void)fmt;}
		void Debug( const char* fmt, ...){(void)fmt;}
		void Info( const char* fmt, ...){(void)fmt;}
		void Warn( const char* fmt, ...){(void)fmt;}
		void Error( const char* fmt, ...){(void)fmt;}
		void Fatal( const char* fmt, ...){(void)fmt;}
		void SetLogLevel( ELogLevel ll){(void)ll;}
		void SetTimeProvider( ILogger::TimeProvider_t time_provider){(void)time_provider;}

	private:
		ELogLevel LogLevel;
		TimeProvider_t TimeProvider;
};

}
}
}
}
