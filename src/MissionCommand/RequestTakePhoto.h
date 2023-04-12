/*
 * TakePhoto.h
 *
 *  Created on: 2021/10/27
 *      Author: takit
 */

#ifndef REQUESTTAKEPHOTO_H_
#define REQUESTTAKEPHOTO_H_

//#include "MissionStatus.hpp"
#include "fw/command/TlvCommandBase.h"

class RequestTakePhoto : public TlvCommandBase
{
public:
/** @brief RequestPingコマンドのValue定義 */
	typedef struct RequestTakePhotoCommand_t
	{
		int8_t TargetCamera;
		int8_t TakeQuantity;
	}RequestTakePhotoCommand;

	typedef struct RequestTakePhotpResponse_t
	{
		int8_t status;
	}RequestTakePhotoResponse;

	enum RequestTakePhotoStatus
	{
		Success = 0, Error = 1, InvalidValue = 2,
	};

	RequestTakePhoto( MissionStatus* status);
	RequestTakePhoto( MissionStatus* status, const char* myName, uint8_t myDestination, uint8_t myType);
	virtual ~RequestTakePhoto();
private:
	MissionStatus* status;
	void ConcreteExecute( TLVmessage_t*, TLVmessage_t*) override;
	void Process( RequestTakePhotoCommand* cmd, RequestTakePhotoResponse* res);
};

#endif /* REQUESTTAKEPHOTO_H_ */
