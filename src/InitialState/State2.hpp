#pragma once
#include <cstdio>
#include "InitialFSM.hpp"

namespace InitialFSM
{

class State2 : public TStateBase
{
	using TStopWatch = rsp::rsp02::fw::time::TStopWatch;
	public:
		State2():TStateBase(StateID::State2, "State2"){}

	private:
		int i;
		TStopWatch sw;

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
				sw = TStopWatch();
				printf("%s:Start\n", StateInfo.Name);
				printf("%s:InnerState0\n", StateInfo.Name);
				i++;
				break;
			case 1:
				printf("%s:InnerState1:%d\n", StateInfo.Name, sw.GetElapsed());
				if( sw.isElapsed( 100)) i++;
				else break;
				// fallthrough
			case 2:
				printf("%s:InnerState2\n", StateInfo.Name);
				printf("%s:Exit\n", StateInfo.Name);
				next = Factory->GetState(StateID::State1);
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