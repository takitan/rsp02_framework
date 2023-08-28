#include <map>
#include <algorithm>
#include "system/Process.hpp"
#include "fw/logger/Logger.hpp"

namespace rsp{
namespace rsp02{
namespace system{

template<typename PRD_T,typename CNS_T>
class TMessageConverter : public PipelineProcess<PRD_T,CNS_T>
{
	using dst_t = typename PRD_T::dst_t;
	private:
		fw::logger::ILogger *logger;
		fw::time::StopWatch sw;
		std::map<dst_t, IConsumer<CNS_T>* > Route;
	public:
		TMessageConverter( rsp::rsp02::time_t prd = 0) :
			PipelineProcess<PRD_T,CNS_T>(prd),
			logger(fw::logger::Logger::GetLogger("MessageConverter")),
			sw(prd){}

		bool ConcreteProcess( PRD_T &product, CNS_T &consume)
		{
			product = PRD_T(consume.Original);
			char buf[32];
			product.print( buf);
			logger->Info("Convert to %s", buf);
			return true;
		}

};
}
}
}
