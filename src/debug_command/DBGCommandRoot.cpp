#include "DBGCommandRoot.hpp"
#include "states/StateRoot.hpp"

TDBGCommandRoot DBGCommandRoot;

TDBGCommandRoot::TDBGCommandRoot():DebugPort(&shell)
{
}

void TDBGCommandRoot::Initialize()
{
	shell.RegisterCommand( "tlvcmd", &tlv_cmd);
	shell.RegisterCommand( "chloglv", &chloglv_cmd);
	shell.RegisterCommand( "trigger", &trigger_cmd);
	trigger_cmd.RegisterState( &StateRoot.MainFSM.st2);
}
