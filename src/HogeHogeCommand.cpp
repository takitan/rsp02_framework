#include "HogeHogeCommand.hpp"
#include "fw/logger/ILogger.hpp"

HogeHoge::HogeHoge():CommandImplBase( "HogeHoge", EDestination::Ground, EType::RequestPing){}

HogeHoge::ExecuteStatus HogeHoge::ConcreteExecute( const HogeHogeCommand_t &cmd)
{
	HogeHogeResponse_t cres = cmd;
	cres.Payload.hage *=2;
	cres.Payload.hige *=2;
	cres.Payload.huge *=2;
	cres.Payload.hege *=2;
	cres.Payload.hoge *=2;
	SendRequest( cres);

	return ExecuteStatus::Success;
}
