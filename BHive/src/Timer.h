#pragma once

#include <iostream>
#include <string>
#include <chrono>

namespace BHive
{
	class Timer
	{
	public:
		Timer()
		{
			Reset();
		}

		void Reset()
		{
			m_Start = std::chrono::high_resolution_clock::now();
		}

		float GetElapsedTime()
		{
			return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - m_Start).count() * .001f * .001f * .001f;
		}

		float GetElapsedTimeMillis()
		{
			return GetElapsedTime() * 1000.0f;
		}

	private:

		std::chrono::time_point<std::chrono::high_resolution_clock> m_Start;
	};
}