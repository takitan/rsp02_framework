/*
 * RequestPing.h
 *
 *  Created on: 2021/10/27
 *      Author: takit
 *
 * TLVコマンドのRequestPing実行クラス
 */

#pragma once

#include "fw/command/TlvCommandBase.h"

class RequestPing : public TlvCommandBase
{
public:
	/** @brief RequestPingコマンドのValue定義 */
	typedef struct RequestPingPayload_t
	{
		uint8_t dummy_data[10];
	}RequestPingPayload;

	RequestPing();
	RequestPing( const char* myName, uint8_t myDestination, uint8_t myType);
	virtual ~RequestPing();
private:
	void ConcreteExecute( TLVmessage_t* cmd, TLVmessage_t* res);
};

#endif /* REQUESTPING_H_ */
