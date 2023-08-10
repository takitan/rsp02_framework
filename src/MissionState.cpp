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
	//if( OnTransfer) OnTransfer( CurrentState, NextState);
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
/*
#include <cstdio>
#include "MissionFSM.hpp"
#include "MissionState/StateIdle.hpp"
#include "MissionState/State1.hpp"
#include "MissionState/State2.hpp"

static State_Idle st_idle;
static State1 st1;
static State2 st2;

const static IState* state[] = { &st_idle, &st1, &st2};

TStateFactory StateFactory(state);
TStateMachine StateMachine(&StateFactory);

TStateFactory *TStateBase::Factory = &StateFactory;

bool fsm::Initialize( void)
{
	return true;
}
TStateMachine* fsm::operator()() const
{
	return &StateMachine;
}

static void DefaultOnEntryCallback( IState* st)
{
	(void)st;
}

static void DefaultOnExecuteCallback( IState* st)
{
	(void)st;
}

static void DefaultOnExitCallback( IState* st)
{
	(void)st;
}

static void DefaultOnTransferCallback( IState* cur, IState* next)
{
	(void)cur;(void)next;
}

template<>
TStateBase::CallBack_t TStateBase::OnEntry = MissionFSM::DefaultOnEntryCallback;

template<>
TStateBase::CallBack_t TStateBase::OnExecute = MissionFSM::DefaultOnExecuteCallback;

template<>
TStateBase::CallBack_t TStateBase::OnExit = MissionFSM::DefaultOnExitCallback;

template<>
TStateMachine::Callback_t TStateMachine::OnTransfer = MissionFSM::DefaultOnTransferCallback;

*/
