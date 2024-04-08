/**
 * @file NullSink.hpp
 * @author Nobuyuki Takita (takitan1972@gmail.com)
 * @brief すべてのログを捨てるロガー
 * @version 0.1
 * @date 2023-04-13
 *
 * @copyright Copyright (c) 2023
 */
#pragma once
#include "ISink.hpp"
#include "time/time.hpp"

namespace rsp{
namespace rsp02{
namespace fw{
namespace logger{

class NullSink : public ISink
{
	public:
		NullSink(){};
		virtual ~NullSink(){}

		void Sink( time_t time, const char *name, const char* ll, const char* fmt, ::va_list arg)
		{(void)time;(void)name;(void)ll;(void)fmt;(void)arg;}
		void operator()( time_t time, const char *name, const char* ll, const char* fmt, ::va_list arg)
		{(void)time;(void)name;(void)ll;(void)fmt;(void)arg;}
};

}
}
}
}
