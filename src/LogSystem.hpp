#pragma once
#include "fw/logger/Logger.hpp"
#include "fw/logger/NullSink.hpp"
#include "fw/logger/FifoSink.hpp"

class TLogSystem
{
	public:
		TLogSystem();
		void Initialize();
	private:
		rsp::rsp02::fw::logger::FifoSink fifo_sink;
};

extern TLogSystem LogSystem;
