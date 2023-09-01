#include "DebugCommand.hpp"
#include "process/CommandKernel.hpp"

extern rsp::rsp02::system::CommandKernel<MissionTLV,MissionTLV,MissionTLV> kernel;

TDebugCommand DebugCommand(&kernel);

TDebugCommand::TDebugCommand(rsp::rsp02::system::CommandKernel<MissionTLV,MissionTLV,MissionTLV>* kernel):
	tlv_cmd(kernel),DebugPort(&shell)
{
}

void TDebugCommand::Initialize()
{
	shell.RegisterCommand( "tlvcmd", &tlv_cmd);
	shell.RegisterCommand( "chloglv", &chloglv_cmd);
	shell.RegisterCommand( "trigger", &trigger_cmd);
}
