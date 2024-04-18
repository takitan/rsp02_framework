/**
 * @file Consumer.hpp
 * @author Nobuyuki Takita (takitan1972@gmail.com)
 * @brief Consumer-ProducerパターンのConsumer
 * @version 0.1
 * @date 2024-04-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once
#include "fw/util/queue.hpp"
#include "IProcess.hpp"

namespace rsp{
namespace rsp02{
namespace system{

template<typename T> class Producer;
template<typename T> class Consumer;

/**
 * @brief @ref Executer
 * 
 * @tparam CNS_T 
 */
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
	constexpr static int N = 1;
	public:
		Consumer( ProcessInfo_t &inf, std::size_t qsz) : Info(inf), queue(){(void)qsz;}
		bool Accept( CNS_T &product)
		{
			auto st = queue.try_put_for( product);
			if( !st)
			{
				Info.QueueOverflow ++;
				return false;
			}
			Info.QueueSize = queue.size();
			return st;
		}
		const ProcessInfo_t GetInfo() const{ return Info;}

	private:
		ProcessInfo_t &Info;
		rsp02::fw::util::queue<CNS_T,N> queue;

		bool TakeProduct( CNS_T &product)
		{
			auto st = queue.try_get_for( product);
			if( !st) return false;
			Info.QueueSize = queue.size();
			return st;
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
