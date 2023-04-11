#include "MissionFSM.hpp"
#include "InitialFSM.hpp"
#include "MissionLogger.hpp"

static MissionLogger logger;
static MissionFSM::fsm m_fsm;
static InitialFSM::fsm i_fsm;

int main(int argc, const char* argv[])
{
	using ELogLevel = rsp::rsp02::fw::logger::ELogLevel;
	auto Logger = logger();
	logger()->SetLogLevel( ELogLevel::Trace);
	logger()->SetLogLevel( ELogLevel::Fatal);
	for( int i=0;; i++)
	{
		Logger->Trace( "hogehoge%d", i);
		Logger->Debug( "hogehoge%d", i);
		Logger->Info( "hogehoge%d", i);
		Logger->Warn( "hogehoge%d", i);
		Logger->Error( "hogehoge%d", i);
		Logger->Fatal( "hogehoge%d", i);
		Logger->SetLogger( i%2);
	}
	(void)argc;(void)argv;
	m_fsm()->ForceTrans( MissionFSM::StateID::Idle);
	i_fsm()->ForceTrans( InitialFSM::StateID::Idle);
	for(;;)
	{
		m_fsm()->Process();
	}
}