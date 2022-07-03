#include "PCH.h"
#include "Log.h"
#include <ctime>
#include <iostream>
#include <fstream>
#include <filesystem>

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

void Log::Init()
{
	std::vector<spdlog::sink_ptr> logsinks;
	logsinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
	logsinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("Engine.log", true));

	logsinks[0]->set_pattern("%^[%T] %n: %v%$");
	logsinks[1]->set_pattern("[%T] [%l] %n: %v");

	s_CoreLogger = std::make_shared<spdlog::logger>("Engine", begin(logsinks), end(logsinks));
	spdlog::register_logger(s_CoreLogger);
	s_CoreLogger->set_level(spdlog::level::trace);
	s_CoreLogger->flush_on(spdlog::level::trace);
}



void Log::Clear()
{
	Buf.clear();
}

struct ImGuiTextBuffer& Log::GetBuffer()
{
	return Buf;
}

void Log::WriteLog(const char* buffer)
{
	std::ofstream ofs;
	ofs.open("Log.txt", std::ios::out | std::ios::app);
	ofs << buffer;
}

struct ImGuiTextBuffer Log::Buf;

bool Log::ScrollToBottom = false;

std::shared_ptr<spdlog::logger> Log::s_CoreLogger;