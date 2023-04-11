#pragma once
#include "StateBase.hpp"

namespace rsp{
namespace rsp02{
namespace fw{
namespace fsm{

template<typename T>
class StateFactory
{
private:
	const IState<T>** state;
	int StateCount = 0;

public:
	template<int N>
	StateFactory(const IState<T>*(&st)[N]):state(st)
	{
		StateCount = N;
	}
	virtual ~StateFactory(){}

	virtual IState<T>* GetState( T id) const
	{
		for(int i=0; i<StateCount; i++)
		{
			if( state[i]->GetStateInfo().ID==id) return const_cast<IState<T>*>( state[i]);
		}
		return nullptr;
	}
};

};
};
};
};
