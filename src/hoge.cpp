#include <vector>
#include "MissionState.hpp"
#include "InitialFSM.hpp"
#include "MissionLogger.hpp"
#include "MissionDefine.hpp"
#include "RequestPingCommand.hpp"
#include "RequestTakePhotoCommand.hpp"
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
#include "system/MessageDispatcher.hpp"
#include "system/MessageConverter.hpp"

using namespace rsp::rsp02;

static TMissionState MissionState;
static rsp::rsp02::fw::logger::FifoSink fifo_sink("FifoSink");
static TRequestPingCommand RequestPingCommand;
static TRequestTakePhotoCommand RequestTakePhotoCommand;
static TinyTLV tlv(10);
static system::TLVDatalinkUp<rsp02TLV> datalink_up( &tlv);
static system::TLVDatalinkDown<rsp02TLV> datalink_down( &tlv);
static system::CommandKernel<MissionTLV,MissionTLV,MissionTLV> kernel;
static system::SystemManager<MissionTLV> SysMan( 1000);
static system::Shell shell;
static system::DebugPort debugport(&shell);
static system::TMessageDispatcher<rsp02TLV,rsp02TLV> Dispatcher;
static system::TMessageConverter<rsp02TLV,MissionTLV> UpConverter;
static system::TMessageConverter<MissionTLV,rsp02TLV> DnConverter;
static tlvcmd tlv_cmd(&kernel);
static chloglv chloglv_cmd;

void TransportTest()
{
	/*
	data flow
	 datalink_up -> Dispatcher -> (Mission Route) -> UpConverter -> kernel -> DnConverter -> datalink_down
                               -> (Attitude Route) -> UnDefined
	*/
	shell.RegisterCommand( "tlvcmd", &tlv_cmd);
	shell.RegisterCommand( "chloglv", &chloglv_cmd);
	kernel.RegisterCommand( &RequestPingCommand);
	kernel.RegisterCommand( &RequestTakePhotoCommand);

	SysMan.RegisterProcess( &datalink_up);
	SysMan.RegisterProcess( &Dispatcher);
	SysMan.RegisterProcess( &UpConverter);
	SysMan.RegisterProcess( &kernel);
	SysMan.RegisterProcess( &DnConverter);
	SysMan.RegisterProcess( &datalink_down);
	SysMan.RegisterProcess( &MissionState);
	datalink_up.SetConsumer( &Dispatcher);
	Dispatcher.RegisterRoute( EDestination::Mission, &UpConverter);
	UpConverter.SetConsumer( &kernel);
	kernel.SetConsumer( &DnConverter);
	DnConverter.SetConsumer( &datalink_down);
	MissionState.ResetState();
//	m_fsm()->ForceTrans( MissionFSM::StateID::Idle);
//	i_fsm()->ForceTrans( InitialFSM::StateID::Idle);

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
//	m_fsm()->ForceTrans( MissionFSM::StateID::Idle);
//	i_fsm()->ForceTrans( InitialFSM::StateID::Idle);
	for(;;)
	{
//		m_fsm()->Process();
	}
}
