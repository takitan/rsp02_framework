#pragma once
#include <cstdio>
#include "fw/fsm/StateBase.hpp"
#include "fw/logger/Logger.hpp"
#include "GlobalDefine.hpp"
#include "fw/fsm/StateFactory.hpp"

class InitialState2 : public rsp::rsp02::fw::fsm::StateBase<StateID>
{
	using StopWatch = rsp::rsp02::fw::time::StopWatch;
	public:
		InitialState2():
			StateBase(StateID::State2, "State2"),
			logger(rsp::rsp02::fw::logger::Logger::GetLogger("State2")){}

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
				logger->Info("%s:Start\n", StateInfo.Name);
				logger->Info("%s:InnerState0\n", StateInfo.Name);
				i++;
				break;
			case 1:
				logger->Trace("%s:InnerState1:%d\n", StateInfo.Name, sw.GetElapsed());
				if( sw.isElapsed( 1500)) i++;
				else break;
				logger->Info("Wait for the trigger of flag 0 or 1");
				// fallthrough
			case 2:
				if( TestEventAndClear( 0))
				{
					logger->Info( "flag 0 Triggered!");
					i = 0;
					break;
				}
				if( TestEventAndClear( 1)) 
				{
					logger->Info( "flag 1 Triggered!");
					next = Factory->GetState(StateID::State1);
					i = 0;
				}
				break;
			}
			return next;
		}

		void Exit()
		{
			return;
		}
};

