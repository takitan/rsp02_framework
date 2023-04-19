#pragma once
#include <cstddef>
#include <queue>
#include "fw/time/StopWatch.hpp"

namespace rsp{
namespace rsp02{
namespace system{

struct ProcessInfo_t
{
	using time_t = rsp::rsp02::time_t;
	/** @brief 処理開始時刻 */
	time_t StartTime;
	/** @brief 処理完了時刻 */
	time_t CompletionTime;
	/** @brief 経過時刻*/
	time_t ElapsedTime;
	/** @brief メッセージキューサイズ*/
	std::size_t QueueSize;
	/** @brief 処理メッセージ数*/
	std::size_t TotalPacket;
	/** @brief キューオーバーフロー回数*/
	int QueueOverflow;
	/** @brief オプション*/
	void* Option;
	ProcessInfo_t() : TotalPacket(0), QueueOverflow(0), Option(nullptr){}
};

template<typename T, typename U>
class TTimeKeeper
{
	using TStopWatch = rsp::rsp02::fw::time::TStopWatch;
	public:
		TTimeKeeper( T &inf, U &q) : info(inf), queue(q){ info.StartTime = sw.Start();}
		~TTimeKeeper()
		{
			info.CompletionTime = sw.Lap();
			info.ElapsedTime = sw.GetElapsed();
			info.QueueSize = queue.size();
		}
	private:
		TStopWatch sw;
		T &info;
		U &queue;
};

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

template<typename T, std::size_t N = 1>
class ProcessBase : public IProcess, public IPacket<T>
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
		ProcessBase(){}

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

}
}
}
