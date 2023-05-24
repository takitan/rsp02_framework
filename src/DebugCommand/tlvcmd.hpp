#pragma once

#include "IShellCommand.hpp"
#include "rsp02.hpp"
#include "MissionDefine.hpp"
//#include "IProcess.hpp"

namespace detail{
class tlvcmd_impl;
}

//class IConsumer<MissionTLV>;

class tlvcmd : public rsp::rsp02::system::IShellCommand
{
	public:
		tlvcmd( rsp::rsp02::system::IConsumer<MissionTLV>* c);
		int operator()( int argc, char** argv, void* extobj);
	private:
		rsp::rsp02::system::IConsumer<MissionTLV>* cns;
		detail::tlvcmd_impl* impl;
};
