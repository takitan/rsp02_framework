#include "logger.hpp"

namespace rsp{
namespace rsp02{
namespace fw{
namespace logger{

const char* LogLevelString(ELogLevel ll)
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
