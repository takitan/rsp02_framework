#include <cstdio>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include "thread.hpp"
#include "ntshell.h"
#include "DebugPort.hpp"

namespace rsp::rsp02::system
{

namespace detail
{

class DebugPortImpl
{
	using Thread = fw::util::Thread;
	public:
		DebugPortImpl()
		{
			th.start( fw::util::callback( this, &DebugPortImpl::func));
		}
	private:
		bool isCanceled;
		Thread th;
		void func()
		{
			isCanceled = false;
			termios iterm, iterm_org, oterm, oterm_org;
			tcgetattr( STDIN_FILENO, &iterm);
			tcgetattr( STDOUT_FILENO, &oterm);
			iterm_org = iterm;
			oterm_org = oterm;
			iterm.c_lflag &= ~(ECHO|ICANON);
			oterm.c_lflag &= ~(ECHO|ICANON);
			tcsetattr( STDIN_FILENO, TCSANOW, &iterm);
			tcsetattr( STDOUT_FILENO, TCSANOW, &oterm);

			ntshell_t ntshell;
			ntshell_init(
				&ntshell,
				&DebugPortImpl::func_read,
				&DebugPortImpl::func_write,
				&DebugPortImpl::func_cb,
				(void*)&ntshell
			);
			ntshell_set_prompt( &ntshell, "rsp02>");
			while( !isCanceled)
			{
				ntshell_execute( &ntshell);
			}
		}
		static int func_read( char* buf, int cnt, void* extobj)
		{
			std::size_t len = 0;
			while( len<cnt)
			{
				std::size_t l;
				l = read( STDIN_FILENO, &buf[len], cnt);
				if( l<1) break;
				len+=l;
			}
			return len;
		}

		static int func_write( const char* buf, int cnt, void* extobj)
		{
			std::size_t len = 0;
			while( len<cnt)
			{
				std::size_t l;
				l = write( STDOUT_FILENO, &buf[len], cnt);
				if( l<1) break;
				len+= l;
			}
			return len;
		}
		static int func_cb( const char* text, void* extobj)
		{
			char buf[32];
			sprintf( buf, "%s uhyo\n\r", text);
			prints( buf, extobj);
			return 0;
		}
		static int prints( const char* text, void* extobj)
		{
			func_write(text, std::strlen(text), extobj);
		}
	};
}

DebugPort::DebugPort()
{
	impl = new detail::DebugPortImpl();
}

bool DebugPort::ConcreteProcess( MissionTLV reproduct)
{
	(void)reproduct;
	return false;
}

}

