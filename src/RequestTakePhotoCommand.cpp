#include "RequestTakePhotoCommand.hpp"
#include "fw/logger/ILogger.hpp"

TRequestTakePhotoCommand::TRequestTakePhotoCommand():CommandImplBase( "RequestTakePhotoCommand", EDestination::Ground, EType::RequestTakePhoto){}

TRequestTakePhotoCommand::ExecuteStatus TRequestTakePhotoCommand::ConcreteExecute( const RequestTakePhotoCommand_t &cmd)
{
	SendRequest( Response);

	return ExecuteStatus::Success;
}
