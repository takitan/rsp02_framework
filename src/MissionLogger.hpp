#pragma once

namespace rsp::rsp02::fw::logger{
class ILogger;
}

class MissionLogger
{
	public:
		static rsp::rsp02::fw::logger::ILogger* Logger();
};
