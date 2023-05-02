#include "MissionLogger.hpp"
#include "fw/logger/Logger.hpp"
#include "fw/logger/PrintfSink.hpp"

using ILogger = rsp::rsp02::fw::logger::ILogger;
using Logger = rsp::rsp02::fw::logger::Logger;
using PrintfSink = rsp::rsp02::fw::logger::PrintfSink;
/*
ILogger* MissionLogger::Logger()
{
	static rsp::rsp02::fw::logger::Logger logger();
	return &logger;
}
*/