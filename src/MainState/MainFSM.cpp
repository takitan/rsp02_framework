#include "MainFSM.hpp"
#include "MissionDefine.hpp"

TMainFSM MainFSM;

TMainFSM::TMainFSM()
{
}

void TMainFSM::Initialize()
{
	StateMachine.StateFactory.RegisterState( &st_idle);
	StateMachine.StateFactory.RegisterState( &st1);
	StateMachine.StateFactory.RegisterState( &st2);
}


namespace rsp::rsp02::fw::fsm{
template<>
void StateMachine<StateID>::OnTransfer()
{
}

template<>
void StateBase<StateID>::OnEntry( const StateInfo_t<StateID>& state)
{
	(void)state;
}

template<>
void StateBase<StateID>::OnExecute( const StateInfo_t<StateID>& state)
{
	(void)state;
}

template<>
void StateBase<StateID>::OnExit( const StateInfo_t<StateID>& state)
{
	(void)state;
}
}
