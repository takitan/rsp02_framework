#include <vector>
#include <cstring>
#include <algorithm>
#include "Shell.hpp"
#include "IShellCommand.hpp"

namespace rsp{
namespace rsp02{
namespace system{

namespace detail{
class ShellImpl
{
	public:
		ShellImpl(){}

		void RegisterCommand( IShellCommand* cmd)
		{
			CommandList.push_back( cmd);
		}

		int Invoke( int argc, char** argv, void* extobj)
		{
			// argv(ポインタ)1個キャプチャするだけだからstackでやれるはず！
			auto it = std::find_if( std::cbegin(CommandList), std::cend(CommandList),
				[argv](IShellCommand* c)
				{
					return ::strncasecmp( c->Name(), argv[0], std::strlen(c->Name()));
				});
			if( it==std::cend(CommandList)) return -1;
			return (*it)->operator()( argc, argv, extobj);
		}

	private:
		std::vector<IShellCommand*> CommandList;
};
}

Shell::Shell()
{
	impl = new detail::ShellImpl();
}

void Shell::RegisterCommand( IShellCommand* cmd)
{
	impl->RegisterCommand( cmd);
}

int Shell::Invoke( int argc, char** argv, void* extobj)
{
	return impl->Invoke( argc, argv, extobj);
}

}
}
}
