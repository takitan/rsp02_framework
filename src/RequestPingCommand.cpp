#include "RequestPingCommand.hpp"
#include "fw/logger/ILogger.hpp"

TRequestPingCommand::TRequestPingCommand() :
	CommandImplBase( "RequestPing", EDestination::Ground, EType::RequestPing),Response(buffer)
{}

TRequestPingCommand::ExecuteStatus TRequestPingCommand::ConcreteExecute( const RequestPingCommand_t &cmd)
{
	auto len = std::min<int>(cmd.Length, RequestPingResponse_t::PayloadSize);
	Response = RequestPingResponse_t( buffer);
	memcpy( &Response.pValue, &cmd.pValue, len);
	SendRequest( Response);

	return ExecuteStatus::Success;
}
