#include <cstdio>
#include "MissionFSM.hpp"
#include "MissionState/StateIdle.hpp"
#include "MissionState/State1.hpp"
#include "MissionState/State2.hpp"

namespace MissionFSM{

static State_Idle st_idle;
static State1 st1;
static State2 st2;

const static IState* state[] = { &st_idle, &st1, &st2};

TStateFactory StateFactory(state);
TStateMachine StateMachine(&StateFactory);

template<>
TStateFactory *TStateBase::Factory = &MissionFSM::StateFactory;

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

}