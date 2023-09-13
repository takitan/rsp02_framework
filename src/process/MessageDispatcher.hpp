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
		GETTER_T getter;

	public:
		TMessageDispatcher( const char* name, GETTER_T index_getter, rsp::rsp02::time_t prd = 0) :
			PipelineProcess<CNS_T,PRD_T>(name, prd),
			logger(fw::logger::Logger::GetLogger("MessageDispatcher")),
			sw(prd),
			getter( index_getter){}

		void RegisterRoute( IDX_T index, IConsumer<CNS_T>* process)
		{
			Route[index] = process;
		}

		bool ConcreteProcess( CNS_T &product, PRD_T &reproduct)
		{
			INF_T index = getter( &product);
			//auto it = Route.find(product.Destination());
			auto it = Route.find(index.first);
			if( it == std::end(Route)) return false;
			reproduct = PRD_T(product);
			logger->Info("Dispatch to %s", index.second);
			(it->second)->Accept( reproduct);
			return false;
		}
};
}
}
}
