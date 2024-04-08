#include "CommandRoot.hpp"

TCommandRoot CommandRoot;

TCommandRoot::TCommandRoot()
{
}

void TCommandRoot::Initialize()
{
	kernel.RegisterCommand( &CommandRoot.RequestPingCommand);
	kernel.RegisterCommand( &CommandRoot.RequestTakePhotoCommand);
}
