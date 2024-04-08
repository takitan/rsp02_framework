#include <map>
#include <algorithm>
#include "Process.hpp"
#include "fw/logger/Logger.hpp"

namespace rsp{
namespace rsp02{
namespace system{

template<typename CNS_T,typename PRD_T>
class TMessageConverter : public PipelineProcess<CNS_T,PRD_T>
{
	using dst_t = typename PRD_T::dst_t;
	private:
		fw::logger::ILogger *logger;
		fw::time::StopWatch sw;
		std::map<dst_t, IConsumer<CNS_T>* > Route;
	public:
		TMessageConverter( rsp::rsp02::time_t prd = 0) :
			PipelineProcess<CNS_T,PRD_T>("MessageConverter", prd),
			logger(fw::logger::Logger::GetLogger("MessageConverter")),
			sw(prd){}

		bool ConcreteProcess( CNS_T &product, PRD_T &reproduct)
		{
			reproduct = PRD_T(product.Original, product.sender_id);
			char buf[64];
			reproduct.print( buf);
			logger->Info("Convert to %s", buf);
			return true;
		}

};
}
}
}
