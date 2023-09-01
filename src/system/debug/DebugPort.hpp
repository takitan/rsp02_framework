#pragma once
#include "MissionDefine.hpp"

namespace rsp{
namespace rsp02{
namespace system{

namespace detail
{
class DebugPortImpl;
}

class IShell;

class DebugPort
{
	friend detail::DebugPortImpl;
	public:
		DebugPort( IShell* sh);
		DebugPort(){}
	private:
		detail::DebugPortImpl* impl;
};

}
}
}
