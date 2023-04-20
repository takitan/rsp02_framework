#pragma once
#include <cstddef>
#include <deque>
#include "fw/time/StopWatch.hpp"

namespace rsp{
namespace rsp02{
namespace system{

struct ProcessInfo_t
{
	using time_t = rsp::rsp02::time_t;
	/** プロセス名*/
	const char* Name;
	/** @brief 処理開始時刻 */
	time_t StartTime;
	/** @brief 処理完了時刻 */
	time_t CompletionTime;
	/** @brief 経過時刻*/
	time_t ElapsedTime;
	/** @brief メッセージキューサイズ*/
	std::size_t QueueSize;
	/** @brief 総受付メッセージ数*/
	std::size_t TotalPacket;
	/** @brief 処理成功メッセージ数*/
	std::size_t PassedPacket;
	/** @brief 処理失敗メッセージ数*/
	std::size_t FailedPacket;
	/** @brief キューオーバーフロー回数*/
	int QueueOverflow;
	/** @brief オプション*/
	void* Option;
	ProcessInfo_t() : TotalPacket(0), QueueOverflow(0), Option(nullptr){}
};

namespace{
class TTimeKeeper
{
	using TStopWatch = rsp::rsp02::fw::time::TStopWatch;
	public:
		TTimeKeeper( ProcessInfo_t &inf) : info(inf){ info.StartTime = sw.Start();}
		~TTimeKeeper()
		{
			info.CompletionTime = sw.Lap();
			info.ElapsedTime = sw.GetElapsed();
		}
	private:
		TStopWatch sw;
		ProcessInfo_t &info;
};
}
/*
class IProcess
{
	public:
		virtual bool Process() = 0;
		virtual const ProcessInfo_t &GetInfo() const = 0;
		IProcess(){}
		virtual ~IProcess(){}
};

template<typename T>
class IPacket
{
	public:
		virtual void SetPostProcess( IPacket<T>*) = 0;
		virtual bool Accept( T &) = 0;

};

*/

class IProcess
{
	public:
		virtual bool Perform() = 0;
		virtual const ProcessInfo_t &GetInfo() const = 0;
};

template<typename CNS_T>
class IConsumer
{
	public:
		virtual bool Accept( CNS_T &) = 0;
};

template<typename PRD_T>
class IProducer
{
	public:
		virtual void SetConsumer( IConsumer<PRD_T>*) = 0;
};

struct NONE_T
{
	constexpr static const char*a_mesage="None of Product.";
	constexpr static const char*b_message1="If this struct is specified to template parameter of PRD_T, Producer role is disabled.";
	constexpr static const char*b_message2="If this struct is specified to template parameter of CNS_T, Consumer role is disabled.";
	constexpr static const char*b_message3="If this struct is specified to template parameter of PRD_T and CNS_T, That is meaningless .";
};

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

template<typename CNS_T>
class ConsumerAdapter
{
	using Consumer = rsp::rsp02::system::Consumer<CNS_T>;
	private:
		Consumer* consumer;

