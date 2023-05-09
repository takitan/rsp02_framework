#include "HogeCommand.hpp"
#include "fw/logger/ILogger.hpp"

Hoge::Hoge():CommandImplBase( "Hoge", EDestination::Ground, EType::RequestPing){}

Hoge::ExecuteStatus Hoge::ConcreteExecute( const HogeCommand_t &cmd, HogeResponse_t &res)
{
	(void)cmd;(void)res;
	res.destination = EDestination::Ground;
	res.type = EType::ReplyPing;
	res.length = cmd.length;
	memcpy( &res.Payload, &cmd.Payload, cmd.length);
	SendRequest();

	return ExecuteStatus::Success;
}
