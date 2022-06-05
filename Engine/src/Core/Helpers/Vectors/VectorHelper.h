#pragma once


#include "PCH.h"


namespace Helpers
{
	namespace Vector
	{
		template<typename T, typename TPred = void, typename = std::enable_if<!std::is_function<TPred>::value>>
		static void Remove(std::vector<T>& in, const T& item)
		{
			auto iterator = std::find(in.begin(), in.end(), item);
			if (iterator != in.end())
			{
				in.erase(iterator);
				
			}
		}

		template<typename T, typename TPred, typename = std::enable_if<std::is_function<TPred>::value>>
		static void Remove(std::vector<T>& in, TPred pred)
		{
			auto iterator = std::find_if(in.begin(), in.end(), pred);

			if (iterator != in.end())
			{
				in.erase(iterator);
			}
		}


		template<typename T, typename Pred>
		static T FindPred(std::vector<T>& in, Pred pred)
		{
			auto iterator = std::find_if(in.begin(), in.end(), pred);
			if (iterator != in.end())
			{
				return *iterator;
			}

			return T();
		}
	}
}