#pragma once
#include "MainState/MainFSM.hpp"
#include "InitialState/InitialFSM.hpp"

class TStateRoot
{
	public:
		TMainFSM MainFSM;
		TInitialFSM InitialFSM;

		TStateRoot();
		void Initialize();
};

extern TStateRoot StateRoot;
