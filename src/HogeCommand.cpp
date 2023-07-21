#include "HogeCommand.hpp"
#include "fw/logger/ILogger.hpp"

Hoge::Hoge():CommandImplBase( "Hoge", EDestination::Ground, EType::RequestPing){}

Hoge::ExecuteStatus Hoge::ConcreteExecute( const HogeCommand_t &cmd)
{
	auto len = std::min<int>(cmd.Length, HogeResponse_t::PayloadSize);
	HogeResponse_t cres( EDestination::Ground, EType::ReplyPing, len);
	memcpy( &cres.pValue, &cmd.pValue, len);
	SendRequest( cres);

	return ExecuteStatus::Success;
}
