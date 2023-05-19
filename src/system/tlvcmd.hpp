#pragma once

#include "IShellCommand.hpp"
#include "rsp02.hpp"
#include "MissionDefine.hpp"
//#include "IProcess.hpp"

namespace rsp{
namespace rsp02{
namespace system{

namespace detail{
class tlvcmd_impl;
}

//class IConsumer<MissionTLV>;

class tlvcmd : public IShellCommand
{
	public:
		tlvcmd( IConsumer<MissionTLV>* c);
		int operator()( int argc, char** argv, void* extobj);
	private:
		IConsumer<MissionTLV>* cns;
		detail::tlvcmd_impl* impl;
};
}
}
}
