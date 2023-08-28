#pragma once

#include "Consumer.hpp"
#include "Producer.hpp"
#include "Executer.hpp"

namespace rsp{
namespace rsp02{
namespace system{

template<typename CNS_T,typename PRD_T>
class ProcessBase : public Producer<PRD_T>, public Consumer<CNS_T>, public Executer<CNS_T, PRD_T>, public IProcess
{
	using StopWatch = rsp::rsp02::fw::time::StopWatch;
	public:
		ProcessBase(const char* name, rsp::rsp02::time_t per = 0, std::size_t queuesz = 1) :
			Producer<PRD_T>( Info),
			Consumer<CNS_T>( Info, queuesz),
			Executer<CNS_T,PRD_T>(this,this,Info),
			Info(name),
			sw(per),
			logger(rsp::rsp02::fw::logger::Logger::GetLogger("Process")){}
		bool Accept( CNS_T &product)
		{
			logger->Info("Accept");
			product.sender_id = IProcess::ProcessID;
			return Consumer<CNS_T>::Accept( product);
		}

		bool Invoke( PRD_T &p)
		{
			logger->Info("Invoke");
			return Producer<PRD_T>::Invoke(p);
		}

		bool Perform()
		{
			bool retval = true;
			if( sw.isPeriod())
			{
				logger->Trace("Process Ticked.");
				retval = Executer<CNS_T,PRD_T>::Perform();
			}
			return retval;

		}

		const ProcessInfo_t GetInfo() const{ return Info;}

	private:
		ProcessInfo_t Info;
		rsp::rsp02::fw::time::StopWatch sw;
		rsp::rsp02::fw::logger::ILogger* logger;
};

template<typename PRD_T>
using ProducerProcess = ProcessBase<NONE_T,PRD_T>;

template<typename CNS_T>
using ConsumerProcess = ProcessBase<CNS_T,NONE_T>;

template<typename CNS_T,typename PRD_T>
using PipelineProcess = ProcessBase<CNS_T,PRD_T>;

using IndivisualProcess = ProcessBase<NONE_T,NONE_T>;

}
}
}
