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
template<typename T>
union aligned
{
	uint8_t src[sizeof(T)];
	T word;
};
}

struct align
{
	template<typename T>
	static T safe_read( void* src)
	{
		constexpr static std::size_t byte_size = sizeof(T);
		alignas(32) aligned<T> dst;
		::memcpy( dst.src, src, byte_size);
		return dst.word;
	}

	template<typename T>
	static T safe_read( const void* src)
	{
		return safe_read<T>( const_cast<void*>(src));
	}

	template<typename T>
	static void safe_write( void* dst, const T src)
	{
		constexpr static std::size_t byte_size = sizeof(T);
		::memcpy( dst, &src, byte_size);
	}

	template<typename T>
	static void safe_write( const void* dst, T src)
	{
		safe_write<T>( const_cast<void*>(dst), src);
	}
};

}
}
}
}

#define SAFE_INIT(x,y) x( align::safe_read<uint8_t>(&y))