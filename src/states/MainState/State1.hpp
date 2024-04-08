#pragma once
#include <cstdio>
#include "fw/fsm/StateBase.hpp"
#include "fw/logger/Logger.hpp"
#include "GlobalDefine.hpp"
#include "fw/fsm/StateFactory.hpp"

class InitialState1 : public rsp::rsp02::fw::fsm::StateBase<StateID>
{
	using StopWatch = rsp::rsp02::fw::time::StopWatch;
	template<size_t N>
	using TinyEvent = rsp::rsp02::fw::fsm::TinyEvent<N>;

	public:
		InitialState1() :
			StateBase(StateID::State1, "State1"),
			trig(),
			logger(rsp::rsp02::fw::logger::Logger::GetLogger("State1")){}

	private:
		int i;
		StopWatch sw;
		TinyEvent<32> trig;
		rsp::rsp02::fw::logger::Logger::ILogger* logger;
		static constexpr size_t EventNumber = 0;
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
					if( trig.TestAndReset(EventNumber))
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

