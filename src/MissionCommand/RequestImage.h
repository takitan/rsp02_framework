/*
 * TakePhoto.h
 *
 *  Created on: 2021/10/27
 *      Author: takit
 */

#pragma once

//#include "MissionStatus.hpp"
#include "fw/command/TlvCommandBase.h"

#define PAYLOAD_SIZE	116

class RequestImage : public TlvCommandBase
{
public:
/** @brief RequestPingコマンドのValue定義 */
	typedef struct RequestImageCommand_t
	{
		int8_t TargetCamera;
		int32_t ImageNumber;
		int16_t Segment;
	}RequestImageCommand;

	typedef struct RequestImageResponse_t
	{
		int8_t status;
		int8_t TargetCamera;
		int32_t ImageNumber;
		int16_t Segment;
		int16_t RemainSegment;
		int16_t Length;
		uint8_t Payload[PAYLOAD_SIZE];
	}RequestImageResponse;

	enum RequestImageStatus
	{
		Success = 0, Error = 1, InvalidValue = 2,
	};

	RequestImage( MissionStatus* status);
	RequestImage( MissionStatus* status, const char* myName, uint8_t myDestination, uint8_t myType);
	virtual ~RequestImage();
private:
	MissionStatus* status;
	void ConcreteExecute( TLVmessage_t*, TLVmessage_t*) override;
};

#endif /* REQUESTTAKEPHOTO_H_ */
