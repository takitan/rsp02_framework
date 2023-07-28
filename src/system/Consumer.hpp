#pragma once
#include <deque>
#include "IProcess.hpp"

namespace rsp{
namespace rsp02{
namespace system{

template<typename T> class Producer;
template<typename T> class Consumer;

template<typename CNS_T>
class ConsumerAdapter
{
	using Consumer = rsp::rsp02::system::Consumer<CNS_T>;
	private:
		Consumer* consumer;

	public:
		ConsumerAdapter( Consumer* c) : consumer(c){}
		bool TakeProduct( CNS_T &product)
		{
			return consumer->TakeProduct( product);
		}
};

template<typename CNS_T>
class Consumer : public IConsumer<CNS_T>
{
	friend ConsumerAdapter<CNS_T>;
	public:
		Consumer( ProcessInfo_t &inf, std::size_t qsz) : Info(inf), queue(){(void)qsz;}
		bool Accept( CNS_T &product)
		{
			if( queue.size() >= queue.max_size())
			{
				Info.QueueOverflow ++;
				return false;
			}
			queue.push_back( product);
			Info.QueueSize = queue.size();
			return true;
		}
	private:
		ProcessInfo_t &Info;
		std::deque<CNS_T> queue;

		bool TakeProduct( CNS_T &product)
		{
			if( queue.empty()) return false;
			product = queue.front();
			queue.pop_front();
			Info.QueueSize = queue.size();
			return true;
		}

};

template<>
class Consumer<NONE_T>
{
	public:
		Consumer( ProcessInfo_t &inf, std::size_t qsz){(void)inf;(void)qsz;}
};

}
}
}
