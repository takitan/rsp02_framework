#pragma once
#include <vector>
#include <queue>
#include <functional>

#include "fw/command/ICommand.hpp"
#include "system/Process.hpp"

namespace rsp{
namespace rsp02{
namespace system{

template<typename TLV_T,typename PRD_T,typename CNS_T>
class CommandKernel : public PipelineProcess<PRD_T,CNS_T>
{
	template<typename X> using ICommand = rsp::rsp02::fw::command::ICommand<X>;

	private:
		std::vector<ICommand<TLV_T>*> CommandList;

	protected:
		bool ConcreteProcess( PRD_T &reproduct, CNS_T &product)
		{
			for( auto it=CommandList.begin(); it!=CommandList.end(); ++it)
			{
				(*it)->Parse( product);
			}
			reproduct = PRD_T();
#pragma message ToDo!!!!!!
		}

	public:
		CommandKernel(){}
		virtual ~CommandKernel(){}

		bool RegisterCommand( ICommand<TLV_T>* cmd)
		{
			auto srf = std::bind(&CommandKernel<TLV_T,PRD_T,CNS_T>::SendRequest, this);
			cmd->SetSendRequestFunc( srf);
			CommandList.push_back( cmd);
			return true;
		}

		void SendRequest()
		{
			;
		}
};

}
}
}
