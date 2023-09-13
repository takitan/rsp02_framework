#include <vector>
#include "process/StateMachine.hpp"
#include "InitialFSM.hpp"
#include "MissionDefine.hpp"
#include "system/SystemManager.hpp"
#include "MissionDefine.hpp"
#include "fw/time/time.hpp"
#include "system/Process.hpp"
#include "system/debug/DebugPort.hpp"
#include "MissionCommand/MissionCommand.hpp"
#include "DebugCommand/DebugCommand.hpp"
#include "process/MissionProcess.hpp"
#include "MainState/MainFSM.hpp"
#include "LogSystem.hpp"

using namespace rsp::rsp02;

system::CommandKernel<MissionTLV,MissionTLV,MissionTLV> kernel;

void TransportTest()
{
	MissionProcess.Dispatcher.RegisterRoute( EDestination::Mission, &MissionProcess.UpConverter);

	MainFSM.StateMachine.ResetState();
//	m_fsm()->ForceTrans( MissionFSM::StateID::Idle);
//	i_fsm()->ForceTrans( InitialFSM::StateID::Idle);

	while(true)
	{
		MissionProcess.SystemManager.Process();
	}
}

int main(int argc, const char* argv[])
{
	// 初期化中にもログを吐くので、真っ先に初期化するべし
	LogSystem.Initialize();
	DebugCommand.Initialize();
	MissionCommand.Initialize();
	MainFSM.Initialize();
	MissionProcess.Initialize();
	DebugCommand.trigger_cmd.RegisterState( &MainFSM.st2);
	auto logger = rsp::rsp02::fw::logger::Logger::GetLogger( "ROOT");
	logger->Info("Let's Start!");

	logger->SetLogLevel( rsp::rsp02::fw::logger::ELogLevel::Trace);
	TransportTest();
	//logger()->SetLogLevel( ELogLevel::Fatal);
	for( int i=0;; i++)
	{
		//Logger->Trace( "hogehoge%d", i);
		//Logger->Debug( "hogehoge%d", i);
		//Logger->Info( "hogehoge%d", i);
		//Logger->Warn( "hogehoge%d", i);
		//Logger->Error( "hogehoge%d", i);
		//Logger->Fatal( "hogehoge%d", i);
		//Logger->SetLogger( i%2);
	}
	(void)argc;(void)argv;
//	m_fsm()->ForceTrans( MissionFSM::StateID::Idle);
//	i_fsm()->ForceTrans( InitialFSM::StateID::Idle);
	for(;;)
	{
//		m_fsm()->Process();
	}
}
