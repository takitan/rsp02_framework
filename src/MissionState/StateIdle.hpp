#pragma once
#include <cstdio>
#include "fw/fsm/StateBase.hpp"
#include "fw/logger/Logger.hpp"
#include "MissionDefine.hpp"

class State_Idle : public rsp::rsp02::fw::fsm::StateBase<StateID>
{
	using StopWatch = rsp::rsp02::fw::time::StopWatch;
	public:
		State_Idle():StateBase(StateID::Idle, "Idle"){}

	private:
		int i;
		StopWatch sw;

		void Entry()
		{
			i = 0;
			return;
		}

		IState* Execute( void)
		{
			IState* next = this;
			switch( i)
			{
			case 0:
				sw = StopWatch(1500);
				logger->Info("%s:Start\n", StateInfo.Name);
				logger->Info("%s:InnerState0\n", StateInfo.Name);
				i++;
				break;
			case 1:
				logger->Trace("%s:InnerState1:%d\n", StateInfo.Name, sw.GetElapsed());
				if( sw.isElapsed()) i++;
				else break;
				// fallthrough
			case 2:
				logger->Info("%s:InnerState2\n", StateInfo.Name);
				logger->Info("%s:Exit\n", StateInfo.Name);
				next = Factory->GetState(StateID::State2);
				i = 0;
				break;
			}
			return next;
		}

		void Exit()
		{
			return;
		}
};