	protected:
		ConsumerAdapter( Consumer* c) : consumer(c){}
		bool TakeProduct( CNS_T &product)
		{
			return consumer->TakeProduct( product);
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

template<typename CNS_T>
class Consumer : public IConsumer<CNS_T>
{
	friend ConsumerAdapter<CNS_T>;
	public:
		Consumer( ProcessInfo_t &inf, std::size_t qsz) : Info(inf), queue(qsz){}
		bool Accept( CNS_T &product)
		{
			if( queue.size() >= queue.max_size())
			{
				Info.QueueOverflow ++;
				return false;
			}
			queue.push_back( product);
			Info.QueueSize = queue.size();
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

template<typename PRD_T, typename CNS_T>
class Executer : public IProcess, public ProducerAdapter<PRD_T>, public ConsumerAdapter<CNS_T>
{
	public:
		Executer( ProcessInfo_t &inf, Producer<PRD_T>* p, Consumer<CNS_T>* c)
			: ProducerAdapter<PRD_T>(p), ConsumerAdapter<CNS_T>(c), Info(inf){}
		
		bool Perform()
		{
			TTimeKeeper kp(Info);
			bool st = true;
			CNS_T product;
			while( ConsumerAdapter<CNS_T>::TakeProduct( product)) 
			{
				PRD_T reproduct;
				if( !ConcreteProcess( reproduct, product))
				{
					Info.FailedPacket++;
					return false;
				}
				if( !ProducerAdapter<PRD_T>::Invoke( reproduct))
				{
					Info.FailedPacket++;
					return false;
				}
				Info.TotalPacket ++;
			}
			return st;
		}
		const ProcessInfo_t &GetInfo() const
		{
			return Info;
		}
	private:
		ProcessInfo_t &Info;
		virtual bool ConcreteProcess( PRD_T reproduct, CNS_T product)
		{
			(void)product;
			reproduct = PRD_T();
		}
};

template<typename PRD_T>
class Executer<PRD_T,NONE_T> : public IProcess, public ProducerAdapter<PRD_T>
{
	public:
		Executer( ProcessInfo_t &inf, Producer<PRD_T>* p, Consumer<NONE_T>* c) :
			ProducerAdapter<PRD_T>(p), Info(inf){}
		bool Perform()
		{
			PRD_T product;
			if( !ConcreteProcess( product)) return false;
			ProducerAdapter<PRD_T>::Invoke( product);
		}
		const ProcessInfo_t &GetInfo() const
		{
			return Info;
		}

	private:
		ProcessInfo_t &Info;
		virtual bool ConcreteProcess( PRD_T &product)
		{
			(void)product;
			return true;
		}
};

template<typename CNS_T>
class Executer<NONE_T,CNS_T> : public IProcess, public ConsumerAdapter<CNS_T>
{
	public:
		Executer( ProcessInfo_t &inf, Producer<NONE_T>* p, Consumer<CNS_T>* c) :
			Info(inf), ConsumerAdapter<CNS_T>(c){}
		bool Perform()
		{
			bool st = true;
			CNS_T product;
			while( ConsumerAdapter<CNS_T>::TakeProduct( product)) 
			{
				st &= ConcreteProcess( product);
				Info.TotalPacket ++;
			}
			return st;
		}
		const ProcessInfo_t &GetInfo() const
		{
			return Info;
		}

	private:
		ProcessInfo_t Info;
		virtual bool ConcreteProcess( CNS_T &product)
		{
			(void)product;
			return true;
		}
};

template<>
class Executer<NONE_T,NONE_T> : public IProcess
{
	public:
		Executer(ProcessInfo_t &inf, Producer<NONE_T>* p, Consumer<NONE_T>* c)
		{(void)inf;(void)p;(void)c;}
		bool Perform(){return ConcreteProcess();}
		const ProcessInfo_t &GetInfo() const{ return Info;}
	private:
		ProcessInfo_t Info;
		virtual bool ConcreteProcess(){ return true;}
};

template<typename PRD_T,typename CNS_T>
class ProcessBase : public Producer<PRD_T>, public Consumer<CNS_T>, public Executer<PRD_T, CNS_T>
{
	public:
		ProcessBase(std::size_t queuesz = 1) :
			Producer<PRD_T>( Info), Consumer<CNS_T>( Info, queuesz), Executer<PRD_T,CNS_T>( Info, this, this){}
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

#if 0
template<typename PRD_T, typename CNS_T>
class PipelineProcess : public ProducerBase<PRD_T>, public ConsumerBase<CNS_T>, public Executer
template<typename T, std::size_t N = 1>
class Executer : public IProcess, public IPacket<T>
{
	using TStopWatch = rsp::rsp02::fw::time::TStopWatch;
	private:
		IPacket<T>* PostProcess;
		std::queue<T> PacketQueue;

	protected:
		ProcessInfo_t Info;
		bool Invoke( T &packet)
		{
			if( PostProcess == nullptr) return false;
			return PostProcess->Accept( packet);
		}
		
		virtual bool ConcreteProcess( T &packet)
		{
			(void)packet;
			return true;
		}

	public:
		Executer(){}

		void SetPostProcess( IPacket<T>* pp)
		{
			PostProcess = pp;
		}

		bool Process()
		{
			TTimeKeeper<ProcessInfo_t,std::queue<T> > tk( Info, PacketQueue);
			bool st = true;
			while( !PacketQueue.empty()) 
			{
				st &= ConcreteProcess( PacketQueue.front());
				PacketQueue.pop();
				Info.TotalPacket ++;
			}
			return st;
		}

		const ProcessInfo_t &GetInfo() const{ return Info;}

		bool Accept( T &packet)
		{
			if( PacketQueue.size() > N)
			{
				Info.QueueOverflow ++;
				return false;
			}
			PacketQueue.push( packet);
		}
};
#endif

}
}
}
