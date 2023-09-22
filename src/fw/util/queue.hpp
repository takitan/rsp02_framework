#pragma once

#include <cstdlib>
#include <cstdint>

#ifdef OFFLINE
#include <mutex>
#include <deque>
#include <condition_variable>
#include <chrono>

#else
//#include "mbed.h"
#endif

namespace rsp{
namespace rsp02{
namespace fw{
namespace util{

/**
 * @brief Queueのラッパ
 * 
 * @tparam T キューイングするデータの型
 * @tparam N キューの深さ
 * 
 * OFFLINEが定義されていたら、C++のdequeとmutexでスレッドセーフなキューで内部実装する
 * OFFLINEが定義されていなかったら、mbedのQueueをラップする
 */
template< typename T, size_t N>
class queue
{
	private:
#ifdef OFFLINE
		mutable std::deque<T> mqueue;
		mutable std::mutex mtx;
		mutable std::condition_variable can_put;
		mutable std::condition_variable can_get;
#else
		Queue<T,N> mqueue;
		MemoryPool<T,N> mpool;
#endif
	public:
		queue(){}

		/**
		 * @brief Queueが空かどうかを返す
		 * 
		 * @return true Queueは空
		 * @return false Queueは空でない
		 */
		bool empty() const
		{
#ifdef OFFLINE
			std::lock_guard<std::mutex> lg(mtx);
#endif
			return mqueue.empty();
		}

		/**
		 * @brief Queueが満杯かどうかを返す
		 * 
		 * @return true Queueは満杯
		 * @return false Queueは満杯でない
		 */
		bool full() const
		{
#ifdef OFFLINE
			std::lock_guard<std::mutex> lg(mtx);
			return mqueue.size()==N;
#else
			return mqueue.full();
#endif
		}

		/**
		 * @brief Queueにあるデータの個数を返す
		 * 
		 * @return uint32_t Queueにあるデータの個数
		 */
		uint32_t size() const
		{
#ifdef OFFLINE
			std::lock_guard<std::mutex> lg(mtx);
			return mqueue.size();
#else
			return mqueue.count();
#endif
		}

		/**
		 * @brief Queueの最大データ数(template parameter N)を返す
		 * 
		 * @return size_t 最大データ数
		 */
		size_t max_size() const
		{
#ifdef OFFLINE
			return N;
#else
			return mqueue.max_size();
#endif
		}

		/**
		 * @brief Queueにデータを格納する
		 * template parameter Nで指定される最大データ数まで格納できる
		 * 最大データ数を超えて格納しようとしたときと、メモリを確保できなかったとき(mbed環境)に失敗する
		 * @param data 格納するデータ
		 * @return true 成功
		 * @return false 失敗
		 */
		bool try_put_for(const T& data, uint32_t milliseconds = 0)
		{
#ifdef OFFLINE
			std::unique_lock<std::mutex> ul(mtx);
			auto rel_time = std::chrono::milliseconds(milliseconds);
			can_put.wait_for(ul, rel_time, [this]{ return mqueue.size()<N;});
			mqueue.push_back( std::move(data));
			can_put.notify_all();
#else
			T* p = mpool.try_alloc(rel_time);
			if( p==nullptr) return false;

			*p = data;
			auto st = mqueue.try_put_for( p, rel_time);
			return st == osOK ? true : false;
#endif
		}

		/**
		 * @brief Queueからデータを取り出す
		 * Queueにデータが格納されていないときに失敗する
		 * 
		 * @param data 取り出したデータの格納先
		 * @return true 成功
		 * @return false 失敗
		 */
		bool get(T& data)
		{
#ifdef OFFLINE
			std::lock_guard<std::mutex> lg{mtx};
			if( mqueue.empty()) return false;
			data = mqueue.front();
			mqueue.pop_front();
			return true;
#else
			osEvent ev = queue.try_get();
			if( ev.status != osOK) return false;
			data = *static_cast<T*>(ev.value.p);
			mpool.free( ev.value.p);
			return true;
#endif
		}
};

}
}
}
}