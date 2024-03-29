#include <cstring>
#include <cstdlib>
#include <algorithm>
#include "IProcess.hpp"
#include "fw/logger/Logger.hpp"
#include "chloglv.hpp"
#include "ntshell/core/ntlibc.h"
using Logger = rsp::rsp02::fw::logger::Logger;
using ILogger = rsp::rsp02::fw::logger::ILogger;

chloglv::chloglv(){}

int chloglv::operator()( int argc, const char** argv, void* extobj)
{
	(void)extobj;
	if( argc < 3)
	{
		printf( "Less arguments.\n");
		return -1;
	}
	ILogger* logger = Logger::GetLogger( argv[1], false);
	if( logger == nullptr)
	{
		printf( "Logger %s is not found.\n", argv[1]);
		return -2;
	}
	if( !logger->SetLogLevel( argv[2]))
	{
		printf("Log level %s is invalid\n", argv[2]);
		return -3;
	};
	printf("Set log level of %s to %s\n", argv[1], argv[2]);
	return 0;
}
