#include "system/Process.hpp"
#include "fw/fsm/StateMachine.hpp"
#include "fw/fsm/StateFactory.hpp"

class MainState : rsp::rsp02::system::IndivisualProcess
{

	virtual bool ConcreteProcess()
	{
		return true;
	}
};