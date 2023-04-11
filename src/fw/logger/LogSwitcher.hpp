#pragma once
#include "logger.hpp"

namespace rsp{
namespace rsp02{
namespace fw{
namespace logger{

class TLogSwitcher : public ILogger
{
	public:
		template<int N>
		TLogSwitcher( const ILogger*(&loggers)[N]):Loggers(loggers),MaxLogger(N)
		{
			SetLogger( 0);
		}
		virtual ~TLogSwitcher(){};
		
		bool SetLogger( int no)
		{
			if( no < 0 || no >= MaxLogger) return false;
			CurLogger = const_cast<ILogger*>( Loggers[ no]);
			return true;
		}
		void Log( ELogLevel ll, const char* fmt, ...)
		{
			va_list arg;
			va_start( arg, fmt);
			CurLogger->Log( ll, fmt, arg);
			va_end( arg);
		}
		void Log( ELogLevel ll, const char* fmt, va_list arg)
		{
			CurLogger->Log( ll, fmt, arg);
		}
		void Trace(const char* fmt, ...)
		{
			va_list arg;
			va_start( arg, fmt);
			Log( ELogLevel::Trace, fmt, arg);
			va_end( arg);
		}
		void Debug(const char* fmt, ...)
		{
			va_list arg;
			va_start( arg, fmt);
			Log( ELogLevel::Debug, fmt, arg);
			va_end( arg);
		}
		void Info(const char* fmt, ...)
		{
			va_list arg;
			va_start( arg, fmt);
			Log( ELogLevel::Info, fmt, arg);
			va_end( arg);
		}
		void Warn(const char* fmt, ...)
		{
			va_list arg;
			va_start( arg, fmt);
			Log( ELogLevel::Warn, fmt, arg);
			va_end( arg);
		}
		void Error(const char* fmt, ...)
		{
			va_list arg;
			va_start( arg, fmt);
			Log( ELogLevel::Error, fmt, arg);
			va_end( arg);
		}
		void Fatal(const char* fmt, ...)
		{
			va_list arg;
			va_start( arg, fmt);
			Log( ELogLevel::Fatal, fmt, arg);
			va_end( arg);
		}
		void SetLogLevel( ELogLevel ll){ CurLogger->SetLogLevel( ll);}
		void SetTimeProvider( ILogger::TimeProvider_t tp){ CurLogger->SetTimeProvider( tp);}
	private:
		const ILogger** Loggers;
		const int MaxLogger;
		ILogger* CurLogger;
};

}
}
}
}
