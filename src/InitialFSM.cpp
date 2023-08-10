/*
#include <cstdio>
#include "InitialFSM.hpp"
#include "InitialState/StateIdle.hpp"
#include "InitialState/State1.hpp"
#include "InitialState/State2.hpp"

namespace InitialFSM{

static State_Idle st_idle;
static State1 st1;
static State2 st2;

const static IState* state[] = { &st_idle, &st1, &st2};

TStateFactory StateFactory(state);
TStateMachine StateMachine(&StateFactory);

template<>
TStateFactory *TStateBase::Factory = &InitialFSM::StateFactory;

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
TStateBase::CallBack_t TStateBase::OnEntry = InitialFSM::DefaultOnEntryCallback;

template<>
TStateBase::CallBack_t TStateBase::OnExecute = InitialFSM::DefaultOnExecuteCallback;

template<>
TStateBase::CallBack_t TStateBase::OnExit = InitialFSM::DefaultOnExitCallback;

template<>
TStateMachine::Callback_t TStateMachine::OnTransfer = InitialFSM::DefaultOnTransferCallback;

}
*/