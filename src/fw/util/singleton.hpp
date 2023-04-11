#pragma once

namespace rsp{
namespace rsp02{
namespace fw{
namespace util{

template< typename T>
class singleton
{
	public:
		static T* GetReference()
		{
			static T Instance = T();
			return &Instance;
		}
	protected:
		singleton(){}
	
	private:
		singleton(const singleton &) = delete;
		singleton& operator=(const singleton &) = delete;
		singleton(singleton &&) = delete;
		singleton& operator=(singleton &&) = delete;
};

}
}
}
}
