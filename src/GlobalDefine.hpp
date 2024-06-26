#pragma once
#include "rsp02_mission.hpp"
#include "fw/command/CommandImplBase.hpp"

using ICommand = rsp::rsp02::fw::command::ICommand<TLVPacket>;
template<typename CMD_T, typename RES_T>
using CommandImplBase =rsp::rsp02::fw::command::CommandImplBase<CMD_T,RES_T,TLVPacket>;

