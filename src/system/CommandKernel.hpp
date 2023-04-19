#pragma once
#include <vector>
#include <queue>
#include "fw/command/ICommand.hpp"
#include "system/IProcess.hpp"

namespace rsp{
namespace rsp02{
namespace system{

template<typename T>
class CommandKernel : public ProcessBase<T>
{
	template<typename X> using ICommand = rsp::rsp02::fw::command::ICommand<X>;

	private:
		std::vector<ICommand<T>*> CommandList;
	
	protected:
		bool ConcreteProcess( T &packet)
		{
			for( auto it=CommandList.begin(); it!=CommandList.end(); ++it)
			{
				(*it)->Parse( packet);
			}
		}

	public:
		CommandKernel(){}
		virtual ~CommandKernel(){}

		bool RegisterCommand( ICommand<T>* cmd)
		{
			CommandList.push_back( cmd);
			return true;
		}
};

}
}
}
