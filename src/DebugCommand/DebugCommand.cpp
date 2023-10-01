#include "DebugCommand.hpp"

TDebugCommand DebugCommand;

TDebugCommand::TDebugCommand():DebugPort(&shell)
{
}

void TDebugCommand::Initialize()
{
	shell.RegisterCommand( "tlvcmd", &tlv_cmd);
	shell.RegisterCommand( "chloglv", &chloglv_cmd);
	shell.RegisterCommand( "trigger", &trigger_cmd);
}
