#pragma once
#include <vector>
#include <queue>
#include <functional>

#include "fw/command/ICommand.hpp"
#include "system/Process.hpp"
#include "fw/logger/Logger.hpp"

namespace rsp{
namespace rsp02{
namespace system{

template<typename TLV_T,typename PRD_T,typename CNS_T>
class CommandKernel : public PipelineProcess<PRD_T,CNS_T>
{
	template<typename X> using ICommand = rsp::rsp02::fw::command::ICommand<X>;

	private:
		std::vector<ICommand<TLV_T>*> CommandList;
		fw::logger::ILogger *logger;

		bool Kernel(PRD_T &reproduct, CNS_T &product)
		{
			for( auto it=CommandList.begin(); it!=CommandList.end(); ++it)
			{
				if( (*it)->Parse( product, reproduct)) return true;
			}
			for( auto it=CommandList.begin(); it!=CommandList.end(); ++it)
			{
				if( (*it)->Execute( product, reproduct)) return true;
			}
			return false;
		}

	protected:
		bool ConcreteProcess( PRD_T &reproduct, CNS_T &product)
		{
			return Kernel(reproduct, product);
		}

	public:
		CommandKernel(rsp::rsp02::time_t prd = 0) : PipelineProcess<PRD_T,CNS_T>(prd), logger(fw::logger::Logger::GetLogger( "CommandKernel")){}
		virtual ~CommandKernel(){}

		bool RegisterCommand( ICommand<TLV_T>* cmd)
		{
			CommandList.push_back( cmd);
			auto info = cmd->GetInfo();
			logger->Info("RegisterCommand:name=%s,type=%d", info.Name, info.Type);
			return true;
		}
};

}
}
}
