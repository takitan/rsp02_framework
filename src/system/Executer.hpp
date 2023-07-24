#pragma once
#include "IProcess.hpp"
#include "Producer.hpp"
#include "Consumer.hpp"
#include "fw/logger/Logger.hpp"

namespace rsp{
namespace rsp02{
namespace system{

template<typename T> class Producer;
template<typename T> class Consumer;

namespace{
class TTimeKeeper
{
	using StopWatch = rsp::rsp02::fw::time::StopWatch;
	public:
		TTimeKeeper( ProcessInfo_t &inf) : info(inf){ info.StartTime = sw.Start();}
		~TTimeKeeper()
		{
			info.CompletionTime = sw.Lap();
			info.ElapsedTime = sw.GetElapsed();
		}
	private:
		StopWatch sw;
		ProcessInfo_t &info;
};
}

template<typename PRD_T, typename CNS_T>
class Executer : public IExecuter<PRD_T,CNS_T>
{
	public:
		Executer( Producer<PRD_T>* p, Consumer<CNS_T>* c, ProcessInfo_t &inf) :
			Info(inf), pro_adp( new ProducerAdapter<PRD_T>(p)), cns_adp( new ConsumerAdapter<CNS_T>(c)),
			logger(fw::logger::Logger::GetLogger("Executer")){}

		bool Perform()
		{
			TTimeKeeper kp(Info);
			bool st = true;
			CNS_T product;
			while( cns_adp->TakeProduct( product))
			{
				logger->Info( "Message is comming");
				PRD_T reproduct;
				if( !ConcreteProcess( reproduct, product))
				{
					Info.FailedPacket++;
					return false;
				}
				if( !pro_adp->Invoke( reproduct))
				{
					Info.FailedPacket++;
					return false;
				}
				Info.TotalPacket ++;
			}
			return st;
		}
		const ProcessInfo_t GetInfo() const
		{
			return Info;
		}
	private:
		ProcessInfo_t &Info;
		ProducerAdapter<PRD_T>* pro_adp;
		ConsumerAdapter<CNS_T>* cns_adp;
		fw::logger::ILogger* logger;

		virtual bool ConcreteProcess( PRD_T& reproduct, CNS_T& product) = 0;
		{
			(void)product;
			reproduct = PRD_T();
			return false;
		}
};

template<typename PRD_T>
class Executer<PRD_T,NONE_T> : public IExecuter<PRD_T,NONE_T>
{
	public:
		Executer( Producer<PRD_T>* p, Consumer<NONE_T>* c, ProcessInfo_t &inf) :
			Info(inf), pro_adp( new ProducerAdapter<PRD_T>(p)){(void)c;}
		bool Perform()
		{
			PRD_T product;
			if( !ConcreteProcess( product)) return false;
			return pro_adp->Invoke( product);
		}

		const ProcessInfo_t GetInfo() const
		{
			return Info;
		}

	private:
		ProcessInfo_t &Info;
		ProducerAdapter<PRD_T>* pro_adp;

		virtual bool ConcreteProcess( PRD_T &product)
		{
			(void)product;
			return true;
		}
};

template<typename CNS_T>
class Executer<NONE_T,CNS_T> : public IExecuter<NONE_T,CNS_T>
{
	public:
		Executer( Producer<NONE_T>* p, Consumer<CNS_T>* c, ProcessInfo_t &inf) :
			Info(inf), cns_adp( new ConsumerAdapter<CNS_T>(c)){(void)p;}
		bool Perform()
		{
			bool st = true;
			CNS_T product;
			while( cns_adp->TakeProduct( product))
			{
				st &= ConcreteProcess( product);
				Info.TotalPacket ++;
			}
			return st;
		}

	private:
		ProcessInfo_t& Info;
		ConsumerAdapter<CNS_T>* cns_adp;

		virtual bool ConcreteProcess( CNS_T &product)
		{
			(void)product;
			return true;
		}
};

template<>
class Executer<NONE_T,NONE_T> : public IExecuter<NONE_T,NONE_T>
{
	public:
		Executer( Producer<NONE_T>* p, Consumer<NONE_T>* c, ProcessInfo_t &inf) : Info(inf)
			{(void)p;(void)c;}
		bool Perform(){return ConcreteProcess();}
	private:
		ProcessInfo_t& Info;
		virtual bool ConcreteProcess(){ return true;}
};

}
}
}
