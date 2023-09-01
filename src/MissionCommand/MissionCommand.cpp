#include "MissionCommand.hpp"

TMissionCommand MissionCommand;

TMissionCommand::TMissionCommand()
{
}

void TMissionCommand::Initialize()
{
	kernel.RegisterCommand( &MissionCommand.RequestPingCommand);
	kernel.RegisterCommand( &MissionCommand.RequestTakePhotoCommand);
}
