#include <ctime>
#include "TimeProvider.hpp"

namespace rsp{
namespace rsp02{
namespace fw{
namespace time{

namespace{
long DefaultTimeProviderMilliSeconds( void)
{
	auto hoge = clock();
	return (long)( (double)hoge*1000 / (double)CLOCKS_PER_SEC);
}
}

TimeProvider_t TimeProvider_a = rsp::rsp02::fw::time::DefaultTimeProviderMilliSeconds;

}
}
}
}
