#if 0
#include "RequestImage.h"
/*
 * TakePhoto.cpp
 *
 *  Created on: 2021/10/27
 *      Author: takit
 *
 *  RequestTakePhotoの実行クラス
 */

static const uint8_t DefaultDestination	= EDestination::Mission;
static const uint8_t DefaultType = EType::CmdRequestImage;
static const char* DefaultName = "RequestImaqge";

RequestImage::RequestImage( MissionStatus* status)
			: RequestImage( status, DefaultName, DefaultDestination, DefaultType)
{
	this->status = status;
}

RequestImage::RequestImage( MissionStatus* status, const char* myName, uint8_t myDestination, uint8_t myType)
			: TlvCommandBase( myName, myDestination, myType)
{
	this->status = status;
}

RequestImage::~RequestImage()
{
}

void RequestImage::ConcreteExecute( TLVmessage_t* cmd, TLVmessage_t* res)
{
	RequestImageCommand* req = ( RequestImageCommand*)cmd->pValue;
	RequestImageResponse* rep = ( RequestImageResponse*)res->pValue;
	res->destination = EDestination::Ground;
	res->type = EType::CmdReplyImage;
	res->length = sizeof( RequestImageResponse);
	rep->status = RequestImageStatus::Success;
	// Requestが条件に合っているか確認する。
	if( req->TargetCamera >= 2)
	{
		rep->status = RequestImageStatus::InvalidValue;
		return;
	}
	if( req->ImageNumber < 0)
	{
		rep->status = RequestImageStatus::InvalidValue;
		return;
	}

response:;
	res->destination = EDestination::Ground;
	res->type = EType::CmdReplyTakePhoto;
	res->length = 1;
}

#endif