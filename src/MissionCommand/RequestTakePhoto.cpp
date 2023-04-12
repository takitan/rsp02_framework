#if 0

//#include "Mission.hpp"
#include "Command/RequestTakePhoto.h"
/*
 * TakePhoto.cpp
 *
 *  Created on: 2021/10/27
 *      Author: takit
 *
 *  RequestTakePhotoの実行クラス
 */

static const uint8_t DefaultDestination	= EDestination::Mission;
static const uint8_t DefaultType = EType::CmdRequestTakePhoto;
static const char* DefaultName = "RequestTakePhoto";

RequestTakePhoto::RequestTakePhoto( MissionStatus* status)
			: RequestTakePhoto( status, DefaultName, DefaultDestination, DefaultType)
{
	this->status = status;
}

RequestTakePhoto::RequestTakePhoto( MissionStatus* status, const char* myName, uint8_t myDestination, uint8_t myType)
			: TlvCommandBase( myName, myDestination, myType)
{
	this->status = status;
}

RequestTakePhoto::~RequestTakePhoto()
{
}

void RequestTakePhoto::ConcreteExecute( TLVmessage_t* cmd, TLVmessage_t* res)
{
	RequestTakePhotoCommand* req = ( RequestTakePhotoCommand*)cmd->pValue;
	RequestTakePhotoResponse* rep = ( RequestTakePhotoResponse*)res->pValue;
	res->destination = EDestination::Ground;
	res->type = EType::CmdReplyTakePhoto;
	res->length = 1;
	// Requestが条件に合っているか確認する。
	if( req->TargetCamera >= 2)
	{
		rep->status = RequestTakePhotoStatus::InvalidValue;
		return;
	}
	if( req->TakeQuantity < 1 || req->TakeQuantity > 11 )
	{
		rep->status = RequestTakePhotoStatus::InvalidValue;
		return;
	}
	// 撮影中だったらエラーレスポンス
	if( status->isRequiredTakePhoto)
	{
		rep->status = RequestTakePhotoStatus::Error;
		return;
	}
	// 撮影中でない場合、撮影のための初期化
	Process( req, rep);
}

void RequestTakePhoto::Process( RequestTakePhotoCommand* req, RequestTakePhotoResponse* rep)
{
		//camera.OV2640_set_JPEG_size(OV2640_1600x1200);
	PhotoSaver &photoSaver = multiplePhotoSaver[req->TargetCamera];

	for( int i=0; i<req->TakeQuantity; i++)
	{
		bool ret = photoSaver.takeAndSaveWithAutoNaming("/fs", req->TargetCamera);
		if ( !ret )
		{
			rep->status = RequestTakePhotoStatus::Error;
			break;
		}
		wait_ms( 100);
	}
	// 大成功
	rep->status = RequestTakePhotoStatus::Success;
}

#endif
