/**
 * @file PrintfLogger.cpp
 * @author Nobuyuki Takita (takitan1972@gmail.com)
 * @brief printfベースのログシステムの実装
 * @version 0.1
 * @date 2023-04-13
  */

#include <cstdio>
#include <cstdarg>
#include "FileSink.hpp"
#include "time/time.hpp"

namespace rsp{
namespace rsp02{
namespace fw{
namespace logger{

FileSink::FileSink(const char* fname, std::size_t maxlines = 10) :
	FileName(fname), MaxLines(maxlines){}

void FileSink::Sink( time_t time, const char* name, const char* ll, const char* fmt, ::va_list arg)
{
	auto fp = fopen( FileName, "a+t");
	if( !fp) return;

	auto line = LineCount(fp);
	if( line > MaxLines)
	{

	}
	fprintf( fp, "%d.8,%s,%s,", time, name, ll);
	vfprintf( fp, fmt, arg);
	fprintf( fp, "\n");
	fflush(fp);
	fclose(fp);
}

void FileSink::operator()( time_t time, const char* name, const char* ll, const char* fmt, ::va_list arg)
{
	Sink( time, name, ll, fmt, arg);
}

std::size_t FileSink::LineCount( ::FILE* fp)
{
	std::size_t line = 0;
	int c;
	while((c=fgetc(fp)) != EOF)
	{
		if(c=='\n') line++;
	}
	return line;
}

}
}
}
}
