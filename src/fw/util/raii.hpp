#pragma once
#include <functional>

namespace rsp{
namespace rsp02{
namespace fw{
namespace util{

class raii
{
	public:
		using function_t = std::function<void(void)>;
		raii( function_t ff) : final_func(ff){}
		~raii()
		{
			final_func();
		}
	private:
		function_t final_func;
};

}
}
}
}
