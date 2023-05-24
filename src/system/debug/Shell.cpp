#include <vector>
#include <cstring>
#include <algorithm>
#include "Shell.hpp"
#include "IShellCommand.hpp"

namespace rsp{
namespace rsp02{
namespace system{

namespace detail{
struct CommandTable
{
	const char* name;
	IShellCommand* cmd;
};

class ShellImpl
{
	public:
		ShellImpl(){}

		void RegisterCommand( const char* name, IShellCommand* cmd)
		{
			CommandTable tbl ={.name=name, .cmd=cmd};
			cmdtbl.push_back( tbl);
		}

		int Invoke( int argc, const char** argv, void* extobj)
		{
			// argv(ポインタ)1個キャプチャするだけだからstackでやれるはず！
			auto it = std::find_if( std::cbegin(cmdtbl), std::cend(cmdtbl),
				[argv]( const CommandTable &c)
				{
					return ::strncasecmp( c.name, argv[0], std::strlen(c.name))==0;
				});
			if( it==std::cend(cmdtbl)) return -1;
			return (*it).cmd->operator()( argc, argv, extobj);
		}

	private:
		std::vector<CommandTable> cmdtbl;
};
}

Shell::Shell()
{
	impl = new detail::ShellImpl();
}

void Shell::RegisterCommand( const char* name, IShellCommand* cmd)
{
	impl->RegisterCommand( name, cmd);
}

int Shell::Invoke( int argc, const char** argv, void* extobj)
{
	return impl->Invoke( argc, argv, extobj);
}

}
}
}
