#pragma once
#include "system/Process.hpp"

class TMissionState : public rsp::rsp02::system::IndivisualProcess
{
	public:
		TMissionState() : rsp::rsp02::system::IndivisualProcess("MissionState"){}
		void ResetState();
	private:
		bool ConcreteProcess();
};

/*
#include <cstdio>

#include "fw/fsm/StateBase.hpp"
#include "fw/fsm/StateMachine.hpp"
#include "fw/fsm/StateFactory.hpp"
#include "fw/time/StopWatch.hpp"


using TStateMachine = rsp::rsp02::fw::fsm::StateMachine<StateID>;
using IState = rsp::rsp02::fw::fsm::IState<StateID>;
using TStateBase = rsp::rsp02::fw::fsm::StateBase<StateID>;
using TStateFactory = rsp::rsp02::fw::fsm::StateFactory<StateID>;

class MissionState
{
	public:
		static bool Initialize();
		bool Perform();
};

*/