#pragma once

#include "IShellCommand.hpp"
#include "rsp02.hpp"
#include "MissionDefine.hpp"

namespace detail{
class loglevel_impl;
}

class loglevel : public rsp::rsp02::system::IShellCommand
{
	public:
		loglevel();
		int operator()( int argc, const char** argv, void* extobj);
	private:
		detail::loglevel_impl* impl;
};
