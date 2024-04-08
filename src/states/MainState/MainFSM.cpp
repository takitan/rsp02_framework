#include "MainFSM.hpp"
#include "GlobalDefine.hpp"

TMainFSM::TMainFSM()
{
}

void TMainFSM::Initialize()
{
	StateMachine.StateFactory.RegisterState( &st_idle);
	StateMachine.StateFactory.RegisterState( &st1);
	StateMachine.StateFactory.RegisterState( &st2);
}
