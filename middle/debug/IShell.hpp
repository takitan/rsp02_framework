#pragma once

namespace rsp{
namespace rsp02{
namespace system{

class IShellCommand;

class IShell
{
	public:
		virtual void RegisterCommand( const char* name, IShellCommand* cmd) = 0;
		virtual int Invoke( int argc, const char** argv, void* extobj) = 0;
};

}
}
}
