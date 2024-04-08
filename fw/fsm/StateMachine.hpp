#pragma once
#include "StateBase.hpp"
#include "StateFactory.hpp"

namespace rsp{
namespace rsp02{
namespace fw{
namespace fsm{

template<typename T>
class StateMachine
{
	private:
		IState<T>* PreState;
		IState<T>* CurrentState;
		IState<T>* NextState;
		StateFactory<T>* Factory;

		__attribute__((weak)) static inline void OnTransfer(){}

	public:
		typedef void (*Callback_t)(IState<T>*,IState<T>*);

		StateMachine( StateFactory<T>* sf)
		{
			Factory = sf;
		}

		bool ForceTrans( T id)
		{
			auto st = Factory->GetState( id);
			if( st==nullptr) return false;

			CurrentState = st;
			return true;
		}

		bool Process( void)
		{
			NextState = CurrentState->Process();
			if( NextState != CurrentState) OnTransfer();
			PreState = CurrentState;
			CurrentState = NextState;
			return true;
		}
};

}
}
}
}
