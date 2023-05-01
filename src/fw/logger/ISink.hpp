#pragma once
#include <cstdarg>

namespace rsp{
namespace rsp02{
namespace fw{
namespace logger{

class ISink
{
	public:
		virtual void Sink( time_t time, const char *name, const char* ll, const char* fmt, ::va_list arg) = 0;
		virtual void operator()( time_t time, const char *name, const char* ll, const char* fmt, ::va_list arg) = 0;
};

}
}
}
}
