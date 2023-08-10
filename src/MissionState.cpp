#include "MissionState.hpp"
#include "fw/fsm/StateBase.hpp"
#include "fw/fsm/StateMachine.hpp"
#include "MissionState/StateIdle.hpp"
#include "MissionState/State1.hpp"
#include "MissionState/State2.hpp"
#include "MissionDefine.hpp"

static State_Idle st_idle;
static State1 st1;
static State2 st2;

namespace{
	static rsp::rsp02::fw::fsm::StateFactory<StateID> sf;
	static rsp::rsp02::fw::fsm::StateMachine<StateID> fsm( &sf);
}

void TMissionState::ResetState()
{
	rsp::rsp02::fw::fsm::StateBase<StateID>::Factory = &sf;
	sf.RegisterState( &st_idle);
	sf.RegisterState( &st1);
	sf.RegisterState( &st2);
	fsm.ForceTrans( StateID::Idle);
}

bool TMissionState::ConcreteProcess()
{
	fsm.Process();
	return true;
}

namespace rsp::rsp02::fw::fsm{
template<>
void StateMachine<StateID>::OnTransfer()
{
}

template<>
void StateBase<StateID>::OnEntry( const StateInfo_t<StateID>& state)
{
}

template<>
void StateBase<StateID>::OnExecute( const StateInfo_t<StateID>& state)
{
}

template<>
void StateBase<StateID>::OnExit( const StateInfo_t<StateID>& state)
{
}

}
