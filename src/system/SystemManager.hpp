#pragma once
#include <vector>
#include "system/IProcess.hpp"

namespace rsp{
namespace rsp02{
namespace system{

enum class SystemStatus : int
{
	Normal,
};

template<typename T>
class SystemManager
{
	public:
		SystemManager(){}

		SystemStatus Process()
		{
			for( auto it=process.begin(); it!=process.end(); ++it)
			{
				(*it)->Process();
				(*it)->GetInfo();
			}
			return SystemStatus::Normal;
		}

		void RegisterProcess( IProcess* p)
		{
			process.push_back( p);

		}

	private:
		std::vector<IProcess*> process;
};

}
}
}
