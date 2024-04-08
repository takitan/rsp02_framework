#include "processes/ProcessRoot.hpp"
#include "ProcessRoot.hpp"
#include "command/CommandRoot.hpp"
#include "MainState/MainFSM.hpp"
#include "debug_command/DBGCommandRoot.hpp"
#include "states/StateRoot.hpp"

TProcessRoot ProcessRoot;

TProcessRoot::TProcessRoot():
	tlv(10),
	datalink_up(&tlv),
	datalink_down(&tlv),
	DSTDispatcher( "DstDispatcher",
		[](TDSTDispatcher::PRD_T* prd)
		{
			using idx_t = TDSTDispatcher::INF_T::first_type;
			idx_t index = prd->Destination();
			const char* name = DestinationString( index);
			return std::make_pair(index,name);
		}),
	PRDispatcher( "PrcDispatcher",
		[](TPRDispatcher::PRD_T* prd)
		{
			using idx_t = TPRDispatcher::INF_T::first_type;
			idx_t index = prd->sender_id;
			static char str[8];
			sprintf( str, "%d", index);
			return std::make_pair(index,str);
		}),
	SystemManager( 1000)
{
}

void TProcessRoot::Initialize()
{
	/*
	data flow
	 datalink_up -> Dispatcher -> (Mission Route) -> UpConverter -> kernel -> DnConverter -> datalink_down
                               -> (Attitude Route) -> UnDefined
	*/
	SystemManager.RegisterProcess( &datalink_up);
	SystemManager.RegisterProcess( &DSTDispatcher);
	SystemManager.RegisterProcess( &UpConverter);
	SystemManager.RegisterProcess( &CommandRoot.kernel);
	SystemManager.RegisterProcess( &DnConverter);
	SystemManager.RegisterProcess( &PRDispatcher);
	SystemManager.RegisterProcess( &datalink_down);
	datalink_up.SetConsumer( &DSTDispatcher);
	UpConverter.SetConsumer( &CommandRoot.kernel);
	CommandRoot.kernel.SetConsumer( &DnConverter);
	DnConverter.SetConsumer( &PRDispatcher);
	SystemManager.RegisterProcess( &StateRoot.MainFSM.StateMachine);
	//SystemManager.RegisterProcess( &DebugCommand.)
	DSTDispatcher.RegisterRoute( EDestination::Mission, &ProcessRoot.UpConverter);
}
