#pragma once
#include <limits.h>
#include "fw/time/StopWatch.hpp"
#include "fw/logger/Logger.hpp"

namespace rsp{
namespace rsp02{
namespace fw{
namespace fsm{

/**
 * Warning!
 * this class is not THREAD SAFE!
*/
class TinyOneshotEvent
{
	private:
		bool flag;
	public:
		TinyOneshotEvent(bool init):flag(init){}
		void Set(){flag=true;}
		void Reset(){flag=false;}
		bool Test()
		{
			auto buf = flag;
			flag = false;
			return buf;
		}
};

template<typename T>
class StateFactory;

enum class EInnerState{Entry,Execute,Exit};

template<typename T>
class StateInfo_t
{
	using StopWatch = rsp::rsp02::fw::time::StopWatch;
	public:
		const char* Name;
		const T ID;
		StopWatch sw;
		long EnteringCount;
		long ExitingCount;
		EInnerState InnerState;
		long ExecutingCount;
		void* Optional;
		void Enter(){ EnteringCount++;sw.Start();}
		void Execute(){ ExecutingCount++;}
		void Exit(){ ExitingCount++;sw.Lap();}
		StateInfo_t( const T id, const char* nam) : Name(nam), ID(id), InnerState(EInnerState::Entry){}
};

template<typename T>
class IState
{
	public:
		virtual IState<T>* Process( void) = 0;
		virtual const StateInfo_t<T>& GetStateInfo( void) const = 0;
};

template<typename T>
class StateBase : public IState<T>
{
	private:
		IState<T>* next;
		__attribute__((weak)) static inline void OnEntry( const StateInfo_t<T>& state){(void)state;}
		__attribute__((weak)) static inline void OnExecute( const StateInfo_t<T>& state){(void)state;}
		__attribute__((weak)) static inline void OnExit( const StateInfo_t<T>& state){(void)state;}

	protected:
		StateInfo_t<T> StateInfo;
		rsp::rsp02::fw::logger::ILogger* logger;

		virtual void Entry( void){}
		virtual IState<T>* Execute( void){ return nullptr;}
		virtual void Exit( void){}

	public:
		static StateFactory<T>* Factory;

		StateBase( T id, char const* const nam) :
			StateInfo( id, nam), logger(rsp::rsp02::fw::logger::Logger::GetLogger("StateBase")){}

		virtual ~StateBase(){}

		IState<T>* Process( void)
		{
			next = this;
			switch( StateInfo.InnerState)
			{
				case EInnerState::Entry:
					OnEntry( StateInfo);
					Entry();
					StateInfo.InnerState = EInnerState::Execute;
					// fallthrough
				case EInnerState::Execute:
					OnExecute( StateInfo);
					next = Execute();
					if( next == this) break;
					StateInfo.InnerState = EInnerState::Exit;
					// fallthrough
				case EInnerState::Exit:
					Exit();
					OnExit( StateInfo);
					StateInfo.InnerState = EInnerState::Entry;
			}
			return next;
		}

		const StateInfo_t<T>& GetStateInfo( void) const{ return StateInfo;}
};

template<typename T>
StateFactory<T>* StateBase<T>::Factory;

}
}
}
}
