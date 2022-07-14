#pragma once

#include<string>
#include <vector>

namespace StringUtilites
{
	static inline std::string RemoveChars(std::string& s, std::vector<char> charstoremove)
	{
		auto result = s;
		
		for (auto character : charstoremove)
		{
			result.erase(std::remove(result.begin(), result.end(), character), result.end());
		}
	}

	static inline void RemoveWhiteSpace(std::string& str)
	{
		str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
	}

	static inline void Trim(std::string& str)
	{
		size_t first = str.find_first_not_of(' ');
		if (first == std::string::npos)
		{
			return;
		}

		size_t last = str.find_last_not_of(' ');
		str = str.substr(first, (last - first + 1));
	}

	static inline void SplitString(const std::string& str, const std::string& delimiter, std::vector<std::string>& out)
	{
		size_t pos = 0;
		size_t start;
		std::string token;

		while ((start = str.find_first_not_of(delimiter, pos)) != std::string::npos)
		{
			pos = str.find(delimiter, start);

			//add 1 to offset space character
			token = str.substr(start, pos - start);

			//RemoveWhiteSpace(token);
			Trim(token);

			out.push_back(token);
		}
	}

}