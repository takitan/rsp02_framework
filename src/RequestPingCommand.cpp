#include "RequestPingCommand.hpp"
#include "fw/logger/ILogger.hpp"

TRequestPingCommand::TRequestPingCommand() :
	CommandImplBase( "RequestPing", EDestination::Mission, EType::ReqPing),Response(buffer)
{}

TRequestPingCommand::ExecuteStatus TRequestPingCommand::ConcreteExecute( const RequestPingCommand_t& cmd)
{
	Response.Destination( EDestination::Ground);
	Response.Type( EType::RepPing);
	Response.Length( cmd.Length());
	auto len = std::min<int>(Response.Length(), RequestPingResponse_t::PayloadSize);
	memcpy( Response.pValue(), cmd.pValue(), len);
	SendRequest( Response);
	return ExecuteStatus::Success;
}
