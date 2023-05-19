#pragma once

namespace rsp{
namespace rsp02{
namespace system{

class IShellCommand
{
	public:
		virtual int operator()( int argc, char** argv, void* extobj) = 0;
		virtual const char* Name() const = 0;
};

}
}
}