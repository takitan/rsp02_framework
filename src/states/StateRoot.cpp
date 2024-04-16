#include "processes/StateMachine.hpp"
#include "StateRoot.hpp"
#include "middle/SystemManager.hpp"

TStateRoot StateRoot;

TStateRoot::TStateRoot()
{
	;
}

void TStateRoot::Initialize()
{
	MainFSM.Initialize();
	InitialFSM.Initialize();
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
