#include <map>
#include <algorithm>
#include <functional>
#include "system/Process.hpp"
#include "fw/logger/Logger.hpp"

namespace rsp{
namespace rsp02{
namespace system{

template<typename PT,typename CT, typename IT>
class TMessageDispatcher : public PipelineProcess<PT,CT>
{
	public:
		using PRD_T = PT;
		using CNS_T = CT;
		using IDX_T = IT;
		using INF_T = std::pair<IDX_T,const char*>;
		using GETTER_T = std::function< INF_T(CNS_T*)>;
	private:
		fw::logger::ILogger *logger;
		fw::time::StopWatch sw;
		std::map<IDX_T, IConsumer<CNS_T>* > Route;
		IConsumer<CNS_T>* DefaultRoute;
		GETTER_T getter;

	public:
		TMessageDispatcher( const char* name, GETTER_T index_getter, rsp::rsp02::time_t prd = 0) :
			PipelineProcess<CNS_T,PRD_T>(name, prd),
			logger(fw::logger::Logger::GetLogger(name)),
			sw(prd),
			DefaultRoute( nullptr),
			getter( index_getter){}

		void RegisterRoute( IDX_T index, IConsumer<CNS_T>* process)
		{
			Route[index] = process;
		}

		void RegisterDefaultRoot( IConsumer<CNS_T>* process)
		{
			DefaultRoute = process;
		}

		bool ConcreteProcess( CNS_T &product, PRD_T &reproduct)
		{
			INF_T index = getter( &product);
			//auto it = Route.find(product.Destination());
			auto it = Route.find(index.first);
			auto route = DefaultRoute;
			if( it == std::end(Route))
			{
				if( route == nullptr)
				{
					logger->Info("Discard Message of index=%s",index.second);
					return false;
				}
				else route = DefaultRoute;
			}
			else
			{
				route = it->second;
			}
			reproduct = PRD_T(product);
			logger->Info("Dispatch Message to %s",route->GetInfo().Name);
			route->Accept( reproduct);
			return false;
		}
};
}
}
}
