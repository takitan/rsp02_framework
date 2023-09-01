#pragma once
#include "process/StateMachine.hpp"
#include "StateIdle.hpp"
#include "State1.hpp"
#include "State2.hpp"

class TMainFSM
{
	public:
		State_Idle st_idle;
		State1 st1;
		State2 st2;
		TStateMachine<StateID> StateMachine;
		TMainFSM();
		void Initialize();
};

extern TMainFSM MainFSM;
