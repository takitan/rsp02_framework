#pragma once
#include "GlobalDefine.hpp"
#include "SystemManager.hpp"
#include "MessageDispatcher.hpp"
#include "MessageConverter.hpp"
#include "CommandKernel.hpp"
#include "TLVStub.hpp"
#include "TLVDatalink.hpp"
#include "debug/DebugPort.hpp"
#include "middle/con_pro/IProcess.hpp"

class TProcessRoot
{
	public:
		using TDSTDispatcher = rsp::rsp02::system::TMessageDispatcher<rsp02TLV,rsp02TLV,rsp02TLV::dst_t>;
		using TPRDispatcher = rsp::rsp02::system::TMessageDispatcher<rsp02TLV,rsp02TLV,int>;
		TinyTLV tlv;
		rsp::rsp02::system::TLVDatalinkUp<rsp02TLV> datalink_up;
		rsp::rsp02::system::TLVDatalinkDown<rsp02TLV> datalink_down;
		rsp::rsp02::system::DebugPort debugport;
		TDSTDispatcher DSTDispatcher;
		TPRDispatcher PRDispatcher;
		rsp::rsp02::system::TMessageConverter<rsp02TLV,TLVPacket> UpConverter;
		rsp::rsp02::system::TMessageConverter<TLVPacket,rsp02TLV> DnConverter;
		
		rsp::rsp02::system::TSystemManager<TLVPacket> SystemManager;

		TProcessRoot();

		void Initialize();
};

extern TProcessRoot ProcessRoot;