#pragma once

#include "fw/logger/LogSwitcher.hpp"

class MissionLogger
{
	using TLogSwitcher = rsp::rsp02::fw::logger::TLogSwitcher;
	using ILogger = rsp::rsp02::fw::logger::ILogger;

	public:
		static bool Initialize();
		TLogSwitcher* operator()() const;
};
