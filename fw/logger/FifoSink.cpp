/**
 * @file FifoSink.cpp
 * @author Nobuyuki Takita (takitan1972@gmail.com)
 * @brief printfベースのログシステムの実装
 * @version 0.1
 * @date 2023-04-13
  */

#include <cstdio>
#include <cstdarg>
#include <cstdio>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <cerrno>
#include <exception>
#include "FifoSink.hpp"
#include "time/time.hpp"

namespace rsp{
namespace rsp02{
namespace fw{
namespace logger{

FifoSink::FifoSink(const char* name) : Name(name)
{
	mkfifo( Name, 0666);
	fd = fopen( Name, "O_WRONLY");
}

void FifoSink::Sink( time_t time, const char* name, const char* ll, const char* fmt, std::va_list arg)
{
	if( !fd)
	{
		#pragma message "Start reading from fifo, Before Start FifoSink!"
		#pragma message "c.f. cat FifoSink"
		printf("Start reading from fifo, Before Start FifoSink!\n");
		printf("c.f. cat FifoSink\n");
		fd = fopen( Name, "a");
	}
	if( !fd) return;

	fprintf( fd, "%08d,%s,%s,", time, name, ll);
	vfprintf( fd, fmt, arg);
	fprintf( fd, "\n");
	fflush(fd);
}

void FifoSink::operator()( time_t time, const char* name, const char* ll, const char* fmt, std::va_list arg)
{
	return Sink( time, name, ll, fmt, arg);
}
}
}
}
}
