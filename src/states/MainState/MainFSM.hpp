#pragma once
#include "processes/StateMachine.hpp"
#include "StateIdle.hpp"
#include "State1.hpp"
#include "State2.hpp"

class TMainFSM
{
	public:
		InitialStateIdle st_idle;
		InitialState1 st1;
		InitialState2 st2;
		TStateMachine<StateID> StateMachine;
		TMainFSM();
		void Initialize();
};
