#include <vector>
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
#include "system/debug/DebugPort.hpp"
#include "MissionDefine.hpp"
#include "fw/time/time.hpp"
#include "system/Process.hpp"
#include "fw/logger/Logger.hpp"
#include "fw/logger/PrintfSink.hpp"
#include "fw/logger/FifoSink.hpp"
#include "system/debug/Shell.hpp"
#include "DebugCommand/tlvcmd.hpp"
#include "DebugCommand/chloglv.hpp"

using namespace rsp::rsp02;

static MissionFSM::fsm m_fsm;
static InitialFSM::fsm i_fsm;
static rsp::rsp02::fw::logger::FifoSink fifo_sink("FifoSink");
static Hoge hoge;
static HogeHoge hogehoge;
static TinyTLV tlv(10);
static system::TLVDatalinkUp<MissionTLV> datalink_up( &tlv);
static system::TLVDatalinkDown<MissionTLV> datalink_down( &tlv);
static system::CommandKernel<MissionTLV,MissionTLV,MissionTLV> kernel;
static system::SystemManager<MissionTLV> SysMan( 1000);
static system::Shell shell;
static system::DebugPort debugport(&shell);
static tlvcmd tlv_cmd(&kernel);
static chloglv chloglv_cmd;

void TransportTest()
{
	shell.RegisterCommand( "tlvcmd", &tlv_cmd);
	shell.RegisterCommand( "chloglv", &chloglv_cmd);
	kernel.RegisterCommand( &hoge);
	kernel.RegisterCommand( &hogehoge);
	SysMan.RegisterProcess( &datalink_up);
	datalink_up.SetConsumer( &kernel);
	SysMan.RegisterProcess( &kernel);
	kernel.SetConsumer( &datalink_down);
	SysMan.RegisterProcess( &datalink_down);

	while(true)
	{
		SysMan.Process();
	}
}

int main(int argc, const char* argv[])
{
	using ELogLevel = rsp::rsp02::fw::logger::ELogLevel;
	auto logger = rsp::rsp02::fw::logger::Logger::GetLogger( "ROOT");
	rsp::rsp02::fw::logger::Logger::Sink = &fifo_sink;
	logger->Info("Let's Start!");

	TransportTest();
	logger->SetLogLevel( ELogLevel::Trace);
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
	m_fsm()->ForceTrans( MissionFSM::StateID::Idle);
	i_fsm()->ForceTrans( InitialFSM::StateID::Idle);
	for(;;)
	{
		m_fsm()->Process();
	}
}
