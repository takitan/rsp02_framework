#pragma once

#include "IShellCommand.hpp"
#include "MissionDefine.hpp"

class tlvcmd : public rsp::rsp02::system::IShellCommand
{
	public:
		tlvcmd( rsp::rsp02::system::IConsumer<MissionTLV>* c);
		int operator()( int argc, const char** argv, void* extobj);
	private:
		rsp::rsp02::system::IConsumer<MissionTLV>* cns;
};
