#include "RequestTakePhotoCommand.hpp"
#include "fw/logger/ILogger.hpp"

TRequestTakePhotoCommand::TRequestTakePhotoCommand():
	CommandImplBase( "RequestTakePhotoCommand", EDestination::Mission, EType::TAKE_PHOTO),Response(buffer){}

TRequestTakePhotoCommand::ExecuteStatus TRequestTakePhotoCommand::ConcreteExecute( const RequestTakePhotoCommand_t &cmd)
{
	(void)cmd;
	Response.Destination(EDestination::Ground);
	Response.Type(EType::TAKE_PHOTO);
	Response.Length(0);
	SendRequest( Response);

	return ExecuteStatus::Success;
}
