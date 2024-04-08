#pragma once

#include "debug/IShellCommand.hpp"
#include "rsp02.hpp"
#include "GlobalDefine.hpp"

class chloglv : public rsp::rsp02::system::IShellCommand
{
	public:
		chloglv();
		int operator()( int argc, const char** argv, void* extobj);
};
