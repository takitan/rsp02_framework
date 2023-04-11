#include "MissionLogger.hpp"
#include "fw/logger/PrintfLogger.hpp"
#include "fw/logger/NullLogger.hpp"

using TPrintfLogger = rsp::rsp02::fw::logger::TPrintfLogger;
using TNullLogger = rsp::rsp02::fw::logger::TNullLogger;
using TLogSwitcher = rsp::rsp02::fw::logger::TLogSwitcher;
using ILogger = rsp::rsp02::fw::logger::ILogger;

static TPrintfLogger PrintfLogger;
static TNullLogger NullLogger;

static const ILogger* Loggers[] =
{
	&PrintfLogger,
	&NullLogger,
};
static TLogSwitcher LogSwitcher(Loggers);

TLogSwitcher* MissionLogger::operator()() const
{
	return &LogSwitcher;
}

bool MissionLogger::Initialize()
{
	return true;
}
