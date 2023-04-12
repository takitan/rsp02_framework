#pragma once
#include <limits.h>
#include "fw/time/TimeProvider.hpp"

namespace rsp{
namespace rsp02{
namespace fw{
namespace fsm{

template<typename T>
class StateFactory;

enum class EInnerState{Entry,Execute,Exit};

template<typename T>
class StateInfo_t
{
	using TimeKeeper = rsp::rsp02::fw::time::TimeKeeper;
	public:
		const char* Name;
		const T ID;
		TimeKeeper time;
		long EnteringCount;
		long ExitingCount;
		EInnerState InnerState;
		long ExecutingCount;
		void* Optional;
		void Enter(){ EnteringCount++;time.Enter();}
		void Execute(){ ExecutingCount++;}
		void Exit(){ ExitingCount++;time.Enter();}
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
		void mOnEntry( void)
		{
			StateInfo.Enter();
			if( OnEntry) OnEntry( this);
		}
		void mOnExecute( void)
		{
			StateInfo.Execute();
			if( OnExecute) OnExecute( this);
		}
		void mOnExit( void)
		{
			StateInfo.Exit();
			if( OnExit) OnExit( this);
		}

	protected:
		StateInfo_t<T> StateInfo;
		virtual void Entry( void){}
		virtual IState<T>* Execute( void){ return nullptr;}
		virtual void Exit( void){}

	public:
		typedef void (*CallBack_t)( IState<T>*);

		static StateFactory<T>* Factory;
		static CallBack_t OnEntry;
		static CallBack_t OnExecute;
		static CallBack_t OnExit;

		StateBase( T id, char const* const nam) : StateInfo( id, nam){}
		
		virtual ~StateBase(){}

		IState<T>* Process( void)
		{
			next = this;
			switch( StateInfo.InnerState)
			{
				case EInnerState::Entry:
					mOnEntry();
					Entry();
					StateInfo.InnerState = EInnerState::Execute;
					__attribute__((fallthrough));
				case EInnerState::Execute:
					mOnExecute();
					next = Execute();
					if( next == this) break;
					StateInfo.InnerState = EInnerState::Exit;
					__attribute__((fallthrough));
				case EInnerState::Exit:
					mOnExit();
					Exit();
					StateInfo.InnerState = EInnerState::Entry;
			}
			return next;
		}

		const StateInfo_t<T>& GetStateInfo( void) const{ return StateInfo;}
};

}
}
}
}
