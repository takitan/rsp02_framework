#pragma once
#include "system/Process.hpp"
#include "fw/logger/Logger.hpp"
#include "fw/util/queue.hpp"

namespace rsp{
namespace rsp02{
namespace system{

template<typename T>
class TMessageInjecter : public ProducerProcess<T>
{
	private:
		fw::logger::ILogger *logger;
		rsp::rsp02::fw::util::queue<T,1> que;
		std::mutex mtx;

	public:
		TMessageInjecter( rsp::rsp02::time_t prd = 0) :
			ProducerProcess<T>("MessageInjecter", prd),
			logger(fw::logger::Logger::GetLogger("MessageInjecter")),
			{
				mtx.lock();
			}

		bool ConcreteProcess( T &product)
		{
			return que.get(product);
		}

		bool InjectMessage( const T &message)
		{
			auto st = que.put(message);
			if( !st) return false;
			mtx.lock();
			return 
		}
};

template<typename T>
class TMessagePeeper : public PipelineProcess<T,T>
{
	public:
		TMessagePeeper( rsp::rsp02::time_t prd = 0) : PipelineProcess<T,T>("MessagePeeker", prd){}
	protected:
		bool ConcreteProcess( T &cns, T &prd)
		{

			prd = cns;
		}
	private:
		ITLV* tlv;
};

}
}
}
