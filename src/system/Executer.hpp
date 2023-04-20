#pragma once
#include "IProcess.hpp"
#include "Producer.hpp"
#include "Consumer.hpp"

namespace rsp{
namespace rsp02{
namespace system{

template<typename T> class Producer;
template<typename T> class Consumer;

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

template<typename PRD_T, typename CNS_T>
class Executer : public IProcess, public ProducerAdapter<PRD_T>, public ConsumerAdapter<CNS_T>
{
	public:
		Executer( Producer<PRD_T>* p, Consumer<CNS_T>* c, ProcessInfo_t &inf)
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
		Executer( Producer<PRD_T>* p, Consumer<NONE_T>* c, ProcessInfo_t &inf) :
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
		Executer( Producer<NONE_T>* p, Consumer<CNS_T>* c, ProcessInfo_t &inf) :
			ConsumerAdapter<CNS_T>(c),Info(inf){}
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
		Executer( Producer<NONE_T>* p, Consumer<NONE_T>* c, ProcessInfo_t &inf)
			{(void)inf;(void)p;(void)c;}
		bool Perform(){return ConcreteProcess();}
		const ProcessInfo_t &GetInfo() const{ return Info;}
	private:
		ProcessInfo_t Info;
		virtual bool ConcreteProcess(){ return true;}
};

}
}
}
