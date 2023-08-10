#pragma once
#include "IProcess.hpp"

namespace rsp{
namespace rsp02{
namespace system{

template<typename T> class Producer;
template<typename T> class Consumer;

template<typename PRD_T>
class ProducerAdapter
{
	using Producer = rsp::rsp02::system::Producer<PRD_T>;
	private:
		Producer* producer;

	protected:
		ProducerAdapter( Producer* p) : producer(p){}
		bool Invoke( PRD_T &product)
		{
			return producer->Invoke( product);
		}
};



template<typename PRD_T>
class Producer : public IProducer<PRD_T>
{
	friend ProducerAdapter<PRD_T>;
	public:
		Producer( ProcessInfo_t &inf) : Info(inf){}
		void SetConsumer( IConsumer<PRD_T>* c){Consumer = c;}

	private:
		ProcessInfo_t &Info;
		IConsumer<PRD_T>* Consumer;

		bool Invoke( PRD_T &p)
		{
			return Consumer->Accept( p);
		}
};
template<>
class Producer<NONE_T>
{
	public:
		Producer( ProcessInfo_t &inf){(void)inf;}
};

}
}
}
