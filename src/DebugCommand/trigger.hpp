#pragma once
#include <vector>
#include "fw/fsm/StateBase.hpp"
#include "system/debug/IShellCommand.hpp"
#include "MissionDefine.hpp"

class trigger : public rsp::rsp02::system::IShellCommand
{
	public:
		trigger();
		void RegisterState( rsp::rsp02::fw::fsm::IState<StateID>* st);
		int operator()( int argc, const char** argv, void* extobj);
	private:
		std::vector<rsp::rsp02::fw::fsm::IState<StateID>*> StateList;
};
