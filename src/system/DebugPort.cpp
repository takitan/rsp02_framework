#include <cstdio>
#include <unistd.h>
#include <thread>
#include "DebugPort.hpp"

namespace rsp::rsp02::system
{
namespace
{

class DebugPortImpl
{
	public:
		DebugPortImpl(){}
	private:
		std::thread th;
}
}

DebugPort::DebugPort()
{

}

bool DebugPort::ConcreteProcess( MissionTLV reproduct)
{


}

}