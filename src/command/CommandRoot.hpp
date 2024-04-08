#pragma once
#include "GlobalDefine.hpp"
#include "processes/CommandKernel.hpp"
#include "RequestPingCommand.hpp"
#include "RequestTakePhotoCommand.hpp"

class TCommandRoot
{
	public:
		TRequestPingCommand RequestPingCommand;
		TRequestTakePhotoCommand RequestTakePhotoCommand;
		rsp::rsp02::system::CommandKernel<TLVPacket,TLVPacket,TLVPacket> kernel;

		TCommandRoot();
		void Initialize();
};

extern TCommandRoot CommandRoot;
