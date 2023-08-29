#pragma once
#include <cstdio>
#include "fw/fsm/StateBase.hpp"
#include "fw/logger/Logger.hpp"
#include "MissionDefine.hpp"

class State1 : public rsp::rsp02::fw::fsm::StateBase<StateID>
{
	using StopWatch = rsp::rsp02::fw::time::StopWatch;
	using TinyOneshotEvent = rsp::rsp02::fw::fsm::TinyOneshotEvent;

	public:
		State1() :
			StateBase(StateID::State1, "State1"),
			logger(rsp::rsp02::fw::logger::Logger::GetLogger("State1")),
			trig(false){}

		bool Trigger()
		{
			trig.Set();
		}

	private:
		int i;
		StopWatch sw;
		TinyOneshotEvent trig;
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
				if( sw.isElapsed( 1500))
				{
					logger->Info( "Timeout");
					i++;
				}
				else
				{
					if( trig.Test())
					{
						logger->Info( "Triggerd");
						i++;
					}
					break;
				}
				// fallthrougf
			case 2:
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

