#include "InitialFSM.hpp"
//#include "GlobalDefine.hpp"

TInitialFSM::TInitialFSM()
{
}

void TInitialFSM::Initialize()
{
	StateMachine.StateFactory.RegisterState( &st_idle);
	StateMachine.StateFactory.RegisterState( &st1);
	StateMachine.StateFactory.RegisterState( &st2);
}
