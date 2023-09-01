#include "LogSystem.hpp"

TLogSystem LogSystem;

TLogSystem::TLogSystem() : fifo_sink("FifoSink")
{
}

void TLogSystem::Initialize()
{
	rsp::rsp02::fw::logger::Logger::Sink = &fifo_sink;
}