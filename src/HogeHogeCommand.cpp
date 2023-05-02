#include "HogeHogeCommand.hpp"
#include "fw/logger/ILogger.hpp"

HogeHoge::HogeHoge():CommandImplBase( "HogeHoge", EDestination::Ground, EType::RequestPing){}

HogeHoge::ExecuteStatus HogeHoge::ConcreteExecute( const HogeHogeCommand_t &cmd, HogeHogeResponse_t &res)
{
	(void)cmd;(void)res;
	return ExecuteStatus::Success;
}
