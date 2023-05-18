#pragma once
#include "system/Process.hpp"
#include "system/TLVStub.hpp"
#include "MissionDefine.hpp"

namespace rsp{
namespace rsp02{
namespace system{

namespace detail{
class DebugPortImpl;
}

class DebugPort : public ProducerProcess<MissionTLV>
{
	friend detail::DebugPortImpl;
	public:
		DebugPort();
	private:
		detail::DebugPortImpl* impl;
		bool ConcreteProcess( MissionTLV product);
};

}
}
}
