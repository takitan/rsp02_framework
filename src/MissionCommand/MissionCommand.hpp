#pragma once
#include "MissionDefine.hpp"
#include "process/CommandKernel.hpp"
#include "RequestPingCommand.hpp"
#include "RequestTakePhotoCommand.hpp"

class TMissionCommand
{
	public:
		TRequestPingCommand RequestPingCommand;
		TRequestTakePhotoCommand RequestTakePhotoCommand;
		rsp::rsp02::system::CommandKernel<MissionTLV,MissionTLV,MissionTLV> kernel;

		TMissionCommand();
		void Initialize();
};

extern TMissionCommand MissionCommand;
