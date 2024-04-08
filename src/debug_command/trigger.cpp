#include <cstring>
#include <cstdlib>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <memory>
#include "IProcess.hpp"
#include "fw/fsm/StateBase.hpp"
#include "fw/fsm/StateFactory.hpp"
#include "fw/logger/Logger.hpp"
#include "trigger.hpp"
#include "ntshell/core/ntlibc.h"
#include "GlobalDefine.hpp"
using Logger = rsp::rsp02::fw::logger::Logger;
using ILogger = rsp::rsp02::fw::logger::ILogger;

trigger::trigger(){}

void trigger::RegisterState( rsp::rsp02::fw::fsm::IState<StateID>* st)
{
	StateList.push_back( st);
}

int trigger::operator()( int argc, const char** argv, void* extobj)
{
	(void)extobj;
	if( argc < 2)
	{
		printf( "Less arguments.\n");
		return -1;
	}
	char* e = nullptr;
	uint8_t dst = strtol( argv[1], &e, 10);
	if( *e!='\0')
	{
		printf( "StateID is invalid.\n");
		return -1;
	}
	if( dst >= StateList.size())
	{
		printf( "Destination State is not Registered.\n");
		return -2;
	}
	uint8_t n = strtol( argv[2], &e, 10);
	if( *e!='\0')
	{
		printf( "Flag is invalid.\n");
		return -1;
	}
	auto state = StateList[dst];
	printf( "Trigger State %s as Flag %d\n", state->GetStateInfo().Name, n);
	state->Trigger( n);
	return 0;
}
