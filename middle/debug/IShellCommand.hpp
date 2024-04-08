#pragma once

namespace rsp{
namespace rsp02{
namespace system{

class IShellCommand
{
	public:
		virtual int operator()( int argc, const char** argv, void* extobj) = 0;
};

}
}
}