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

void Test()
{
	MainFSM.StateMachine.ResetState();

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
	Test();
}
