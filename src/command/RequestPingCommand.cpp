#include "RequestPingCommand.hpp"
#include "fw/logger/ILogger.hpp"

TRequestPingCommand::TRequestPingCommand() :
	CommandImplBase( "RequestPing", EDestination::Mission, EType::REQ_PING),Response(buffer)
{}

TRequestPingCommand::ExecuteStatus TRequestPingCommand::ConcreteExecute( const RequestPingCommand_t& cmd)
{
	Response.Destination( EDestination::Ground);
	Response.Type( EType::REQ_PING);
	Response.Length( cmd.Length());
	auto len = std::min<int>(Response.Length(), RequestPingResponse_t::PayloadSize);
	memcpy( Response.pValue(), cmd.pValue(), len);
	SendRequest( Response);
	return ExecuteStatus::Success;
}
