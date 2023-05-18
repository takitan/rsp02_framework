#pragma once
#include "rsp02.hpp"
#include "fw/command/CommandImplBase.hpp"
#include "system/TLVDatalink.hpp"
#include "system/TLVTransport.hpp"
#include "system/CommandKernel.hpp"
#include "system/SystemManager.hpp"

using MissionTLV = TLVpacket_t<EDestination,EType>;
using ICommand = rsp::rsp02::fw::command::ICommand<MissionTLV>;

template<typename CMD_T, typename RES_T>
using CommandImplBase =rsp::rsp02::fw::command::CommandImplBase<CMD_T,RES_T,MissionTLV>;

using CommandKernel = rsp::rsp02::system::CommandKernel<MissionTLV,MissionTLV,MissionTLV>;
//using TLVTransport = rsp::rsp02::system::TLVTransport<MissionTLV>;
using TLVDatalinkUp = rsp::rsp02::system::TLVDatalinkUp<MissionTLV>;
using TLVDatalinkDown = rsp::rsp02::system::TLVDatalinkDown<MissionTLV>;

using SystemManager = rsp::rsp02::system::SystemManager<MissionTLV>;
