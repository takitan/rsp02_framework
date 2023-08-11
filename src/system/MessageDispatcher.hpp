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
		std::map<dst_t, IProcess* > Route;
	public:
		TMessageDispatcher( rsp::rsp02::time_t prd = 0) :
			PipelineProcess<PRD_T,CNS_T>(prd),
			logger(fw::logger::Logger::GetLogger("MessageDispatcher")),
			sw(prd){}
		void RegisterRoute( dst_t dst, IProcess* process)
		{
			Route[dst] = process;
		}

		bool ConcreteProcess( PRD_T &product, CNS_T &consume)
		{
			auto it = Route.find(product.Destination());
			if( it == std::end(Route)) return false;
			consume = product;
			logger->Info("Dispatch to %s", (it->second)->GetInfo().Name);
			return true;
		}

};
}
}
}
