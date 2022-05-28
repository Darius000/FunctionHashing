#pragma once


#include "PCH.h"


namespace Helpers
{
	namespace Vector
	{
		template<typename T>
		static void Remove(std::vector<T>& in, T& item)
		{
			auto iterator = std::find(in.begin(), in.end(), item);
			if (iterator != in.end())
			{
				in.erase(iterator);
				
			}
		}

		template<typename T, typename Pred>
		static void Remove(std::vector<T>& in, T& item, Pred pred)
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