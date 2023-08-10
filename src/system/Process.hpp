#pragma once

#include "Consumer.hpp"
#include "Producer.hpp"
#include "Executer.hpp"

namespace rsp{
namespace rsp02{
namespace system{


template<typename PRD_T,typename CNS_T>
class ProcessBase : public Producer<PRD_T>, public Consumer<CNS_T>, public Executer<PRD_T, CNS_T>
{
	public:
		ProcessBase(std::size_t queuesz = 1) :
			Producer<PRD_T>( Info), Consumer<CNS_T>( Info, queuesz), Executer<PRD_T,CNS_T>(this,this,Info){}
	private:
		ProcessInfo_t Info;
};

template<typename PRD_T>
using ProducerProcess = ProcessBase<PRD_T,NONE_T>;

template<typename CNS_T>
using ConsumerProcess = ProcessBase<NONE_T,CNS_T>;

template<typename PRD_T,typename CNS_T>
using PipelineProcess = ProcessBase<PRD_T,CNS_T>;

using IndivisualProcess = ProcessBase<NONE_T,NONE_T>;

}
}
}
