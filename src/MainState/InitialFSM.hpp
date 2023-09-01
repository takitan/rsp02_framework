/*
#pragma once

#include <cstdio>

#include "fw/fsm/StateBase.hpp"
#include "fw/fsm/StateMachine.hpp"
#include "fw/fsm/StateFactory.hpp"
#include "fw/time/StopWatch.hpp"

namespace InitialFSM{

enum class StateID : int
{
	Idle = 0,
	State1 = 1,
	State2 = 2,
};

using TStateMachine = rsp::rsp02::fw::fsm::StateMachine<StateID>;
using IState = rsp::rsp02::fw::fsm::IState<StateID>;
using TStateBase = rsp::rsp02::fw::fsm::StateBase<StateID>;
using TStateFactory = rsp::rsp02::fw::fsm::StateFactory<StateID>;

class fsm
{
	public:
		static bool Initialize( void);
		TStateMachine* operator()() const;
};

}
*/