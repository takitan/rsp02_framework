#include "align.hpp"
#include <cstdint>

namespace rsp{
namespace rsp02{
namespace fw{
namespace util{

// template<int N>
// typename byte_type<N>::type align::safe_read( uint8_t* byte)
// {
// 	alignas(32) uint8_t dat[N];
// 	for( int i=0;i<N;i++) dat[i] = byte[i];
// 	return *(typename byte_type<N>::type*)dat;
// }

// template<int N>
// typename byte_type<N>::type align::safe_read( const uint8_t* byte)
// {
// 	safe_read<N>( const_cast<uint8_t*>(byte));
// }

}
}
}
}
