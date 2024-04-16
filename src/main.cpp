#include <vector>
#include "src/processes/StateMachine.hpp"
#include "GlobalDefine.hpp"
#include "middle/SystemManager.hpp"
#include "GlobalDefine.hpp"
#include "fw/time/time.hpp"
#include "middle/con_pro/Process.hpp"
#include "middle/debug/DebugPort.hpp"
#include "command/CommandRoot.hpp"
#include "debug_command/DBGCommandRoot.hpp"
#include "processes/ProcessRoot.hpp"
#include "MainState/MainFSM.hpp"
#include "LogSystem.hpp"
#include "states/StateRoot.hpp"

using namespace rsp::rsp02;

system::CommandKernel<TLVPacket,TLVPacket,TLVPacket> kernel;
auto logger = rsp::rsp02::fw::logger::Logger::GetLogger( "ROOT");

void Initialize()
{
	// 初期化中にもログを吐くので、真っ先に初期化するべし
	LogSystem.Initialize();
	DBGCommandRoot.Initialize();
	CommandRoot.Initialize();
	StateRoot.Initialize();
	ProcessRoot.Initialize();
	StateRoot.MainFSM.StateMachine.ResetState();
}

void MainLoop()
{
	while(true)
	{
		ProcessRoot.SystemManager.Process();
	}
}

int main(int argc, const char* argv[])
{
	logger->Info("Let's Start!");
	logger->SetLogLevel( rsp::rsp02::fw::logger::ELogLevel::Trace);
	MainLoop();
}
