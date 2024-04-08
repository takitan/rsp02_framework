#pragma once
#include "middle/con_pro/Process.hpp"
#include "fw/fsm/StateMachine.hpp"
#include "fw/fsm/StateFactory.hpp"
#include "GlobalDefine.hpp"

template<typename T>
class TStateMachine : public rsp::rsp02::system::IndivisualProcess
{
	public:
		rsp::rsp02::fw::fsm::StateFactory<T> StateFactory;
		rsp::rsp02::fw::fsm::StateMachine<T> fsm;
		TStateMachine() : rsp::rsp02::system::IndivisualProcess("MissionState"), fsm(&StateFactory)
		{
			::rsp::rsp02::fw::fsm::StateBase<T>::Factory = &StateFactory;
		}
		
		void ResetState()
		{
			fsm.ForceTrans( StateID::Idle);
		}
	private:
		bool ConcreteProcess()
		{
			fsm.Process();
			return true;
		}
};
