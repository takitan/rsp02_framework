#pragma once
#include <cstddef>
#include "fw/time/StopWatch.hpp"

namespace rsp{
namespace rsp02{
namespace system{

struct ProcessInfo_t
{
	using time_t = rsp::rsp02::time_t;
	/** プロセス名*/
	const char* Name;
	/** @brief 処理開始時刻 */
	time_t StartTime;
	/** @brief 処理完了時刻 */
	time_t CompletionTime;
	/** @brief 経過時刻*/
	time_t ElapsedTime;
	/** @brief メッセージキューサイズ*/
	std::size_t QueueSize;
	/** @brief 総受付メッセージ数*/
	std::size_t TotalPacket;
	/** @brief 処理成功メッセージ数*/
	std::size_t PassedPacket;
	/** @brief 処理失敗メッセージ数*/
	std::size_t FailedPacket;
	/** @brief キューオーバーフロー回数*/
	int QueueOverflow;
	/** @brief オプション*/
	void* Option;
	ProcessInfo_t() = default;
	inline ProcessInfo_t(const ProcessInfo_t &) = default;
	ProcessInfo_t( ProcessInfo_t &&) = default;
	ProcessInfo_t( const char* name):Name(name){}
};

class IProcess
{
	public:
		int ProcessID;
		virtual bool Perform() = 0;
		virtual const ProcessInfo_t GetInfo() const = 0;
};

template<typename CNS_T,typename PRD_T>
class IExecuter
{
	public:
		virtual bool Perform() = 0;
};

template<typename CNS_T>
class IConsumer
{
	public:
		virtual bool Accept( CNS_T &) = 0;
};

template<typename PRD_T>
class IProducer
{
	public:
		virtual void SetConsumer( IConsumer<PRD_T>*) = 0;
};

struct NONE_T
{
	constexpr static const char*a_mesage="None of Product.";
	constexpr static const char*b_message1="If this struct is specified to template parameter of PRD_T, Producer role is disabled.";
	constexpr static const char*b_message2="If this struct is specified to template parameter of CNS_T, Consumer role is disabled.";
	constexpr static const char*b_message3="If this struct is specified to template parameter of PRD_T and CNS_T, That is meaningless .";
};

}
}
}
