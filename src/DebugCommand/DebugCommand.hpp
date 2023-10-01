#pragma once
#include "tlvcmd.hpp"
#include "chloglv.hpp"
#include "trigger.hpp"
#include "system/debug/Shell.hpp"
#include "system/IProcess.hpp"
#include "system/debug/DebugPort.hpp"
#include "CommandKernel.hpp"

class TDebugCommand
{
	public:
		tlvcmd tlv_cmd;
		chloglv chloglv_cmd;
		trigger trigger_cmd;
		rsp::rsp02::system::Shell shell;
		rsp::rsp02::system::DebugPort DebugPort;

		TDebugCommand();

		void Initialize();
};

extern TDebugCommand DebugCommand;
