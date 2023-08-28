#include <map>
#include <algorithm>
#include "system/Process.hpp"
#include "fw/logger/Logger.hpp"

namespace rsp{
namespace rsp02{
namespace system{

template<typename PRD_T,typename CNS_T>
class TMessageDispatcher : public PipelineProcess<PRD_T,CNS_T>
{
	using dst_t = typename PRD_T::dst_t;
	private:
		fw::logger::ILogger *logger;
		fw::time::StopWatch sw;
		std::map<dst_t, IConsumer<CNS_T>* > Route;
	public:
		TMessageDispatcher( rsp::rsp02::time_t prd = 0) :
			PipelineProcess<CNS_T,PRD_T>("MessageDispatcher", prd),
			logger(fw::logger::Logger::GetLogger("MessageDispatcher")),
			sw(prd){}

		void RegisterRoute( dst_t dst, IConsumer<CNS_T>* process)
		{
			Route[dst] = process;
		}

		bool ConcreteProcess( CNS_T &product, PRD_T &reproduct)
		{
			auto it = Route.find(product.Destination());
			if( it == std::end(Route)) return false;
			reproduct = PRD_T(product);
			logger->Info("Dispatch to %s", DestinationString( reproduct.Destination()));
			(it->second)->Accept( reproduct);
			return false;
		}

};
}
}
}
