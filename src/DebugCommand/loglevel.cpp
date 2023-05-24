#include <cstring>
#include <cstdlib>
#include <algorithm>
#include "IProcess.hpp"
#include "fw/logger/Logger.hpp"
#include "loglevel.hpp"
#include "ntshell/core/ntlibc.h"
using Logger = rsp::rsp02::fw::logger::Logger;
using ILogger = rsp::rsp02::fw::logger::ILogger;

namespace detail{

class loglevel_impl
{
	public:
		loglevel_impl(){}

		int operator()( int argc, const char** argv, void* extobj)
		{
			if( argc < 3)
			{
				printf( "Less arguments.\n");
				return -1;
			}
			ILogger* logger = Logger::GetLogger( argv[1], false);
			if( logger == nullptr)
			{
				printf( "Logger is not found.\n");
				return -2;
			}
			if( !logger->SetLogLevel( argv[2]))
			{

			};
			return 1;
		}
	private:
};
}

loglevel::loglevel()
{
	impl = new detail::loglevel_impl();
}
int loglevel::operator()( int argc, const char** argv, void* extobj)
{
	return impl->operator()( argc, argv, extobj);
}
