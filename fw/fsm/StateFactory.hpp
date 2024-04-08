#pragma once
#include <vector>
#include <algorithm>
#include "StateBase.hpp"

namespace rsp{
namespace rsp02{
namespace fw{
namespace fsm{

template<typename T>
class StateFactory
{
private:
	std::vector<IState<T>*> StateList;

public:
	StateFactory():StateList(){}

	StateFactory( std::vector<IState<T>*> &st):StateList(std::move(st)){}

	virtual bool RegisterState( IState<T>* st)
	{
		StateList.push_back( st);
		return true;
	}
	virtual ~StateFactory(){}

	virtual IState<T>* GetState( T id) const
	{
		auto it = std::find_if( std::cbegin(StateList), std::cend(StateList), [id](IState<T>* e){ return e->GetStateInfo().ID == id;});
		if( it == std::cend(StateList)) return nullptr;
		else return *it;
	}
};

}
}
}
}
