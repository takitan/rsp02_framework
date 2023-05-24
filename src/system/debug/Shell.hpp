#pragma once
#include "IShell.hpp"

namespace rsp{
namespace rsp02{
namespace system{

namespace detail
{
	class ShellImpl;
}

class Shell : public IShell
{
	friend class detail::ShellImpl;
	public:
		Shell();
		void RegisterCommand( const char* name, IShellCommand* cmd);
		int Invoke( int argc, char** argv, void* extobj);
	private:
		detail::ShellImpl* impl;
};

}
}
}
