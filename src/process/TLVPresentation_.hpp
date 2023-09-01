#pragma once
#include "system/Process.hpp"
#include "system/TLVStub.hpp"

namespace rsp{
namespace rsp02{
namespace system{

template<typename T, typename U>
class TLVPresentationUp : public PipelineProcess<T,U>
{
	private:

	public:
		TLVPresentationUp(){}

		bool ConcreteProcess( T &product, U &reproduct)
		{
			reproduct = U(product);
			return true;
		}
};

template<typename T, typename U>
class TLVPresentationDown : public PipelineProcess<T,U>
{
	public:
		TLVPresentationDown(){}
	protected:
		bool ConcreteProcess( T &product, U &reproduct)
		{
			reproduct = U(reproduct);
			return true;
		}
};

}
}
}
