#pragma once


class MissionLogger
{
	using PrintfLogger = rsp::rsp02::fw::logger::PrintfLogger;
	using FileLogger = rsp::rsp02::fw::logger::FileLogger;
	using ILogger = rsp::rsp02::fw::logger::ILogger;

	public:
		static bool Initialize();
		PrintfLogger* operator()() const;
};
