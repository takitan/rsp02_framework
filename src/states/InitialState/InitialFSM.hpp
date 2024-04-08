#pragma once
#include "processes/StateMachine.hpp"
#include "InitialStateIdle.hpp"
#include "InitialState1.hpp"
#include "InitialState2.hpp"

class TInitialFSM
{
	public:
		InitialStateIdle st_idle;
		InitialState1 st1;
		InitialState2 st2;
		TStateMachine<StateID> StateMachine;
		TInitialFSM();
		void Initialize();
};

