#include <cstdio>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include "thread.hpp"
#include "ntshell/core/ntshell.h"
#include "ntshell/util/ntopt.h"
#include "DebugPort.hpp"
#include "Shell.hpp"

namespace rsp::rsp02::system
{

namespace
{
static int tr_read( char* buf, int cnt, void* extobj);
static int tr_write( const char* buf, int cnt, void* extobj);
static int tr_cb( const char* text, void* extobj);
static int tr_parse( int argc, char** argv, void* extobj);
}

namespace detail
{

class DebugPortImpl
{
	using Thread = fw::util::Thread;
	public:
		DebugPortImpl( IShell* sh)
		{
			shell = sh;
			th.start( fw::util::callback( this, &DebugPortImpl::func));
		}
	private:
		bool isCanceled;
		Thread th;
		IShell* shell;

		void SetupConsole()
		{
			termios iterm, iterm_org, oterm, oterm_org;
			tcgetattr( STDIN_FILENO, &iterm);
			tcgetattr( STDOUT_FILENO, &oterm);
			iterm_org = iterm;
			oterm_org = oterm;
			iterm.c_lflag &= ~(ECHO|ICANON);
			oterm.c_lflag &= ~(ECHO|ICANON);
			tcsetattr( STDIN_FILENO, TCSANOW, &iterm);
			tcsetattr( STDOUT_FILENO, TCSANOW, &oterm);
		}

		void func()
		{
			isCanceled = false;
			ntshell_t ntshell;
			ntshell_init(
				&ntshell,
				tr_read,
				tr_write,
				tr_cb,
				(void*)this
			);
			ntshell_set_prompt( &ntshell, "rsp02>");
			printf("\n\n");
			printf("\e[34m");
			printf("====================================\n");
			printf("  Welcome to RSP-02 DEBUG SHELL.\n");
			printf("====================================\n");
			printf("\e[37m");
			printf("Type 'help' for a list of commands.\n");
			while( !isCanceled)
			{
				ntshell_execute( &ntshell);
			}
		}

	// 以下のメソッドはトランポリンから呼ばれるから、publicにしてしまう
	// 閉じた名前空間にあるprivateなクラスだからいいよね・・・
	public:
		int func_read( char* buf, int cnt, void* extobj)
		{
			(void)extobj;
			int len = 0;
			while( len<cnt)
			{
				std::size_t l;
				l = read( STDIN_FILENO, &buf[len], cnt);
				if( l<1) break;
				len+=l;
			}
			return len;
		}

		int func_write( const char* buf, int cnt, void* extobj)
		{
			(void)extobj;
			int len = 0;
			while( len<cnt)
			{
				std::size_t l;
				l = write( STDOUT_FILENO, &buf[len], cnt);
				if( l<1) break;
				len+= l;
			}
			return len;
		}
		int func_cb( const char* text, void* extobj)
		{
			return ntopt_parse( text, tr_parse, extobj);
		}
		int func_parse( int argc, char** argv, void* extobj)
		{
			return shell->Invoke( argc, argv, extobj);
		}
		int prints( const char* text, void* extobj)
		{
			return func_write(text, std::strlen(text), extobj);
		}
	};
}

// Cスタイルコールバックのトランポリン
namespace
{
static int tr_read( char* buf, int cnt, void* extobj)
{
	return static_cast<detail::DebugPortImpl*>(extobj)->func_read(buf,cnt,extobj);
}

static int tr_write( const char* buf, int cnt, void* extobj)
{
	return static_cast<detail::DebugPortImpl*>(extobj)->func_write(buf,cnt,extobj);
}
static int tr_cb( const char* text, void* extobj)
{
	return static_cast<detail::DebugPortImpl*>(extobj)->func_cb(text,extobj);
}

static int tr_parse( int argc, char** argv, void* extobj)
{
	return static_cast<detail::DebugPortImpl*>(extobj)->func_parse( argc, argv, extobj);
}
}

DebugPort::DebugPort( IShell* sh)
{
	impl = new detail::DebugPortImpl( sh);
}

}

