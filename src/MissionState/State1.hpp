#pragma once
#include <cstdio>
#include "fw/fsm/StateBase.hpp"
#include "fw/logger/Logger.hpp"
#include "MissionDefine.hpp"

class State1 : public rsp::rsp02::fw::fsm::StateBase<StateID>
{
	using StopWatch = rsp::rsp02::fw::time::StopWatch;

	public:
		State1():StateBase(StateID::State1, "State1"),logger(rsp::rsp02::fw::logger::Logger::GetLogger("State1")){}

	private:
		int i;
		StopWatch sw;
		rsp::rsp02::fw::logger::Logger::ILogger* logger;

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
				i++;
				break;
			case 1:
				logger->Trace("%s:InnerState1:%d\n", StateInfo.Name, sw.GetElapsed());
				if( sw.isElapsed( 1500)) i++;
				else break;
				// fallthrougf
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

