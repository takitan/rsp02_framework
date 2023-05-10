#include "HogeCommand.hpp"
#include "fw/logger/ILogger.hpp"

Hoge::Hoge():CommandImplBase( "Hoge", EDestination::Ground, EType::RequestPing){}

Hoge::ExecuteStatus Hoge::ConcreteExecute( const HogeCommand_t &cmd)
{
	HogeResponse_t cres( EDestination::Ground, EType::ReplyPing, cmd.length);
	memcpy( &cres.Payload, &cmd.Payload, cmd.length);
	SendRequest( cres);

	return ExecuteStatus::Success;
}
