#pragma once
#ifndef OFFLINE
#else
#include <thread>
#include "callback.hpp"
#include <cstdint>
#endif

namespace rsp{
namespace rsp02{
namespace fw{
namespace util{

#ifndef OFFLINE

#include "thread.h"
using Thread = mbed::Thread;

#else

typedef int32_t                  osStatus;
#define osOK					(0x00)
#define osEventSignal           (0x08)
#define osEventMessage          (0x10)
#define osEventMail             (0x20)
#define osEventTimeout          (0x40)
#define osErrorOS               (-1)
#define osErrorTimeoutResource  (-2)
#define osErrorISRRecursive     (-126)
#define osErrorValue            (-127)
#define osErrorPriority         (-128)

class Thread
{
	public:
		Thread(){}
		osStatus start( const Callback<void()> &f)
		{
			func = f;
			th = std::thread( &Thread::trampoline, this);
			return osOK;
		}

		osStatus join()
		{
			if( !th.joinable()) return osErrorOS;
			th.join();
			return osOK;
		}

	private:
		std::thread th;
		Callback<void()> func;
		void trampoline()
		{
			func();
		}
};
#endif

}
}
}
}
