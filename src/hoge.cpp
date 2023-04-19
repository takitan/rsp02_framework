#include "MissionFSM.hpp"
#include "InitialFSM.hpp"
#include "MissionLogger.hpp"
#include "MissionDefine.hpp"
#include "HogeCommand.hpp"
#include "HogeHogeCommand.hpp"
#include "system/SystemManager.hpp"
#include "system/TLVStub.hpp"
#include "system/TLVDatalink.hpp"
#include "system/CommandKernel.hpp"
#include "MissionDefine.hpp"

static MissionLogger logger;
static MissionFSM::fsm m_fsm;
static InitialFSM::fsm i_fsm;
static Hoge hoge;
static HogeHoge hogehoge;
static TinyTLV tlv(10);
static TLVDatalinkUp datalink_up( &tlv);
static TLVDatalinkDown datalink_down( &tlv);
static CommandKernel kernel;
static SystemManager SysMan;

void TransportTest()
{
	kernel.RegisterCommand( &hoge);
	kernel.RegisterCommand( &hogehoge);
	SysMan.RegisterProcess( &datalink_up);
	datalink_up.SetPostProcess( &kernel);
	SysMan.RegisterProcess( &kernel);
	kernel.SetPostProcess( &datalink_down);
	SysMan.RegisterProcess( &datalink_down);
	datalink_down.SetPostProcess( nullptr);
	while(true)
	{
		SysMan.Process();
	}
}

int main(int argc, const char* argv[])
{
	TransportTest();
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
