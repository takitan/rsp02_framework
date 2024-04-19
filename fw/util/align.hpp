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
 *
 * N=16 : ワードアクセス
 *  uint16_t safe_read<16>(uint16_t* src);
 *
 * N=32 : ダブルワードアクセス
 *  uint32_t safe_read<32>(uint32_t* src);
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

/** @brief 8bit幅の定義 */
template<>
struct byte_type<8>
{
	typedef uint8_t type;
	constexpr static std::size_t byte_size = sizeof(type)/sizeof(uint8_t);
};

/** @brief 16bit幅の定義 */
template<>
struct byte_type<16>
{
	typedef uint16_t type;
	constexpr static std::size_t byte_size = sizeof(type)/sizeof(uint8_t);
};

/** @brief 32bit幅の定義 */
template<>
struct byte_type<32>
{
	typedef uint32_t type;
	constexpr static std::size_t byte_size = sizeof(type)/sizeof(uint8_t);
};

namespace {
/** @brief バイトアクセスとまとめてアクセスのための共用体 */
template<typename T>
union aligned
{
	uint8_t src[sizeof(T)];
	T word;
};
}

struct align
{
	/**
	 * @brief バイトアライメントを気にせずにリードする
	 * @tparam T アクセスする時の型
	 * @param src リード先
	 * @return T リードした値
	 */
	template<typename T>
	static T safe_read( void* src)
	{
		constexpr static std::size_t byte_size = sizeof(T);
		alignas(32) aligned<T> dst;
		::memcpy( dst.src, src, byte_size);
		return dst.word;
	}

	/**
	 * @brief バイトアライメントを気にせずにリードする(constバージョン)
	 * @tparam T アクセスする時の型
	 * @param src リード先
	 * @return T リードした値
	 */
	template<typename T>
	static T safe_read( const void* src)
	{
		return safe_read<T>( const_cast<void*>(src));
	}

	/**
	 * @brief バイトアライメントを気にせずにライトする
	 * @tparam T アクセスする時の型
	 * @param dst ライト先
	 * @param src ライトする値
	 */
	template<typename T>
	static void safe_write( void* dst, const T src)
	{
		constexpr static std::size_t byte_size = sizeof(T);
		::memcpy( dst, &src, byte_size);
	}

	/**
	 * @brief バイトアライメントを気にせずにライトする(constバージョン)
	 * @note 悪いことしてる自覚はある・・・・
	 * @tparam T アクセスする時の型
	 * @param dst ライト先
	 * @param src ライトする値
	 */
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

/** @brief バイトアライメントを気にせずにbyteで値を設定する便利関数 */
#define SAFE_INIT(x,y) x( align::safe_read<uint8_t>(&y))

/** @brief バイトアライメントを気にせずにbyteで値を設定する便利関数 */
#define SAFE_INIT8(x,y) x( align::safe_read<uint8_t>(&y))

/** @brief バイトアライメントを気にせずにwordで値を設定する便利関数 */
#define SAFE_INIT16(x,y) x( align::safe_read<uint16_t>(&y))

/** @brief バイトアライメントを気にせずにdwordで値を設定する便利関数 */
#define SAFE_INIT32(x,y) x( align::safe_read<uint32_t>(&y))