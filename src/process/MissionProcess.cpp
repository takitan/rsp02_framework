#include "process/MissionProcess.hpp"
#include "MissionProcess.hpp"
#include "MissionCommand/MissionCommand.hpp"
#include "MainState/MainFSM.hpp"
#include "DebugCommand/DebugCommand.hpp"

TMissionProcess MissionProcess;

TMissionProcess::TMissionProcess():
	tlv(10),
	datalink_up(&tlv),
	datalink_down(&tlv),
	DSTDispatcher( "Destination Dispatcher",
		[](TDSTDispatcher::PRD_T* prd)
		{
			using idx_t = TDSTDispatcher::INF_T::first_type;
			idx_t index = prd->Destination();
			const char* name = DestinationString( index);
			return std::make_pair(index,name);
		}),
	PRDispatcher( "Process Dispatcher",
		[](TPRDispatcher::PRD_T* prd)
		{
			using idx_t = TPRDispatcher::INF_T::first_type;
			idx_t index = prd->sender_id;
			const char* name = "I can't know the Process Name";
			return std::make_pair(index,name);
		}),
	SystemManager( 1000)
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
	SystemManager.RegisterProcess( &DSTDispatcher);
	SystemManager.RegisterProcess( &UpConverter);
	SystemManager.RegisterProcess( &MissionCommand.kernel);
	SystemManager.RegisterProcess( &DnConverter);
	SystemManager.RegisterProcess( &datalink_down);
	datalink_up.SetConsumer( &DSTDispatcher);
	UpConverter.SetConsumer( &MissionCommand.kernel);
	MissionCommand.kernel.SetConsumer( &DnConverter);
	DnConverter.SetConsumer( &datalink_down);
	SystemManager.RegisterProcess( &MainFSM.StateMachine);
	//SystemManager.RegisterProcess( &DebugCommand.)
}
