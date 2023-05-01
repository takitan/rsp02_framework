/**
 * @file PrintfSink.cpp
 * @author Nobuyuki Takita (takitan1972@gmail.com)
 * @brief printfベースのログシステムの実装
 * @version 0.1
 * @date 2023-04-13
  */

#include <cstdio>
#include <cstdarg>
#include "PrintfSink.hpp"
#include "time/time.hpp"

namespace rsp{
namespace rsp02{
namespace fw{
namespace logger{

PrintfSink::PrintfSink(){}

void PrintfSink::Sink( time_t time, const char* name, const char* ll, const char* fmt, std::va_list arg)
{
	printf( "%d.8,%s,%s,", time, name, ll);
	vprintf( fmt, arg);
	printf( "\n");
}

}
}
}
}
