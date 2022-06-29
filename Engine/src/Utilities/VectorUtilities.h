#pragma once


#include <vector>
#include <stdint.h>

namespace VectorUtilities
{
	template<typename T>
	static bool RemoveAt(std::vector<T>& in, uint64_t index)
	{
		//assert(index < 0 || index >= in.size());

		if (index < 0 || index >= in.size()) return false;

		in.erase(in.begin() + index);

		return true;
	}

	template<typename T, typename TPred = void, typename = std::enable_if<!std::is_function<TPred>::value>>
	static bool Remove(std::vector<T>& in, const T& item)
	{
		auto iterator = std::find(in.begin(), in.end(), item);
		if (iterator != in.end())
		{
			in.erase(iterator);
				
			return true;
		}

		return false;
	}

		

	template<typename T, typename TPred, typename = std::enable_if<std::is_function<TPred>::value>>
	static bool Remove(std::vector<T>& in, TPred pred)
	{
		auto iterator = std::find_if(in.begin(), in.end(), pred);

		if (iterator != in.end())
		{
			in.erase(iterator);

			return true;
		}

		return false;
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

	template<typename T, typename TPred>
	static uint64_t FindIndex(std::vector<T>& in, TPred pred)
	{
		auto index = std::distance(in.begin(), std::find_if(in.begin(), in.end(), pred));

		return index;
	}
}