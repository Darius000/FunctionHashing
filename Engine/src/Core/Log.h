#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"

#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

#include "imgui.h"

struct  ImGuiTextBuffer;

template<typename T>
struct ImVector;

class Log
{
public:
	static void Init();

	template<typename... Args>
	static void AddLog(fmt::format_string<Args...> fmt, Args &&... args);

	static void Clear();

	static struct ImGuiTextBuffer& GetBuffer();

	static void WriteLog(const char* buffer);

	static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }

private:

	static struct ImGuiTextBuffer Buf;

	static std::shared_ptr<spdlog::logger> s_CoreLogger;

public:
	static bool ScrollToBottom;

};

template<typename... Args>
inline void Log::AddLog(fmt::format_string<Args...> fmt, Args &&... args)
{
	time_t rawtime;
	struct tm* timeinfo;
	char datebuffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(datebuffer, sizeof(datebuffer), "%d-%m-%Y %H:%M:%S ", timeinfo);

	auto old_size = Buf.size();

	std::string s = fmt::format(fmt, std::forward<Args>(args)...);

	Buf.append(datebuffer);
	Buf.append(s.c_str());
	Buf.append("\n");


	ScrollToBottom = true;

	auto new_size = Buf.size();

	if (Buf.size() > 0)
	{
		std::string buf(Buf.c_str());
		WriteLog(buf.substr(old_size, new_size).c_str());
	}

}

template<typename OStream, glm::length_t L, typename T, glm::qualifier Q>
inline OStream operator<<(OStream& os, const glm::vec<L, T, Q>& vector)
{
	return os << glm::to_string(vector);
}

template<typename OStream, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
inline OStream operator<<(OStream& os, const glm::mat<C, R, T, Q>& matrix)
{
	return os << glm::to_string(matrix);
}

template<typename OStream, typename T, glm::qualifier Q>
inline OStream operator<<(OStream& os, glm::qua<T, Q> quaternion)
{
	return os << glm::to_string(quaternion);
}

#define LOG_TRACE(...) Log::AddLog(__VA_ARGS__); Log::GetCoreLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...) Log::AddLog(__VA_ARGS__); Log::GetCoreLogger()->info(__VA_ARGS__)
#define LOG_WARN(...) Log::AddLog(__VA_ARGS__); Log::GetCoreLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...) Log::AddLog(__VA_ARGS__); Log::GetCoreLogger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...) Log::AddLog(__VA_ARGS__); Log::GetCoreLogger()->critical(__VA_ARGS__)