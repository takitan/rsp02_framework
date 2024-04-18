/**
 * @file raii.hpp
 * @author Nobuyuki Takita (takitan1972@gmail.com)
 * @brief RAII(Resource Acquisition Is Initialization)のための枠組み
 * @version 0.1
 * @date 2024-04-18
 * 
 * class raiiが破棄されるタイミングで、final_funcを自動的に呼び出すことで、
 * 確実にリソースを破棄する。
 * 
 * それ以外にも、スコープを抜けるタイミングで何かをしたいという良くある？要望に応えることができる。
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once
#include <functional>

namespace rsp{
namespace rsp02{
namespace fw{
namespace util{

class raii
{
	public:
		using function_t = std::function<void(void)>;
		/**
		 * @brief Construct a new raii object
		 * 
		 * @param ff デストラクト時に呼ぶ処理
		 */
		raii( function_t ff) : final_func(ff){}
		~raii()
		{
			final_func();
		}
	private:
		function_t final_func;
};

}
}
}
}
