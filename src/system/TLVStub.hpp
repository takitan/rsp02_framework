#pragma once
#include <cstdint>
#include <cstddef>
#include "fw/util/align.hpp"

class ITLV
{
	public:
		virtual bool HasData() = 0;

		virtual uint8_t  send(uint8_t msgDest ,uint8_t msgType ,void* msgVal ,uint16_t msgLen ,
					bool waitReply = true , float timeout = -1 , int retryCount = -1 ) = 0;
		virtual uint8_t recv( rsp02TLV& packet, int sender_id) = 0;

		virtual uint8_t GetResult() = 0;
		virtual uint8_t GetDestination() = 0;
		virtual uint8_t GetType() = 0;
		virtual uint16_t GetLength() = 0;
		virtual uint8_t* GetPV() = 0;
};

class TinyTLV : public ITLV
{
	using align = rsp::rsp02::fw::util::align;
	public:
		int state;
		int data_receive_count;
		int ScanOfDataReceive;
		uint8_t* pValue;
		std::size_t length;
		bool result;
		std::size_t pBufIdx;

		uint8_t pBuf[2][16] =
		{
			{ 0x05, 0x31, 0x0a, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09},
			{ 0x05, 0x31, 0x09, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08},
		};
		static constexpr std::size_t pBufNum = sizeof(pBuf)/sizeof(pBuf[0]);

		bool HasData()
		{
			if( result) return true;
			switch( state)
			{
			case 1:
				state=0;
				data_receive_count = 0;
				result = false;
			case 0:
				if( data_receive_count++ < ScanOfDataReceive) break;
				result = true;
				pValue = &pBuf[pBufIdx][4];
				if( ++pBufIdx == pBufNum) pBufIdx=0;
				state++;
				break;
			}
			return true;
		}

		uint8_t  send(uint8_t msgDest ,uint8_t msgType ,void* msgVal ,uint16_t msgLen ,
					bool waitReply = true , float timeout = -1 , int retryCount = -1 )
		{
			(void)msgDest;(void)msgType;(void)msgVal;(void)msgLen;(void)waitReply;(void)timeout;(void)retryCount;
			return 0x01;
		}

		uint8_t recv( rsp02TLV& packet, int sender_id)
		{
			packet = rsp02TLV(pBuf[pBufIdx], sender_id);
			pBufIdx = (pBufIdx+0x01)&0x01;
			return 0x01;
		}
		uint8_t GetResult(){ return result;}
		uint8_t GetDestination(){ return align::safe_read<uint8_t>( &pBuf[pBufIdx][0]);}
		uint8_t GetType(){ return align::safe_read<uint8_t>(&pBuf[pBufIdx][1]);}
		uint16_t GetLength(){ return align::safe_read<uint16_t>(&pBuf[pBufIdx][2]); }
		uint8_t* GetPV(){ return &pBuf[pBufIdx][4];}

		uint8_t send( rsp02TLV pkt)
		{
			return 0x01;
		}
		TinyTLV(int sdr)
			: state(0), data_receive_count(0), ScanOfDataReceive(sdr), pValue(pBuf[0]), length(0), result(false), pBufIdx(0){}
};
