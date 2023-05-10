#pragma once
#include <cstdio>
#include "MissionFSM.hpp"

namespace MissionFSM
{

class State1 : public TStateBase
{
	using StopWatch = rsp::rsp02::fw::time::StopWatch;

	public:
		State1():TStateBase(StateID::State1, "State1"){}

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
				sw = StopWatch();
				i++;
				break;
			case 1:
				printf("%s:InnerState1:%d\n", StateInfo.Name, sw.GetElapsed());
				if( sw.isElapsed( 1000)) i++;
				else break;
				// fallthrougf
			case 2:
				printf("%s:InnerState2\n", StateInfo.Name);
				printf("%s:Exit\n", StateInfo.Name);
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

};