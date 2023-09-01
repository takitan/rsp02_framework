#pragma once
#include "rsp02_mission.hpp"
#include "fw/command/CommandImplBase.hpp"

using ICommand = rsp::rsp02::fw::command::ICommand<MissionTLV>;
template<typename CMD_T, typename RES_T>
using CommandImplBase =rsp::rsp02::fw::command::CommandImplBase<CMD_T,RES_T,MissionTLV>;

enum class StateID : int
{
	Idle = 0,
	State1 = 1,
	State2 = 2,
};
