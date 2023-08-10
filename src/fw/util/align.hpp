/**
 * @file align.hpp
 * @author Nobuyuki Takita (takitan1972@gmail.com)
 * @brief バイトアライメントをなるべく気にせずにアクセスする手段たち
 * @version 0.1
 * @date 2023-04-18
 * @copyright Copyright (c) 2023
 *
 * usage:
 * 要は、テンプレート引数にビットサイズを渡すと適切にアクセスしてくれる
 *
 * N=8 : バイトアクセス(実際には普通に読めば良い)
 *  uint8_t safe_read<8>(uint8_t* src);
 */
#pragma once
#include <cstdint>
#include <cstring>

namespace rsp{
namespace rsp02{
namespace fw{
namespace util{

template<int N>
struct byte_type{};

template<>
struct byte_type<8>
{
	typedef uint8_t type;
	constexpr static std::size_t byte_size = sizeof(type)/sizeof(uint8_t);
};

template<>
struct byte_type<16>
{
	typedef uint16_t type;
	constexpr static std::size_t byte_size = sizeof(type)/sizeof(uint8_t);
};

template<>
struct byte_type<32>
{
	typedef uint32_t type;
	constexpr static std::size_t byte_size = sizeof(type)/sizeof(uint8_t);
};

namespace {
template<int N>
union aligned
{
	uint8_t src[byte_type<N>::byte_size];
	typename byte_type<N>::type word;
};
}

struct align
{
	template<int N>
	static typename byte_type<N>::type safe_read( uint8_t* src)
	{
		alignas(32) aligned<N> dst;
		::memcpy( dst.src, src, byte_type<N>::byte_size);
		return dst.word;
	}

	template<int N>
	static typename byte_type<N>::type safe_read( const uint8_t* src)
	{
		return safe_read<N>( const_cast<uint8_t*>(src));
	}

	template<int N>
	static void safe_write( uint8_t* dst, typename byte_type<N>::type src)
	{
		::memcpy( dst, &src, N);
	}

	template<int N>
	static void safe_write( const uint8_t* dst, typename byte_type<N>::type src)
	{
		safe_write( const_cast<uint8_t*>(dst), src);
	}
};

}
}
}
}

#define SAFE_INIT(x,y) x( align::safe_read<sizeof(x)*8>(&y))