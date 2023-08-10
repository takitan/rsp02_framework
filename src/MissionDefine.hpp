#pragma once
#include "rsp02_mission.hpp"
#include "fw/command/CommandImplBase.hpp"
/*
#include "system/TLVDatalink.hpp"
#include "system/TLVTransport.hpp"
#include "system/CommandKernel.hpp"
#include "system/SystemManager.hpp"
*/
using ICommand = rsp::rsp02::fw::command::ICommand<MissionTLV>;
template<typename CMD_T, typename RES_T>
using CommandImplBase =rsp::rsp02::fw::command::CommandImplBase<CMD_T,RES_T,MissionTLV>;

enum class StateID : int
{
	Idle = 0,
	State1 = 1,
	State2 = 2,
};

/*

using CommandKernel = rsp::rsp02::system::CommandKernel<MissionTLV,MissionTLV,MissionTLV>;
//using TLVTransport = rsp::rsp02::system::TLVTransport<MissionTLV>;
using TLVDatalinkUp = rsp::rsp02::system::TLVDatalinkUp<MissionTLV>;
using TLVDatalinkDown = rsp::rsp02::system::TLVDatalinkDown<MissionTLV>;

using SystemManager = rsp::rsp02::system::SystemManager<MissionTLV>;
*/