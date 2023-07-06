#pragma once

#include "IShellCommand.hpp"
#include "rsp02.hpp"
#include "MissionDefine.hpp"

namespace detail{
class chloglv_impl;
}

class chloglv : public rsp::rsp02::system::IShellCommand
{
	public:
		chloglv();
		int operator()( int argc, const char** argv, void* extobj);
	private:
		detail::chloglv_impl* impl;
};
