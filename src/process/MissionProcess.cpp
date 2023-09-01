#include "process/MissionProcess.hpp"
#include "MissionProcess.hpp"
#include "MissionCommand/MissionCommand.hpp"
#include "MainState/MainFSM.hpp"
#include "DebugCommand/DebugCommand.hpp"

TMissionProcess MissionProcess;

TMissionProcess::TMissionProcess():
	tlv(10),datalink_up(&tlv),datalink_down(&tlv), SystemManager( 1000)
{
}

void TMissionProcess::Initialize()
{
	/*
	data flow
	 datalink_up -> Dispatcher -> (Mission Route) -> UpConverter -> kernel -> DnConverter -> datalink_down
                               -> (Attitude Route) -> UnDefined
	*/
	SystemManager.RegisterProcess( &datalink_up);
	SystemManager.RegisterProcess( &Dispatcher);
	SystemManager.RegisterProcess( &UpConverter);
	SystemManager.RegisterProcess( &MissionCommand.kernel);
	SystemManager.RegisterProcess( &DnConverter);
	SystemManager.RegisterProcess( &datalink_down);
	datalink_up.SetConsumer( &Dispatcher);
	UpConverter.SetConsumer( &MissionCommand.kernel);
	MissionCommand.kernel.SetConsumer( &DnConverter);
	DnConverter.SetConsumer( &datalink_down);
	SystemManager.RegisterProcess( &MainFSM.StateMachine);
	//SystemManager.RegisterProcess( &DebugCommand.)
}
