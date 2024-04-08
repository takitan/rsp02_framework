#pragma once
#include "tlvcmd.hpp"
#include "chloglv.hpp"
#include "trigger.hpp"
#include "middle/debug/Shell.hpp"
#include "middle/con_pro/IProcess.hpp"
#include "middle/debug/DebugPort.hpp"
//#include "CommandKernel.hpp"

class TDBGCommandRoot
{
	public:
		tlvcmd tlv_cmd;
		chloglv chloglv_cmd;
		trigger trigger_cmd;
		rsp::rsp02::system::Shell shell;
		rsp::rsp02::system::DebugPort DebugPort;

		TDBGCommandRoot();

		void Initialize();
};

extern TDBGCommandRoot DBGCommandRoot;
