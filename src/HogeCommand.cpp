#include "HogeCommand.hpp"
#include "fw/logger/ILogger.hpp"

Hoge::Hoge():CommandImplBase( "Hoge", EDestination::Ground, EType::RequestPing){}

Hoge::ExecuteStatus Hoge::ConcreteExecute( const HogeCommand_t &cmd, HogeResponse_t &res)
{
	(void)cmd;(void)res;
	return ExecuteStatus::Success;
}
